module;

#include <concepts>

export module br.dev.pedrolamarao.structures:deck;

import :position;

using namespace std;

namespace br::dev::pedrolamarao::structures
{
    /// Linear structure with access to the bottom and the top.
    export
    template <typename Structure>
    concept deck = requires (Structure structure)
    {
        requires default_initializable<Structure>;

        typename Structure::value_type;

        requires default_initializable< typename Structure::value_type >;

        { structure.bottom() } -> same_as< typename Structure::value_type >;

        { structure.top() } -> same_as< typename Structure::value_type >;

        { structure.erase_bottom() };

        { structure.erase_top() };

        requires requires (typename Structure::value_type value)
        {
            { structure.insert_bottom(value) };

            { structure.insert_top(value) };
        };
    };
}