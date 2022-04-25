#include "State.h"

State::State(int sz1, int sz2) {
    core_1.resize(sz1);
    core_2.resize(sz2);
    fill(core_1.begin(), core_1.end(), -1);
    fill(core_2.begin(), core_2.end(), -1);
    for (int i = 0; i < sz1; ++i) {
        fN1.insert(i);
    }
    for (int i = 0; i < sz2; ++i) {
        fN2.insert(i);
    }
}

void State::removeFN(int no, int i) {
    if (no == 1) {
        if (fN1.find(i) != fN1.end()) {
            fN1.erase(i);
        }
    }
    else {
        if (fN2.find(i) != fN2.end()) {
            fN2.erase(i);
        }
    }
}
