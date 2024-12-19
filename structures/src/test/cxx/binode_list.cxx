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

TEST(binode_list_test,defaultt)
{
    auto list = binode_list<thing>();
}

TEST(binode_list_test,default_insert_at)
{
    auto list = binode_list<thing>();
    list.insert_at(list.first(),thing::forty_nine);
    ASSERT_EQ( list.load(list.first()), thing::forty_nine );
}

TEST(binode_list_test,filled)
{
    auto list = binode_list<thing>::filled(thing::one,127);
    ASSERT_EQ( list.load(list.first()), thing::one );
}

TEST(binode_list_test,filled_erase_at)
{
    auto list = binode_list<thing>::filled(thing::one,1);
    list.erase_at( list.first() );
    ASSERT_EQ( list.first(), list.limit() );
}

TEST(binode_list_test,filled_insert_at)
{
    auto list = binode_list<thing>::filled(thing::one,1);
    list.insert_at(list.first(),thing::forty_nine);
    ASSERT_EQ( list.load(list.first()), thing::forty_nine );
}
