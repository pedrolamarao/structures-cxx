module;

#include <concepts>

export module br.dev.pedrolamarao.structures:position;

using namespace std;

namespace br::dev::pedrolamarao::structures
{
    template <typename Type>
    concept referenceable = requires (Type type)
    {
        { static_cast<Type &>(type) };
    };

    /// Structural position.
    export
    template <typename Position>
    concept position = requires (Position position)
    {
        { is_equal(position,position) } -> convertible_to<bool>;

        { not_equal(position,position) } -> convertible_to<bool>;

        { load(position) } -> referenceable;
    };

    /// Value type stored in a position.
    export
    template <position P>
    using stored_type_of = decltype( load(P()) );

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