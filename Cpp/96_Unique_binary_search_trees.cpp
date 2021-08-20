/*  -*- coding: utf-8 -*-
 * File    : 96_Unique_binary_search_trees.cpp
 * Author  : MeteorDream
 * Time    : 2021/06/29 23:12:39
 * language: C/C++
 * Software: Visual Studio Code
*/

#include "LeetCode.h"

#ifdef __096__

/* 
[96. 不同的二叉搜索树](https://leetcode-cn.com/problems/unique-binary-search-trees/)

难度: 中等

题解：https://leetcode-cn.com/problems/unique-binary-search-trees/solution/bu-tong-de-er-cha-sou-suo-shu-di-gui-don-klcp/


*/

/* 递归
class Solution {
public:
    unordered_map<int, int> cache;
    int dfs(int n) {
        if (n <= 1)
            return 1;
        else if (cache.find(n) == cache.end()) {
            int c = 0;
            for (int i = 0; i < n; ++i)
                c += dfs(i) * dfs(n - 1 - i);
            cache.emplace(n, c);
            return c;
        }
        else
            return cache[n];
    }

    int numTrees(int n) {
        return dfs(n);
    }
}; */

/* 动态规划 
class Solution {
public:
    int numTrees(int n) {
        vector<int> dp(n + 1, 0);
        dp[0] = 1;
        for (int i = 1; i <= n; ++i)
            for (int j = 0; j < i; ++j)
                dp[i] += dp[j] * dp[i - 1 - j];
        return dp[n];
    }
};*/

/* 数学 
class Solution {
public:
    int numTrees(int n) {
        long s = 1;
        for (int i = 1; i <= n; ++i)
            s = s * (4 * i - 2) / (i + 1);
        return s;
    }
};*/

/* 打表 */
class Solution {
public:
    int numTrees(int n) {
        int catalan[] = {1, 1, 2, 5, 14, 42, 132, 429, 1430, 4862, 16796, 58786, 208012, 742900, 2674440, 9694845, 35357670, 129644790, 477638700, 1767263190};
        return catalan[n];
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