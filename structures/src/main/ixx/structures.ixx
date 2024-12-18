module;

#include <algorithm>
#include <chrono>
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

        using value_type = T;

        auto is_equal (segment_list_position that)
        {
            return current == that.current;
        }

        auto not_equal (segment_list_position that)
        {
            return current != that.current;
        }

        auto load ()
        {
            return *current;
        }

        // requires: ?
        auto next ()
        {
            return segment_list_position(current+1);
        }
    };

    export
    template <typename T>
    auto is_equal (segment_list_position<T> x, segment_list_position<T> y)
    {
        return x.is_equal(y);
    }

    export
    template <typename T>
    auto operator== (segment_list_position<T> x, segment_list_position<T> y)
    {
        return x.is_equal(y);
    }

    export
    template <typename T>
    auto not_equal (segment_list_position<T> x, segment_list_position<T> y)
    {
        return x.not_equal(y);
    }

    export
    template <typename T>
    auto operator!= (segment_list_position<T> x, segment_list_position<T> y)
    {
        return x.not_equal(y);
    }

    export
    template <typename T>
    auto load (segment_list_position<T> x)
    {
        return x.load();
    }

    export
    template <typename T>
    auto next (segment_list_position<T> x)
    {
        return x.next();
    }

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

        using value_type = T;

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

        auto insert_at (size_t index, T value) requires copyable<T>
        {
            auto new_count = std::max(count_,index) + 1;
            expand(new_count);
            shift(index);
            root_.base[index] = value;
            count_ = new_count;
            return segment_list_position<T>(root_.base+index);
        }

        auto insert_first (T value)
        {
            return insert_at(0,value);
        }

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

    private:

        // provides: [0,capacity) is initialized
        void expand (size_t capacity) requires default_initializable<T> && copyable<T>
        {
            if (capacity <= root_.length)
                return;
            auto new_base = new T[capacity];
            for (auto i = 0; i != count_; ++i)
                new_base[i] = root_.base[i];
            delete [] root_.base;
            root_.base = new_base;
            root_.length = capacity;
        }

        // requires: count < capacity
        // requires: [0,capacity) is initialized
        void shift (size_t index) requires copyable<T>
        {
            if (count_ <= index)
                return;
            for (auto i = count_; i != index; --i)
                root_.base[i] = root_.base[i-1];
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

        using value_type = T;

        // regular

        auto is_equal (uninode_list_position that)
        {
            return node == that.node;
        }

        auto not_equal (uninode_list_position that)
        {
            return node != that.node;
        }

        auto load ()
        {
            return node->content;
        }

        // requires: current != nullptr
        auto next ()
        {
            return uninode_list_position(node->link);
        }
    };

    export
    template <typename T>
    auto is_equal (uninode_list_position<T> x, uninode_list_position<T> y)
    {
        return x.is_equal(y);
    }

    export
    template <typename T>
    auto operator== (uninode_list_position<T> x, uninode_list_position<T> y)
    {
        return x.is_equal(y);
    }

    export
    template <typename T>
    auto not_equal (uninode_list_position<T> x, uninode_list_position<T> y)
    {
        return x.not_equal(y);
    }

    export
    template <typename T>
    auto operator!= (uninode_list_position<T> x, uninode_list_position<T> y)
    {
        return x.not_equal(y);
    }

    export
    template <typename T>
    auto load (uninode_list_position<T> x)
    {
        return x.load();
    }

    export
    template <typename T>
    auto next (uninode_list_position<T> x)
    {
        return x.next();
    }

    /// List on uni-link nodes.
    // Exported above.
    template <typename T>
    class uninode_list
    {
        uninode<T> * root_;

        explicit uninode_list (uninode<T> * r) noexcept : root_{r} {}

    public:

        using value_type = T;

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

    /// Structural position.
    export
    template <typename Position>
    concept position = requires (Position position)
    {
        typename Position::value_type;
        { is_equal(position,position) } -> convertible_to<bool>;
        { not_equal(position,position) } -> convertible_to<bool>;
        { load(position) } -> convertible_to<typename Position::value_type>;
    };

    /// Structural position with forward traversal.
    export
    template <typename Position>
    concept forward_position = position<Position> && requires (Position position)
    {
        { next(position) } -> convertible_to<Position>;
    };

    /// Distance from first to limit.
    export
    template <typename Position>
    requires forward_position<Position>
    auto distance (Position position, Position limit) -> size_t
    {
        size_t counter {};
        while (not_equal(position,limit)) {
            ++counter;
            position = next(position);
        }
        return counter;
    }

    export
    template <typename Position>
    requires forward_position<Position> && equality_comparable<typename Position::value_type>
    auto find (Position position, Position limit, typename Position::value_type value)
    {
        while (not_equal(position,limit) && load(position) != value)
            position = next(position);
        return position;
    }
}