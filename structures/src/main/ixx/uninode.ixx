export module br.dev.pedrolamarao.structures:uninode;

namespace br::dev::pedrolamarao::structures
{
    /// Sparse memory positions explicitly related by one "links".
    export
    template <typename T>
    struct uninode
    {
        uninode * link;
        T         content;
    };
}