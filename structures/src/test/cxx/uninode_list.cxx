#include <gmock/gmock.h>

import br.dev.pedrolamarao.structures;

using namespace br::dev::pedrolamarao;
using namespace br::dev::pedrolamarao::structures;
using namespace std;

TEST(uninode_list_test,defaultt)
{
    auto list = uninode_list<int>();

    auto cursor = list.cursor();
    ASSERT_EQ( structures::count(cursor), 0 );
}

TEST(uninode_list_test,filled)
{
    auto list = uninode_list<int>::filled(1,128u);

    auto cursor = list.cursor();
    ASSERT_EQ( structures::count(cursor), 128 );
}
