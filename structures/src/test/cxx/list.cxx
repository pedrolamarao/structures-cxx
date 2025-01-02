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
    forty_nine = 49u,
};

template <typename T>
struct list_test : testing::Test
{
    static_assert( structures::list<T> );
};

using types = testing::Types<
    binode_list_v1<thing>,
    binode_list_v2<thing>,
    binode_list_v3<thing>,
    segment_list<thing>,
    uninode_list_v1<thing>,
    uninode_list_v2<thing>,
    uninode_list_v3<thing>
>;

TYPED_TEST_SUITE(list_test,types);

TYPED_TEST(list_test,defaultt)
{
    TypeParam empty;
    ASSERT_TRUE( empty.is_empty() );
    ASSERT_EQ( empty.first(), empty.after_last() );
    ASSERT_EQ( 0, distance(empty.first(),empty.after_last()) );
}

TYPED_TEST(list_test,filled)
{
    auto empty = TypeParam::filled(thing::zero,0);
    ASSERT_TRUE( empty.is_empty() );
    ASSERT_EQ( empty.first(), empty.after_last() );
    ASSERT_EQ( 0, distance(empty.first(),empty.after_last()) );

    auto one = TypeParam::filled(thing::one,1);
    ASSERT_TRUE( one.not_empty() );
    ASSERT_NE( one.first(), one.after_last() );
    ASSERT_EQ( 1, distance(one.first(),one.after_last()) );

    auto filled = TypeParam::filled(thing::forty_nine,49);
    ASSERT_TRUE( filled.not_empty() );
    ASSERT_EQ( 49, distance(filled.first(),filled.after_last()) );
}

TYPED_TEST(list_test,default_insert_remove_first)
{
    TypeParam list;
    ASSERT_TRUE(list.is_empty());
    ASSERT_EQ(list.first(),list.after_last());

    list.insert_first(thing::one);
    ASSERT_TRUE(list.not_empty());
    ASSERT_NE(list.first(),list.after_last());
    ASSERT_EQ(load(list.first()),thing::one);

    list.insert_first(thing::two);
    ASSERT_TRUE(list.not_empty());
    ASSERT_NE(list.first(),list.after_last());
    ASSERT_EQ(load(list.first()),thing::two);

    list.insert_first(thing::forty_nine);
    ASSERT_TRUE(list.not_empty());
    ASSERT_NE(list.first(),list.after_last());
    ASSERT_EQ(load(list.first()),thing::forty_nine);

    list.remove_first();
    ASSERT_TRUE(list.not_empty());
    ASSERT_NE(list.first(),list.after_last());
    ASSERT_EQ(load(list.first()),thing::two);

    list.remove_first();
    ASSERT_TRUE(list.not_empty() );
    ASSERT_NE(list.first(),list.after_last());
    ASSERT_EQ(load(list.first()),thing::one);

    list.remove_first();
    ASSERT_TRUE(list.is_empty());
    ASSERT_EQ(list.first(),list.after_last());
}

TYPED_TEST(list_test,default_insert_last_remove_first)
{
    TypeParam list;
    ASSERT_TRUE(list.is_empty());
    ASSERT_EQ(list.first(),list.after_last());

    auto last = list.insert_first(thing::one);
    ASSERT_TRUE(list.not_empty());
    ASSERT_NE(list.first(),list.after_last());
    ASSERT_EQ(load(list.first()),thing::one);

    last = list.insert_after(last,thing::two);
    ASSERT_TRUE(list.not_empty());
    ASSERT_NE(list.first(),list.after_last());
    ASSERT_EQ(load(list.first()),thing::one);

    last = list.insert_after(last,thing::forty_nine);
    ASSERT_TRUE(list.not_empty());
    ASSERT_NE(list.first(),list.after_last());
    ASSERT_EQ(load(list.first()),thing::one);

    list.remove_first();
    ASSERT_TRUE(list.not_empty());
    ASSERT_NE(list.first(),list.after_last());
    ASSERT_EQ(load(list.first()),thing::two);

    list.remove_first();
    ASSERT_TRUE(list.not_empty() );
    ASSERT_NE(list.first(),list.after_last());
    ASSERT_EQ(load(list.first()),thing::forty_nine);

    list.remove_first();
    ASSERT_TRUE(list.is_empty());
    ASSERT_EQ(list.first(),list.after_last());
}

TYPED_TEST(list_test,default_insert_remove_last)
{
    TypeParam list;
    ASSERT_TRUE(list.is_empty());
    ASSERT_EQ(list.first(),list.after_last());

    auto last = list.insert_first(thing::one);
    ASSERT_TRUE(list.not_empty());
    ASSERT_NE(list.first(),list.after_last());
    ASSERT_EQ(load(list.first()),thing::one);

    last = list.insert_after(last,thing::two);
    ASSERT_TRUE(list.not_empty());
    ASSERT_NE(list.first(),list.after_last());
    ASSERT_EQ(load(list.first()),thing::one);

    last = list.insert_after(last,thing::forty_nine);
    ASSERT_TRUE(list.not_empty());
    ASSERT_NE(list.first(),list.after_last());
    ASSERT_EQ(load(list.first()),thing::one);

    list.remove_after(next(list.first()));
    ASSERT_TRUE(list.not_empty());
    ASSERT_NE(list.first(),list.after_last());
    ASSERT_EQ(load(list.first()),thing::one);

    list.remove_after(list.first());
    ASSERT_TRUE(list.not_empty() );
    ASSERT_NE(list.first(),list.after_last());
    ASSERT_EQ(load(list.first()),thing::one);

    list.remove_first();
    ASSERT_TRUE(list.is_empty());
    ASSERT_EQ(list.first(),list.after_last());
}
