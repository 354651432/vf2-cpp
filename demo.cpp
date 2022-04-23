#include "demo.h"
#include "constant.h"
#include "match.h"

#include "c4.h"
#include "k14.h"
#include "p5.h"

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
        auto g = Constant::demoG1;
        auto matchResults = match(g, Constant::p3);
        for (VType pts : matchResults) {
            std::cout << "p3->" << std::endl;
            showVType(pts);
        }
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

        auto matchResults = match(g, p5);
        for (auto res : matchResults) {
            auto results = Z4(g, res);
            if (results.size() <= 0) {
                cout << "no results" << endl;
                return;
            }
            for (auto res : results) {
                showVType(res);
            }
        }
    }

    void testN113() {
        auto g = Graph::fromJson("graph-data/graph1.json");
        Graph p5 = Graph::fromJson("graph-data/p5-n113.json");

        auto matchResults = match(g, p5);
        for (auto res : matchResults) {
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
}