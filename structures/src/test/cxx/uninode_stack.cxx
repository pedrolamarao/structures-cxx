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

TEST(uninode_stack_test,default_insert)
{
    auto stack = uninode_stack<thing>();
    ASSERT_TRUE( stack.is_empty() );

    stack.insert(thing::one);
    ASSERT_TRUE( stack.not_empty() );
    ASSERT_EQ( stack.top(), thing::one );

    stack.insert(thing::two);
    ASSERT_TRUE( stack.not_empty() );
    ASSERT_EQ( stack.top(), thing::two );

    stack.insert(thing::forty_nine);
    ASSERT_TRUE( stack.not_empty() );
    ASSERT_EQ( stack.top(), thing::forty_nine );

    stack.erase();
    ASSERT_TRUE( stack.not_empty() );
    ASSERT_EQ( stack.top(), thing::two );

    stack.erase();
    ASSERT_TRUE( stack.not_empty() );
    ASSERT_EQ( stack.top(), thing::one );

    stack.erase();
    ASSERT_TRUE( stack.is_empty() );
}
