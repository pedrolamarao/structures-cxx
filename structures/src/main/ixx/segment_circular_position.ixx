export module br.dev.pedrolamarao.structures:segment_circular_position;

namespace br::dev::pedrolamarao::structures
{
    /// Circular position on a memory segment.
    export
    template <typename T>
    class segment_circular_position
    {
        T* base_;

        T* position_;

        T* limit_;

        explicit segment_circular_position (T* base, T* position, T* limit) :
            base_ { base }, position_ { position }, limit_ { limit }
        { }

    public:

        using value_type = T;

        auto is_equal (segment_circular_position that)
        {
            return position_ == that.position_;
        }

        auto not_equal (segment_circular_position that)
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
        auto next ()
        {
            auto p = position_ + 1;
            if (p == limit_) p = base_;
            return segment_circular_position(base_,p,limit_);
        }

        // requires: ?
        auto previous ()
        {
            auto p = position_ == base_ ? position_ : limit_;
            return segment_circular_position(p - 1);
        }
    };

    export
    template <typename T>
    auto is_equal (segment_circular_position<T> x, segment_circular_position<T> y)
    {
        return x.is_equal(y);
    }

    export
    template <typename T>
    auto not_equal (segment_circular_position<T> x, segment_circular_position<T> y)
    {
        return x.not_equal(y);
    }

    export
    template <typename T>
    auto next (segment_circular_position<T> x)
    {
        return x.next();
    }

    export
    template <typename T>
    auto previous (segment_circular_position<T> x)
    {
        return x.previous();
    }

    export
    template <typename T>
    auto load (segment_circular_position<T> x)
    {
        return x.load();
    }

    export
    template <typename T>
    auto& store (segment_circular_position<T> x)
    {
        return x.store();
    }
}