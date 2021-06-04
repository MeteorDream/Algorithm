/*     -*- coding: utf-8 -*-     */
/* File    : 1074_number_of_submatrices_that_sum_to_target.cpp */
/* Author  : MeteorDream         */
/* Time    : 2021/05/29 11:00:15 */
/* language: C/C++               */
/* Software: Visual Studio Code  */

#include "LeetCode.h"

#ifdef __1074__

/* 
[1074. 元素和为目标值的子矩阵数量](https://leetcode-cn.com/problems/number-of-submatrices-that-sum-to-target/)

难度: 困难

*/

class Solution {
public:
    /* // 二维前缀和 暴力解法 
    int s[107][107];
    int numSubmatrixSumTarget(vector<vector<int>>& matrix, int target) {
        // 二维前缀和
        int n = matrix.size(), m = matrix[0].size();
        int ans = 0;
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j)
                s[i + 1][j + 1] = matrix[i][j] + s[i + 1][j] + s[i][j + 1] - s[i][j];
        // 暴力搜索
        for (int a = 1; a <= n; ++a)
            for (int b = 1; b <= m; ++b)
                for (int c = 1; c <= a; ++c)
                    for (int d = 1; d <= b; ++d)
                        if (s[a][b] - s[a][d - 1] - s[c - 1][b] + s[c - 1][d - 1] == target)
                            ++ans;
        return ans;
    }*/

    /* // 二维前缀和 + 哈希表 */
    int s[107][107];
    int numSubmatrixSumTarget(vector<vector<int>>& matrix, int target) {
        // 二维前缀和
        int n = matrix.size(), m = matrix[0].size();
        int ans = 0;
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j)
                s[i + 1][j + 1] = matrix[i][j] + s[i + 1][j] + s[i][j + 1] - s[i][j];
        // 枚举三条边，第四条边透过hashmap查找
        for (int a = 1; a <= n; ++a) {
            for (int b = a; b <= n; ++b) {
                unordered_map<int, int> sm(229);
                for (int c = 1; c <= m; ++c) {
                    int tmp = s[b][c] - s[a - 1][c];
                    if (tmp == target) ++ans;
                    ans += sm[tmp - target];
                    ++sm[tmp];
                }
            }
        }
        vector<int> ssss;
        auto it = ssss.begin() + 10;
        return ans;
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