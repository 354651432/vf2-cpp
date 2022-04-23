#include "demo.h"
#include "constant.h"
#include "match.h"

#include "c4.h"
#include "k14.h"

namespace Demo1 {
    void showGraph(Graph g) {
        showVType(g.V);

        std::cout << std::endl;
        std::cout << "graph:" << endl;

        for (auto arr : g.G) {
            for (auto pt : arr) {
                std::cout << pt << " ";
            }
            std::cout << std::endl;
        }
    }
    void showVType(VType arr) {
        std::cout << "points: ";
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
}