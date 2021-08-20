/*  -*- coding: utf-8 -*-
 * File    : 189_Rotate_array.cpp
 * Author  : MeteorDream
 * Time    : 2021/07/24 01:11:14
 * language: C/C++
 * Software: Visual Studio Code
*/

#include "LeetCode.h"

#ifdef __189__

/* 
[189. 旋转数组](https://leetcode-cn.com/problems/rotate-array/)

难度: 中等

题解：


*/

/* 复制数组 
class Solution {
public:
    void rotate(vector<int>& nums, int k) {
        int n = nums.size();
        vector<int> s(n);
        k %= n;
        for (int i = 0; i < n; ++i)
            s[(i + k) % n] = nums[i];
        for (int i = 0; i < n; ++i)
            nums[i] = s[i];
    }
};*/

/* 循环交换 
class Solution {
public:
    void rotate(vector<int>& nums, int k) {
        int n = nums.size(), cnt = 0;
        k %= n;
        for (int i = 0; i < n; ++i) {
            int prev = nums[i];
            for (int j = (i + k) % n; j != i; j = (j + k) % n) {
                swap(nums[j], prev);
                ++cnt;
            }
            swap(nums[i], prev);
            ++cnt;
            if (cnt == n) break;
        }
    }
};*/

/* 三次翻转 */
class Solution {
public:
    void rotate(vector<int>& nums, int k) {
        k %= nums.size();
        reverse(nums.begin(), nums.end());
        reverse(nums.begin(), nums.begin() + k);
        reverse(nums.begin() + k, nums.end());
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