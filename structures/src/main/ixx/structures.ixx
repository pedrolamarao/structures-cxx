module;

#include <concepts>
#include <cstdint>

export module br.dev.pedrolamarao.structures;

using namespace std;

namespace br::dev::pedrolamarao::structures
{
    /**
     * Memory segment.
     */
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

    /**
     * Cursor traversing a list on a segment.
     */
    export
    template <typename T>
    class segment_list_cursor
    {
        template <typename>
        friend class segment_list;

        T       * position;
        T const * limit;

        explicit segment_list_cursor (T * p, T * l) :
            position{p}, limit{l}
        { }

    public:

        auto good () const
        {
            return position < limit;
        }

        // requires: good()
        void advance ()
        {
            ++position;
        }
    };

    /**
     * Iterator traversing a list on a segment.
     */
    export
    template <typename T>
    class segment_list_iterator
    {
        template <typename>
        friend class segment_list;

        T const * position;
        T const * limit;

        explicit segment_list_iterator (T * p, T * l) :
            position{p}, limit{l}
        { }

    public:

        // requires: good()
        auto next ()
        {
            return segment_list_iterator<T>(position+1,limit);
        }
    };

    /**
     * List on a segment.
     */
    // Previously exported.
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

        // properties

        auto is_empty () const
        {
            return count_ == 0;
        }

        // query

        auto cursor ()
        {
            return segment_list_cursor(root_.base,root_.base+count_);
        }

        // requires: index <= count
        auto load (size_t index) const
        {
            return root_.base[index];
        }

        // update

        // requires: index <= count
        auto store (size_t index, T value)
        {
            return root_.base[index] = value;
        }
    };

    /**
     * Memory node with one link.
     */
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

    /**
     * Cursor traversing a list on uninodes.
     */
    export
    template <typename T>
    class uninode_list_cursor
    {
        template <typename>
        friend class uninode_list;

        uninode<T> * position;

        explicit uninode_list_cursor (uninode<T> * p) : position{p} {}

    public:

        auto good () const
        {
            return position != nullptr;
        }

        // requires: good()
        void advance ()
        {
            position = position->link;
        }
    };

    /**
     * List on uninodes.
     */
    // Previously exported.
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

        // properties

        auto is_empty () const
        {
            return root_ == nullptr;
        }

        // query

        auto cursor ()
        {
            return uninode_list_cursor<T>(root_);
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

        // update

        // requires: index <= count
        void store (size_t index, T value)
        {
            auto node = root_;
            while (index > 0) {
                node = node->link;
                --index;
            }
            node->content = std::move(value);
        }
    };

    /**
     * Forward traversing cursor.
     */
    export
    template <typename Cursor>
    concept forward_cursor = requires (Cursor cursor)
    {
        { cursor.good() } -> convertible_to<bool>;
        { cursor.advance() };
    };

    /**
     * Forward traversing iterator.
     */
    export
    template <typename Iterator>
    concept forward_iterator = requires (Iterator iterator)
    {
        { iterator.next() } -> convertible_to<Iterator>;
    };

    /**
     * Count positions until end-of-cursor.
     */
    export
    template <typename Cursor>
    requires forward_cursor<Cursor>
    auto count (Cursor cursor) -> size_t
    {
        size_t count {};
        while (cursor.good()) {
            ++count;
            cursor.advance();
        }
        return count;
    }

    /**
     * Count positions in range [first,limit).
     */
    export
    template <typename Iterator>
    requires forward_iterator<Iterator>
    auto count (Iterator first, Iterator limit) -> size_t
    {
        size_t count {};
        while (first != limit) {
            ++count;
            first = first.next();
        }
        return count;
    }
}