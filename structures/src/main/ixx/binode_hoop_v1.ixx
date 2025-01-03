module;

#include <concepts>

export module br.dev.pedrolamarao.structures:binode_hoop_v1;

import :binode;
import :binode_list_position;

using std::copyable;
using std::size_t;

namespace br::dev::pedrolamarao::structures
{
    /// Hoop projected onto a bi-linked memory chain.
    ///
    /// Nodes link left towards previous and right towards next.
    ///
    /// The hoop links to the first node.
    ///
    /// Advantages of this implementation:
    /// - ?
    ///
    /// Disadvantages of this implementation:
    /// - ?
    export
    template <typename T>
    class binode_hoop_v1
    {
        binode<T>* first_;

        explicit binode_hoop_v1 (binode<T>* first) noexcept :
            first_ { first }
        { }

    public:

        using value_type = T;

        using position_type = binode_linear_position<T>;

        // type

        /// Constructs an empty hoop.
        binode_hoop_v1 () noexcept :
            first_ {}
        { }

        /// Moves that hoop into this hoop.
        binode_hoop_v1 (binode_hoop_v1 && that) noexcept :
            first_ { that.first_ }
        {
            that.first_ = {};
        }

        /// Moves that hoop into this hoop.
        auto& operator= (binode_hoop_v1 && that) noexcept
        {
            using std::swap;
            swap(first_,that.first_);
            return *this;
        }

        binode_hoop_v1 (binode_hoop_v1 const & that) = delete;

        auto operator= (binode_hoop_v1 const & that) = delete;

        /// Destructs this hoop.
        ~binode_hoop_v1 ()
        {
            if (first_ == nullptr) return;
            auto node = first_->right;
            while (node != first_) {
                auto next = first_->right;
                delete first_;
                first_ = next;
            }
            delete first_;
        }

        // factories

        /// Creates a hoop filled with copies of a value.
        ///
        /// Provides: distance(first,limit) == count
        template <typename TT>
        requires copyable<TT>
        static
        auto filled (TT value, size_t count)
        {
            if (count == 0)
                return binode_hoop_v1<TT>();
            auto first = new binode<TT>;
            first->content = value;
            auto current = first;
            count = count - 1;
            while (count > 0) {
                auto next = new binode<TT>;
                next->content = value;
                next->left = current;
                current->right = next;
                current = next;
                count = count - 1;
            }
            first->left = current;
            current->right = first;
            return binode_hoop_v1<TT>(first);
        }

        // properties

        auto is_empty () const
        {
            return first_ == nullptr;
        }

        auto not_empty () const
        {
            return first_ != nullptr;
        }

        // positions

        /// Position of the first element.
        auto first ()
        {
            return binode_linear_position<T>(first_);
        }

        // update

        auto insert_first (T value)
        requires copyable<T>
        {
            auto inserted = new binode<T>;
            inserted->content = value;
            if (first_ == nullptr) {
                inserted->left = inserted;
                inserted->right = inserted;
            }
            else {
                auto previous = first_->left;
                inserted->left = previous;
                inserted->right = first_;
                previous->right = inserted;
                first_->left = inserted;
            }
            first_ = inserted;
            return binode_linear_position<T>(inserted);
        }

        auto insert_after (binode_linear_position<T> position, T value)
        requires copyable<T>
        // requires is_reachable(first(),position)
        {
            auto previous = position.node;
            auto next = previous->right;
            auto inserted = new binode<T>(previous,next,value);
            if (next != nullptr) next->left = inserted;
            previous->right = inserted;
            return binode_linear_position<T>(inserted);
        }

        auto remove_first ()
        // requires not_empty()
        {
            auto previous = first_->left;
            auto next = first_->right;
            auto erased = first_;
            if (erased == next) {
                first_ = nullptr;
            }
            else {
                previous->right = next;
                next->left = previous;
                first_ = next;
            }
            delete erased;
        }

        auto remove_after (position_type position)
        // requires is_reachable(first(),position)
        {
            auto previous = position.node;
            auto erased = previous->right;
            auto next = erased->right;
            // is this the only node?
            if (erased == next) {
                first_ = nullptr;
            }
            // after removing, does only one node remain?
            else if (previous == next)  {
                previous->right = next;
                next->left = previous;
                first_ = next;
            }
            else {
                previous->right = next;
                next->left = previous;
            }
            delete erased;
        }
    };
}