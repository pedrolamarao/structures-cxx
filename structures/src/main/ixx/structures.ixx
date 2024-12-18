module;

#include <concepts>
#include <cstdint>

export module br.dev.pedrolamarao.structures;

using namespace std;

namespace br::dev::pedrolamarao::structures
{
    /// Memory segment.
    template <typename T>
    struct segment
    {
        T*     base   {};
        size_t length {};
    };

    // Definition below.
    export
    template <typename T>
    class segment_list;

    /// Position on segment lists.
    export
    template <typename T>
    class segment_list_position
    {
        template <typename>
        friend class segment_list;

        T * current;

        explicit segment_list_position (T * c) :
            current{c}
        { }

    public:

        // requires: ?
        auto next ()
        {
            return segment_list_position(current+1);
        }
    };

    /// List on a segment.
    // Exported above.
    template <typename T>
    class segment_list
    {
        segment<T> root_;
        size_t     count_;

        explicit segment_list (segment<T> r, size_t c) noexcept :
            root_{r},count_{c}
        { }

    public:

        // type

        segment_list () noexcept :
            segment_list({},0)
        { }

        segment_list (segment_list && that) noexcept :
            root_{that.root_}, count_{that.count_}
        {
            that.root_ = {};
            that.count_ = {};
        }

        auto operator= (segment_list && that) noexcept -> segment_list&
        {
            root_ = that.root_;
            count_ = that.count_;
            that.root_ = {};
            that.count_ = {};
            return *this;
        }

        segment_list (segment_list const & that) = delete;

        auto operator= (segment_list const & that) = delete;

        ~segment_list ()
        {
            delete [] root_.base;
        }

        // factories

        /**
         * Creates a list filled with copies of a value.
         */
        template <typename TT>
        requires copyable<TT>
        static
        auto filled (TT value, size_t count)
        {
            auto memory_ = new TT[count];
            for (auto i = 0; i != count; ++i)
                memory_[i] = value;
            auto segment_ = segment<TT>(memory_,count);
            return segment_list<TT>(segment_,count);
        }

        // query

        auto first ()
        {
            return segment_list_position<T>(root_.base);
        }

        auto is_empty () const
        {
            return count_ == 0;
        }

        // requires: index <= count
        auto load (size_t index) const
        {
            return root_.base[index];
        }

        // requires: position in [first,limit)
        auto load (segment_list_position<T> position) const
        {
            return *(position.current);
        }

        auto limit ()
        {
            return segment_list_position<T>(root_.base+count_);
        }

        // update

        // requires: index <= count
        auto store (size_t index, T value)
        {
            return root_.base[index] = value;
        }

        // requires: ?
        void store (segment_list_position<T> position, T value)
        {
            *(position.current) = value;
        }
    };

    /// Memory node with one link.
    export
    template <typename T>
    struct uninode
    {
        uninode<T> * link;
        T            content;
    };

    // Definition below.
    export
    template <typename T>
    class uninode_list;

    /// Position on uni-link node lists.
    export
    template <typename T>
    class uninode_list_position
    {
        template <typename>
        friend class uninode_list;

        uninode<T> * node;

        explicit uninode_list_position (uninode<T> * p) : node{p} {}

    public:

        // requires: current != nullptr
        auto next ()
        {
            return uninode_list_position(node->link);
        }
    };

    /// List on uni-link nodes.
    // Exported above.
    template <typename T>
    class uninode_list
    {
        uninode<T> * root_;

        explicit uninode_list (uninode<T> * r) noexcept : root_{r} {}

    public:

        // type

        uninode_list () noexcept :
            uninode_list{nullptr}
        { }

        uninode_list (uninode_list && that) noexcept :
            root_{std::move(that.root_)}
        {
            that.root_ = nullptr;
        }

        auto operator= (uninode_list && that) noexcept
        {
            root_ = that.root_;
            that.root_ = nullptr;
            return *this;
        }

        uninode_list (uninode_list const & that) = delete;

        auto operator= (uninode_list const & that) = delete;

        ~uninode_list ()
        {
            while (root_ != nullptr) {
                auto next = root_->link;
                delete root_;
                root_ = next;
            }
        }

        // factories

        /**
         * Creates a list filled with copies of a value.
         */
        template <typename TT>
        requires copyable<TT>
        static
        auto filled (TT value, size_t count)
        {
            uninode<TT> * root = nullptr;
            if (count > 0) {
                root = new uninode<TT>(nullptr,value);
                --count;
            }
            uninode<TT> * current = root;
            while (count > 0) {
                auto next = new uninode<TT>(nullptr,value);
                current->link = next;
                current = next;
                --count;
            }
            return uninode_list<TT>(root);
        }

        // query

        auto first ()
        {
            return uninode_list_position<T>(root_);
        }

        auto is_empty () const
        {
            return root_ == nullptr;
        }

        // requires: index <= count
        auto load (size_t index) const
        {
            auto node = root_;
            while (index > 0) {
                node = node->link;
                --index;
            }
            return node->content;
        }

        // requires: position in [first,limit)
        auto load (uninode_list_position<T> position) const
        {
            return position.node->content;
        }

        auto limit ()
        {
            return uninode_list_position<T>(nullptr);
        }

        // update

        /// Inserts value after position.
        auto insert_after (uninode_list_position<T> position, T value) requires copyable<T>
        {
            auto previous = position.node;
            auto next = previous->link;
            auto inserted = new uninode<T>(next,value);
            previous->link = inserted;
            return uninode_list_position<T>(inserted);
        }

        /// Inserts value at first position.
        auto insert_first (T value) requires copyable<T>
        {
            auto next = root_ != nullptr ? root_ : nullptr;
            root_ = new uninode<T>(next,value);
            return uninode_list_position<T>(root_);
        }

        // requires: index <= count
        void store (size_t index, T value)
        {
            auto node = root_;
            while (index > 0) {
                node = node->link;
                --index;
            }
            node->content = value;
        }

        // requires: ?
        void store (uninode_list_position<T> position, T value)
        {
            position.node->content = value;
        }
    };

    /// Forward traversing position.
    export
    template <typename Position>
    concept forward_position = requires (Position position)
    {
        { position.next() } -> convertible_to<Position>;
    };

    /// Distance from first to limit.
    export
    template <typename Position>
    requires forward_position<Position>
    auto distance (Position first, Position limit) -> size_t
    {
        size_t count {};
        while (first != limit) {
            ++count;
            first = first.next();
        }
        return count;
    }
}