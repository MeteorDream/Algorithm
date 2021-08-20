/*  -*- coding: utf-8 -*-
 * File    : 1818_Minimum_absolute_sum_difference.cpp
 * Author  : MeteorDream
 * Time    : 2021/07/14 13:14:34
 * language: C/C++
 * Software: Visual Studio Code
*/

#include "LeetCode.h"

#ifdef __1818__

/* 
[1818. 绝对差值和](https://leetcode-cn.com/problems/minimum-absolute-sum-difference/)

难度: 中等

题解：https://leetcode-cn.com/problems/minimum-absolute-sum-difference/solution/jue-dui-chai-zhi-he-mei-ju-er-fen-by-met-8ec4/


*/

class Solution {
public:
    int minAbsoluteSumDiff(vector<int>& nums1, vector<int>& nums2) {
        int n = nums1.size();
        vector<int> st(nums1);
        sort(st.begin(), st.end());
        long s = 0, mx = 0;
        for (int i = 0; i < n; ++i) {
            int x = nums1[i], y = nums2[i];
            if (x == y) continue;
            int z = abs(x - y);
            s += z;
            int left = 0, right = n - 1;
            while (left < right) {
                int mid = left + right >> 1;
                if (st[mid] < y)
                    left = mid + 1;
                else
                    right = mid;
            }
            mx = max(mx, (long)z - min(abs(st[left] - y), (left - 1 > 0 ? abs(st[left - 1] - y) : z)));
        }
        return (s - mx) % 1000000007;
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