module;

#include <concepts>

export module br.dev.pedrolamarao.structures;

export import :binode;
export import :binode_deck;
export import :binode_list;
export import :binode_list_position;

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
    template <typename List>
    concept list = requires (List list)
    {
        typename List::value_type;

        default_initializable< typename List::value_type >;

        typename List::position_type;

        position< typename List::position_type >;

        same_as< typename List::value_type, typename List::position_type::value_type >;

        { list.before_first() } -> same_as< typename List::position_type >;

        { list.first() } -> same_as< typename List::position_type >;

        { list.last() } -> same_as< typename List::position_type >;

        { list.after_last() } -> same_as< typename List::position_type >;

        requires requires (typename List::position_type position, typename List::value_type value)
        {
            { list.erase_after(position) };

            { list.insert_after(position,value) } -> same_as< typename List::position_type >;
        };
    };

    /// Linear structure with access to the bottom and the top.
    export
    template <typename Deck>
    concept deck = requires (Deck deck)
    {
        typename Deck::value_type;

        default_initializable< typename Deck::value_type >;

        { deck.bottom() } -> same_as< typename Deck::value_type >;

        { deck.top() } -> same_as< typename Deck::value_type >;

        { deck.erase_bottom() };

        { deck.erase_top() };

        requires requires (typename Deck::value_type value)
        {
            { deck.insert_bottom(value) };

            { deck.insert_top(value) };
        };
    };

    /// Linear structure with access to the top.
    export
    template <typename Stack>
    concept stack = requires (Stack stack)
    {
        typename Stack::value_type;

        default_initializable< typename Stack::value_type >;

        { stack.top() } -> same_as< typename Stack::value_type >;

        { stack.erase() };

        requires requires (typename Stack::value_type value)
        {
            { stack.insert(value) };
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