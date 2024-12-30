module;

#include <concepts>

export module br.dev.pedrolamarao.structures:binode_list_v3;

import :binode;
import :binode_list_position;

using std::copyable;

namespace br::dev::pedrolamarao::structures
{
    /// List projected onto a bi-linked memory chain.
    ///
    /// Nodes link left towards first and right towards last.
    ///
    /// There is a head node, dynamically allocated,
    /// linking left to the last node and right to the first node.
    ///
    /// The last node links right to the head node.
    ///
    /// Advantages of this implementation:
    /// - before_first and last positions are available
    /// - insert_first, insert_after, remove_first and remove_after are fast
    ///
    /// Disadvantages of this implementation:
    /// - list object contains head with unused space
    /// - empty list requires "remote" storage
    /// - default and move initialization may throw bad_alloc
    export
    template <typename T>
    class binode_list_v3
    {
        binode<T>* head_;

        explicit binode_list_v3 (binode<T>* head) noexcept :
            head_ { head }
        { }

    public:

        using value_type = T;

        using position_type = binode_list_position<T>;

        // type

        /// Constructs an empty list.
        binode_list_v3 () :
            head_ {}
        {
            head_ = new binode<T>;
            head_->left = head_;
            head_->right = head_;
        }

        /// Moves that list into this list.
        binode_list_v3 (binode_list_v3 && that) :
            head_ { that.head_ }
        {
            that.head_ = new binode<T>;
            that.head_->left = that.head_;
            that.head_->right = that.head_;
        }

        /// Moves that list into this list.
        auto& operator= (binode_list_v3 && that) noexcept
        {
            using std::swap;
            swap(head_,that.head_);
            return *this;
        }

        binode_list_v3 (binode_list_v3 const & that) = delete;

        auto operator= (binode_list_v3 const & that) = delete;

        /// Destructs this list.
        ~binode_list_v3 ()
        {
            auto node = head_->right;
            while (node != head_) {
                auto next = node->right;
                delete node;
                node = next;
            }
            delete head_;
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
            auto head = new binode<TT>;
            auto current = head;
            while (count > 0) {
                auto next = new binode<TT>;
                next->content = value;
                next->left = current;
                current->right = next;
                current = next;
                --count;
            }
            head->left = current;
            current->right = head;
            return binode_list_v3<TT>(head);
        }

        // properties

        auto is_empty () const
        {
            return head_->right == head_;
        }

        auto not_empty () const
        {
            return head_->right != head_;
        }

        // positions

        /// Position before the first element.
        auto before_first ()
        {
            return binode_list_position<T>(head_);
        }

        /// Position of the first element.
        auto first ()
        {
            return binode_list_position<T>(head_->right);
        }

        /// Position of the last element.
        auto last ()
        {
            return binode_list_position<T>(head_->left);
        }

        /// Position after the last element.
        auto after_last ()
        {
            return binode_list_position<T>(head_);
        }

        // update

        auto insert_first (T value)
        requires copyable<T>
        {
            auto inserted = new binode<T>(head_,head_->right,value);
            head_->right = inserted;
            return binode_list_position<T>(inserted);
        }

        auto insert_after (binode_list_position<T> position, T value)
        requires copyable<T>
        // requires is_reachable(first(),position)
        {
            auto previous = position.node;
            auto next = previous->right;
            auto inserted = new binode<T>(previous,next,value);
            previous->right = inserted;
            next->left = inserted;
            return binode_list_position<T>(inserted);
        }

        auto remove_first ()
        // requires not_empty()
        {
            auto erased = head_->right;
            auto next = erased->right;
            head_->right = next;
            next->left = head_;
            delete erased;
        }

        auto remove_after (position_type position)
        // requires is_reachable(first(),position)
        {
            auto previous = position.node;
            auto erased = previous->right;
            auto next = erased->right;
            previous->right = next;
            next->left = previous;
            delete erased;
        }
    };
}