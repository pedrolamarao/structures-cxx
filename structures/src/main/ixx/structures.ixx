module;

#include <concepts>

export module br.dev.pedrolamarao.structures;

export import :segment;
export import :segment_list;
export import :segment_list_position;

export import :uninode;
export import :uninode_list;
export import :uninode_list_position;

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