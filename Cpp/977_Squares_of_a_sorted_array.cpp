/*  -*- coding: utf-8 -*-
 * File    : 977_Squares_of_a_sorted_array.cpp
 * Author  : MeteorDream
 * Time    : 2021/07/23 15:31:03
 * language: C/C++
 * Software: Visual Studio Code
*/

#include "LeetCode.h"

#ifdef __977__

/* 
[977. 有序数组的平方](https://leetcode-cn.com/problems/squares-of-a-sorted-array/)

难度: 简单

题解：https://leetcode-cn.com/problems/squares-of-a-sorted-array/solution/you-xu-shu-zu-de-ping-fang-gui-bing-pai-5r2ue/


*/

/* 排序 
class Solution {
public:
    vector<int> sortedSquares(vector<int>& nums) {
        int n = nums.size();
        vector<int> s(nums);
        for (int i = 0; i < n; ++i)
            s[i] *= s[i];
        sort(s.begin(), s.end());
        return s;
    }
};*/

/* 归并排序 
class Solution {
public:
    vector<int> sortedSquares(vector<int>& nums) {
        int n = nums.size();
        vector<int> s(n);
        // 二分查找 分割点
        auto right = lower_bound(nums.begin(), nums.end(), 0);
        auto left = right - 1;
        for (int i = 0; i < n; ++i) {
            if (left < nums.begin() || (right != nums.end() && -(*left) > (*right))) {
                s[i] = pow(*right, 2);
                ++right;
            }
            else {
                s[i] = pow(*left, 2);
                --left;
            }
        }
        return s;
    }
};*/

/* 双指针 */
class Solution {
public:
    vector<int> sortedSquares(vector<int>& nums) {
        int n = nums.size();
        vector<int> s(n);
        auto left = nums.begin();
        auto right = nums.rbegin();
        for (int i = n - 1; i >= 0; --i) {
            if (-(*left) < (*right)) {
                s[i] = pow(*right, 2);
                ++right;
            }
            else {
                s[i] = pow(*left, 2);
                ++left;
            }
        }
        return s;
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