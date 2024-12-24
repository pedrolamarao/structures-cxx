module;

#include <concepts>

export module br.dev.pedrolamarao.structures:uninode_stack;

import :uninode;

using std::copyable;

namespace br::dev::pedrolamarao::structures
{
    /// Linear sequence with insert and remove at "top"
    /// projected onto uni-linked memory nodes.
    ///
    /// The root node links to the last element.
    /// Intermediate elements link to previous.
    /// The first element links to root.
    /// Therefore, the root node marks the end of the sequence.
    /// The last element is the "top" element.
    export
    template <typename T>
    class uninode_stack
    {
        uninode<T> * root_;

        explicit uninode_stack (uninode<T> * r) noexcept : root_{r} {}

    public:

        using value_type = T;

        // type

        /// Constructs an empty stack.
        uninode_stack () noexcept :
            root_{}
        {
            root_ = new uninode<T>;
            root_->link = root_;
        }

        /// Moves that stack into this stack.
        uninode_stack (uninode_stack && that) noexcept :
            root_{that.root_}
        {
            that.root_ = new uninode<T>;
            that.root_->link = that.root_;
        }

        /// Moves that stack into this stack.
        auto operator= (uninode_stack && that) noexcept
        {
            using std::swap;
            swap(root_,that.root_);
            return *this;
        }

        uninode_stack (uninode_stack const & that) = delete;

        auto operator= (uninode_stack const & that) = delete;

        /// Destructs this stack.
        ~uninode_stack ()
        {
            auto node = root_->link;
            while (node != root_) {
                auto next = node->link;
                delete node;
                node = next;
            }
            delete root_;
        }

        // query

        auto is_empty () const
        {
            return root_->link == root_;
        }

        auto not_empty () const
        {
            return root_->link != root_;
        }

        /// Top of the stack.
        ///
        /// Requires: not_empty
        auto top () -> value_type
        {
            return root_->link->content;
        }

        // update

        /// Erases from the stack.
        ///
        /// Requires: not_empty
        void erase ()
        {
            auto target = root_->link;
            auto next = target->link;
            root_->link = next;
            delete target;
        }

        /// Inserts into the stack.
        void insert (T value) requires copyable<T>
        {
            auto inserted = new uninode<T>(root_->link,value);
            root_->link = inserted;
        }
    };
}