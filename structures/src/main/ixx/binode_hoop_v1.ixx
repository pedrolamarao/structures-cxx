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
        binode<T>* start_;

        explicit binode_hoop_v1 (binode<T>* start) noexcept :
            start_ { start }
        { }

    public:

        using value_type = T;

        using position_type = binode_linear_position<T>;

        // type

        /// Constructs an empty hoop.
        binode_hoop_v1 () noexcept :
            start_ {}
        { }

        /// Moves that hoop into this hoop.
        binode_hoop_v1 (binode_hoop_v1 && that) noexcept :
            start_ { that.start_ }
        {
            that.start_ = {};
        }

        /// Moves that hoop into this hoop.
        auto& operator= (binode_hoop_v1 && that) noexcept
        {
            using std::swap;
            swap(start_,that.start_);
            return *this;
        }

        binode_hoop_v1 (binode_hoop_v1 const & that) = delete;

        auto operator= (binode_hoop_v1 const & that) = delete;

        /// Destructs this hoop.
        ~binode_hoop_v1 ()
        {
            if (start_ == nullptr) return;
            auto node = start_->right;
            while (node != start_) {
                auto next = start_->right;
                delete start_;
                start_ = next;
            }
            delete start_;
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
            auto start = new binode<TT>;
            start->content = value;
            auto current = start;
            count = count - 1;
            while (count > 0) {
                auto next = new binode<TT>;
                next->content = value;
                next->left = current;
                current->right = next;
                current = next;
                count = count - 1;
            }
            start->left = current;
            current->right = start;
            return binode_hoop_v1<TT>(start);
        }

        // properties

        auto is_empty () const
        {
            return start_ == nullptr;
        }

        auto not_empty () const
        {
            return start_ != nullptr;
        }

        // positions

        /// Position of the start element.
        auto start ()
        {
            return binode_linear_position<T>(start_);
        }

        // update

        auto insert_start (T value)
        requires copyable<T>
        {
            auto inserted = new binode<T>(nullptr,start_,value);
            if (start_ != nullptr) start_->left = inserted;
            start_ = inserted;
            return binode_linear_position<T>(inserted);
        }

        auto insert_after (binode_linear_position<T> position, T value)
        requires copyable<T>
        // requires is_reachable(start(),position)
        {
            auto previous = position.node;
            auto next = previous->right;
            auto inserted = new binode<T>(previous,next,value);
            if (next != nullptr) next->left = inserted;
            previous->right = inserted;
            return binode_linear_position<T>(inserted);
        }

        auto remove_start ()
        // requires not_empty()
        {
            auto erased = start_;
            auto next = erased->right;
            if (next != nullptr) next->left = nullptr;
            start_ = next;
            delete erased;
        }

        auto remove_after (position_type position)
        // requires is_reachable(start(),position)
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