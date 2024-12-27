module;

#include <concepts>

export module br.dev.pedrolamarao.structures:stack;

import :position;

using namespace std;

namespace br::dev::pedrolamarao::structures
{
    /// Linear composite structure with access to the top.
    ///
    /// Composite structures are made of parts with unique positions.
    ///
    /// Linear structures are composed of positions with a single predecessor and successor.
    ///
    /// Stacks allow access only at the last position, called the top.
    export
    template <typename Structure>
    concept stack = requires (Structure structure)
    {
        requires default_initializable<Structure>;

        typename Structure::value_type;

        requires default_initializable< typename Structure::value_type >;

        { structure.top() } -> same_as< typename Structure::value_type >;

        { structure.erase() };

        requires requires (typename Structure::value_type value)
        {
            { structure.insert(value) };
        };
    };
}