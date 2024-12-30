module;

#include <concepts>

export module br.dev.pedrolamarao.structures:binode_list_v1;

import :binode;
import :binode_list_position;

using std::copyable;

namespace br::dev::pedrolamarao::structures
{
    /// List projected onto a bi-linked memory chain.
    ///
    /// Nodes link left towards first and right towards last.
    ///
    /// The list links to the first node.
    ///
    /// The last node links right to nullptr.
    ///
    /// Advantages of this implementation:
    /// - minimal list object
    /// - empty list requires no "remote" storage
    /// - noexcept default and move initialization
    ///
    /// Disadvantages of this implementation:
    /// - before_first and last positions are not available
    /// - insert_first, insert_after, remove_first and remove_after are slowed by nullptr guards
    export
    template <typename T>
    class binode_list_v1
    {
        binode<T>* first_;

        explicit binode_list_v1 (binode<T>* first) noexcept :
            first_ { first }
        { }

    public:

        using value_type = T;

        using position_type = binode_list_position<T>;

        // type

        /// Constructs an empty list.
        binode_list_v1 () noexcept :
            first_ {}
        { }

        /// Moves that list into this list.
        binode_list_v1 (binode_list_v1 && that) noexcept :
            first_ { that.first_ }
        {
            that.first_ = {};
        }

        /// Moves that list into this list.
        auto& operator= (binode_list_v1 && that) noexcept
        {
            using std::swap;
            swap(first_,that.first_);
            return *this;
        }

        binode_list_v1 (binode_list_v1 const & that) = delete;

        auto operator= (binode_list_v1 const & that) = delete;

        /// Destructs this list.
        ~binode_list_v1 ()
        {
            while (first_ != nullptr) {
                auto next = first_->right;
                delete first_;
                first_ = next;
            }
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
            if (count == 0)
                return binode_list_v2<TT>();
            auto first = new binode<TT>;
            first->value = value;
            auto current = first;
            while (count > 0) {
                auto next = new binode<TT>;
                next->content = value;
                next->left = current;
                current->right = next;
                current = next;
                --count;
            }
            return binode_list_v1<TT>(first);
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
            return binode_list_position<T>(first_);
        }

        /// Position after the last element.
        auto after_last ()
        {
            return binode_list_position<T>(nullptr);
        }

        // update

        auto insert_first (T value)
        requires copyable<T>
        {
            auto inserted = new binode<T>(nullptr,first_,value);
            if (first_ != nullptr) first_->left = inserted;
            first_ = inserted;
            return binode_list_position<T>(inserted);
        }

        auto insert_after (binode_list_position<T> position, T value)
        requires copyable<T>
        // requires is_reachable(first(),position)
        {
            auto previous = position.node;
            auto next = previous->right;
            auto inserted = new binode<T>(previous,next,value);
            if (next != nullptr) next->left = inserted;
            previous->right = inserted;
            return binode_list_position<T>(inserted);
        }

        auto remove_first ()
        // requires not_empty()
        {
            auto erased = first_;
            auto next = erased->right;
            if (next != nullptr) next->left = nullptr;
            first_ = next;
            delete erased;
        }

        auto remove_after (position_type position)
        // requires is_reachable(first(),position)
        {
            auto previous = position.node;
            auto erased = previous->right;
            if (erased == nullptr) return;
            auto next = erased->right;
            if (next != nullptr) next->left = previous;
            previous->right = next;
            delete erased;
        }
    };
}