#include "AcMatch.h"
#include "c4.h"
#include "combination.h"
#include "demo.h"
#include "graph.h"
#include "k14.h"
#include "match.h"
#include "p5.h"

// 对于返回多个点 T＝vector<VType> 返回一个点 T＝VType
template <typename T>
vector<vector<T>> batchGetResult(Graph g, vector<VType> results, vector<T> (*callback)(Graph, VType)) {
    vector<vector<T>> ret;
    for (auto it : results) {
        auto result = callback(g, it);
        if (result.size() <= 0) {
            continue;
        }

        ret.push_back(result);
    }

    return ret;
}

int main(int argc, char** argv) {
    if (argc <= 1) {
        std::cout << "input error" << std::endl;
        return -1;
    }

    try {
        Graph g = Graph::fromJson(argv[1]); // 检测的大图
        Graph p3 = Graph::fromJson("graph-data/p3.json"); // p3
        Graph p5 = Graph::fromJson("graph-data/p5.json"); // p5

        g.validate();

        string str1 = "One of the picture does not, Finish the program,the graph is super-eumerian";
        if (g.V.size() < 7) {
            std::cout << str1 << std::endl;
            return -2;
        }

        auto p3MatchResults = AcMatch(g, p3).match(); // match p3 的结果集
        auto p5MatchResults = AcMatch(g, p5).match();

        if (p3MatchResults.size() <= 0) {
            std::cout << str1 << std::endl;
            return -2;
        }

        auto k13Results = batchGetResult(g, p3MatchResults, k13);
        auto p7Results = batchGetResult(g, p5MatchResults, P7);
        auto z4Results = batchGetResult(g, p5MatchResults, Z4);
        auto N113Results = batchGetResult(g, p5MatchResults, N113);
        if (k13Results.size() <= 0) { // 匹配k13失败
            if (p7Results.size() > 0 && z4Results.size() > 0 && N113Results.size() > 0) {
                std::cout << "/* message1 */" << std::endl;
                return 0;
            }

            // 匹配k13失败 匹配p7 z4 n113失败
            std::cout << "/* message1 */" << std::endl;
            return 0;
        }

        // 匹配k13成功
        if (p5MatchResults.size() > 0) { // if have p5
            //匹配k13成功 p5成功
            std::cout << "/* message2 */" << std::endl;
            return 0;
        }

        auto c4Results = batchGetResult(g, p3MatchResults, C4);
        auto k14Results = batchGetResult(g, p3MatchResults, k14);
        if (c4Results.size() > 0 && k14Results.size() > 0) { // 匹配k13成功 p5失败 匹配c4 k14成功
            std::cout << "/* message3 */" << std::endl;
            return 0;
        }

        // 匹配k13成功 p5失败 匹配c4 k14失败
        std::cout << "/* message4 */" << std::endl;

    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
    }

    return 0;
}
