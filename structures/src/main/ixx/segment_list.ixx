module;

#include <algorithm>
#include <concepts>

export module br.dev.pedrolamarao.structures:segment_list;

import :segment;
import :segment_list_position;

using std::copyable;
using std::default_initializable;
using std::max;

namespace br::dev::pedrolamarao::structures
{
    /// Linear sequence projected onto a memory segment.
    ///
    /// Actual elements are stored in "words" [0,count).
    /// The first "word" stores the first element.
    /// Subsequent "words" stores subsequent elements.
    export
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

        using position_type = segment_linear_position<T>;

        // type

        /// Constructs an empty list.
        segment_list () noexcept :
            segment_list({},0)
        { }

        /// Moves that list into this list.
        segment_list (segment_list && that) noexcept :
            root_{that.root_}, count_{that.count_}
        {
            that.root_ = {};
            that.count_ = {};
        }

        /// Moves that list into this list.
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

        /// Destructs this list.
        ~segment_list ()
        {
            delete [] root_.base;
        }

        // factories

        /// Creates a list filled with copies of a value.
        ///
        /// Provides: distance(first,limit) == count
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

        /// Position after the last element.
        auto after_last ()
        {
            return segment_linear_position<T>(root_.base + count_);
        }

        /// Position before the first element.
        auto before_first ()
        {
            return segment_linear_position<T>(root_.base - 1);
        }

        /// Position of the first element.
        auto first ()
        {
            return segment_linear_position<T>(root_.base);
        }

        auto is_empty () const
        {
            return count_ == 0;
        }

        auto not_empty () const
        {
            return count_ != 0;
        }

        // update

        auto insert_first (value_type value)
        {
            return insert_at(first(),value);
        }

        auto insert_after (position_type position, T value)
        requires copyable<T>
        // requires is_reachable(first(),position)
        {
            return insert_at(next(position),value);
        }

        auto insert_at (size_t index, T value) requires copyable<T>
        {
            auto new_count = max(count_,index) + 1;
            expand(new_count);
            shift_right(index);
            root_.base[index] = value;
            count_ = new_count;
            return segment_linear_position<T>(root_.base+index);
        }

        auto insert_at (position_type position, T value)
        // requires is_reachable(first(),position)
        {
            size_t index = position.position_ - root_.base;
            return insert_at(index,value);
        }

        void remove_first ()
        // requires not_empty()
        {
            shift_left(root_,0,count_);
            --count_;
        }

        void remove_after (position_type position)
        // requires is_reachable(first(),position)
        {
            remove_at(next(position));
        }

        void remove_at (size_t index)
        {
            shift_left(root_,index,count_);
            --count_;
        }

        void remove_at (position_type position)
        // is_reachable(first(),position)
        {
            size_t index = position.position_ - root_.base;
            remove_at(index);
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

        void shift_right (size_t index)
        {
            if (count_ <= index)
                return;
            structures::shift_right(root_,index,count_);
        }
    };
}