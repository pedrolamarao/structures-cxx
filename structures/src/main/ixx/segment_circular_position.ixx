export module br.dev.pedrolamarao.structures:segment_circular_position;

namespace br::dev::pedrolamarao::structures
{
    /// Circular position on a memory segment.
    export
    template <typename T>
    class segment_circular_position
    {
        T* base;

        T* address;

        T* limit;

        explicit segment_circular_position (T* base, T* position, T* limit) :
            base { base }, address { position }, limit { limit }
        { }

    public:

        using value_type = T;

        auto is_equal (segment_circular_position that)
        {
            return address == that.address;
        }

        auto not_equal (segment_circular_position that)
        {
            return address != that.address;
        }

        // ---

        auto load ()
        {
            return *address;
        }

        auto& store ()
        {
            return *address;
        }

        // ---

        // requires: ?
        auto next ()
        {
            auto next = address + 1;
            if (next == limit) next = base;
            return segment_circular_position(base,next,limit);
        }

        // requires: ?
        auto previous ()
        {
            auto current = address == base ? limit : address;
            return segment_circular_position(base,current - 1,limit);
        }

        template <typename>
        friend class segment_hoop_v1;
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