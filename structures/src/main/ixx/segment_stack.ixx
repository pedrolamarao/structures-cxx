module;

#include <algorithm>
#include <concepts>

export module br.dev.pedrolamarao.structures:segment_stack;

import :segment;

using std::copyable;
using std::default_initializable;
using std::max;

namespace br::dev::pedrolamarao::structures
{
    /// Linear sequence with insert and remove at "top"
    /// projected onto a memory segment.
    ///
    /// Actual elements are stored in "words" [0,count).
    /// The first "word" stores the first element.
    /// Subsequent "words" stores subsequent elements.
    /// The last element is the "top" element.
    export
    template <typename T>
    class segment_stack
    {
        segment<T> root_;
        size_t     count_;

        explicit segment_stack (segment<T> r, size_t c) noexcept :
            root_{r},count_{c}
        { }

    public:

        using value_type = T;

        // type

        /// Constructs an empty stack.
        segment_stack () noexcept :
            segment_stack({},0)
        { }

        /// Moves that stack into this stack.
        segment_stack (segment_stack && that) noexcept :
            root_{that.root_}, count_{that.count_}
        {
            that.root_ = {};
            that.count_ = {};
        }

        /// Moves that stack into this stack.
        auto operator= (segment_stack && that) noexcept -> segment_stack&
        {
            root_ = that.root_;
            count_ = that.count_;
            that.root_ = {};
            that.count_ = {};
            return *this;
        }

        segment_stack (segment_stack const & that) = delete;

        auto operator= (segment_stack const & that) = delete;

        /// Destructs this stack.
        ~segment_stack ()
        {
            delete [] root_.base;
        }

        // query

        auto is_empty () const
        {
            return count_ == 0;
        }

        auto not_empty () const
        {
            return count_ != 0;
        }

        /// Position of the top element.
        auto top ()
        {
            return root_.base[ count_ - 1 ];
        }

        // update

        /// Erases from the stack.
        void erase ()
        {
            --count_;
        }

        /// Inserts into the stack.
        void insert (T value) requires copyable<T>
        {
            auto new_count = count_ + 1;
            expand(new_count);
            root_.base[count_] = value;
            count_ = new_count;
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
    };
}