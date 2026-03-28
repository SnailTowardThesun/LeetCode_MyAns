//
// Created by 韩堃 on 2025/12/9.
//
#include <gtest/gtest.h>
#include <vector>
#include <unordered_map>

TEST(Daily, 3583) {
    class Solution {
    public:
        static std::size_t lower_position(const std::vector<int> &vec, int key) noexcept {
            std::size_t low = 0;
            std::size_t high = vec.size(); // 开区间 [low, high)

            while (low < high) {
                std::size_t mid = low + (high - low) / 2;
                if (vec[mid] <= key)
                    low = mid + 1; // 舍弃左半段
                else
                    high = mid; // 舍弃右半段（含 mid）
            }
            return low; // low 即为所求位置
        }

        int specialTriplets(std::vector<int> &nums) {
            if (nums.size() < 2) {
                return 0;
            }

            int64_t result = 0;

            std::unordered_map<int, std::vector<int> > container;

            for (auto i = 0; i < nums.size(); ++i) {
                if (container.find(nums[i]) == container.end()) {
                    container[nums[i]] = std::vector<int>();
                }

                container[nums[i]].push_back(i);
            }

            for (auto &it: container) {
                // sort it->second
                std::sort(it.second.begin(), it.second.end());
            }

            for (auto i = 1; i < nums.size() - 1; i++) {
                auto target = nums[i] * 2;
                auto it = container.find(target);
                if (it == container.end()) {
                    continue;
                }

                auto pos = lower_position(it->second, i);
                if (target == 0) {
                    result += int(pos) * (it->second.size() - pos - 1);
                } else {
                    result += int(pos) * (it->second.size() - pos);
                }
            }

            return int(result % 1000000007);
        }
    };
    Solution solution;

    // auto eg = std::vector<int> {6,3,6};
    auto eg = std::vector<int>{0, 1, 0, 0};
    // auto eg = std::vector<int>{8, 4, 2, 8, 4};
    auto ret = solution.specialTriplets(eg);
    EXPECT_EQ(ret, 2);
}
