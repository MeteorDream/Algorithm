/*  -*- coding: utf-8 -*-
 * File    : 542_01_matrix.cpp
 * Author  : MeteorDream
 * Time    : 2021/07/30 14:16:37
 * language: C/C++
 * Software: Visual Studio Code
*/

#include "LeetCode.h"

#ifdef __542__

/* 
[542. 01 矩阵](https://leetcode-cn.com/problems/01-matrix/)

难度: 中等

题解：


*/

/* 多源BFS 
class Solution {
public:
    vector<vector<int>> dir{{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
    vector<vector<int>> updateMatrix(vector<vector<int>>& mat) {
        int n = mat.size(), m = mat[0].size();
        vector<vector<int>> ans(n, vector<int>(m, 0));

        queue<vector<int>> s;
        unordered_set<string> vis;

        // 将所有值为 0 的点作为源点
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (mat[i][j] == 0) {
                    s.emplace(vector<int>{i, j, 0});
                    vis.emplace(to_string(i) + '_' + to_string(j));
                }
            }
        }

        // 多源BFS
        while (!s.empty()) {
            vector<int>& cur = s.front();
            int x = cur[0], y = cur[1], step = cur[2];
            s.pop();
            ans[x][y] = step;
            for (auto& d : dir) {
                int dx = x + d[0], dy = y + d[1];
                if (dx >= 0 && dx < n && dy >= 0 && dy < m) {
                    string k = to_string(dx) + '_' + to_string(dy);
                    if (vis.find(k) == vis.end()) {
                        s.emplace(vector<int>{dx, dy, step + 1});
                        vis.emplace(to_string(dx) + '_' + to_string(dy));
                    }
                }
            }
        }

        return ans;
    }
};*/

/* 动态规划 */
class Solution {
public:
    vector<vector<int>> updateMatrix(vector<vector<int>>& mat) {
        int n = mat.size(), m = mat[0].size();
        int MAXVAL = n + m;
        vector<vector<int>> ans(n, vector<int>(m, MAXVAL));

        // 初始化最左和最上
        if (mat[0][0] == 0)
            ans[0][0] = 0;
        for (int i = 1; i < n; ++i) {
            if (mat[i][0] == 0)
                ans[i][0] = 0;
            else
                ans[i][0] = ans[i - 1][0] + 1;
        }
        for (int i = 1; i < m; ++i) {
            if (mat[0][i] == 0)
                ans[0][i] = 0;
            else
                ans[0][i] = ans[0][i - 1] + 1;
        }

        // 从左上向右下
        for (int i = 1; i < n; ++i) {
            for (int j = 1; j < m; ++j) {
                if (mat[i][j] == 0)
                    ans[i][j] = 0;
                else
                    ans[i][j] = min(ans[i - 1][j], ans[i][j - 1]) + 1;
            }
        }

        // 初始化最右和最下
        for (int i = n - 2; i >= 0; --i) {
            if (mat[i][m - 1] == 1)
                ans[i][m - 1] = min(ans[i][m - 1], ans[i + 1][m - 1] + 1);
        }
        for (int i = m - 2; i >= 0; --i) {
            if (mat[n - 1][i] == 1)
                ans[n - 1][i] = min(ans[n - 1][i], ans[n - 1][i + 1] + 1);
        }

        // 从右下向左上
        for (int i = n - 2; i >= 0; --i) {
            for (int j = m - 2; j >= 0; --j) {
                if (mat[i][j] == 1)
                    ans[i][j] = min(ans[i][j], min(ans[i + 1][j], ans[i][j + 1]) + 1);
            }
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