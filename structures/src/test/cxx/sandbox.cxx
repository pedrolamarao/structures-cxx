#include <list>

#include <gmock/gmock.h>

enum class thing
{
    zero       =  0u,
    one        =  1u,
    two        =  2u,
    forty_nine = 49u,
};

TEST(sandbox,empty_insert_begin)
{
    auto list = std::list<thing>();
    list.insert(list.begin(),thing::one);
    ASSERT_EQ( *list.begin(), thing::one );
}

TEST(sandbox,empty_insert_end)
{
    auto list = std::list<thing>();
    list.insert(list.end(),thing::one);
    ASSERT_EQ( *list.begin(), thing::one );
}

TEST(sandbox,nonempty_insert_end)
{
    auto list = std::list<thing>{ thing::one, thing::two };
    list.insert(list.end(),thing::forty_nine);
    ASSERT_EQ( *list.begin(), thing::one );
}
