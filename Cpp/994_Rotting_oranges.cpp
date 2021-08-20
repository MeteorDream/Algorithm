/*  -*- coding: utf-8 -*-
 * File    : 994_Rotting_oranges.cpp
 * Author  : MeteorDream
 * Time    : 2021/07/30 14:56:02
 * language: C/C++
 * Software: Visual Studio Code
*/

#include "LeetCode.h"

#ifdef __994__

/* 
[994. 腐烂的橘子](https://leetcode-cn.com/problems/rotting-oranges/)

难度: 中等

题解：

和 542 差不多
*/

class Solution {
public:
    vector<vector<int>> dir{{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
    int orangesRotting(vector<vector<int>>& grid) {
        int n = grid.size(), m = grid[0].size();
        int cnt = 0;    // 橘子的个数

        queue<vector<int>> s;
        unordered_set<int> vis;

        // 将所有值为 2 的点作为源点
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (grid[i][j] == 2) {
                    s.emplace(vector<int>{i, j, 0});
                    vis.emplace(i * 32 + j);
                    cnt++;
                }
                else if (grid[i][j] == 1)
                    cnt++;
            }
        }

        // 多源BFS
        int tim = 0;
        while (!s.empty()) {
            vector<int>& cur = s.front();
            int x = cur[0], y = cur[1], step = cur[2];
            cnt--;
            s.pop();
            if (step > tim) tim = step;
            for (auto& d : dir) {
                int dx = x + d[0], dy = y + d[1];
                if (dx >= 0 && dx < n && dy >= 0 && dy < m && grid[dx][dy] == 1) {
                    int k = dx * 32 + dy;
                    if (vis.find(k) == vis.end()) {
                        s.emplace(vector<int>{dx, dy, step + 1});
                        vis.emplace(k);
                    }
                }
            }
        }

        return cnt == 0 ? tim : -1;
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