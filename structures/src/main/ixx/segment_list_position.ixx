export module br.dev.pedrolamarao.structures:segment_list_position;

namespace br::dev::pedrolamarao::structures
{
    /// Position on segment lists.
    export
    template <typename T>
    class segment_list_position
    {
        template <typename>
        friend class segment_list;

        T * current;

        explicit segment_list_position (T * c) :
            current{c}
        { }

    public:

        using value_type = T;

        auto is_equal (segment_list_position that)
        {
            return current == that.current;
        }

        auto not_equal (segment_list_position that)
        {
            return current != that.current;
        }

        auto load ()
        {
            return *current;
        }

        // requires: ?
        auto next ()
        {
            return segment_list_position(current+1);
        }
    };

    export
    template <typename T>
    auto is_equal (segment_list_position<T> x, segment_list_position<T> y)
    {
        return x.is_equal(y);
    }

    export
    template <typename T>
    auto not_equal (segment_list_position<T> x, segment_list_position<T> y)
    {
        return x.not_equal(y);
    }

    export
    template <typename T>
    auto load (segment_list_position<T> x)
    {
        return x.load();
    }

    export
    template <typename T>
    auto next (segment_list_position<T> x)
    {
        return x.next();
    }
}