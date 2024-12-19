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
    ASSERT_EQ( list.first(), list.limit() );
}

TEST(uninode_list_test,default_insert_first)
{
    auto list = uninode_list<thing>();
    list.insert_first(thing::forty_nine);
    ASSERT_NE( list.first(), list.limit() );
    ASSERT_EQ( list.load(list.first()), thing::forty_nine );
}

TEST(uninode_list_test,filled)
{
    auto list = uninode_list<thing>::filled(thing::one,127);
    ASSERT_NE( list.first(), list.limit() );
    ASSERT_EQ( list.load(list.first()), thing::one );
}

TEST(uninode_list_test,filled_erase_after)
{
    auto list = uninode_list<thing>::filled(thing::one,2);
    list.erase_after( list.first() );
    ASSERT_EQ( list.load(list.first()), thing::one );
}

TEST(uninode_list_test,filled_erase_first)
{
    auto list = uninode_list<thing>::filled(thing::one,1);
    list.erase_first();
    ASSERT_EQ( list.first(), list.limit() );
}

TEST(uninode_list_test,filled_insert_after)
{
    auto list = uninode_list<thing>::filled(thing::one,2);
    list.insert_after(list.first(),thing::forty_nine);
    ASSERT_EQ( list.load(list.first()), thing::one );
}

TEST(uninode_list_test,filled_insert_first)
{
    auto list = uninode_list<thing>::filled(thing::one,1);
    list.insert_first(thing::forty_nine);
    ASSERT_EQ( list.load(list.first()), thing::forty_nine );
}
