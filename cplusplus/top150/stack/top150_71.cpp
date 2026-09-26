//
// Created by 韩堃 on 2026/9/26.
//

#include <gtest/gtest.h>

using namespace std;

class Solution {
public:
    string simplifyPath(string path) {
        string ret = "";

        vector<string> container;
        string tmp = "";
        for (auto i: path) {
            if (i == '/') {
                if (tmp != "") {
                    container.emplace_back(tmp);
                }
                tmp = "";
                continue;
            }
            tmp += i;
        }

        if (tmp != "") {
            container.emplace_back(tmp);
        }

        vector<string> simple_container;
        for (auto i: container) {
            if (i == "..") {
                if (!simple_container.empty()) {
                    simple_container.pop_back();
                }
            } else if (i == ".") {
                continue;
            } else {
                simple_container.emplace_back(i);
            }
        }

        ret = "/";
        for (auto i: simple_container) {
            ret += i;
            ret += '/';
        }

        if (ret.size() > 1 && ret.at(ret.size() - 1) == '/') {
            ret.pop_back();
        }

        return ret;
    }
};


TEST(top150, 71) {
    Solution s;
    auto path = "/home/user/Documents/../Pictures";
    auto ret = s.simplifyPath(path);
    EXPECT_EQ("/home/user/Pictures", ret);
}
