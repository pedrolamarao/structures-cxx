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
struct stack_test : testing::Test
{
    static_assert( stack<T> );
};

using types = testing::Types<
    segment_stack<thing>,
    uninode_stack<thing>
>;

TYPED_TEST_SUITE(stack_test,types);

TYPED_TEST(stack_test,default_insert)
{
    TypeParam stack;
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
