export module br.dev.pedrolamarao.structures:segment;

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
}