module;

#include <concepts>

export module br.dev.pedrolamarao.structures:binode_list_v2;

import :binode;
import :binode_list_position;

using std::copyable;

namespace br::dev::pedrolamarao::structures
{
    /// List projected onto a bi-linked memory chain.
    ///
    /// Nodes link left towards first and right towards last.
    ///
    /// There is a head node, embedded in the list,
    /// linking left to the last node and right to the first node.
    ///
    /// The last node links to nullptr.
    ///
    /// Advantages of this implementation:
    /// - empty list requires no "remote" storage
    /// - noexcept default and move initialization
    /// - before_first and last positions are available
    ///
    /// Disadvantages of this implementation:
    /// - list object contains head with unused space
    /// - insert_first, insert_after, remove_first and remove_after are slowed by nullptr guards
    export
    template <typename T>
    class binode_list_v2
    {
        binode<T> head_;

        explicit binode_list_v2 (binode<T>* first, binode<T>* last) noexcept :
            head_ { .left = last, .right = first }
        { }

    public:

        using value_type = T;

        using position_type = binode_linear_position<T>;

        // type

        /// Constructs an empty list.
        binode_list_v2 () noexcept :
            head_ {}
        {}

        /// Moves that list into this list.
        binode_list_v2 (binode_list_v2 && that) noexcept :
            head_ { that.head_ }
        {
            that.head_ = {};
        }

        /// Moves that list into this list.
        auto& operator= (binode_list_v2 && that) noexcept
        {
            using std::swap;
            swap(this->head_,that.head_);
            return *this;
        }

        binode_list_v2 (binode_list_v2 const & that) = delete;

        auto operator= (binode_list_v2 const & that) = delete;

        /// Destructs this list.
        ~binode_list_v2 ()
        {
            auto node = head_.right;
            while (node != nullptr) {
                auto next = node->right;
                delete node;
                node = next;
            }
        }

        // factories

        /// Creates a list filled with copies of a value.
        ///
        /// Provides: distance(first,limit) == count
        template <typename TT>
        static
        auto filled (TT value, size_t count)
        requires copyable<TT>
        {
            if (count == 0)
                return binode_list_v2<TT>();
            auto first = new binode<TT>;
            first->content = value;
            auto current = first;
            while (count > 0) {
                auto next = new binode<TT>;
                next->content = value;
                next->left = current;
                current->right = next;
                current = next;
                --count;
            }
            return binode_list_v2<TT>(first,current);
        }

        // properties

        auto is_empty () const
        {
            return head_.right == nullptr;
        }

        auto not_empty () const
        {
            return head_.right != nullptr;
        }

        // positions

        /// Position before the first element.
        auto before_first ()
        {
            return binode_linear_position<T>(&head_);
        }

        /// Position of the first element.
        auto first ()
        {
            return binode_linear_position<T>(head_.right);
        }

        /// Position of the last element.
        auto last ()
        {
            return binode_linear_position<T>(head_.left);
        }

        /// Position after the last element.
        auto after_last ()
        {
            return binode_linear_position<T>(nullptr);
        }

        // update

        auto insert_first (T value)
        requires copyable<T>
        {
            auto inserted = new binode<T>(&head_,head_.right,value);
            head_.right = inserted;
            return binode_linear_position<T>(inserted);
        }

        auto insert_after (binode_linear_position<T> position, T value)
        requires copyable<T>
        // requires is_reachable(first(),position)
        {
            auto previous = position.node;
            auto next = previous->right;
            auto inserted = new binode<T>(previous,next,value);
            previous->right = inserted;
            if (next != nullptr) next->left = inserted;
            return binode_linear_position<T>(inserted);
        }

        auto remove_first ()
        // requires not_empty()
        {
            auto erased = head_.right;
            auto next = erased->right;
            head_.right = next;
            if (next != nullptr) next->left = &head_;
            delete erased;
        }

        auto remove_after (position_type position)
        // requires is_reachable(first(),position)
        {
            auto previous = position.node;
            auto erased = previous->right;
            if (erased == nullptr) return;
            auto next = erased->right;
            previous->right = next;
            if (next != nullptr) next->left = previous;
            delete erased;
        }
    };
}