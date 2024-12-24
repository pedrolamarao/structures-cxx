export module br.dev.pedrolamarao.structures:binode;

namespace br::dev::pedrolamarao::structures
{
    /// Sparse memory positions explicitly related by two "links".
    export
    template <typename T>
    struct binode
    {
        binode * left;
        binode * right;
        T        content;
    };

    template <typename TT>
    void link (binode<TT>* x, binode<TT>* y)
    {
        x->right = y;
        y->left = x;
    }
}