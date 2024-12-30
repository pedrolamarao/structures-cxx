module;

#include <concepts>

export module br.dev.pedrolamarao.structures:binode_list;

import :binode;
import :binode_list_position;

using std::copyable;

namespace br::dev::pedrolamarao::structures
{
    /// Linear sequence projected onto bi-linked memory nodes.
    ///
    /// Nodes link left towards first and right towards last.
    /// The root node links right with the first node
    /// and links left with the last node.
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
        binode_list (binode_list && that) :
            root_{that.root_}
        {
            that.root_ = new binode<T>;
            link(that.root_,that.root_);
        }

        /// Moves that list into this list.
        auto& operator= (binode_list && that) noexcept
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

        // properties

        auto is_empty () const
        {
            return root_->right == root_;
        }

        auto not_empty () const
        {
            return root_->right != root_;
        }

        // positions

        /// Position before the first element.
        auto before_first ()
        {
            return binode_list_position<T>(root_);
        }

        /// Position of the first element.
        auto first ()
        {
            return binode_list_position<T>(root_->right);
        }

        /// Position of the last element.
        auto last ()
        {
            return binode_list_position<T>(root_->left);
        }

        /// Position after the last element.
        auto after_last ()
        {
            return binode_list_position<T>(root_);
        }

        // update

        auto insert_first (T value)
        requires copyable<T>
        {
            auto inserted = new binode<T>(root_,root_->right,value);
            root_->right = inserted;
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
            auto erased = root_->right;
            auto next = erased->right;
            root_->right = next;
            next->left = root_;
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
            next->left = previous;
            delete erased;
        }
    };
}