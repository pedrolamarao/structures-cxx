module;

#include <concepts>

export module br.dev.pedrolamarao.structures:forward_position;

import :position;

using std::equality_comparable;
using std::invocable;
using std::predicate;

namespace br::dev::pedrolamarao::structures
{
    /// Structural position with forward traversal.
    export
    template <typename Position>
    concept forward_position = structures::position<Position> && requires (Position position)
    {
        { next(position) } -> std::convertible_to<Position>;
    };

    /// Terminates if, either:
    /// first equals target or
    /// there is a successor of first that equals target;
    /// otherwise does not terminate.
    template <forward_position Position>
    bool is_reachable (Position first, Position target);

    export
    template <forward_position Position>
    auto distance (Position first, Position limit) -> size_t
    // requires is_reachable(first,limit)
    {
        size_t counter {};
        while (not_equal(first,limit)) {
            ++counter;
            first = next(first);
        }
        return counter;
    }

    export
    template <forward_position Position, invocable<stored_type_of<Position>> Visitor>
    auto visit (Position first, Position limit, Visitor visit)
    // requires is_reachable(first,limit)
    {
        while (not_equal(first,limit)) {
            visit(load(first));
            first = next(first);
        }
    }

    export
    template <forward_position Position>
    auto count (Position first, Position limit, stored_type_of<Position> value) -> size_t
    // requires is_reachable(first,limit)
    requires equality_comparable< stored_type_of<Position> >
    {
        size_t counter {};
        while (not_equal(first,limit)) {
            if (load(first) == value)
                ++counter;
            first = next(first);
        }
        return counter;
    }

    export
    template <forward_position Position, predicate< stored_type_of<Position> > Predicate>
    auto count_if (Position first, Position limit, Predicate test) -> size_t
    // requires is_reachable(first,limit)
    {
        size_t counter {};
        while (not_equal(first,limit)) {
            if (test(load(first)))
                ++counter;
            first = next(first);
        }
        return counter;
    }

    export
    template <forward_position Position>
    auto search (Position first, Position limit, stored_type_of<Position> value)
    // requires is_reachable(first,limit)
    requires equality_comparable< stored_type_of<Position> >
    {
        while (not_equal(first,limit) && load(first) != value)
            first = next(first);
        return first;
    }

    export
    template <forward_position Position, predicate< stored_type_of<Position> > Predicate>
    auto search_if (Position first, Position limit, Predicate test)
    // requires is_reachable(first,limit)
    {
        while (not_equal(first,limit) && !test(load(first)))
            first = next(first);
        return first;
    }
}
