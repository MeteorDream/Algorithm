/*  -*- coding: utf-8 -*-
 * File    : 1833_Maximum_ice_cream_bars.cpp
 * Author  : MeteorDream
 * Time    : 2021/07/02 14:39:38
 * language: C/C++
 * Software: Visual Studio Code
*/

#include "LeetCode.h"

#ifdef __1833__

/* 
[1833. 雪糕的最大数量](https://leetcode-cn.com/problems/maximum-ice-cream-bars/)

难度: 简单

题解：


*/

/* 简单贪心，先排序再由小到大取即可 */
class Solution {
public:
    int maxIceCream(vector<int>& costs, int coins) {
        sort(costs.begin(), costs.end());
        int cnt = 0;
        for (auto c : costs) {
            if (c > coins)
                break;
            else {
                ++cnt;
                coins -= c;
            }
        }
        return cnt;
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