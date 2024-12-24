module;

#include <concepts>

export module br.dev.pedrolamarao.structures:binode_deck;

import :binode;

using std::copyable;

namespace br::dev::pedrolamarao::structures
{
    /// Linear sequence with access at "bottom" and "top"
    /// projected onto bi-linked memory nodes.
    ///
    /// Nodes link left towards bottom and right towards top.
    /// The root node links right with the bottom node
    /// and links left with the top node.
    export
    template <typename T>
    class binode_deck
    {
        binode<T>* root_;

        explicit binode_deck (binode<T>* root) noexcept :
            root_{root}
        { }

    public:

        using value_type = T;

        // type

        /// Constructs an empty deck.
        binode_deck () :
            root_ {}
        {
            root_ = new binode<T>;
            link(root_,root_);
        }

        /// Moves that deck into this deck.
        binode_deck (binode_deck && that) noexcept :
            root_{that.root_}
        {
            that.root_ = new binode<T>;
            link(that.root_,that.root_);
        }

        /// Moves that deck into this deck.
        auto operator= (binode_deck && that) noexcept
        {
            using std::swap;
            swap(this->root_,that.root_);
            return *this;
        }

        binode_deck (binode_deck const & that) = delete;

        auto operator= (binode_deck const & that) = delete;

        /// Destructs this deck.
        ~binode_deck ()
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

        /// Creates a deck filled with copies of a value.
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
            return binode_deck<TT>(root);
        }

        // query

        auto bottom () -> value_type
        {
            return root_->right->content;
        }

        auto is_empty () const
        {
            return root_->right == root_;
        }

        auto not_empty () const
        {
            return root_->right != root_;
        }

        auto top () -> value_type
        {
            return root_->left->content;
        }

        // update

        void erase_bottom ()
        {
            auto target = root_->right;
            auto previous = target->left;
            auto next = target->right;
            link(previous,next);
            delete target;
        }

        void erase_top ()
        {
            auto target = root_->left;
            auto previous = target->left;
            auto next = target->right;
            link(previous,next);
            delete target;
        }

        void insert_bottom (T value)
        {
            auto next = root_->right;
            auto previous = next->left;
            auto inserted = new binode<T>;
            link(previous,inserted);
            link(inserted,next);
            inserted->content = value;
        }

        void insert_top (T value)
        {
            auto previous = root_->left;
            auto next = previous->right;
            auto inserted = new binode<T>;
            link(previous,inserted);
            link(inserted,next);
            inserted->content = value;
        }
    };
}