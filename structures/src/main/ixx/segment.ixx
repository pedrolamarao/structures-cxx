module;

#include <concepts>

export module br.dev.pedrolamarao.structures:segment;

using std::copyable;
using std::movable;

namespace br::dev::pedrolamarao::structures
{
    /// Contiguous memory positions implicitly related by "offset".
    export
    template <typename T>
    struct segment
    {
        T*     base   {};
        size_t length {};
    };

    /// Shift memory segment "words" one position to the left.
    ///
    /// The leftmost "word" is lost.
    ///
    /// Requires: 0 < first < limit <= segment.length
    export
    template <typename T>
    void shift_left (segment<T>& segment, size_t first, size_t limit) requires copyable<T>
    {
        for (auto i = first, j = first+1; j != limit; ++i, ++j)
            segment.base[i] = segment.base[j];
    }

    /// Shift memory segment "words" one position to the right.
    ///
    /// The rightmost "word" is lost.
    ///
    /// Requires: 0 <= first < limit < segment.length
    export
    template <typename T>
    void shift_right (segment<T>& segment, size_t first, size_t limit) requires copyable<T>
    {
        for (auto i = limit; i != first; --i)
            segment.base[i] = segment.base[i-1];
    }
}
