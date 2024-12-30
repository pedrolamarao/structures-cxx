module;

#include <concepts>

export module br.dev.pedrolamarao.structures:uninode_stack;

import :uninode;

using std::copyable;

namespace br::dev::pedrolamarao::structures
{
    /// Stack projected onto a uni-linked memory chain.
    ///
    /// Nodes link from top to bottom.
    ///
    /// The stack links to the top node.
    ///
    /// The bottom node links to nullptr.
    export
    template <typename T>
    class uninode_stack
    {
        uninode<T> * top_;

        explicit uninode_stack (uninode<T>* top) noexcept :
            top_{top}
        {}

    public:

        using value_type = T;

        // type

        /// Constructs an empty stack.
        uninode_stack () noexcept :
            top_{}
        {}

        /// Moves that stack into this stack.
        uninode_stack (uninode_stack && that) noexcept :
            top_ { that.top_ }
        {
            that.top_ = {};
        }

        /// Moves that stack into this stack.
        auto& operator= (uninode_stack && that) noexcept
        {
            using std::swap;
            swap(top_,that.top_);
            return *this;
        }

        uninode_stack (uninode_stack const & that) = delete;

        auto operator= (uninode_stack const & that) = delete;

        /// Destructs this stack.
        ~uninode_stack ()
        {
            while (top_ != nullptr) {
                auto next = top_->link;
                delete top_;
                top_ = next;
            }
        }

        // properties

        auto is_empty () const
        {
            return top_ == nullptr;
        }

        auto not_empty () const
        {
            return top_ != nullptr;
        }

        // elements

        /// Top of the stack.
        ///
        /// Requires: not_empty
        auto top () -> value_type
        {
            return top_->content;
        }

        // update

        /// Inserts into the stack.
        void insert (T value) requires copyable<T>
        {
            auto inserted = new uninode<T>(top_,value);
            top_ = inserted;
        }

        /// Erases from the stack.
        ///
        /// Requires: not_empty
        void erase ()
        {
            auto erased = top_;
            top_ = erased->link;
            delete erased;
        }
    };
}