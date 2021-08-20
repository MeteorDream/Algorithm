/*     -*- coding: utf-8 -*-     */
/* File    : 122_Best_time_to_buy_and_sell_stock_ii.cpp */
/* Author  : MeteorDream         */
/* Time    : 2021/06/19 00:02:44 */
/* language: C/C++               */
/* Software: Visual Studio Code  */

#include "LeetCode.h"

#ifdef __122__

/* 
[122. 买卖股票的最佳时机 II](https://leetcode-cn.com/problems/best-time-to-buy-and-sell-stock-ii/)

难度: 简单

*/

class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int ans = 0, n = prices.size();
        for (int i = 1; i < n; ++i) {
            int d = prices[i] - prices[i - 1];
            if (d > 0)
                ans += d;
        }
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