/*  -*- coding: utf-8 -*-
 * File    : 283_Move_zeroes.cpp
 * Author  : MeteorDream
 * Time    : 2021/07/24 13:50:29
 * language: C/C++
 * Software: Visual Studio Code
*/

#include "LeetCode.h"

#ifdef __283__

/* 
[283. 移动零](https://leetcode-cn.com/problems/move-zeroes/)

难度: 简单

题解：


*/

/* 双指针 
class Solution {
public:
    void moveZeroes(vector<int>& nums) {
        int i = 0, j = 0, n = nums.size();
        for (; j < n; ++j) {
            if (nums[j] != 0)
                nums[i++] = nums[j];
        }
        while (i < n) nums[i++] = 0;
    }
};*/

/* 排序 */
class Solution {
public:
    void moveZeroes(vector<int>& nums) {
        stable_sort(nums.begin(), nums.end(), [&](const int a, const int b) -> bool {
            if (b == 0)
                return true;
            else
                return false;
        });
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