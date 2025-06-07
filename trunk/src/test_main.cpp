#include <gtest/gtest.h>
#include <cmath>
// Example test case
TEST(SampleTest, AssertionTrue) {
    EXPECT_TRUE(false);
}

TEST(Daily, 20250330) {
    // No.2109
    class Solution {
        public:
            std::string addSpaces(std::string s, std::vector<int> spaces) {
                // for (auto i = 0; i < spaces.size(); ++i) {
                //     auto index = spaces[i] + i;
                //     s.insert(index, " ");
                // }
                // return s;
                std::string result;
                auto i = 0, j = 0;
                for (; i < s.size(); i++) {
                    if (i == spaces[j]) {
                        result += ' ';
                        j++;
                    }
                    result += s[i];
                }

                return result;

            }
    };

    auto s = Solution();

    auto output = s.addSpaces("icodeinpython", { 1,5,7,9 });
    auto expect = "Leetcode Helps Me Learn";
    EXPECT_EQ(output, expect);
}

TEST(Daily, 20250420) {
    class Solution {
    public:
        int numRabbits(std::vector<int>& answers) {
            std::vector<int> container (1000, 0);
            for (auto i : answers) {
                container[i]++;
            }

            int ret =0;
            for (auto i = 0; i < container.size(); i++) {
                if (container[i] == 0) {
                    continue;
                }

                ret += int(std::ceil(container[i] * 1.0 / (i+1))) * (i+1);
            }
            return ret;
        }
    };

    Solution s;
    auto input = std::vector<int>{10, 10, 10};
    auto ret = s.numRabbits(input);
    std::cout << ret << std::endl;
}