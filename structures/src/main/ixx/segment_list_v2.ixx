module;

#include <algorithm>
#include <concepts>

export module br.dev.pedrolamarao.structures:segment_list_v2;

import :segment;
import :segment_list_position;

using std::copyable;
using std::default_initializable;
using std::max;

namespace br::dev::pedrolamarao::structures
{
    /// List projected onto a memory segment.
    ///
    /// List positions are memory "words".
    ///
    /// Unused storage is maintained at left and right.
    /// Compacting shifts towards left.
    ///
    /// Advantages of this implementation:
    /// - insert and remove at left may reuse space
    ///
    /// Disadvantages of this implementation:
    /// - list object requires additional storage
    /// - insert_after and remove_after requires two levels of branching
    export
    template <typename T>
    class segment_list_v2
    {
        segment<T> segment_;

        size_t     first_;

        size_t     count_;

        explicit segment_list_v2 (segment<T> segment, size_t first, size_t count) noexcept :
            segment_ { segment }, first_ { first }, count_ { count }
        { }

    public:

        using value_type = T;

        using position_type = segment_linear_position<T>;

        // type

        /// Constructs an empty list.
        segment_list_v2 () noexcept :
            segment_list_v2({},{},{})
        { }

        /// Moves that list into this list.
        segment_list_v2 (segment_list_v2 && that) noexcept :
            segment_ { that.segment_ }, first_ { that.first_ }, count_ { that.count_ }
        {
            that.segment_ = {};
            that.first_ = {};
            that.count_ = {};
        }

        /// Moves that list into this list.
        auto operator= (segment_list_v2 && that) noexcept -> segment_list_v2&
        {
            using std::swap;
            swap(segment_,that.segment_);
            swap(first_,that.first_);
            swap(count_,that.count_);
            return *this;
        }

        segment_list_v2 (segment_list_v2 const & that) = delete;

        auto operator= (segment_list_v2 const & that) = delete;

        /// Destructs this list.
        ~segment_list_v2 ()
        {
            delete [] segment_.base;
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
            return segment_list_v2<TT>(segment_,0,count);
        }

        // properties

        auto is_empty () const
        {
            return count_ == 0;
        }

        auto not_empty () const
        {
            return count_ != 0;
        }

        // positions

        /// Position before the first element.
        auto before_first ()
        {
            return segment_linear_position<T>(segment_.base + first_ - 1);
        }

        /// Position of the first element.
        auto first ()
        {
            return segment_linear_position<T>(segment_.base + first_);
        }

        /// Position of the last element.
        auto last ()
        {
            return segment_linear_position<T>(segment_.base + first_ + count_ - 1);
        }

        /// Position after the last element.
        auto after_last ()
        {
            return segment_linear_position<T>(segment_.base + first_ + count_);
        }

        // update

        auto insert_first (value_type value)
        {
            return insert_at(0,value);
        }

        auto insert_after (position_type position, T value)
        requires copyable<T>
        // requires is_reachable(first(),position)
        {
            return insert_at(next(position),value);
        }

        auto insert_at (position_type position, T value)
        // requires is_reachable(first(),position)
        {
            size_t index = position.address_ - segment_.base;
            return insert_at(index,value);
        }

        auto insert_at (size_t index, T value)
        requires copyable<T>
        // requires index < count_
        {
            // insert at left?
            if (index == 0)
            {
                // has space at left?
                if (first_ > 0)
                {
                    --first_;
                }
                // no space
                else
                {
                    expand_right(index);
                }
            }
            // insert at right?
            else if (index == count_)
            {
                // has space at right?
                if (count_ < segment_.length - first_)
                {
                }
                // no space
                else
                {
                    expand_right(index);
                }
            }
            // insert at middle
            else
            {
                // has space at right?
                if (count_ < segment_.length - first_)
                {
                    shift_right(index);
                }
                // no space
                else
                {
                    expand_right(index);
                }
            }
            // store
            segment_.base[ first_ + index ] = value;
            ++count_;
            return segment_linear_position<T>(segment_.base + first_ + index);
        }

        void remove_first ()
        // requires not_empty()
        {
            remove_at(0);
        }

        void remove_after (position_type position)
        // requires is_reachable(first(),position)
        {
            remove_at(next(position));
        }

        void remove_at (position_type position)
        // is_reachable(first(),position)
        {
            size_t index = position.address_ - segment_.base;
            remove_at(index);
        }

        void remove_at (size_t index)
        // requires index < count_
        {
            // erase at left?
            if (index == 0)
                ++first_;
            // erase at middle or right
            else
                shift_left(index);
            --count_;
        }

    private:

        // requires: index <= count_
        // provides: capacity is approximately doubled
        // provides: every cell is initialized
        void expand_right (size_t index)
        {
            auto floor = segment_.length / 2;
            auto length = (floor + 1) * 2;
            auto base = new T[ length ];
            for (auto i = 0; i < index; ++i)
                base[i] = segment_.base[i];
            for (auto i = index; i != count_; ++i)
                base[i+1] = segment_.base[i];
            delete [] segment_.base;
            segment_.base = base;
            segment_.length = length;
        }

        // requires: index <= count_
        void shift_left (size_t index)
        {
            structures::shift_left(segment_,first_ + index,count_);
        }

        // requires: index <= count_
        void shift_right (size_t index)
        {
            structures::shift_right(segment_,first_ + index,count_);
        }
    };
}