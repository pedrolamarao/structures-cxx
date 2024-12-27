module;

#include <concepts>

export module br.dev.pedrolamarao.structures:queue;

import :position;

using namespace std;

namespace br::dev::pedrolamarao::structures
{
    /// Linear structure with insertion at back and access at front.
    export
    template <typename Structure>
    concept queue = requires (Structure structure)
    {
        requires default_initializable<Structure>;

        typename Structure::value_type;

        requires default_initializable< typename Structure::value_type >;

        { structure.front() } -> same_as< typename Structure::value_type >;

        { structure.remove() };

        requires requires (typename Structure::value_type value)
        {
            { structure.insert(value) };
        };
    };
}