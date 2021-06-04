/*     -*- coding: utf-8 -*-     */
/* File    : 121_best_time_to_buy_and_sell_stock.cpp */
/* Author  : MeteorDream         */
/* Time    : 2021/05/31 21:09:47 */
/* language: C/C++               */
/* Software: Visual Studio Code  */

#include "LeetCode.h"

#ifdef __121__

/* 
[121. 买卖股票的最佳时机](https://leetcode-cn.com/problems/best-time-to-buy-and-sell-stock/)

难度: 简单

*/

class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        if (n < 2)
            return 0;
        int ans = 0, buy = prices[0];
        for (int& p : prices) {
            if (p < buy)
                buy = p;
            else
                ans = max(ans, p - buy);
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