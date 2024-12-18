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

TEST(segment_list_position_test,distance_0)
{
    auto list = segment_list<thing>();
    auto count = structures::distance(list.first(),list.limit());
    ASSERT_EQ( count, 0 );
}

TEST(segment_list_position_test,distance_127)
{
    auto list = segment_list<thing>::filled(thing::one,127);
    auto count = structures::distance(list.first(),list.limit());
    ASSERT_EQ( count, 127 );
}

TEST(segment_list_position_test,find)
{
    auto list = segment_list<thing>::filled(thing::one,127);
    list.insert_at(64,thing::forty_nine);
    auto position = structures::find(list.first(),list.limit(),thing::forty_nine);
    ASSERT_NE( position, list.limit() );
}

TEST(segment_list_position_test,find_but_absent)
{
    auto list = segment_list<thing>::filled(thing::one,127);
    auto position = structures::find(list.first(),list.limit(),thing::forty_nine);
    ASSERT_EQ( position, list.limit() );
}
