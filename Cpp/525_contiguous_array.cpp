/*     -*- coding: utf-8 -*-     */
/* File    : 525_contiguous_array.cpp */
/* Author  : MeteorDream         */
/* Time    : 2021/06/03 16:54:58 */
/* language: C/C++               */
/* Software: Visual Studio Code  */

#include "LeetCode.h"

#ifdef __525__

/* 
525. 连续数组

难度: 中等

*/

class Solution {
public:
    int findMaxLength(vector<int>& nums) {
        // 前缀和
        // 1. 预处理数组，将 0 改为 -1，使得 0 和 1 数量相等的子数组和为 0
        // 2. 使用 HashMap 记录(前缀和,下标)，一次遍历计算得结果
        int n = nums.size(), ans = 0, s = 0;
        unordered_map<int, int> st{{0, -1}};
        for (int i = 0; i < n; ++i) {
            s += (nums[i] == 1 ? 1 : -1);
            if (st.find(s) == st.end())
                st.emplace(s, i);
            else
                ans = max(ans, i - st[s]);
        }
        return ans;
    }
};

int Submit() {
    Solution s;

    /* 输入 */
    cout << "输入:" << endl;
    vector<int> nums{1, 1, 1, 0, 0};

    /* 输出 */
    cout << "输出:" << endl;
    cout << s.findMaxLength(nums) << endl;

    return 0;
}

#endif