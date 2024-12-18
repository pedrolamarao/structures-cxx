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

TEST(uninode_list_position_test,distance_0)
{
    auto list = uninode_list<thing>();
    auto count = structures::distance(list.first(),list.limit());
    ASSERT_EQ( count, 0 );
}

TEST(uninode_list_position_test,distance_127)
{
    auto list = uninode_list<thing>::filled(thing::one,127);
    auto count = structures::distance(list.first(),list.limit());
    ASSERT_EQ( count, 127 );
}

TEST(uninode_list_position_test,find)
{
    auto list = uninode_list<thing>::filled(thing::one,127);
    list.insert_after(list.first(),thing::forty_nine);
    auto position = structures::find(list.first(),list.limit(),thing::forty_nine);
    ASSERT_NE( position, list.limit() );
}

TEST(uninode_list_position_test,find_but_absent)
{
    auto list = uninode_list<thing>::filled(thing::one,127);
    auto position = structures::find(list.first(),list.limit(),thing::forty_nine);
    ASSERT_EQ( position, list.limit() );
}
