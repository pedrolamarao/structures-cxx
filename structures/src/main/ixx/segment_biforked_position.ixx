export module br.dev.pedrolamarao.structures:segment_biforked_position;

namespace br::dev::pedrolamarao::structures
{
    /// Bi-forked position on a memory segment.
    export
    template <typename T>
    class segment_biforked_position
    {
        T* position_;

        explicit segment_biforked_position (T* position) :
            position_ { position }
        { }

    public:

        using value_type = T;

        auto is_equal (segment_biforked_position that)
        {
            return position_ == that.position_;
        }

        auto not_equal (segment_biforked_position that)
        {
            return position_ != that.position_;
        }

        // ---

        auto load ()
        {
            return *position_;
        }

        auto& store ()
        {
            return *position_;
        }

        // ---

        // requires: ?
        auto up ()
        {
            auto p = ( position_ - 1 ) >> 1;
            return segment_biforked_position(p);
        }

        // requires: ?
        auto left ()
        {
            auto p = ( position_ << 1 ) + 1;
            return segment_biforked_position(p);
        }

        // requires: ?
        auto right ()
        {
            auto p = ( position_ << 1 ) + 2;
            return segment_biforked_position(p);
        }
    };

    export
    template <typename T>
    auto is_equal (segment_biforked_position<T> x, segment_biforked_position<T> y)
    {
        return x.is_equal(y);
    }

    export
    template <typename T>
    auto not_equal (segment_biforked_position<T> x, segment_biforked_position<T> y)
    {
        return x.not_equal(y);
    }

    export
    template <typename T>
    auto left (segment_biforked_position<T> x)
    {
        return x.left();
    }

    export
    template <typename T>
    auto right (segment_biforked_position<T> x)
    {
        return x.right();
    }

    export
    template <typename T>
    auto up (segment_biforked_position<T> x)
    {
        return x.up();
    }

    export
    template <typename T>
    auto load (segment_biforked_position<T> x)
    {
        return x.load();
    }

    export
    template <typename T>
    auto& store (segment_biforked_position<T> x)
    {
        return x.store();
    }
}