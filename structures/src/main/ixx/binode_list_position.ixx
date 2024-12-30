export module br.dev.pedrolamarao.structures:binode_list_position;

import :binode;

namespace br::dev::pedrolamarao::structures
{
    /// Position on bi-link node lists.
    export
    template <typename T>
    class binode_list_position
    {
        binode<T> * node;

        explicit binode_list_position (binode<T> * p) : node{p} {}

    public:

        using value_type = T;

        binode_list_position () = delete;

        auto is_equal (binode_list_position that)
        {
            return node == that.node;
        }

        auto not_equal (binode_list_position that)
        {
            return node != that.node;
        }

        // ---

        auto load ()
        {
            return node->content;
        }

        // ---

        // requires: current != nullptr
        auto next ()
        {
            return binode_list_position(node->right);
        }

        // requires: current != nullptr
        auto previous ()
        {
            return binode_list_position(node->left);
        }

        template <typename>
        friend class binode_list_v1;

        template <typename>
        friend class binode_list_v2;

        template <typename>
        friend class binode_list_v3;
    };

    export
    template <typename T>
    auto is_equal (binode_list_position<T> x, binode_list_position<T> y)
    {
        return x.is_equal(y);
    }

    export
    template <typename T>
    auto not_equal (binode_list_position<T> x, binode_list_position<T> y)
    {
        return x.not_equal(y);
    }

    export
    template <typename T>
    auto load (binode_list_position<T> x)
    {
        return x.load();
    }

    export
    template <typename T>
    auto next (binode_list_position<T> x)
    {
        return x.next();
    }

    export
    template <typename T>
    auto previous (binode_list_position<T> x)
    {
        return x.previous();
    }
}