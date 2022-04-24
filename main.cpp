#include "combination.h"
#include "demo.h"

int main() {
    // Demo1::testC4();
    // Demo1::testK13();
    // Demo1::testK14();
    // Demo1::testMatch();

    // Demo1::testZ4();

    Combination cb(vector<char> {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o'});
    auto results = cb.arrangement(4);
    for (auto it : results) {
        Demo1::showVType(it);
    }
}