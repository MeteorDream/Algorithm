/*     -*- coding: utf-8 -*-     */
/* File    : 79_word_search.cpp */
/* Author  : MeteorDream         */
/* Time    : 2021/05/28 14:36:27 */
/* language: C/C++               */
/* Software: Visual Studio Code  */

#include "LeetCode.h"

#ifdef __079__

/* 
[79. 单词搜索](https://leetcode-cn.com/problems/word-search/)

难度: 中等

*/

class Solution {
public:
    bool exist(vector<vector<char>>& board, string word) {
        // 回溯 + dfs
        int n = board.size(), m = board[0].size(), s = word.size();
        unordered_map<char, int> map;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                ++map[board[i][j]];
            }
        }
        for (char s : word)
            if (--map[s] < 0)
                return false;

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (dfs(board, word, i, j, 0))
                    return true;
            }
        }
        return false;
    }

    bool dfs(vector<vector<char>>& board, string word, int i, int j, int id) {
        //  word 查询完了说明查找到了!
        if (id == word.size())
            return true;
        // 越界返回 false
        else if (i < 0 || i >= board.size() || j < 0 || j >= board[0].size())
            return false;
        // 不匹配返回 false
        else if (board[i][j] != word[id])
            return false;
        else {
            // 匹配，则 dfs 递归查询
            // dfs 查找前先做标记
            char tmp = board[i][j];
            board[i][j] = '#';
            // 查询结果为 上下左右 四个方位的和
            if (dfs(board, word, i + 1, j, id + 1) || dfs(board, word, i - 1, j, id + 1) || dfs(board, word, i, j + 1, id + 1) || dfs(board, word, i, j - 1, id + 1)) {
                // 回溯，恢复现场
                board[i][j] = tmp;
                return true;
            }
            else {
                // 回溯，恢复现场
                board[i][j] = tmp;
                return false;
            }
        }
    }
};

int Submit() {
    Solution s;

    /* 输入 */
    cout << "输入:" << endl;
    vector<char> s1{'A', 'B', 'C', 'E'};
    vector<char> s2{'S', 'F', 'E', 'S'};
    vector<char> s3{'A', 'D', 'E', 'E'};
    vector<vector<char>> ss{s1, s2, s3};

    /* 输出 */
    cout << "输出:" << endl;
    s.exist(ss, "ABCESEEEFS");

    return 0;
}

#endif