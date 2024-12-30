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

TEST(uninode_list_test,filled)
{
    auto filled = uninode_list_v3<thing>::filled(thing::forty_nine,49);
    ASSERT_FALSE( filled.is_empty() );

    auto moved = std::move(filled);
    ASSERT_FALSE( moved.is_empty() );
    ASSERT_TRUE( filled.is_empty() );
}