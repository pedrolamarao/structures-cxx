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
            uninode_list{nullptr}
        { }

        uninode_list (uninode_list && that) noexcept :
            root_{that.root_}
        {
            that.root_ = nullptr;
        }

        auto operator= (uninode_list && that) noexcept
        {
            root_ = that.root_;
            that.root_ = nullptr;
            return *this;
        }

        uninode_list (uninode_list const & that) = delete;

        auto operator= (uninode_list const & that) = delete;

        ~uninode_list ()
        {
            while (root_ != nullptr) {
                auto next = root_->link;
                delete root_;
                root_ = next;
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
            uninode<TT> * root = nullptr;
            if (count > 0) {
                root = new uninode<TT>(nullptr,value);
                --count;
            }
            uninode<TT> * current = root;
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
            return uninode_list_position<T>(root_);
        }

        auto is_empty () const
        {
            return root_ == nullptr;
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
        auto erase_after (position_type position)
        {
            auto previous = position.node;
            if (previous == nullptr)
                return;
            auto target = previous->link;
            if (target == nullptr)
                return;
            previous->link = target->link;
            delete target;
        }

        /// Erases element at first position.
        auto erase_first ()
        {
            if (root_ == nullptr)
                return;
            auto target = root_;
            root_ = root_->link;
            delete target;
        }

        /// Inserts element after position.
        ///
        /// Requires: first < position
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
            auto next = root_ != nullptr ? root_ : nullptr;
            root_ = new uninode<T>(next,value);
            return uninode_list_position<T>(root_);
        }

        // requires: ?
        void store (uninode_list_position<T> position, T value)
        {
            position.node->content = value;
        }
    };
}