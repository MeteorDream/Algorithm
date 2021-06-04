/*     -*- coding: utf-8 -*-     */
/* File    : 477_total_hamming_distance.cpp */
/* Author  : MeteorDream         */
/* Time    : 2021/05/28 00:26:36 */
/* language: C/C++               */
/* Software: Visual Studio Code  */

#include "LeetCode.h"

#ifdef __477__

/* 
[477. 汉明距离总和](https://leetcode-cn.com/problems/total-hamming-distance/)

难度: 中等

*/

/*  
class Solution {
public:
    // 暴力解法，TLE
    int totalHammingDistance(vector<int>& nums) {
        int n = nums.size(), ans = 0;
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < i; ++j)
                for (int k = nums[i] ^ nums[j]; k != 0; k &= k - 1)
                    ++ans;
        return ans;
    }
};
*/

class Solution {
public:
    /* // 按位求值 
    int totalHammingDistance(vector<int>& nums) {
        int n = nums.size(), sum = 1, ans = 0;
        while (sum != 0) {
            sum = 0;
            int zero = 0, one = 0;
            for (int i = 0; i < n; ++i) {
                if (nums[i] & 1)
                    ++one;
                else
                    ++zero;
                nums[i] >>= 1;
                if (nums[i])
                    ++sum;
            }
            ans += zero * one;
        }
        return ans;
    }*/

    /* // 按位求值优化 */
    int totalHammingDistance(vector<int>& nums) {
        int n = nums.size(), ans = 0;
        for (int i = 0; i < 32; ++i) {
            int s = 0;    // 统计第i位为1的数量
            for (int num : nums)
                if (num & (1 << i))
                    ++s;
            ans += s * (n - s);
        }
        return ans;
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