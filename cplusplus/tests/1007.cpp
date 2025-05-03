#include <gtest/gtest.h>
#include <vector>

// Demonstrate some basic assertions.
TEST(HelloTest, BasicAssertions) {
    /**
     * 1007. Minimum Domino Rotations For Equal Row
     *
     * In a row of dominoes, tops[i] and bottoms[i] represent the top and bottom halves of the ith domino. (A domino is a tile with two numbers from 1 to 6 - one on each half of the tile.)
     *
     * We may rotate the ith domino, so that tops[i] and bottoms[i] swap values.
     *
     * Return the minimum number of rotations so that all the values in tops are the same, or all the values in bottoms are the same.
     *
     * If it cannot be done, return -1.
     *
     * Example 1:
     * Input: tops = [2,1,2,4,2,2], bottoms = [5,2,6,2,3,2]
     * Output: 2
     * Explanation:
     * The first figure represents the dominoes as given by tops and bottoms: before we do any rotations.
     * If we rotate the second and fourth dominoes, we can make every value in the top row equal to 2, as indicated by the second figure.
     *
     * Example 2:
     * Input: tops = [3,5,1,2,3], bottoms = [3,6,3,3,4]
     * Output: -1
     * Explanation:
     * In this case, it is not possible to rotate the dominoes to make one row of values equal.
     **/
    class Solution {
    public:
        int minDominoRotations(std::vector<int>& tops, std::vector<int>& bottoms) {
            auto length = (int)tops.size();

            auto target = std::vector<int>{tops[0], bottoms[0]};
            if (target.at(0) == target.at(1)) {
                target.pop_back();
            }
            auto result = INT_MAX;

            for (auto &t : target) {
                auto top_rotation_times = 0;
                auto bottom_rotation_times = 0;
                for (auto i = 0; i< length; i++) {
                    if (tops[i] != t && bottoms[i] != t) {
                        top_rotation_times = INT_MAX;
                        break;
                    }

                    if (tops[i] == t && bottoms[i] != t) {
                        bottom_rotation_times++;
                    }

                    if (tops[i] != t && bottoms[i] == t) {
                        top_rotation_times++;
                    }
                }

                if (top_rotation_times != INT_MAX){
                    result = std::min(result, top_rotation_times);
                    result = std::min(result, bottom_rotation_times);
                }
            }

            return result == INT_MAX ? -1 : result;
        }
    };
    Solution s;
    std::vector<int> tops = {1,2,1,1,1,2,2,2};
    std::vector<int> bottoms = {2,1,2,2,2,2,2,2};
    ASSERT_EQ(s.minDominoRotations(tops, bottoms), 1);
}