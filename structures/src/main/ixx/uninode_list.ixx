module;

#include <concepts>

export module br.dev.pedrolamarao.structures:uninode_list;

import :uninode;
import :uninode_list_position;

using std::copyable;

namespace br::dev::pedrolamarao::structures
{
    /// List on uni-link nodes.
    export
    template <typename T>
    class uninode_list
    {
        uninode<T> * root_;

        explicit uninode_list (uninode<T> * r) noexcept : root_{r} {}

    public:

        using value_type = T;

        using position_type = uninode_list_position<T>;

        // type

        uninode_list () noexcept :
            root_{}
        {
            root_ = new uninode<T>(nullptr,{});
        }

        uninode_list (uninode_list && that) noexcept :
            root_{that.root_}
        {
            that.root_ = new uninode<T>(nullptr,{});
        }

        auto operator= (uninode_list && that) noexcept
        {
            using std::swap;
            swap(root_,that.root_);
            return *this;
        }

        uninode_list (uninode_list const & that) = delete;

        auto operator= (uninode_list const & that) = delete;

        ~uninode_list ()
        {
            auto node = root_;
            while (node != nullptr) {
                auto next = node->link;
                delete node;
                node = next;
            }
        }

        // factories

        /**
         * Creates a list filled with copies of a value.
         */
        template <typename TT>
        requires copyable<TT>
        static
        auto filled (TT value, size_t count)
        {
            auto root = new uninode<TT>(nullptr,{});
            auto current = root;
            while (count > 0) {
                auto next = new uninode<TT>(nullptr,value);
                current->link = next;
                current = next;
                --count;
            }
            return uninode_list<TT>(root);
        }

        // query

        auto first ()
        {
            return uninode_list_position<T>(root_->link);
        }

        auto is_empty () const
        {
            return root_->link == nullptr;
        }

        // requires: position in [first,limit)
        auto load (uninode_list_position<T> position) const
        {
            return position.node->content;
        }

        auto limit ()
        {
            return uninode_list_position<T>(nullptr);
        }

        // update

        /// Erases element after position.
        ///
        /// Requires: first <= position < limit
        auto erase_after (position_type position)
        {
            auto previous = position.node;
            auto target = previous->link;
            auto next = target == nullptr ? nullptr : target->link;
            previous->link = next;
            delete target;
        }

        /// Erases element at first position.
        auto erase_first ()
        {
            auto target = root_->link;
            auto next = target == nullptr ? nullptr : target->link;
            root_->link = next;
            delete target;
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

        /// Inserts element at first position.
        auto insert_first (T value) requires copyable<T>
        {
            auto inserted = new uninode<T>(root_->link,value);
            root_->link = inserted;
            return uninode_list_position<T>(inserted);
        }

        // requires: ?
        void store (uninode_list_position<T> position, T value)
        {
            position.node->content = value;
        }
    };
}