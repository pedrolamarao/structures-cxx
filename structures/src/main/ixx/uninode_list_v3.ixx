module;

#include <concepts>

export module br.dev.pedrolamarao.structures:uninode_list_v3;

import :uninode;
import :uninode_list_position;

using std::copyable;

namespace br::dev::pedrolamarao::structures
{
    /// List projected onto a uni-linked memory chain.
    ///
    /// Nodes link from first to last.
    ///
    /// There is a head node, dynamically allocated, linking to the first node.
    ///
    /// The last node links to the head node.
    ///
    /// Advantages of this implementation:
    /// - minimal list object size
    /// - before_first is available
    /// - branchless remove_after
    ///
    /// Disadvantages of this implementation:
    /// - empty list requires additional storage
    /// - default and move initialization may throw
    export
    template <typename T>
    class uninode_list_v3
    {
        uninode<T>* head_;

        explicit uninode_list_v3 (uninode<T> * head) noexcept :
            head_ { head }
        { }

    public:

        using value_type = T;

        using position_type = uninode_list_position<T>;

        // type

        /// Constructs an empty list.
        uninode_list_v3 () :
            head_ {}
        {
            head_ = new uninode<T>;
            head_->link = head_;
        }

        /// Moves that list into this list.
        uninode_list_v3 (uninode_list_v3 && that) :
            head_ { that.head_ }
        {
            that.head_ = new uninode<T>;
            that.head_->link = that.head_;
        }

        /// Moves that list into this list.
        auto& operator= (uninode_list_v3 && that) noexcept
        {
            using std::swap;
            swap(head_,that.head_);
            return *this;
        }

        uninode_list_v3 (uninode_list_v3 const & that) = delete;

        auto operator= (uninode_list_v3 const & that) = delete;

        /// Destructs this list.
        ~uninode_list_v3 ()
        {
            auto node = head_->link;
            while (node != head_) {
                auto next = node->link;
                delete node;
                node = next;
            }
            delete head_;
        }

        // factories

        /// Creates a list filled with copies of a value.
        ///
        /// Provides: distance(first,last) == count
        template <copyable TT>
        static
        auto filled (TT value, size_t count)
        {
            auto head = new uninode<TT>;
            auto current = head;
            while (count > 0) {
                auto next = new uninode<TT>;
                next->content = value;
                current->link = next;
                current = next;
                --count;
            }
            current->link = head;
            return uninode_list<TT>(head);
        }

        // properties

        auto is_empty () const
        {
            return head_->link == head_;
        }

        auto not_empty () const
        {
            return head_->link != head_;
        }

        // positions

        /// Position before the first element.
        auto before_first ()
        {
            return uninode_list_position<T>(head_);
        }

        /// Position of the first element.
        auto first ()
        {
            return uninode_list_position<T>(head_->link);
        }

        /// Position after the last element.
        auto after_last ()
        {
            return uninode_list_position<T>(head_);
        }

        // update

        /// Inserts element at first position.
        auto insert_first (T value) requires copyable<T>
        {
            auto inserted = new uninode<T>(head_->link,value);
            head_->link = inserted;
            return uninode_list_position<T>(inserted);
        }

        /// Inserts element after position.
        ///
        /// Requires: first <= position < limit
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
            auto erased = head_->link;
            auto next = erased->link;
            head_->link = next;
            delete erased;
        }

        /// Erases element after position.
        ///
        /// Requires: first <= position < limit
        auto remove_after (position_type position)
        {
            auto previous = position.node;
            auto erased = previous->link;
            auto next = erased->link;
            previous->link = next;
            delete erased;
        }
    };
}