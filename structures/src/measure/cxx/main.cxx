#define ANKERL_NANOBENCH_IMPLEMENT 1

#include <forward_list>
#include <list>
#include <vector>

#include <nanobench.h>

import br.dev.pedrolamarao.structures;

using namespace br::dev::pedrolamarao::structures;

enum class integral_type : uintptr_t
{
    zero = 0u,
    one,
    two,
    three,
    four,
    five,
    six,
    seven,
    eight,
    nine
};

void list_insert_left ()
{
    for (auto inserts : std::vector<unsigned>{ 1, 10, 100, 1000, 10000 })
    { 
        ankerl::nanobench::Bench benchmarker;
        benchmarker.minEpochTime(std::chrono::seconds(1));
        benchmarker.performanceCounters(true);
        benchmarker.relative(true);
        benchmarker.title("list insert first x " + std::to_string(inserts));

        benchmarker.run("std_forward_list",[=]
        {
            std::forward_list<integral_type> list;
            for (auto i = 0u; i != inserts; ++i)
                ankerl::nanobench::doNotOptimizeAway( list.insert_after( list.before_begin(), integral_type::one ) );
        });

        benchmarker.run("std_list",[=]
        {
            std::list<integral_type> list;
            for (auto i = 0u; i != inserts; ++i)
                ankerl::nanobench::doNotOptimizeAway( list.insert( list.begin(), integral_type::one ) );
        });

        benchmarker.run("std_vector",[=]
        {
            std::vector<integral_type> list;
            for (auto i = 0u; i != inserts; ++i)
                ankerl::nanobench::doNotOptimizeAway( list.insert( list.begin(), integral_type::one ) );
        });

        benchmarker.run("binode_list_v1",[=]
        {
            binode_list_v1<integral_type> list;
            for (auto i = 0u; i != inserts; ++i)
                ankerl::nanobench::doNotOptimizeAway( list.insert_first( integral_type::one ) );
        });

        benchmarker.run("binode_list_v2",[=]
        {
            binode_list_v2<integral_type> list;
            for (auto i = 0u; i != inserts; ++i)
                ankerl::nanobench::doNotOptimizeAway( list.insert_first( integral_type::one ) );
        });

        benchmarker.run("binode_list_v3",[=]
        {
            binode_list_v3<integral_type> list;
            for (auto i = 0u; i != inserts; ++i)
                ankerl::nanobench::doNotOptimizeAway( list.insert_first( integral_type::one ) );
        });

        benchmarker.run("segment_list_v1",[=]
        {
            segment_list_v1<integral_type> list;
            for (auto i = 0u; i != inserts; ++i)
                ankerl::nanobench::doNotOptimizeAway( list.insert_after( list.before_first(), integral_type::one ) );
        });

        benchmarker.run("segment_list_v2",[=]
        {
            segment_list_v2<integral_type> list;
            for (auto i = 0u; i != inserts; ++i)
                ankerl::nanobench::doNotOptimizeAway( list.insert_after( list.before_first(), integral_type::one ) );
        });

        benchmarker.run("uninode_list_v1",[=]
        {
            uninode_list_v1<integral_type> list;
            for (auto i = 0u; i != inserts; ++i)
                ankerl::nanobench::doNotOptimizeAway( list.insert_first( integral_type::one ) );
        });

        benchmarker.run("uninode_list_v2",[=]
        {
            uninode_list_v2<integral_type> list;
            for (auto i = 0u; i != inserts; ++i)
                ankerl::nanobench::doNotOptimizeAway( list.insert_first( integral_type::one ) );
        });

        benchmarker.run("uninode_list_v3",[=]
        {
            uninode_list_v3<integral_type> list;
            for (auto i = 0u; i != inserts; ++i)
                ankerl::nanobench::doNotOptimizeAway( list.insert_first( integral_type::one ) );
        });
    }
}

void list_insert_first_after ()
{
    for (auto inserts : std::vector<unsigned>{ 2, 10, 100, 1000, 10000 })
    {
        ankerl::nanobench::Bench benchmarker;
        benchmarker.minEpochTime(std::chrono::seconds(1));
        benchmarker.performanceCounters(true);
        benchmarker.relative(true);
        benchmarker.title("list insert first, after x " + std::to_string(inserts));

        benchmarker.run("std_vector",[=]
        {
            std::vector<integral_type> list;
            auto last = list.insert( list.begin(), integral_type::one );
            for (auto i = 0u; i != inserts - 1; ++i)
                ankerl::nanobench::doNotOptimizeAway( list.insert( last, integral_type::one ) );
        });

        benchmarker.run("std_forward_list",[=]
        {
            std::forward_list<integral_type> list;
            auto last = list.insert_after( list.before_begin(), integral_type::one );
            for (auto i = 0u; i != inserts - 1; ++i)
                ankerl::nanobench::doNotOptimizeAway( last = list.insert_after( last, integral_type::one ) );
        });

        benchmarker.run("std_list",[=]
        {
            std::list<integral_type> list;
            auto last = list.insert( list.begin(), integral_type::one );
            for (auto i = 0u; i != inserts - 1; ++i)
                ankerl::nanobench::doNotOptimizeAway( list.insert( last, integral_type::one ) );
        });

        benchmarker.run("binode_list_v1",[=]
        {
            binode_list_v1<integral_type> list;
            auto last = list.insert_first(integral_type::one);
            for (auto i = 0u; i != inserts - 1; ++i)
                ankerl::nanobench::doNotOptimizeAway( last = list.insert_after( last, integral_type::one ) );
        });

        benchmarker.run("binode_list_v2",[=]
        {
            binode_list_v2<integral_type> list;
            auto last = list.insert_first(integral_type::one);
            for (auto i = 0u; i != inserts - 1; ++i)
                ankerl::nanobench::doNotOptimizeAway( last = list.insert_after( last, integral_type::one ) );
        });

        benchmarker.run("binode_list_v3",[=]
        {
            binode_list_v3<integral_type> list;
            auto last = list.insert_first(integral_type::one);
            for (auto i = 0u; i != inserts - 1; ++i)
                ankerl::nanobench::doNotOptimizeAway( last = list.insert_after( last, integral_type::one ) );
        });

        benchmarker.run("segment_list_v1",[=]
        {
            segment_list_v1<integral_type> list;
            auto last = list.insert_first(integral_type::one);
            for (auto i = 0u; i != inserts - 1; ++i)
                ankerl::nanobench::doNotOptimizeAway( last = list.insert_after( last, integral_type::one ) );
        });

        benchmarker.run("segment_list_v2",[=]
        {
            segment_list_v2<integral_type> list;
            auto last = list.insert_first(integral_type::one);
            for (auto i = 0u; i != inserts - 1; ++i)
                ankerl::nanobench::doNotOptimizeAway( list.insert_after( last, integral_type::one ) );
        });

        benchmarker.run("uninode_list_v1",[=]
        {
            uninode_list_v1<integral_type> list;
            auto last = list.insert_first(integral_type::one);
            for (auto i = 0u; i != inserts - 1; ++i)
                ankerl::nanobench::doNotOptimizeAway( last = list.insert_after( last, integral_type::one ) );
        });

        benchmarker.run("uninode_list_v2",[=]
        {
            uninode_list_v2<integral_type> list;
            auto last = list.insert_first(integral_type::one);
            for (auto i = 0u; i != inserts - 1; ++i)
                ankerl::nanobench::doNotOptimizeAway( last = list.insert_after( last, integral_type::one ) );
        });

        benchmarker.run("uninode_list_v3",[=]
        {
            uninode_list_v3<integral_type> list;
            auto last = list.insert_first(integral_type::one);
            for (auto i = 0u; i != inserts - 1; ++i)
                ankerl::nanobench::doNotOptimizeAway( last = list.insert_after( last, integral_type::one ) );
        });
    }
}

int main (int, char* [])
{
    list_insert_left();
    list_insert_right();
    return 0;
}
