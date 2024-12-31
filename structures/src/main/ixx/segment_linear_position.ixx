export module br.dev.pedrolamarao.structures:segment_list_position;

namespace br::dev::pedrolamarao::structures
{
    /// Linear position on a memory segment.
    export
    template <typename T>
    class segment_linear_position
    {
        template <typename>
        friend class segment_list;

        T* position_;

        explicit segment_linear_position (T* position) :
            position_ { position }
        { }

    public:

        using value_type = T;

        auto is_equal (segment_linear_position that)
        {
            return position_ == that.position_;
        }

        auto not_equal (segment_linear_position that)
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
            return segment_linear_position(position_+1);
        }

        // requires: ?
        auto previous ()
        {
            return segment_linear_position(position_-1);
        }
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