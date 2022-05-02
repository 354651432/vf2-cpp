#include "gtest/gtest.h"
#include <iostream>
// #include <iterator>
#include <unordered_set>

using namespace std;

TEST(Other, tset) {
    unordered_set<int> st {10, 20, 30, 40, 55, 66, 77, 11, 132};
    // copy(st.begin(), st.end(), ostream_iterator<int>(cout, " "));

    vector<int> vec(st.begin(), st.end());
    // copy(vec.begin(), vec.end(), ostream_iterator<int>(cout, " "));

    // EXPECT_EQ(*st.begin(), 20);
}

TEST(Other, vtest) {
    vector<int> vec {10, 20, 30, 40, 55, 66, 77, 11, 132};
    auto fRet = find(vec.begin(), vec.end(), 99);

    EXPECT_EQ(fRet, vec.end());
}

TEST(Other, formatTest) {
    string str(100, '\n');
    sprintf(const_cast<char*>(str.c_str()), "%s: %d -> %d\0", "E", 100, 22);
    // cout << str << endl;

    // 但是能用
    EXPECT_STREQ(str.c_str(), "E: 100 -> 22");
}

namespace A {
    class A { };
    void fuckA(int, A&) { }
}

TEST(Other, argFlowTest) {
    A::A obj;
    fuckA(20, obj);
}