#include "../graph-fromjson.hpp"
#include "../graph.hpp"
#include "../vf2.hpp"
#include "gtest/gtest.h"

class Match : public testing::Test {
public:
    shared_ptr<Graph<string>> p3, p5, p6, t1, t2, g1;

    void SetUp() {
        p3 = make_shared<Graph<string>>(graphFromJsonFile("../../graph-data/p3.json"));
        p5 = make_shared<Graph<string>>(graphFromJsonFile("../../graph-data/p5.json"));
        p6 = make_shared<Graph<string>>(graphFromJsonFile("../../graph-data/p6.json"));

        t1 = make_shared<Graph<string>>(graphFromJsonFile("../../graph-data/t1.json"));
        t2 = make_shared<Graph<string>>(graphFromJsonFile("../../graph-data/t2.json"));

        g1 = make_shared<Graph<string>>(graphFromJsonFile("../../graph-data/graph1.json"));
    }
};

TEST_F(Match, test1) {

    Vf2 vf2(*p5, *p3);
    auto length = vf2.vf2({});

    EXPECT_EQ(length, 6);
}
