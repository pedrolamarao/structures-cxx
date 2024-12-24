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
struct deck_test : testing::Test
{
    static_assert( deck<T> );
};

using types = testing::Types<
    segment_deck<thing>,
    binode_deck<thing>
>;

TYPED_TEST_SUITE(deck_test,types);

TYPED_TEST(deck_test,default_insert_erase_bottom)
{
    TypeParam deck;
    ASSERT_TRUE(deck.is_empty() );

    deck.insert_bottom(thing::one);
    ASSERT_TRUE(deck.not_empty() );
    ASSERT_EQ(deck.bottom(), thing::one );

    deck.insert_bottom(thing::two);
    ASSERT_TRUE(deck.not_empty() );
    ASSERT_EQ(deck.bottom(), thing::two );

    deck.insert_bottom(thing::forty_nine);
    ASSERT_TRUE(deck.not_empty() );
    ASSERT_EQ(deck.bottom(), thing::forty_nine );

    deck.erase_bottom();
    ASSERT_TRUE(deck.not_empty() );
    ASSERT_EQ(deck.bottom(), thing::two );

    deck.erase_bottom();
    ASSERT_TRUE(deck.not_empty() );
    ASSERT_EQ(deck.bottom(), thing::one );

    deck.erase_bottom();
    ASSERT_TRUE(deck.is_empty() );
}

TYPED_TEST(deck_test,default_insert_erase_top)
{
    TypeParam deck;
    ASSERT_TRUE(deck.is_empty() );

    deck.insert_top(thing::one);
    ASSERT_TRUE(deck.not_empty() );
    ASSERT_EQ(deck.top(), thing::one );

    deck.insert_top(thing::two);
    ASSERT_TRUE(deck.not_empty() );
    ASSERT_EQ(deck.top(), thing::two );

    deck.insert_top(thing::forty_nine);
    ASSERT_TRUE(deck.not_empty() );
    ASSERT_EQ(deck.top(), thing::forty_nine );

    deck.erase_top();
    ASSERT_TRUE(deck.not_empty() );
    ASSERT_EQ(deck.top(), thing::two );

    deck.erase_top();
    ASSERT_TRUE(deck.not_empty() );
    ASSERT_EQ(deck.top(), thing::one );

    deck.erase_top();
    ASSERT_TRUE(deck.is_empty() );
}
