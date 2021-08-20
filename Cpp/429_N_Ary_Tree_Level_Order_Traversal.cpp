/*  -*- coding: utf-8 -*-
 * File    : 429_Snakes_and_ladders.cpp
 * Author  : MeteorDream
 * Time    : 2021/06/29 15:23:33
 * language: C/C++
 * Software: Visual Studio Code
*/

#include "LeetCode.h"

#ifdef __429__

/* 
[429. N 叉树的层序遍历](https://leetcode-cn.com/problems/n-ary-tree-level-order-traversal/)

难度: 中等

*/

class Solution {
public:
    vector<vector<int>> levelOrder(Node* root) {
        vector<vector<int>> value;
        queue<Node*> s;
        if (root != nullptr)
            s.push(root);
        int cnt = s.size();
        auto q = vector<int>();
        while (!s.empty()) {
            Node* cur = s.front();
            s.pop();
            q.emplace_back(cur->val);
            for (auto child : cur->children)
                s.push(child);
            if (--cnt == 0) {
                value.emplace_back(q);
                q = vector<int>();
                cnt = s.size();
            }
        }
        return value;
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