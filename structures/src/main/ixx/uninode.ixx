export module br.dev.pedrolamarao.structures:uninode;

namespace br::dev::pedrolamarao::structures
{
    /// Memory node with one link.
    export
    template <typename T>
    struct uninode
    {
        uninode * link;
        T         content;
    };
}