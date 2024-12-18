export module br.dev.pedrolamarao.structures:segment;

namespace br::dev::pedrolamarao::structures
{
    /// Memory segment.
    export
    template <typename T>
    struct segment
    {
        T*     base   {};
        size_t length {};
    };
}