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
    binode_list<thing>,
    segment_list<thing>,
    uninode_list<thing>
>;

TYPED_TEST_SUITE(list_test,types);

TYPED_TEST(list_test,default_insert_erase_first)
{
    TypeParam list;
    ASSERT_TRUE(list.is_empty());
    ASSERT_EQ(list.first(),list.after_last());

    list.insert_after(list.before_first(),thing::one);
    ASSERT_TRUE(list.not_empty());
    ASSERT_NE(list.first(),list.after_last());
    ASSERT_EQ(load(list.first()),thing::one);

    list.insert_after(list.before_first(),thing::two);
    ASSERT_TRUE(list.not_empty());
    ASSERT_NE(list.first(),list.after_last());
    ASSERT_EQ(load(list.first()),thing::two);

    list.insert_after(list.before_first(),thing::forty_nine);
    ASSERT_TRUE(list.not_empty());
    ASSERT_NE(list.first(),list.after_last());
    ASSERT_EQ(load(list.first()),thing::forty_nine);

    list.erase_after(list.before_first());
    ASSERT_TRUE(list.not_empty());
    ASSERT_NE(list.first(),list.after_last());
    ASSERT_EQ(load(list.first()),thing::two);

    list.erase_after(list.before_first());
    ASSERT_TRUE(list.not_empty() );
    ASSERT_NE(list.first(),list.after_last());
    ASSERT_EQ(load(list.first()),thing::one);

    list.erase_after(list.before_first());
    ASSERT_TRUE(list.is_empty());
    ASSERT_EQ(list.first(),list.after_last());
}

TYPED_TEST(list_test,default_insert_last_erase_first)
{
    TypeParam list;
    ASSERT_TRUE(list.is_empty());
    ASSERT_EQ(list.first(),list.after_last());

    auto last = list.insert_after(list.before_first(),thing::one);
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

    list.erase_after(list.before_first());
    ASSERT_TRUE(list.not_empty());
    ASSERT_NE(list.first(),list.after_last());
    ASSERT_EQ(load(list.first()),thing::two);

    list.erase_after(list.before_first());
    ASSERT_TRUE(list.not_empty() );
    ASSERT_NE(list.first(),list.after_last());
    ASSERT_EQ(load(list.first()),thing::forty_nine);

    list.erase_after(list.before_first());
    ASSERT_TRUE(list.is_empty());
    ASSERT_EQ(list.first(),list.after_last());
}

TYPED_TEST(list_test,default_insert_erase_last)
{
    TypeParam list;
    ASSERT_TRUE(list.is_empty());
    ASSERT_EQ(list.first(),list.after_last());

    auto last = list.insert_after(list.before_first(),thing::one);
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

    list.erase_after(next(list.first()));
    ASSERT_TRUE(list.not_empty());
    ASSERT_NE(list.first(),list.after_last());
    ASSERT_EQ(load(list.first()),thing::one);

    list.erase_after(list.first());
    ASSERT_TRUE(list.not_empty() );
    ASSERT_NE(list.first(),list.after_last());
    ASSERT_EQ(load(list.first()),thing::one);

    list.erase_after(list.before_first());
    ASSERT_TRUE(list.is_empty());
    ASSERT_EQ(list.first(),list.after_last());
}
