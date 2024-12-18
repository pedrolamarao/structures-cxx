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

TEST(uninode_list_test,defaultt)
{
    auto list = uninode_list<thing>();
}

TEST(uninode_list_test,default_insert_first)
{
    auto list = uninode_list<thing>();
    list.insert_first(thing::forty_nine);
    ASSERT_EQ( list.load(0), thing::forty_nine );
}

TEST(uninode_list_test,filled)
{
    auto list = uninode_list<thing>::filled(thing::one,127);
    ASSERT_EQ( list.load(0),   thing::one );
    ASSERT_EQ( list.load(126), thing::one );
}

TEST(uninode_list_test,filled_insert_first)
{
    auto list = uninode_list<thing>::filled(thing::one,1);
    list.insert_first(thing::forty_nine);
    ASSERT_EQ( list.load(0), thing::forty_nine );
    ASSERT_EQ( list.load(1), thing::one );
}

TEST(uninode_list_test,filled_insert_after)
{
    auto list = uninode_list<thing>::filled(thing::one,2);
    list.insert_after(list.first(),thing::forty_nine);
    ASSERT_EQ( list.load(0), thing::one );
    ASSERT_EQ( list.load(1), thing::forty_nine );
    ASSERT_EQ( list.load(2), thing::one );
}

TEST(uninode_list_test,filled_store_load)
{
    auto list = uninode_list<thing>::filled(thing::one,127);
    list.store(1,thing::forty_nine);
    ASSERT_EQ( list.load(0),   thing::one );
    ASSERT_EQ( list.load(1),   thing::forty_nine );
    ASSERT_EQ( list.load(126), thing::one );
}

TEST(uninode_list_test,filled_store_position_load)
{
    auto list = uninode_list<thing>::filled(thing::one,127);
    list.store(1,thing::forty_nine);
    auto position = list.first();
    ASSERT_EQ( list.load(position), thing::one );
    position = position.next();
    ASSERT_EQ( list.load(position), thing::forty_nine );
    for (auto i = 2; i <= 127; i++) position = position.next();
    ASSERT_EQ( list.load(126), thing::one );
}