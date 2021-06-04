/*     -*- coding: utf-8 -*-     */
/* File    : 1744_can_you_eat_your_favorite_candy_on_your_favorite_day.cpp */
/* Author  : MeteorDream         */
/* Time    : 2021/06/01 16:26:32 */
/* language: C/C++               */
/* Software: Visual Studio Code  */

#include "LeetCode.h"

#ifdef __1744__

/* 
[1744. 你能在你最喜欢的那天吃到你最喜欢的糖果吗？](https://leetcode-cn.com/problems/can-you-eat-your-favorite-candy-on-your-favorite-day/)

难度: 中等
*/

class Solution {
public:
    vector<bool> canEat(vector<int>& candiesCount, vector<vector<int>>& queries) {
        // candiesCount[i] 表示你拥有的第 i 类糖果的数目
        // queries[i] = [favoriteTypei, favoriteDayi, dailyCapi]
        // 即 喜欢的糖果下标， 喜欢的天数， 每天最多吃糖
        // 在每天吃 不超过 dailyCapi 颗糖果的前提下
        // 你可以在第 favoriteDayi 天吃到第 favoriteTypei 类糖果
        int n = candiesCount.size(), m = queries.size();
        // s[i] 表示前 i-1 类糖果的数量和
        vector<long> s(n + 1);
        vector<bool> ans(m);
        for (int i = 0; i < n; ++i)
            s[i + 1] = s[i] + candiesCount[i];
        for (int i = 0; i < m; ++i) {
            // min 表示喜欢那天最少要吃的糖果数量和最多能吃的糖果数量
            long min = queries[i][1], max = (long)queries[i][2] * (queries[i][1] + 1);
            // 只要[s[q], s[q + 1]]与[min, max]区间有交集，即可在喜欢那天吃到喜欢的糖果
            ans[i] = (min < s[queries[i][0] + 1]) && (max > s[queries[i][0]]);
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