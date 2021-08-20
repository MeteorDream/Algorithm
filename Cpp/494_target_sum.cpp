/*     -*- coding: utf-8 -*-     */
/* File    : 494_target_sum.cpp */
/* Author  : MeteorDream         */
/* Time    : 2021/06/08 11:38:51 */
/* language: C/C++               */
/* Software: Visual Studio Code  */

#include "LeetCode.h"

#ifdef __494__

/* 
[494. 目标和](https://leetcode-cn.com/problems/target-sum/)

难度: 中等

*/

/* // 深度优先搜索 
class Solution {
public:
    int findTargetSumWays(vector<int>& nums, int target) {
        return dfs(nums, 0, 0, target);
    }

    int dfs(vector<int>& nums, int i, int s, int target) {
        if (i == nums.size())
            if (s == target)
                return 1;
            else
                return 0;
        return dfs(nums, i + 1, s + nums[i], target) + dfs(nums, i + 1, s - nums[i], target);
    }
};*/

/* // 记忆化dfs 
class Solution {
public:
    int findTargetSumWays(vector<int>& nums, int target) {
        vector<vector<int>> memory(nums.size(), vector<int>(2007, -1));
        return dfs(nums, 0, 0, target, memory);
    }

    int dfs(vector<int>& nums, int i, int s, int target, vector<vector<int>>& memory) {
        if (i == nums.size()) {
            if (s == target)
                return 1;
            else
                return 0;
        }
        else if (memory[i][s + 1000] == -1)
            memory[i][s + 1000] = dfs(nums, i + 1, s + nums[i], target, memory) + dfs(nums, i + 1, s - nums[i], target, memory);
        return memory[i][s + 1000];
    }
};*/

/* // 广度优先搜索 
class Solution {
public:
    int findTargetSumWays(vector<int>& nums, int target) {
        int n = nums.size();
        unordered_map<int, int> s;
        ++s[nums[0]];
        ++s[-nums[0]];
        for (int i = 1; i < n; ++i) {
            unordered_map<int, int> tmp;
            swap(s, tmp);
            for (auto k : tmp) {
                s[k.first + nums[i]] += k.second;
                s[k.first - nums[i]] += k.second;
            }
        }
        return s[target];
    }
};*/

/* // 动态规划 */
class Solution {
public:
    int findTargetSumWays(vector<int>& nums, int target) {
        int n = nums.size(), s = 0;
        for (int i : nums)
            s += abs(i);
        if (target > s)
            return 0;
        vector<vector<int>> dp(n + 1, vector<int>(2 * s + 1));
        dp[0][s] = 1;
        for (int i = 1; i <= n; ++i) {
            int tmp = nums[i - 1];
            for (int j = -s; j <= s; ++j) {
                if ((j - tmp) + s >= 0)
                    dp[i][j + s] += dp[i - 1][(j - tmp) + s];
                if ((j + tmp) + s <= 2 * s)
                    dp[i][j + s] += dp[i - 1][(j + tmp) + s];
            }
        }
        return dp[n][target + s];
    }
};

int Submit() {
    Solution s;

    /* 输入 */
    cout << "输入:" << endl;

    /* 输出 */
    cout << "输出:" << endl;

    return 0;
}

#endif