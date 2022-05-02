#include "../graph-fromjson.hpp"
#include "../graph.hpp"
#include "../vf2.hpp"
#include "gtest/gtest.h"

class Match : public testing::Test {
public:
    unique_ptr<Graph<string>> p3, p5, p6, t1, t2, g1;

    void SetUp() {
        p3 = graphFromJsonFile("../../graph-data/p3.json");
        p5 = graphFromJsonFile("../../graph-data/p5.json");
        p6 = graphFromJsonFile("../../graph-data/p6.json");

        t1 = graphFromJsonFile("../../graph-data/t1.json");
        t2 = graphFromJsonFile("../../graph-data/t2.json");

        g1 = graphFromJsonFile("../../graph-data/graph1.json");
    }
};

TEST_F(Match, testp5_p3) {

    Vf2 vf2(*p5, *p3);
    auto length = vf2.vf2({});

    EXPECT_EQ(length, 6);
}

TEST_F(Match, testg1_p5) {
    Vf2 vf2(*g1, *p5);
    auto length = vf2.vf2({});

    EXPECT_EQ(length, 14);
}

TEST_F(Match, test_runVf2) {

    auto results = Vf2<string>::runV2f(*g1, *p6);

    EXPECT_EQ(results.size(), 12);

    auto firstResult = *results.begin();
    auto firstMapping = *firstResult.begin();

    EXPECT_EQ(firstMapping.first, "2");
    EXPECT_EQ(firstMapping.second, "A");
}