module;

#include <concepts>

export module br.dev.pedrolamarao.structures:list;

import :position;

using namespace std;

namespace br::dev::pedrolamarao::structures
{
    /// Linear composite structure allowing "random" insertion and removal.
    ///
    /// Composite structures are made of parts with unique positions.
    ///
    /// Linear structures are composed of positions with a single predecessor and successor.
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

        requires requires (typename Structure::position_type position, typename Structure::value_type value)
        {
            { structure.erase_after(position) };

            { structure.insert_after(position,value) } -> same_as< typename Structure::position_type >;
        };
    };
}