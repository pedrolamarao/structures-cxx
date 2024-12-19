module;

#include <concepts>

export module br.dev.pedrolamarao.structures:binode_list;

import :binode;
import :binode_list_position;

using std::copyable;

namespace br::dev::pedrolamarao::structures
{
    /// List on bi-link nodes.
    ///
    /// The list is projected onto a circular bi-link node structure.
    export
    template <typename T>
    class binode_list
    {
        binode<T>* root_;

        explicit binode_list (binode<T>* root) noexcept :
            root_{root}
        { }

    public:

        using value_type = T;

        using position_type = binode_list_position<T>;

        // type

        /// Constructs an empty list.
        binode_list () :
            root_ {}
        {
            root_ = new binode<T>;
            link(root_,root_);
        }

        /// Moves that list into this list.
        binode_list (binode_list && that) noexcept :
            root_{that.root_}
        {
            that.root_ = new binode<T>;
            link(that.root_,that.root_);
        }

        /// Moves that list into this list.
        auto operator= (binode_list && that) noexcept
        {
            using std::swap;
            swap(this->root_,that.root_);
            return *this;
        }

        binode_list (binode_list const & that) = delete;

        auto operator= (binode_list const & that) = delete;

        /// Destructs this list.
        ~binode_list ()
        {
            auto node = root_->right;
            while (node != root_) {
                auto next = node->right;
                delete node;
                node = next;
            }
            delete root_;
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
            auto root = new binode<TT>;
            auto current = root;
            while (count > 0) {
                auto next = new binode<TT>;
                link(current,next);
                next->content = value;
                current = next;
                --count;
            }
            link(current,root);
            return binode_list<TT>(root);
        }

        // query

        /// Position of the first element.
        auto first ()
        {
            return binode_list_position<T>(root_->right);
        }

        auto is_empty () const
        {
            return root_->right == root_;
        }

        auto not_empty () const
        {
            return root_->right != root_;
        }

        /// Loads value at position.
        ///
        /// Requires: position in [first,limit)
        auto load (binode_list_position<T> position) const
        {
            return position.node->content;
        }

        auto limit ()
        {
            return binode_list_position<T>(root_);
        }

        // update

        /// Erases element at position.
        ///
        /// Requires: first <= position < limit
        auto erase_at (position_type position)
        {
            auto target = position.node;
            auto previous = target->left;
            auto next = target->right;
            link(previous,next);
            delete target;
        }

        /// Inserts element at position.
        auto insert_at (binode_list_position<T> position, T value) requires copyable<T>
        {
            auto next = position.node;
            auto previous = next->left;
            auto inserted = new binode<T>;
            link(previous,inserted);
            link(inserted,next);
            inserted->content = value;
            return binode_list_position<T>(inserted);
        }

        /// Requires: first <= position < limit
        void store (binode_list_position<T> position, T value) requires copyable<T>
        {
            position.node->content = value;
        }
    };
}