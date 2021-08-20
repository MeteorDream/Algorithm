/*  -*- coding: utf-8 -*-
 * File    : 909_Snakes_and_ladders.cpp
 * Author  : MeteorDream
 * Time    : 2021/06/27 18:39:23
 * language: C/C++
 * Software: Visual Studio Code
*/

#include "LeetCode.h"

#ifdef __909__

/* 
[909. 蛇梯棋](https://leetcode-cn.com/problems/snakes-and-ladders/)

难度: 中等


*/

/* 朴素bfs */
class Solution {
public:
    int snakesAndLadders(vector<vector<int>>& board) {
        int n = board.size();
        // 预处理棋盘
        unordered_map<int, int> jump;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (board[i][j] != -1)
                    jump[trans(i, j, n)] = board[i][j];
            }
        }

        int target = n * n;
        queue<int> q;
        unordered_map<int, int> turn;
        q.emplace(1);
        turn[1] = 0;
        while (!q.empty()) {
            int start = q.front();
            q.pop();
            int tim = turn[start] + 1;
            for (int i = 1; i <= 6; ++i) {
                int next = start + i;
                if (jump.find(next) != jump.end())
                    next = jump[next];
                if (turn.find(next) == turn.end()) {
                    if (next == target)
                        return tim;
                    q.emplace(next);
                    turn[next] = tim;
                }
            }
        }
        return -1;
    }

    int trans(int i, int j, int n) {
        // 将矩阵坐标转换为棋盘数字
        i = n - 1 - i;
        int num = i * n;
        if (i % 2 == 1)
            return num + n - j;
        else
            return num + j + 1;
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