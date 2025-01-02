module;

#include <algorithm>
#include <concepts>

export module br.dev.pedrolamarao.structures:segment_deck;

import :segment;

using std::copyable;
using std::default_initializable;
using std::max;
using std::size_t;

namespace br::dev::pedrolamarao::structures
{
    /// Deck projected onto a memory segment.
    ///
    /// Elements are stored bottom at left, top at right.
    export
    template <typename T>
    class segment_deck
    {
        segment<T> segment_;

        size_t     first_;

        size_t     count_;

        explicit segment_deck (segment<T> segment, size_t first, size_t count) noexcept :
            segment_ { segment }, first_ { first }, count_ { count }
        { }

    public:

        using value_type = T;

        // type

        /// Constructs an empty deck.
        segment_deck () noexcept :
            segment_deck({},{},{})
        { }

        /// Moves that deck into this deck.
        segment_deck (segment_deck && that) noexcept :
            segment_ { that.segment_ }, first_ { that.first_ }, count_ { that.count_ }
        {
            that.segment_ = {};
            that.first_ = {};
            that.count_ = {};
        }

        /// Moves that deck into this deck.
        auto operator= (segment_deck && that) noexcept -> segment_deck&
        {
            using std::swap;
            swap(segment_,that.segment_);
            swap(first_,that.first_);
            swap(count_,that.count_);
            return *this;
        }

        segment_deck (segment_deck const & that) = delete;

        auto operator= (segment_deck const & that) = delete;

        /// Destructs this deck.
        ~segment_deck ()
        {
            delete [] segment_.base;
        }

        // query

        /// Bottom of the deck.
        ///
        /// Requires: not_empty
        auto bottom () -> value_type
        {
            return segment_.base[ first_ ];
        }

        auto is_empty () const
        {
            return count_ == 0;
        }

        auto not_empty () const
        {
            return count_ != 0;
        }

        /// Top of the deck.
        ///
        /// Requires: not_empty
        auto top () -> value_type
        {
            return segment_.base[ count_ - first_ - 1 ];
        }

        // update

        /// Erases from the bottom.
        ///
        /// Requires: not_empty
        void erase_bottom ()
        {
            ++first_;
            --count_;
        }

        /// Erases from the top.
        ///
        /// Requires: not_empty
        void erase_top ()
        {
            --count_;
        }

        /// Inserts into the bottom.
        void insert_bottom (T value) requires copyable<T>
        {
            if (first_ > 0)
                --first_;
            else
                expand_right(0);
            segment_.base[first_] = value;
            ++count_;
        }

        /// Inserts into the top.
        void insert_top (T value) requires copyable<T>
        {
            if (count_ == segment_.length - first_)
                expand_right(count_);
            segment_.base[count_] = value;
            ++count_;
        }

    private:

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
        void shift_right (size_t index)
        {
            structures::shift_right(segment_,first_ + index,count_);
        }
    };
}