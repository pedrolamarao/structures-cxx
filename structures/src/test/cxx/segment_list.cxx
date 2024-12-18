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

TEST(segment_list_test,defaultt)
{
    auto list = segment_list<thing>();
}

TEST(segment_list_test,default_insert_first)
{
    auto list = segment_list<thing>();
    list.insert_first(thing::forty_nine);
    ASSERT_EQ( list.load(0), thing::forty_nine );
}

TEST(segment_list_test,default_insert_at)
{
    auto list = segment_list<thing>();
    list.insert_at(2,thing::forty_nine);
    ASSERT_EQ( list.load(2), thing::forty_nine );
}

TEST(segment_list_test,filled)
{
    auto list = segment_list<thing>::filled(thing::one,127);
    ASSERT_EQ( list.load(0),   thing::one );
    ASSERT_EQ( list.load(126), thing::one );
}

TEST(segment_list_test,filled_insert_at)
{
    auto list = segment_list<thing>::filled(thing::one,2);
    list.insert_at(1,thing::forty_nine);
    ASSERT_EQ( list.load(0),thing::one );
    ASSERT_EQ( list.load(1),thing::forty_nine );
    ASSERT_EQ( list.load(2),thing::one );
}

TEST(segment_list_test,filled_store_load)
{
    auto list = segment_list<thing>::filled(thing::one,127);
    list.store(1,thing::forty_nine);
    ASSERT_EQ( list.load(0),   thing::one );
    ASSERT_EQ( list.load(1),   thing::forty_nine );
    ASSERT_EQ( list.load(126), thing::one );
}

TEST(segment_list_test,filled_store_position_load)
{
    auto list = segment_list<thing>::filled(thing::one,127);
    list.store(1,thing::forty_nine);
    auto position = list.first();
    ASSERT_EQ( list.load(position), thing::one );
    position = position.next();
    ASSERT_EQ( list.load(position), thing::forty_nine );
    for (auto i = 2; i <= 127; i++) position = position.next();
    ASSERT_EQ( list.load(126), thing::one );
}

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
