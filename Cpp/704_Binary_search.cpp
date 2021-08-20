/*  -*- coding: utf-8 -*-
 * File    : 704_Binary_search.cpp
 * Author  : MeteorDream
 * Time    : 2021/07/22 22:23:59
 * language: C/C++
 * Software: Visual Studio Code
*/

#include "LeetCode.h"

#ifdef __704__

/* 
[704. 二分查找](https://leetcode-cn.com/problems/binary-search/)

难度: 简单

题解：https://leetcode-cn.com/problems/binary-search/solution/er-fen-cha-zhao-er-fen-cha-zhao-by-meteo-mt0f/


*/

/* 顺序查找 
class Solution {
public:
    int search(vector<int>& nums, int target) {
        int n = nums.size();
        for (int i = 0; i < n; ++i)
            if (nums[i] == target)
                return i;
            else if (nums[i] > target)
                return -1;
        return -1;
    }
};*/

/* 二分查找 */
class Solution {
public:
    int search(vector<int>& nums, int target) {
        int left = 0, right = nums.size() - 1;
        while (left <= right) {
            int mid = left + (right - left >> 1);
            if (nums[mid] == target)
                return mid;
            else if (nums[mid] > target)
                right = mid - 1;
            else
                left = mid + 1;
        }
        return -1;
    }
};

/* STL 
class Solution {
public:
    int search(vector<int>& nums, int target) {
        auto ans = distance(nums.begin(), lower_bound(nums.begin(), nums.end(), target));
        return nums[ans] == target ? ans : -1;
    }
};*/

int Submit() {
    Solution s;

    /* 输入 */
    cout << "输入:" << endl;

    /* 输出 */
    cout << "输出:" << endl;

    return 0;
}

#endif