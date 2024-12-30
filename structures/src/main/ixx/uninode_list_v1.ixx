module;

#include <concepts>

export module br.dev.pedrolamarao.structures:uninode_list_v1;

import :uninode;
import :uninode_list_position;

using std::copyable;

namespace br::dev::pedrolamarao::structures
{
    /// List projected onto a uni-linked memory chain.
    ///
    /// Nodes link from first towards last.
    ///
    /// The list links to the first node.
    ///
    /// The last node links to nullptr.
    ///
    /// Advantages of this implementation:
    /// - minimal list object size
    /// - noexcept default and move initialization
    /// - empty list requires not additional storage
    ///
    /// Disadvantages of this implementation:
    /// - before_first is not available
    /// - remove_after tests for nullptr
    export
    template <typename T>
    class uninode_list_v1
    {
        uninode<T>* first_;

        explicit uninode_list_v1 (uninode<T>* first) noexcept :
            first_ { first }
        {}

    public:

        using value_type = T;

        using position_type = uninode_list_position<T>;

        // type

        /// Constructs an empty list.
        uninode_list_v1 () noexcept :
            first_ {}
        {
        }

        /// Moves that list into this list.
        uninode_list_v1 (uninode_list_v1 && that) noexcept :
            first_ { that.first_ }
        {
            that.first_ = {};
        }

        /// Moves that list into this list.
        auto& operator= (uninode_list_v1 && that) noexcept
        {
            using std::swap;
            swap(first_,that.first_);
            return *this;
        }

        uninode_list_v1 (uninode_list_v1 const & that) = delete;

        auto operator= (uninode_list_v1 const & that) = delete;

        /// Destructs this list.
        ~uninode_list_v1 ()
        {
            while (first_ != nullptr) {
                auto next = first_->link;
                delete first_;
                first_ = next;
            }
        }

        // factories

        /// Creates a list filled with copies of a value.
        ///
        /// Provides: distance(first,last) == count
        template <copyable TT>
        static
        auto filled (TT value, size_t count)
        {
            if (count == 0)
                return uninode_list_v1<TT>();
            auto first = new uninode<TT>;
            first->content = value;
            auto current = first;
            while (count > 0) {
                auto next = new uninode<TT>;
                next->content = value;
                current->link = next;
                current = next;
                --count;
            }
            return uninode_list_v1<TT>(first);
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
            return uninode_list_position<T>(first_);
        }

        /// Position after the last element.
        auto after_last ()
        {
            return uninode_list_position<T>(nullptr);
        }

        // update

        /// Inserts element at first position.
        auto insert_first (T value) requires copyable<T>
        {
            auto inserted = new uninode<T>(first_,value);
            first_ = inserted;
            return uninode_list_position<T>(inserted);
        }

        /// Inserts element after position.
        ///
        /// Requires: is_reachable(first(),position)
        auto insert_after (uninode_list_position<T> position, T value) requires copyable<T>
        {
            auto previous = position.node;
            auto next = previous->link;
            auto inserted = new uninode<T>(next,value);
            previous->link = inserted;
            return uninode_list_position<T>(inserted);
        }

        /// Erases element at first position.
        ///
        /// Requires: not_empty
        auto remove_first ()
        {
            auto erased = first_;
            first_ = erased->link;
            delete erased;
        }

        /// Erases element after position.
        ///
        /// Requires: not_empty() && is_reachable(first(),position)
        auto remove_after (position_type position)
        {
            auto previous = position.node;
            auto erased = previous->link;
            if (erased == nullptr) return;
            previous->link = erased->link;
            delete erased;
        }
    };
}