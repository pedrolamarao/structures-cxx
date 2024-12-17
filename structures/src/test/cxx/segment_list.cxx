#include <gmock/gmock.h>

import br.dev.pedrolamarao.structures;

using namespace br::dev::pedrolamarao;
using namespace br::dev::pedrolamarao::structures;
using namespace std;

TEST(segment_list_test,defaultt)
{
    auto list = segment_list<int>();

    auto cursor = list.cursor();
    ASSERT_EQ( structures::count(cursor), 0 );
}

TEST(segment_list_test,filled)
{
    auto list = segment_list<int>::filled(1,128u);

    auto cursor = list.cursor();
    ASSERT_EQ( structures::count(cursor), 128 );
}
