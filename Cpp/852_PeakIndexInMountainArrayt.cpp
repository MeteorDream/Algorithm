/*     -*- coding: utf-8 -*-     */
/* File    : 852_peakIndexInMountainArrayt.cpp */
/* Author  : MeteorDream         */
/* Time    : 2021/06/16 11:03:58 */
/* language: C/C++               */
/* Software: Visual Studio Code  */

#include "LeetCode.h"

#ifdef __852__

/* 
[852. 山脉数组的峰顶索引](https://leetcode-cn.com/problems/peak-index-in-a-mountain-array/)

难度: 简单


*/

/* 顺序查找
class Solution {
public:
    int peakIndexInMountainArray(vector<int>& arr) {
        int n = arr.size() - 1;
        for (int i = 1; i < n; ++i) {
            if (arr[i] > arr[i + 1])
                return i;
        }
        return n;
    }
}; */

/* 二分查找 */
class Solution {
public:
    int peakIndexInMountainArray(vector<int>& arr) {
        int left = 1, right = arr.size() - 1;
        while (left < right) {
            int mid = left + (right - left) / 2;
            if (arr[mid] > arr[mid + 1])
                right = mid;
            else
                left = mid + 1;
        }
        return left;
    }
};

/* 三分查找
class Solution {
public:
    int peakIndexInMountainArray(vector<int>& arr) {
        int left = 1, right = arr.size() - 1;
        while (left < right) {
            int m = (right - left) / 3;
            int m1 = left + m, m2 = right - m;
            if (arr[m1] > arr[m2])
                right = m2 - 1;
            else
                left = m1 + 1;
        }
        return left;
    }
}; */

/* 伪三分查找(变形二分查找)
class Solution {
public:
    int peakIndexInMountainArray(vector<int>& arr) {
        int left = 1, right = arr.size() - 2;
        while (left < right) {
            int m = (right - left) / 3;
            int m1 = left + m, m2 = right - m;
            if (arr[m1] > arr[m1 + 1])
                right = m1;
            else if (arr[m2] < arr[m2 + 1])
                left = m2 + 1;
            else {
                left = m1 + 1;
                right = m2;
            }
        }
        return left;
    }
}; */

int Submit() {
    Solution s;

    /* 输入 */
    cout << "输入:" << endl;

    /* 输出 */
    cout << "输出:" << endl;

    return 0;
}

#endif