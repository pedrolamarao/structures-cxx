module;

#include <algorithm>
#include <concepts>

export module br.dev.pedrolamarao.structures:segment_deck;

import :segment;

using std::copyable;
using std::default_initializable;
using std::max;

namespace br::dev::pedrolamarao::structures
{
    /// Linear sequence with access at "bottom" and "top"
    /// projected onto a memory segment.
    ///
    /// Actual elements are stored in "words" [0,count).
    /// The first "word" stores the "bottom" element.
    /// The last "word" stores the "top" element.
    export
    template <typename T>
    class segment_deck
    {
        segment<T> root_;
        size_t     count_;

        explicit segment_deck (segment<T> r, size_t c) noexcept :
            root_{r},count_{c}
        { }

    public:

        using value_type = T;

        // type

        /// Constructs an empty deck.
        segment_deck () noexcept :
            segment_deck({},0)
        { }

        /// Moves that deck into this deck.
        segment_deck (segment_deck && that) noexcept :
            root_{that.root_}, count_{that.count_}
        {
            that.root_ = {};
            that.count_ = {};
        }

        /// Moves that deck into this deck.
        auto operator= (segment_deck && that) noexcept -> segment_deck&
        {
            root_ = that.root_;
            count_ = that.count_;
            that.root_ = {};
            that.count_ = {};
            return *this;
        }

        segment_deck (segment_deck const & that) = delete;

        auto operator= (segment_deck const & that) = delete;

        /// Destructs this deck.
        ~segment_deck ()
        {
            delete [] root_.base;
        }

        // query

        /// Bottom of the deck.
        ///
        /// Requires: not_empty
        auto bottom () -> value_type
        {
            return root_.base[0];
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
            return root_.base[ count_ - 1 ];
        }

        // update

        /// Erases from the bottom.
        ///
        /// Requires: not_empty
        void erase_bottom ()
        {
            shift_left(root_,0,count_);
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
            auto new_count = count_ + 1;
            expand(new_count);
            shift_right(root_,0,count_);
            root_.base[0] = value;
            count_ = new_count;
        }

        /// Inserts into the top.
        void insert_top (T value) requires copyable<T>
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