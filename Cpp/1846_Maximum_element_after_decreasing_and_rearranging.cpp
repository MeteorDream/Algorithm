/*  -*- coding: utf-8 -*-
 * File    : 1846_Maximum_element_after_decreasing_and_rearranging.cpp
 * Author  : MeteorDream
 * Time    : 2021/07/15 22:39:17
 * language: C/C++
 * Software: Visual Studio Code
*/

#include "LeetCode.h"

#ifdef __1846__

/* 
[1846. 减小和重新排列数组后的最大元素](https://leetcode-cn.com/problems/maximum-element-after-decreasing-and-rearranging/)

难度: 中等

题解：https://leetcode-cn.com/problems/maximum-element-after-decreasing-and-rearranging/solution/jian-xiao-he-zhong-xin-pai-lie-shu-zu-ho-sv8z/


*/

/* 排序+贪心 */
class Solution {
public:
    int maximumElementAfterDecrementingAndRearranging(vector<int>& arr) {
        int n = arr.size();
        sort(arr.begin(), arr.end());
        arr[0] = 1;
        for (int i = 1; i < n; ++i) {
            if (arr[i] > arr[i - 1] + 1)
                arr[i] = arr[i - 1] + 1;
        }
        return arr[n - 1];
    }
};

/* 计数排序 
class Solution {
public:
    int maximumElementAfterDecrementingAndRearranging(vector<int>& arr) {
        int n = arr.size();
        vector<int> s(n + 1);
        for (auto& a : arr) {
            if (a > n)
                ++s[n];
            else
                ++s[a];
        }
        int cnt = 0, k = 0;
        for (int i = n; i > 0; --i) {
            if (s[i] != 0)
                k += s[i] - 1;
            else if (k != 0)
                --k;
            else
                ++cnt;
        }
        return n - cnt;
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