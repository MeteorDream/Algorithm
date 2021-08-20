/*  -*- coding: utf-8 -*-
 * File    : 167_Two_sum_ii_input_array_is_sorted.cpp
 * Author  : MeteorDream
 * Time    : 2021/07/24 12:31:56
 * language: C/C++
 * Software: Visual Studio Code
*/

#include "LeetCode.h"

#ifdef __167__

/* 
[167. 两数之和 II - 输入有序数组](https://leetcode-cn.com/problems/two-sum-ii-input-array-is-sorted/)

难度: 简单

题解：


*/

/* 双指针 
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        int n = nums.size();
        for (int i = 0, j = n - 1; i < j;) {
            int s = nums[i] + nums[j];
            if (s < target)
                ++i;
            else if (s > target)
                --j;
            else
                return vector<int>{i + 1, j + 1};
        }
        return vector<int>{-1, -1};
    }
};*/

/* 双指针 + 二分查找 */
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        int n = nums.size();
        for (int i = 0, j = n - 1; i < j;) {
            int s = nums[i] + nums[j];
            if (s < target) {
                int left = i + 1, right = j - 1;
                while (left < right) {
                    int mid = left + right >> 1;
                    int sum = nums[mid] + nums[j];
                    if (sum < target)
                        left = mid + 1;
                    else if (sum > target)
                        right = mid - 1;
                    else
                        return vector<int>{mid + 1, j + 1};
                }
                i = left;
            }
            else if (s > target) {
                int left = i + 1, right = j - 1;
                while (left < right) {
                    int mid = left + right >> 1;
                    int sum = nums[i] + nums[mid];
                    if (sum < target)
                        left = mid + 1;
                    else if (sum > target)
                        right = mid - 1;
                    else
                        return vector<int>{i + 1, mid + 1};
                }
                j = left;
            }
            else
                return vector<int>{i + 1, j + 1};
        }
        return vector<int>{-1, -1};
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