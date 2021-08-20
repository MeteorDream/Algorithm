/*     -*- coding: utf-8 -*-     */
/* File    : 879_profitable_schemes.cpp */
/* Author  : MeteorDream         */
/* Time    : 2021/06/09 12:48:10 */
/* language: C/C++               */
/* Software: Visual Studio Code  */

#include "LeetCode.h"

#ifdef __879__

/* 
[879. 盈利计划](https://leetcode-cn.com/problems/profitable-schemes/)

难度: 困难
*/

class Solution {
public:
    /* // 记忆化dfs超时，朴素dfs更不用考虑了，所以直接上动态规划 */
    int profitableSchemes(int n, int minProfit, vector<int>& group, vector<int>& profit) {
        int m = group.size();
        // dp[i][j][k] 的含义是，前i项任务，使用不超过j个员工，产生至少k的利润
        vector<vector<vector<long>>> dp(m + 1, vector<vector<long>>(n + 1, vector<long>(minProfit + 1)));
        // 0项任务，任意数量员工，最小利润为0的方案数为1
        for (int i = 0; i <= n; ++i)
            dp[0][i][0] = 1;
        for (int i = 1; i <= m; ++i) {
            // 第 i - 1 项任务，考虑做和不做两种情况
            for (int j = 0; j <= n; ++j) {
                for (int k = 0; k <= minProfit; ++k) {
                    // 不做第i项任务
                    long s = dp[i - 1][j][k];
                    // 做第i项任务首先得有足够多的人员
                    if (group[i - 1] <= j)
                        s += dp[i - 1][j - group[i - 1]][max(0, k - profit[i - 1])];
                    dp[i][j][k] = s % 1000000007;
                }
            }
        }
        return (int)dp[m][n][minProfit];
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