module;

#include <concepts>

export module br.dev.pedrolamarao.structures;

export import :binode;
export import :binode_deck;
export import :binode_list;
export import :binode_list_position;
export import :binode_queue;

export import :segment;
export import :segment_deck;
export import :segment_list;
export import :segment_list_position;
export import :segment_stack;

export import :uninode;
export import :uninode_list;
export import :uninode_list_position;
export import :uninode_stack;

using namespace std;

namespace br::dev::pedrolamarao::structures
{
    /// Structural position.
    export
    template <typename Position>
    concept position = requires (Position position)
    {
        typename Position::value_type;
        { is_equal(position,position) } -> convertible_to<bool>;
        { not_equal(position,position) } -> convertible_to<bool>;
        { load(position) } -> convertible_to<typename Position::value_type>;
    };

    export
    template <position P>
    auto operator== (P x, P y)
    {
        return x.is_equal(y);
    }

    export
    template <position P>
    auto operator!= (P x, P y)
    {
        return x.not_equal(y);
    }

    /// Linear structure with "random" access.
    export
    template <typename Structure>
    concept list = requires (Structure structure)
    {
        default_initializable<Structure>;

        typename Structure::value_type;

        default_initializable< typename Structure::value_type >;

        typename Structure::position_type;

        position< typename Structure::position_type >;

        same_as< typename Structure::value_type, typename Structure::position_type::value_type >;

        { structure.before_first() } -> same_as< typename Structure::position_type >;

        { structure.first() } -> same_as< typename Structure::position_type >;

        { structure.last() } -> same_as< typename Structure::position_type >;

        { structure.after_last() } -> same_as< typename Structure::position_type >;

        requires requires (typename Structure::position_type position, typename Structure::value_type value)
        {
            { structure.erase_after(position) };

            { structure.insert_after(position,value) } -> same_as< typename Structure::position_type >;
        };
    };

    /// Linear structure with access to the bottom and the top.
    export
    template <typename Structure>
    concept deck = requires (Structure structure)
    {
        default_initializable<Structure>;

        typename Structure::value_type;

        default_initializable< typename Structure::value_type >;

        { structure.bottom() } -> same_as< typename Structure::value_type >;

        { structure.top() } -> same_as< typename Structure::value_type >;

        { structure.erase_bottom() };

        { structure.erase_top() };

        requires requires (typename Structure::value_type value)
        {
            { structure.insert_bottom(value) };

            { structure.insert_top(value) };
        };
    };

    /// Linear structure with access to the top.
    export
    template <typename Structure>
    concept stack = requires (Structure structure)
    {
        default_initializable<Structure>;

        typename Structure::value_type;

        default_initializable< typename Structure::value_type >;

        { structure.top() } -> same_as< typename Structure::value_type >;

        { structure.erase() };

        requires requires (typename Structure::value_type value)
        {
            { structure.insert(value) };
        };
    };

    /// Linear structure with insertion at back and access at front.
    export
    template <typename Structure>
    concept queue = requires (Structure structure)
    {
        default_initializable<Structure>;

        typename Structure::value_type;

        default_initializable< typename Structure::value_type >;

        { structure.front() } -> same_as< typename Structure::value_type >;

        { structure.remove() };

        requires requires (typename Structure::value_type value)
        {
            { structure.insert(value) };
        };
    };

    /// Structural position with forward traversal.
    export
    template <typename Position>
    concept forward_position = position<Position> && requires (Position position)
    {
        { next(position) } -> convertible_to<Position>;
    };

    /// Distance from first to limit.
    export
    template <typename Position>
    requires forward_position<Position>
    auto distance (Position position, Position limit) -> size_t
    {
        size_t counter {};
        while (not_equal(position,limit)) {
            ++counter;
            position = next(position);
        }
        return counter;
    }

    export
    template <typename Position>
    requires forward_position<Position> && equality_comparable<typename Position::value_type>
    auto find (Position position, Position limit, typename Position::value_type value)
    {
        while (not_equal(position,limit) && load(position) != value)
            position = next(position);
        return position;
    }
}