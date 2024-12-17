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

TEST(segment_list_test,filled)
{
    auto list = segment_list<thing>::filled(thing::one,127);
    ASSERT_EQ( list.load(0),   thing::one );
    ASSERT_EQ( list.load(126), thing::one );
}

TEST(segment_list_test,filled_store_load)
{
    auto list = segment_list<thing>::filled(thing::one,127);
    list.store(1,thing::forty_nine);
    ASSERT_EQ( list.load(0),   thing::one );
    ASSERT_EQ( list.load(1),   thing::forty_nine );
    ASSERT_EQ( list.load(126), thing::one );
}

TEST(segment_list_test,filled_store_cursor_load)
{
    auto list = segment_list<thing>::filled(thing::one,127);
    list.store(1,thing::forty_nine);
    auto cursor = list.cursor();
    ASSERT_EQ( list.load(cursor), thing::one );
    cursor.advance();
    ASSERT_EQ( list.load(cursor), thing::forty_nine );
    for (auto i = 2; i <= 127; i++) cursor.advance();
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
