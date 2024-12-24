module;

#include <concepts>

export module br.dev.pedrolamarao.structures:uninode_list;

import :uninode;
import :uninode_list_position;

using std::copyable;

namespace br::dev::pedrolamarao::structures
{
    /// Linear sequence projected onto uni-linked memory nodes.
    ///
    /// The root node links to the first element.
    /// Intermediate elements link to next.
    /// The last element links to root.
    /// Therefore, the root node marks the end of the sequence.
    export
    template <typename T>
    class uninode_list
    {
        uninode<T> * root_;

        explicit uninode_list (uninode<T> * r) noexcept : root_{r} {}

    public:

        using value_type = T;

        using position_type = uninode_list_position<T>;

        // type

        /// Constructs an empty list.
        uninode_list () noexcept :
            root_{}
        {
            root_ = new uninode<T>;
            root_->link = root_;
        }

        /// Moves that list into this list.
        uninode_list (uninode_list && that) noexcept :
            root_{that.root_}
        {
            that.root_ = new uninode<T>;
            that.root_->link = that.root_;
        }

        /// Moves that list into this list.
        auto operator= (uninode_list && that) noexcept
        {
            using std::swap;
            swap(root_,that.root_);
            return *this;
        }

        uninode_list (uninode_list const & that) = delete;

        auto operator= (uninode_list const & that) = delete;

        /// Destructs this list.
        ~uninode_list ()
        {
            auto node = root_->link;
            while (node != root_) {
                auto next = node->link;
                delete node;
                node = next;
            }
            delete root_;
        }

        // factories

        /// Creates a list filled with copies of a value.
        ///
        /// Provides: distance(first,last) == count
        template <typename TT>
        requires copyable<TT>
        static
        auto filled (TT value, size_t count)
        {
            auto root = new uninode<TT>;
            auto current = root;
            while (count > 0) {
                auto next = new uninode<TT>(nullptr,value);
                current->link = next;
                current = next;
                --count;
            }
            current->link = root;
            return uninode_list<TT>(root);
        }

        // query

        /// Position of the first element.
        auto first ()
        {
            return uninode_list_position<T>(root_->link);
        }

        auto is_empty () const
        {
            return root_->link == root_;
        }

        auto not_empty () const
        {
            return root_->link != root_;
        }

        /// Loads value at position.
        ///
        /// Requires: position in [first,limit)
        auto load (uninode_list_position<T> position) const
        {
            return position.node->content;
        }

        auto limit ()
        {
            return uninode_list_position<T>(root_);
        }

        // update

        /// Erases element after position.
        ///
        /// Requires: first <= position < limit
        auto erase_after (position_type position)
        {
            auto previous = position.node;
            auto target = previous->link;
            auto next = target->link;
            previous->link = next;
            delete target;
        }

        /// Erases element at first position.
        ///
        /// Requires: not_empty
        auto erase_first ()
        {
            auto target = root_->link;
            auto next = target->link;
            root_->link = next;
            delete target;
        }

        /// Inserts element after position.
        ///
        /// Requires: first <= position < limit
        auto insert_after (uninode_list_position<T> position, T value) requires copyable<T>
        {
            auto previous = position.node;
            auto next = previous->link;
            auto inserted = new uninode<T>(next,value);
            previous->link = inserted;
            return uninode_list_position<T>(inserted);
        }

        /// Inserts element at first position.
        auto insert_first (T value) requires copyable<T>
        {
            auto inserted = new uninode<T>(root_->link,value);
            root_->link = inserted;
            return uninode_list_position<T>(inserted);
        }

        // requires: ?
        void store (uninode_list_position<T> position, T value)
        {
            position.node->content = value;
        }
    };
}