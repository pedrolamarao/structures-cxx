module;

#include <concepts>

export module br.dev.pedrolamarao.structures:queue;

import :position;

using namespace std;

namespace br::dev::pedrolamarao::structures
{
    /// Linear composite structure with insertion at back and access at front.
    ///
    /// Composite structures are made of parts with unique positions.
    ///
    /// Linear structures are composed of positions with a single predecessor and successor.
    ///
    /// Queues allow inserting only at the first position and loading or erasing at the last position,
    /// respectively called the back and the front.
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