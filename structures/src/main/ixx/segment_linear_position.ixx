export module br.dev.pedrolamarao.structures:segment_list_position;

namespace br::dev::pedrolamarao::structures
{
    /// Linear position on a memory segment.
    export
    template <typename T>
    class segment_linear_position
    {
        T* address_;

        explicit segment_linear_position (T* position) :
            address_ { position }
        { }

    public:

        using value_type = T;

        auto is_equal (segment_linear_position that)
        {
            return address_ == that.address_;
        }

        auto not_equal (segment_linear_position that)
        {
            return address_ != that.address_;
        }

        // ---

        auto load ()
        {
            return *address_;
        }

        auto& store ()
        {
            return *address_;
        }

        // ---

        // requires: ?
        auto next ()
        {
            return segment_linear_position(address_+1);
        }

        // requires: ?
        auto previous ()
        {
            return segment_linear_position(address_-1);
        }

        template <typename>
        friend class segment_list_v1;

        template <typename>
        friend class segment_list_v2;

        template <typename>
        friend class segment_list_v3;
    };

    export
    template <typename T>
    auto is_equal (segment_linear_position<T> x, segment_linear_position<T> y)
    {
        return x.is_equal(y);
    }

    export
    template <typename T>
    auto not_equal (segment_linear_position<T> x, segment_linear_position<T> y)
    {
        return x.not_equal(y);
    }

    export
    template <typename T>
    auto next (segment_linear_position<T> x)
    {
        return x.next();
    }

    export
    template <typename T>
    auto previous (segment_linear_position<T> x)
    {
        return x.previous();
    }

    export
    template <typename T>
    auto load (segment_linear_position<T> x)
    {
        return x.load();
    }

    export
    template <typename T>
    auto& store (segment_linear_position<T> x)
    {
        return x.store();
    }
}