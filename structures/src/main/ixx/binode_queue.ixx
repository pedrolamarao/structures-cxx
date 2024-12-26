module;

#include <concepts>

export module br.dev.pedrolamarao.structures:binode_queue;

import :binode;

using std::copyable;

namespace br::dev::pedrolamarao::structures
{
    /// Linear sequence with insertion at "back" and removal at "front"
    /// projected onto bi-linked memory nodes.
    ///
    /// Nodes link left towards bottom and right towards top.
    /// The root node links right with the bottom node
    /// and links left with the top node.
    export
    template <typename T>
    class binode_queue
    {
        binode<T>* root_;

        explicit binode_queue (binode<T>* root) noexcept :
            root_{root}
        { }

    public:

        using value_type = T;

        // type

        /// Constructs an empty queue.
        binode_queue () :
            root_ {}
        {
            root_ = new binode<T>;
            link(root_,root_);
        }

        /// Moves that queue into this queue.
        binode_queue (binode_queue && that) noexcept :
            root_{that.root_}
        {
            that.root_ = new binode<T>;
            link(that.root_,that.root_);
        }

        /// Moves that queue into this queue.
        auto operator= (binode_queue && that) noexcept
        {
            using std::swap;
            swap(this->root_,that.root_);
            return *this;
        }

        binode_queue (binode_queue const & that) = delete;

        auto operator= (binode_queue const & that) = delete;

        /// Destructs this queue.
        ~binode_queue ()
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

        // query

        auto is_empty () const
        {
            return root_->right == root_;
        }

        auto not_empty () const
        {
            return root_->right != root_;
        }

        auto front () -> value_type
        {
            return root_->left->content;
        }

        // update

        void insert (T value)
        {
            auto next = root_->right;
            auto previous = next->left;
            auto inserted = new binode<T>;
            link(previous,inserted);
            link(inserted,next);
            inserted->content = value;
        }

        void remove ()
        {
            auto target = root_->left;
            auto previous = target->left;
            auto next = target->right;
            link(previous,next);
            delete target;
        }
    };
}