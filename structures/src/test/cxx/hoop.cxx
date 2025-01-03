#include <gmock/gmock.h>

import br.dev.pedrolamarao.structures;

using namespace br::dev::pedrolamarao;
using namespace br::dev::pedrolamarao::structures;
using namespace std;

enum class thing
{
    zero       =  0u,
    one        =  1u,
    two        =  2u,
    three      =  3u,
    forty_nine = 49u,
};

template <typename T>
struct hoop_test : testing::Test
{
    static_assert( hoop<T> );
};

using types = testing::Types<
    binode_hoop_v1<thing>,
    segment_hoop_v1<thing>
>;

TYPED_TEST_SUITE(hoop_test,types);

TYPED_TEST(hoop_test,defaultt)
{
    TypeParam hoop;
    ASSERT_TRUE(hoop.is_empty());
}

TYPED_TEST(hoop_test,filled)
{
    auto empty = TypeParam::filled(thing::forty_nine,0);
    ASSERT_TRUE( empty.is_empty() );

    auto one = TypeParam::filled(thing::one,1);
    ASSERT_TRUE( one.not_empty() );
    ASSERT_EQ( one.first(), next(one.first()) );

    auto filled = TypeParam::filled(thing::forty_nine,49);
    ASSERT_TRUE( filled.not_empty() );
    ASSERT_EQ( 48, distance(filled.first(),previous(filled.first())) );
}

TYPED_TEST(hoop_test,default_insert_first)
{
    TypeParam hoop;

    hoop.insert_first(thing::one);
    ASSERT_TRUE( hoop.not_empty() );
    ASSERT_EQ( thing::one, load(hoop.first()) );

    hoop.insert_first(thing::two);
    ASSERT_TRUE( hoop.not_empty() );
    ASSERT_EQ( thing::two, load(hoop.first()) );

    hoop.insert_first(thing::three);
    ASSERT_TRUE( hoop.not_empty() );
    ASSERT_EQ( thing::three, load(hoop.first()) );
}

TYPED_TEST(hoop_test,default_insert_last)
{
    TypeParam hoop;

    auto last = hoop.insert_first(thing::one);
    ASSERT_TRUE( hoop.not_empty() );
    ASSERT_EQ( thing::one, load(last) );

    last = hoop.insert_after(last,thing::two);
    ASSERT_TRUE( hoop.not_empty() );
    ASSERT_EQ( thing::two, load(last) );

    last = hoop.insert_after(last,thing::three);
    ASSERT_TRUE( hoop.not_empty() );
    ASSERT_EQ( thing::three, load(last) );
}

TYPED_TEST(hoop_test,filled_remove_first)
{
    auto hoop = TypeParam::filled(thing::forty_nine,3);

    hoop.remove_first();
    ASSERT_TRUE( hoop.not_empty() );
    ASSERT_EQ( thing::forty_nine, load(hoop.first()) );

    hoop.remove_first();
    ASSERT_TRUE( hoop.not_empty() );
    ASSERT_EQ( thing::forty_nine, load(hoop.first()) );

    hoop.remove_first();
    ASSERT_TRUE( hoop.is_empty() );
}

TYPED_TEST(hoop_test,filled_remove_after_first)
{
    auto hoop = TypeParam::filled(thing::forty_nine,3);

    hoop.remove_after(hoop.first());
    ASSERT_TRUE( hoop.not_empty() );
    ASSERT_EQ( thing::forty_nine, load(hoop.first()) );

    hoop.remove_after(hoop.first());
    ASSERT_TRUE( hoop.not_empty() );
    ASSERT_EQ( thing::forty_nine, load(hoop.first()) );

    hoop.remove_after(hoop.first());
    ASSERT_TRUE( hoop.is_empty() );
}
