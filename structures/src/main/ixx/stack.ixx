module;

#include <concepts>

export module br.dev.pedrolamarao.structures:stack;

import :position;

using namespace std;

namespace br::dev::pedrolamarao::structures
{
    /// Linear structure with access to the top.
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