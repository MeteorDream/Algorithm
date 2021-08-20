/*     -*- coding: utf-8 -*-     */
/* File    : 162_FindPeakElement.cpp */
/* Author  : MeteorDream         */
/* Time    : 2021/06/16 11:07:20 */
/* language: C/C++               */
/* Software: Visual Studio Code  */

#include "LeetCode.h"

#ifdef __162__

/* 
[162. 寻找峰值](https://leetcode-cn.com/problems/find-peak-element/)

难度: 中等

*/

/* 简单顺序查找
class Solution {
public:
    int findPeakElement(vector<int>& nums) {
        int n = nums.size();
        if (n <= 1 || nums[0] > nums[1])
            return 0;
        for (int i = 1; i < n - 1; ++i)
            if (nums[i] > nums[i + 1] && nums[i] > nums[i - 1])
                return i;
        return n - 1;
    }
}; */

/* 二分查找 */
class Solution {
public:
    int findPeakElement(vector<int>& nums) {
        int n = nums.size();
        if (n <= 1 || nums[0] > nums[1])
            return 0;
        if (nums[n - 1] > nums[n - 2])
            return n - 1;
        int lo = 1, hi = n - 1;
        while (lo < hi) {
            int mid = lo + (hi - lo >> 1);
            if (nums[mid] > nums[mid + 1])
                hi = mid;
            else
                lo = mid + 1;
        }
        return lo;
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