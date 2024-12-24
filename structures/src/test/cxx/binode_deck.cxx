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

TEST(binode_deck_test,default_insert_erase_bottom)
{
    auto stack = binode_deck<thing>();
    ASSERT_TRUE( stack.is_empty() );

    stack.insert_bottom(thing::one);
    ASSERT_TRUE( stack.not_empty() );
    ASSERT_EQ( stack.bottom(), thing::one );

    stack.insert_bottom(thing::two);
    ASSERT_TRUE( stack.not_empty() );
    ASSERT_EQ( stack.bottom(), thing::two );

    stack.insert_bottom(thing::forty_nine);
    ASSERT_TRUE( stack.not_empty() );
    ASSERT_EQ( stack.bottom(), thing::forty_nine );

    stack.erase_bottom();
    ASSERT_TRUE( stack.not_empty() );
    ASSERT_EQ( stack.bottom(), thing::two );

    stack.erase_bottom();
    ASSERT_TRUE( stack.not_empty() );
    ASSERT_EQ( stack.bottom(), thing::one );

    stack.erase_bottom();
    ASSERT_TRUE( stack.is_empty() );
}

TEST(binode_deck_test,default_insert_erase_top)
{
    auto stack = binode_deck<thing>();
    ASSERT_TRUE( stack.is_empty() );

    stack.insert_top(thing::one);
    ASSERT_TRUE( stack.not_empty() );
    ASSERT_EQ( stack.top(), thing::one );

    stack.insert_top(thing::two);
    ASSERT_TRUE( stack.not_empty() );
    ASSERT_EQ( stack.top(), thing::two );

    stack.insert_top(thing::forty_nine);
    ASSERT_TRUE( stack.not_empty() );
    ASSERT_EQ( stack.top(), thing::forty_nine );

    stack.erase_top();
    ASSERT_TRUE( stack.not_empty() );
    ASSERT_EQ( stack.top(), thing::two );

    stack.erase_top();
    ASSERT_TRUE( stack.not_empty() );
    ASSERT_EQ( stack.top(), thing::one );

    stack.erase_top();
    ASSERT_TRUE( stack.is_empty() );
}
