module;

#include <concepts>

export module br.dev.pedrolamarao.structures:position;

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

    export
    template <position P>
    auto operator== (P x, P y)
    {
        return x.is_equal(y);
    }

    export
    template <position P>
    auto operator!= (P x, P y)
    {
        return x.not_equal(y);
    }
}