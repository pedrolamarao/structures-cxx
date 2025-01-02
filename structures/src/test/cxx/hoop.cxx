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
    binode_hoop_v1<thing>
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
    ASSERT_EQ( one.start(), next(one.start()) );

    auto filled = TypeParam::filled(thing::forty_nine,49);
    ASSERT_TRUE( filled.not_empty() );
    ASSERT_EQ( 48, distance(filled.start(),previous(filled.start())) );
}

TYPED_TEST(hoop_test,default_insert)
{
    TypeParam hoop;

    hoop.insert_start(thing::one);
    ASSERT_TRUE( hoop.not_empty() );
    ASSERT_EQ( thing::one, load(hoop.start()) );

    hoop.insert_start(thing::two);
    ASSERT_TRUE( hoop.not_empty() );
    ASSERT_EQ( thing::two, load(hoop.start()) );

    hoop.insert_start(thing::three);
    ASSERT_TRUE( hoop.not_empty() );
    ASSERT_EQ( thing::three, load(hoop.start()) );
}
