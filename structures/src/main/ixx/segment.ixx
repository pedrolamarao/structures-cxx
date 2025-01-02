module;

#include <concepts>

export module br.dev.pedrolamarao.structures:segment;

using std::copyable;
using std::movable;

namespace br::dev::pedrolamarao::structures
{
    /// Memory segments are sequences of memory cells identified by memory addresses.
    export
    template <typename T>
    struct segment
    {
        T*     base   {};
        size_t length {};
    };

    /// Shifts memory cells one position to the left.
    ///
    /// The content of the leftmost cell is destroyed.
    export
    template <typename T>
    void shift_left (segment<T>& segment, size_t first, size_t limit)
    requires copyable<T>
    // requires: 0 < first <= limit <= segment.length
    {
        for (auto i = first, j = first+1; j < limit; ++i, ++j)
            segment.base[i] = segment.base[j];
    }

    /// Shifts memory cells one position to the right.
    ///
    /// The content of the rightmost cell is destroyed.
    export
    template <typename T>
    void shift_right (segment<T>& segment, size_t first, size_t limit)
    requires copyable<T>
    // requires: 0 <= first << limit < segment.length
    {
        for (auto i = limit, j = limit - 1; i > first; --i, --j)
            segment.base[i] = segment.base[j];
    }
}
