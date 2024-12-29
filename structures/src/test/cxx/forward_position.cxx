#include <gmock/gmock.h>

import br.dev.pedrolamarao.structures;

using namespace br::dev::pedrolamarao;
using namespace br::dev::pedrolamarao::structures;

enum class thing : unsigned
{
    zero       =  0,
    one        =  1,
    two        =  2,
    three      =  3,
    forty_nine = 49,
};

auto is_equal (thing* x, thing* y) { return x == y; }

auto not_equal (thing* x, thing* y) { return x != y; }

auto load (thing* position) { return *position; }

auto next (thing* position) { return position + 1; }

TEST(forward_position,distance)
{
    thing things [] { thing::zero, thing::one, thing::two, thing::three };
    ASSERT_EQ( 0, distance(things,things)     );
    ASSERT_EQ( 4, distance(things,things + 4) );
}

TEST(forward_position,visit)
{
    thing things [] { thing::zero, thing::one, thing::two, thing::three };
    size_t i = 0;
    visit(things,things+4,[&] (auto value)
    {
        ASSERT_EQ( value, things[i++] );
    });
}

TEST(forward_position,count)
{
    thing things [] { thing::zero, thing::one, thing::two, thing::three };
    ASSERT_EQ( 1, count(things,things + 4, thing::two ) );
}

TEST(forward_position,count_if)
{
    thing things [] { thing::zero, thing::one, thing::two, thing::three };
    ASSERT_EQ( 3, count_if(things,things + 4, [] (auto value) { return value < thing::three; } ) );
}

TEST(forward_position,search)
{
    thing things [] { thing::zero, thing::one, thing::two, thing::three };
    ASSERT_EQ( things + 2, search(things,things + 4, thing::two ) );
}

TEST(forward_position,search_if)
{
    thing things [] { thing::zero, thing::one, thing::two, thing::three };
    ASSERT_EQ( things + 2, search_if(things,things + 4, [] (auto value) { return value == thing::two; } ) );
}