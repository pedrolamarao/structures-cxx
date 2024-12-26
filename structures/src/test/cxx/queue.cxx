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
struct queue_test : testing::Test
{
    static_assert( queue<T> );
};

using types = testing::Types<
    binode_queue<thing>
>;

TYPED_TEST_SUITE(queue_test,types);

TYPED_TEST(queue_test,insert_erase)
{
    TypeParam deck;
    ASSERT_TRUE(deck.is_empty());

    deck.insert(thing::one);
    ASSERT_TRUE(deck.not_empty());
    ASSERT_EQ(deck.front(), thing::one);

    deck.insert(thing::two);
    ASSERT_TRUE(deck.not_empty());
    ASSERT_EQ(deck.front(), thing::one);

    deck.insert(thing::forty_nine);
    ASSERT_TRUE(deck.not_empty());
    ASSERT_EQ(deck.front(), thing::one);

    deck.remove();
    ASSERT_TRUE(deck.not_empty());
    ASSERT_EQ(deck.front(), thing::two);

    deck.remove();
    ASSERT_TRUE(deck.not_empty());
    ASSERT_EQ(deck.front(), thing::forty_nine);

    deck.remove();
    ASSERT_TRUE(deck.is_empty());
}