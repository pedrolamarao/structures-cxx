module;

#include <concepts>

export module br.dev.pedrolamarao.structures:list;

import :position;

using namespace std;

namespace br::dev::pedrolamarao::structures
{
    /// Linear composite structure allowing "random" access.
    ///
    /// Composite structures are made of parts with unique positions.
    ///
    /// Linear structures' parts are like points in a line,
    /// each position having a single predecessor and a single successor.
    export
    template <typename Structure>
    concept list = requires (Structure structure)
    {
        requires default_initializable<Structure>;

        typename Structure::value_type;

        requires default_initializable< typename Structure::value_type >;

        typename Structure::position_type;

        requires position< typename Structure::position_type >;

        requires same_as< typename Structure::value_type, typename Structure::position_type::value_type >;

        { structure.before_first() } -> same_as< typename Structure::position_type >;

        { structure.first() } -> same_as< typename Structure::position_type >;

        { structure.after_last() } -> same_as< typename Structure::position_type >;

        requires requires (typename Structure::position_type p1, typename Structure::position_type p2)
        {
            { ( next(p1) == next(p2) ) == ( p1 == p2 ) };
        };

        requires requires (typename Structure::position_type position, typename Structure::value_type value)
        {
            { structure.erase_after(position) };

            { structure.insert_after(position,value) } -> same_as< typename Structure::position_type >;
        };
    };
}