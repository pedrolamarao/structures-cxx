#include <list>
#include <vector>

#include <celero/Celero.h>

import br.dev.pedrolamarao.structures;

using namespace br::dev::pedrolamarao::structures;

enum class integral_type : uintptr_t
{
    zero = 0,
    one,
    two,
    three,
    four,
    five,
    six,
    seven,
    eight,
    nine,
};

struct fixture : celero::TestFixture
{
    std::list<integral_type>       std_list;
    std::vector<integral_type>     std_vector;
    binode_list_v1<integral_type>  binode_list_v1;
    binode_list_v2<integral_type>  binode_list_v2;
    binode_list_v3<integral_type>  binode_list_v3;
    segment_list_v1<integral_type> segment_list_v1;
    segment_list_v2<integral_type> segment_list_v2;
    uninode_list_v1<integral_type> uninode_list_v1;
    uninode_list_v2<integral_type> uninode_list_v2;
    uninode_list_v3<integral_type> uninode_list_v3;

	virtual std::vector<std::shared_ptr<celero::TestFixture::ExperimentValue>> getExperimentValues () const
    {
	    std::vector<std::shared_ptr<ExperimentValue>> values;
	    auto inserts = 3;
	    for (auto i = 0u; i < 6u; i++) {
	        values.push_back( std::make_shared<ExperimentValue>( inserts ) );
	        inserts = inserts * 3;
	    }
	    return std::move(values);
    }

    int64_t inserts;

    virtual void setUp (const celero::TestFixture::ExperimentValue* experimentValue)
    {
        inserts = experimentValue->Value;
    }
};

BASELINE_F(list_insert_first,std_list,fixture,30,1000)
{
    for (auto i = 0u; i != inserts; ++i)
        celero::DoNotOptimizeAway( std_list.insert( std_list.begin(), integral_type::one ) );
}

BENCHMARK_F(list_insert_first,std_vector,fixture,30,1000)
{
    for (auto i = 0u; i != inserts; ++i)
        celero::DoNotOptimizeAway( std_vector.insert( std_vector.begin(), integral_type::one ) );
}

BENCHMARK_F(list_insert_first,binode_list_v1,fixture,30,1000)
{
    for (auto i = 0u; i != inserts; ++i)
        celero::DoNotOptimizeAway( binode_list_v1.insert_first( integral_type::one ) );
}

BENCHMARK_F(list_insert_first,binode_list_v2,fixture,30,1000)
{
    for (auto i = 0u; i != inserts; ++i)
        celero::DoNotOptimizeAway( binode_list_v2.insert_first( integral_type::one ) );
}

BENCHMARK_F(list_insert_first,binode_list_v3,fixture,30,1000)
{
    for (auto i = 0u; i != inserts; ++i)
        celero::DoNotOptimizeAway( binode_list_v3.insert_first( integral_type::one ) );
}

BENCHMARK_F(list_insert_first,segment_list_v1,fixture,30,1000)
{
    for (auto i = 0u; i != inserts; ++i)
        celero::DoNotOptimizeAway( segment_list_v1.insert_first( integral_type::one ) );
}

BENCHMARK_F(list_insert_first,segment_list_v2,fixture,30,1000)
{
    for (auto i = 0u; i != inserts; ++i)
        celero::DoNotOptimizeAway( segment_list_v2.insert_first( integral_type::one ) );
}

BENCHMARK_F(list_insert_first,uninode_list_v1,fixture,30,1000)
{
    for (auto i = 0u; i != inserts; ++i)
        celero::DoNotOptimizeAway( uninode_list_v1.insert_first( integral_type::one ) );
}

BENCHMARK_F(list_insert_first,uninode_list_v2,fixture,30,1000)
{
    for (auto i = 0u; i != inserts; ++i)
        celero::DoNotOptimizeAway( uninode_list_v2.insert_first( integral_type::one ) );
}

BENCHMARK_F(list_insert_first,uninode_list_v3,fixture,30,1000)
{
    for (auto i = 0u; i != inserts; ++i)
        celero::DoNotOptimizeAway( uninode_list_v3.insert_first( integral_type::one ) );
}