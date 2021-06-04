/*     -*- coding: utf-8 -*-     */
/* File    : 523_continuous_subarray_sum.cpp */
/* Author  : MeteorDream         */
/* Time    : 2021/06/02 10:34:58 */
/* language: C/C++               */
/* Software: Visual Studio Code  */

#include "LeetCode.h"

#ifdef __523__

/* 
[523. 连续的子数组和](https://leetcode-cn.com/problems/continuous-subarray-sum/)

难度: 中等

OJ:
[23,2,4,6,7]
6
[23,2,6,4,7]
6
[23,2,6,4,7]
13
[0,1,1,1]
19
[0,1,2,3]
6
[23,2,4,6,6]
7
[1,0]
2

*/

class Solution {
public:
    bool checkSubarraySum(vector<int>& nums, int k) {
        int n = nums.size(), sum = 0;
        unordered_map<int, int> s{pair(0, -1)};
        for (int i = 0; i < n; ++i) {
            sum = (sum + nums[i]) % k;
            if (s.find(sum) == s.end())
                s.emplace(sum, i);
            else if (s[sum] + 1 < i)
                return true;
        }
        return false;
    }
};

int Submit() {
    Solution s;

    /* 输入 */
    cout << "输入:" << endl;
    vector<int> nums = {23, 2, 4, 6, 6};
    int k = 7;

    /* 输出 */
    cout << "输出:" << endl;
    s.checkSubarraySum(nums, k);

    return 0;
}

#endif