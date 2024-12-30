module;

#include <concepts>

export module br.dev.pedrolamarao.structures:uninode_list_v2;

import :uninode;
import :uninode_list_position;

using std::copyable;

namespace br::dev::pedrolamarao::structures
{
    /// List projected onto a uni-linked memory chain.
    ///
    /// Nodes link from first to last.
    ///
    /// There is a head node, embedded in the list, linking to the first node.
    ///
    /// The last node links to nullptr.
    ///
    /// Advantages of this implementation:
    /// - noexcept default and move initialization
    /// - empty list requires not additional storage
    /// - before_first is available
    ///
    /// Disadvantages of this implementation:
    /// - list object size requires additional unused space
    /// - remove_after tests for nullptr
    export
    template <typename T>
    class uninode_list_v2
    {
        uninode<T> head_;

        explicit uninode_list_v2 (uninode<T> * first) noexcept :
            head_ { first }
        { }

    public:

        using value_type = T;

        using position_type = uninode_list_position<T>;

        // type

        /// Constructs an empty list.
        uninode_list_v2 () noexcept :
            head_ {}
        { }

        /// Moves that list into this list.
        uninode_list_v2 (uninode_list_v2 && that) noexcept :
            head_ { that.head_ }
        {
        }

        /// Moves that list into this list.
        auto& operator= (uninode_list_v2 && that) noexcept
        {
            using std::swap;
            swap(head_,that.head_);
            return *this;
        }

        uninode_list_v2 (uninode_list_v2 const & that) = delete;

        auto operator= (uninode_list_v2 const & that) = delete;

        /// Destructs this list.
        ~uninode_list_v2 ()
        {
            auto node = head_.link;
            while (node != nullptr) {
                auto next = node->link;
                delete node;
                node = next;
            }
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
            if (count == 0)
                return uninode_list_v2<TT>();
            auto first = new uninode<T>;
            first->value = value;
            auto current = first;
            while (--count > 0) {
                auto next = new uninode<TT>;
                next->value = value;
                current->link = next;
                current = next;
            }
            return uninode_list_v2<TT>(first);
        }

        // properties

        auto is_empty () const
        {
            return head_.link == nullptr;
        }

        auto not_empty () const
        {
            return head_.link != nullptr;
        }

        // positions

        /// Position before the first element.
        auto before_first ()
        {
            return uninode_list_position<T>(&head_);
        }

        /// Position of the first element.
        auto first ()
        {
            return uninode_list_position<T>(head_.link);
        }

        /// Position after the last element.
        auto after_last ()
        {
            return uninode_list_position<T>(nullptr);
        }

        // update

        /// Inserts element at first position.
        auto insert_first (T value) requires copyable<T>
        {
            auto inserted = new uninode<T>(head_.link,value);
            head_.link = inserted;
            return uninode_list_position<T>(inserted);
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

        /// Erases element at first position.
        ///
        /// Requires: not_empty
        auto remove_first ()
        {
            auto erased = head_.link;
            head_.link = erased->link;
            delete erased;
        }

        /// Erases element after position.
        ///
        /// Requires: not_empty() && is_reachable(first(),position)
        auto remove_after (position_type position)
        {
            auto previous = position.node;
            auto erased = previous->link;
            if (erased == nullptr) return;
            auto next = erased->link;
            previous->link = next;
            delete erased;
        }
    };
}