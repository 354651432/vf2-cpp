#include "demo.h"
#include "AcMatch.h"
#include "constant.h"
#include "match.h"

#include "V2fMatch.h"
#include "c4.h"
#include "k14.h"
#include "p5.h"

#include "vf2-vector/graph.h"

using namespace std;

namespace Demo1 {
    void showGraph(Graph g) {
        showVType(g.V, g.title);

        std::cout << std::endl;
        std::cout << g.title << " matrix:" << endl;

        for (auto arr : g.G) {
            for (auto pt : arr) {
                std::cout << pt << " ";
            }
            std::cout << std::endl;
        }
    }

    void showVType(VType arr) {
        showVType(arr, "");
    }

    void showVType(VType arr, string title) {
        std::cout << title << " points: ";
        for (auto pt : arr) {
            std::cout << pt << " ";
        }
        cout << endl;
    }

    void testC4() {
        auto g = Constant::demoG1;
        auto matchResults = match(g, Constant::p3);

        for (VType pts : matchResults) {
            auto results = C4(g, pts);
            if (results.size() <= 0) {
                continue;
            }

            std::cout << "\np3->" << std::endl;
            showVType(pts);

            std::cout << "c4 results:";
            for (auto res : results) {
                cout << res << " ";
            }

            cout << endl;
        }
    }

    void testK14() {
        auto g = Constant::demoG1;
        auto matchResults = match(g, Constant::p3);
        for (VType pts : matchResults) {
            auto results = k14(g, pts);
            if (results.size() <= 0) {
                continue;
            }

            std::cout << "p3->" << std::endl;
            showVType(pts);

            std::cout << "k14 results:" << endl;
            for (auto res : results) {
                showVType(res);
            }

            cout << endl
                 << endl;
        }
    }

    void testK13() {
        auto g = Constant::demoG1;
        auto matchResults = match(g, Constant::p3);
        for (VType pts : matchResults) {

            auto results = k13(g, pts);
            if (results.size() <= 0) {
                continue;
            }

            std::cout << "p3->" << std::endl;
            showVType(pts);
            showVType(results);

            cout << endl
                 << endl;
        }
    }

    void testMatch() {
        auto matchResults = match(
            Graph::fromJson("graph-data/graph1.json"),
            Graph::fromJson("graph-data/p5.json"));

        for (VType pts : matchResults) {
            std::cout << "p3->" << std::endl;
            showVType(pts);
        }
    }

    void testAcMatch() {

        AcMatch matcher(Graph::fromJson("graph-data/graph1.json"),
            Graph::fromJson("graph-data/p5.json"));

        for (VType pts : matcher.match()) {
            std::cout << "p3->" << std::endl;
            showVType(pts);
        }
    }

    void testV2fMatch() {

        V2fMatch matcher(Graph::fromJson("graph-data/graph1.json"),
            Graph::fromJson("graph-data/p5.json"));

        for (VType pts : matcher.match()) {
            std::cout << "p3->" << std::endl;
            showVType(pts);
        }
    }

    void testV2Transf() {
        // auto g1 = Graph::fromJson("graph-data/graph1.json");
        auto g2 = Graph::fromJson("graph-data/p5.json");
        GraphVec gg1 = ::GraphVecFromGraph(g2);
        showGraph(g2);

        std::cout << "\n\nedges ->" << std::endl;
        for (auto i : gg1.edge) {
            std::cout << i.v << " ";
            std::cout << i.w << " ";
            std::cout << i.next << std::endl;
        }

        std::cout << "\npoints ->" << std::endl;
        for (auto i : gg1.node) {
            std::cout << (char)i << " ";
        }
        std::cout << std::endl;
    }

    void testP7() {
        auto g = Graph::fromJson("graph-data/graph1.json");

        Graph p5 = Graph::fromJson("graph-data/p5.json");
        auto matchResults = match(g, p5);
        for (auto res : matchResults) {
            auto results = P7(g, res);
            if (results.size() <= 0) {
                cout << "no results" << endl;
                return;
            }

            std::cout << "p5 ->" << std::endl;
            showVType(res);
            std::cout << "results ->" << std::endl;
            for (auto res : results) {
                showVType(res);
            }
            std::cout << std::endl;
        }
    }

    void testZ4() {
        auto g = Graph::fromJson("graph-data/graph1.json");

        Graph p5 = Graph::fromJson("graph-data/p5.json");
        VType res = {'7', '6', '5', '4', '3'};
        auto results = Z4(g, res);
        if (results.size() <= 0) {
            cout << "no results" << endl;
            return;
        }

        std::cout << "p5 ->" << std::endl;
        showVType(res);
        std::cout << "results ->" << std::endl;
        for (auto res : results) {
            showVType(res);
        }
        std::cout << std::endl;
    }

    void testN113() {
        auto g = Graph::fromJson("graph-data/graph1.json");
        Graph p5 = Graph::fromJson("graph-data/p5-n113.json");

        VType res = {'0', '9', '7', '6', '5', '4'};
        auto results = N113(g, res);
        if (results.size() <= 0) {
            cout << "no results" << endl;
            return;
        }
        for (auto res : results) {
            showVType(res);
        }
    }
}