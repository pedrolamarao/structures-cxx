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

        requires movable<Structure>;

        typename Structure::value_type;

        requires default_initializable< typename Structure::value_type >;

        typename Structure::position_type;

        requires position< typename Structure::position_type >;

        requires same_as< typename Structure::value_type, typename Structure::position_type::value_type >;

        // factories

        requires requires (typename Structure::value_type v, size_t z)
        {
            { Structure::filled(v,z) } -> same_as<Structure>;
        };

        // positions

        { structure.first() } -> same_as< typename Structure::position_type >;

        { structure.after_last() } -> same_as< typename Structure::position_type >;

        // operations

        requires requires (typename Structure::position_type position, typename Structure::value_type value)
        {
            { structure.insert_first(value) } -> same_as< typename Structure::position_type >;

            { structure.insert_after(position,value) } -> same_as< typename Structure::position_type >;

            { structure.remove_first() };

            { structure.remove_after(position) };
        };
    };
}