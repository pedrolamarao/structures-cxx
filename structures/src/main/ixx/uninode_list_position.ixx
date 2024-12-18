export module br.dev.pedrolamarao.structures:uninode_list_position;

import :uninode;

namespace br::dev::pedrolamarao::structures
{
    /// Position on uni-link node lists.
    export
    template <typename T>
    class uninode_list_position
    {
        template <typename>
        friend class uninode_list;

        uninode<T> * node;

        explicit uninode_list_position (uninode<T> * p) : node{p} {}

    public:

        using value_type = T;

        // regular

        auto is_equal (uninode_list_position that)
        {
            return node == that.node;
        }

        auto not_equal (uninode_list_position that)
        {
            return node != that.node;
        }

        auto load ()
        {
            return node->content;
        }

        // requires: current != nullptr
        auto next ()
        {
            return uninode_list_position(node->link);
        }
    };

    export
    template <typename T>
    auto is_equal (uninode_list_position<T> x, uninode_list_position<T> y)
    {
        return x.is_equal(y);
    }

    export
    template <typename T>
    auto operator== (uninode_list_position<T> x, uninode_list_position<T> y)
    {
        return x.is_equal(y);
    }

    export
    template <typename T>
    auto not_equal (uninode_list_position<T> x, uninode_list_position<T> y)
    {
        return x.not_equal(y);
    }

    export
    template <typename T>
    auto operator!= (uninode_list_position<T> x, uninode_list_position<T> y)
    {
        return x.not_equal(y);
    }

    export
    template <typename T>
    auto load (uninode_list_position<T> x)
    {
        return x.load();
    }

    export
    template <typename T>
    auto next (uninode_list_position<T> x)
    {
        return x.next();
    }
}