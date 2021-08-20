/*  -*- coding: utf-8 -*-
 * File    : 35_Search_insert_position.cpp
 * Author  : MeteorDream
 * Time    : 2021/07/22 20:50:09
 * language: C/C++
 * Software: Visual Studio Code
*/

#include "LeetCode.h"

#ifdef __035__

/* 
[35. 搜索插入位置](https://leetcode-cn.com/problems/search-insert-position/)

难度: 简单

题解：https://leetcode-cn.com/problems/search-insert-position/solution/sou-suo-cha-ru-wei-zhi-jian-dan-er-fen-m-3bla/


*/

/* 顺序搜索 
class Solution {
public:
    int searchInsert(vector<int>& nums, int target) {
        int n = nums.size();
        for (int i = 0; i < n; ++i) {
            if (nums[i] >= target)
                return i;
        }
        return n;
    }
};*/

/* 二分搜索 
class Solution {
public:
    int searchInsert(vector<int>& nums, int target) {
        int left = 0, right = nums.size();
        while (left < right) {
            int mid = left + (right - left >> 1);
            if (nums[mid] < target)
                left = mid + 1;
            else
                right = mid;
        }
        return left;
    }
};*/

/* 二分搜索API */
class Solution {
public:
    int searchInsert(vector<int>& nums, int target) {
        return distance(nums.begin(), lower_bound(nums.begin(), nums.end(), target));
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