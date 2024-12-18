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
    /// List on a segment.
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
            auto new_count = max(count_,index) + 1;
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
}