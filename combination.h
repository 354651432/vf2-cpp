#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

template <typename T>
class Combination {
    vector<vector<T>> results;
    vector<T> vec;
    void pick() {
        int n = results.size();
        for (int i = 0; i < n; i++) {
            vector<T> head = *results.begin();
            results.erase(results.begin());

            vector<T> last = diff(vec, head);
            for (auto it : last) {
                vector<T> headCopy = head;
                headCopy.push_back(it);
                if (!inResults(headCopy))
                    results.push_back(headCopy);
            }
        }
    }
    vector<T> diff(vector<T> arr1, vector<T> arr2) {
        vector<T> res;
        for (auto it : arr1) {
            if (find(arr2.begin(), arr2.end(), it) == arr2.end()) {
                res.push_back(it);
            }
        }

        return res;
    }

    bool inResults(vector<T> vec) {
        return false; // 排除直接返回 false 以下逻辑是组合用的
        for (auto arr : results) {
            if (arr.size() != vec.size()) {
                continue;
            }
            vector<T> arr1 = vec;

            if (arrEq(arr, arr1)) {
                return true;
            }
        }

        return false;
    }

    bool arrEq(vector<T> arr, vector<T> arr1) {
        sort(arr.begin(), arr.end());
        sort(arr1.begin(), arr1.end());
        for (int i = 0; i < arr.size(); i++) {
            if (arr[i] != arr1[i]) {
                return false;
            }
        }

        return true;
    }

public:
    Combination(vector<T> vec1)
        : vec(vec1) { }

    vector<vector<T>> run(int m) {
        for (auto it : vec) {
            results.push_back(vector<T> {it});
        }

        for (int i = 0; i < m - 1; i++) {
            pick();
        }

        return results;
    }
};
