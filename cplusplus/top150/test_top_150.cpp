//
// Created by hanvs on 2025/5/26.
//
#include <gtest/gtest.h>

#include <algorithm>
#include <vector>
#include <iterator>

using namespace std;

TEST(TOP150, No88_MergeTwoSortedLists) {
    class Solution {
       public:
        void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
            std::vector<int> container;
            container.reserve(m + n);

            int pos1 = 0, pos2 = 0;
            while (pos1 < m && pos2 < n) {
                if (nums1[pos1] < nums2[pos2]) {
                    container.emplace_back(nums1[pos1++]);
                } else {
                    container.emplace_back(nums2[pos2++]);
                }
            }

            while (pos1 < m) {
                container.emplace_back(nums1[pos1++]);
            }

            while (pos2 < n) {
                container.emplace_back(nums2[pos2++]);
            }

            nums1 = container;
        }
    };

    Solution solution;
    vector<int> nums1{1, 3, 5};
    vector<int> nums2{2, 4, 6};

    solution.merge(nums1, 3, nums2, 3);
    for (auto& i : nums1) {
        cout << i << ", ";
    }

    cout << std::endl;
}

TEST(TOP150, NO27_RemoveElement) {
    class Solution {
       public:
        int removeElement(vector<int>& nums, int val) {
            for (auto it = nums.begin(); it != nums.end();) {
                if (*it == val) {
                    it = nums.erase(it);
                } else {
                    it++;
                }
            }

            return nums.size();
        }
    };

    Solution solution;

    vector<int> nums{3, 2, 2, 3};
    int val = 3;

    int k = solution.removeElement(nums, val);

    cout << k << std::endl;
}

TEST(TOP150, NO26_RemoveDuplicatesFromSortedArray) {
    class Solution {
       public:
        int removeDuplicates(vector<int>& nums) {
            for (auto it = nums.begin(); it != nums.end() - 1;) {
                if (*it == *(it + 1)) {
                    it = nums.erase(it);
                } else {
                    it++;
                }
            }

            return nums.size();
        }
    };

    Solution solution;
    std::vector<int> nums{1, 1, 2};
    auto ret = solution.removeDuplicates(nums);
    assert(ret == 2);
}

TEST(TOP150, NO80_RemoveDeplicates) {
    class Solution {
       public:
        int removeDuplicates(vector<int>& nums) {
            for (auto it = nums.begin(); it < nums.end() - 2;) {
                if (*it == *(it + 2)) {
                    it + 2 = nums.erase(it + 2);
                } else {
                    it++;
                }
            }
            return nums.size();
        }
    };

    Solution solution;

    std::vector<int> nums{1, 1, 1, 2, 2, 3};
    auto ret = solution.removeDuplicates(nums);

    EXPECT_EQ(ret, 5);
}

TEST(TOP150, NO169_MajorityElement) {
    class Solution {
       public:
        int majorityElement(vector<int>& nums) {
            auto candidates = -1;
            auto count = 0;
            for (auto& i : nums) {
                if (candidates == i) {
                    count++;
                } else if (count-- < 0) {
                    candidates = i;
                    count = 1;
                }
            }

            return nums.size();
        }
    };

    Solution solution;
    std::vector<int> nums{3, 2, 3};
    auto ret = solution.majorityElement(nums);

    EXPECT_EQ(ret, 3);
}

TEST(TOP150, NO189_Rotate) {
    class Solution {
       public:
        void rotate(vector<int>& nums, int k) {
            auto real_steps = k % nums.size();
            std::vector<int> container(nums.end() - real_steps, nums.end());
            container.insert(container.end(), nums.begin(), nums.end() - real_steps);
            nums = container;
        }
    };

    Solution solution;
    std::vector<int> nums{-1,-100,3,99};
    auto k = 2;
    solution.rotate(nums, k);
}

TEST(TOP150, NO121_MaxProfit) {
    class Solution {
    public:
        int maxProfit(vector<int>& prices) {
            auto ret = 0;
            auto min_price = prices[0];
            for (auto i = 1; i < prices.size(); i++) {
                if (prices[i] < min_price) {
                    min_price = prices[i];
                } else {
                    ret = std::max(ret, prices[i] - min_price);
                }
            }
        }
    };

    Solution solution;
    std::vector<int> prices{7, 1, 5, 3, 6, 4};
    auto ret = solution.maxProfit(prices);

    EXPECT_EQ(ret, 5);
}

TEST(TOP150, NO122_MaxProfit) {
    class Solution {
    public:
        int maxProfit(vector<int>& prices) {
            auto n = prices.size();
            std::vector<std::vector<int>> dp(n, std::vector<int>(2, 0));

            dp[0][0] = 0;
            dp[0][1] = -prices[0];
            for (int i = 1; i < n; i++) {
                dp[i][0] = std::max(dp[i - 1][0], dp[i - 1][1] + prices[i]);
                dp[i][1] = std::max(dp[i - 1][1], dp[i - 1][0] - prices[i]);
            }

            std::cout << "0: " << std::endl;
            for (auto i = 0; i < n; i++) {
                std::cout << dp[i][0] << ", ";
            }

            std::cout << std::endl;

            std::cout << "1: " << std::endl;
            for (auto i = 0 ; i < n; i++) {
                std::cout << dp[i][1] << ", ";
            }

            return dp[n-1][0];

        }
    };

    Solution solution;
    std::vector<int> prices{7, 1, 5, 3, 6, 4};
    auto ret = solution.maxProfit(prices);
    EXPECT_EQ(ret, 7);
}

TEST(TOP150, NO55_CanJump) {
    class Solution {
    public:
        bool canJump(vector<int>& nums) {
            auto right_most = 0;
            for (auto i = 0; i < nums.size(); i++) {
                if (i <= right_most) {
                    right_most = std::max(right_most, i + nums[i]);
                    if (right_most >= nums.size() - 1) {
                        return true;
                    }
                }
            }

            return false;
        }
    };

    Solution solution;
    vector<int> nums{2,3,1,1,4};
    auto ret = solution.canJump(nums);
    EXPECT_EQ(ret, true);
}

TEST(TOP150, NO45_jump) {
    class Solution {
    public:
        int jump(vector<int>& nums) {
            auto max_pos = 0;
            auto end = 0;
            auto ret = 0;

            for (auto i = 0;i < nums.size() - 1; i++) {
                if (max_pos >= i) {
                    max_pos = std::max(max_pos, i + nums[i]);
                    if (i == end) {
                        end = max_pos;
                        ret++;
                    }
                }
            }

            return ret;
        }
    };
    Solution solution;
    std::vector<int> nums{2,3,1,1,4};
    auto ret = solution.jump(nums);
    EXPECT_EQ(ret, 2);
}

TEST(TOP150, NO274_HIndex) {
    class Solution {
    public:
        int hIndex(vector<int>& citations) {
            std::sort(citations.begin(), citations.end(), std::greater<int>());
            auto ret = 0;

            for (auto i = 0; i < citations.size(); i++) {
                if (citations[i] > ret) {
                    ret++;
                }
            }

            return ret;
        }
    };

    Solution solution;
    std::vector<int> citations{3,0,6,1,5};
    auto ret = solution.hIndex(citations);
    EXPECT_EQ(ret, 3);
}

TEST(TOP150, NO380_RandomizedSet) {
    class RandomizedSet {
    private:
        std::set<int> container;
    public:
        RandomizedSet() {}

        bool insert(int val) {
            if (container.find(val) == container.end()) {
                container.insert(val);
                return true;
            }

            return false;
        }

        bool remove(int val) {
            if (container.find(val) != container.end()) {
                container.erase(val);
                return true;
            }

            return false;
        }

        int getRandom() {
            auto it = container.begin();
            std::advance(it, rand() % container.size());
            return *it;
        }
    };

    RandomizedSet randomizedSet;

    bool param_1 = randomizedSet.insert(1);
    EXPECT_EQ(param_1, true);
    bool param_2 = randomizedSet.remove(2);
    EXPECT_EQ(param_2, false);

    bool param_3 = randomizedSet.insert(2);
    EXPECT_EQ(param_3, true);

    auto ret = randomizedSet.getRandom();
    EXPECT_TRUE(ret == 2 || ret == 1);

    auto param_4 = randomizedSet.remove(1);
    EXPECT_EQ(param_4, true);

    auto param_5 = randomizedSet.insert(2);
    EXPECT_EQ(param_5, false);

    ret =randomizedSet.getRandom();
    EXPECT_TRUE(ret == 2);
}

TEST(TOP150, NO239_ProductExceptSelf) {
    class Solution {
    public:
        vector<int> productExceptSelf(vector<int>& nums) {
            std::vector<int> ret(nums.begin(), nums.end());

            int zero_count = 0;
            int64_t total = 1;

            for (auto i = 0; i < nums.size(); i++) {
                if (nums[i] == 0) {
                    zero_count++;
                } else {
                    total *= nums[i];
                }
            }

            if (zero_count >= 2) {
                return std::vector<int>(nums.size(), 0);
            }

            for (auto i = 0; i < nums.size(); i++) {
                if (zero_count == 1) {
                    if (nums[i] == 0) {
                        ret[i] = total;
                    }else {
                        ret[i] = 0;
                    }
                } else {
                    ret[i] = total / nums[i];
                }
            }


            return ret;
        }
    };
    Solution solution;
    std::vector<int> nums{1,2,3,4};
    auto ret = solution.productExceptSelf(nums);
    EXPECT_EQ(ret.size(), 4);
}

TEST(TOP150, NO134_CanCompleteCircuit) {
    class Solution {
    public:
        int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
            std::vector<int> container;
            auto min_gas = INT_MAX;
            auto min_idx = 0;
            auto left = 0;

            for (auto i = 0; i < gas.size(); i++) {
                left += gas[i] - cost[i];
                if (min_gas > left) {
                    min_gas = left;
                    min_idx = i;
                }
            }

            return left < 0 ? -1 : (min_idx + 1) % gas.size();
        }
    };

    Solution solution;
    std::vector<int> gas{1,2,3, 4, 5};
    std::vector<int> cost{3,4,5,1,2};
    auto ret = solution.canCompleteCircuit(gas, cost);
    EXPECT_EQ(ret, 3);
}