/*  -*- coding: utf-8 -*-
 * File    : 559_Maximum_depth_of_n_ary_tree.cpp
 * Author  : MeteorDream
 * Time    : 2021/06/29 15:48:35
 * language: C/C++
 * Software: Visual Studio Code
*/

#include "LeetCode.h"

#ifdef __559__

/* 
[559. N 叉树的最大深度](https://leetcode-cn.com/problems/maximum-depth-of-n-ary-tree/)

难度: 简单

*/

/* 递归
class Solution {
public:
    int maxDepth(Node* root) {
        if (root == nullptr)
            return 0;
        int d = 1;
        for (auto child : root->children)
            d = max(d, maxDepth(child) + 1);
        return d;
    }
}; */

/* dfs
class Solution {
public:
    int maxDepth(Node* root) {
        if (root == nullptr)
            return 0;
        int d = 1;
        stack<pair<Node*, int>> s;
        s.push(pair(root, 1));
        while (!s.empty()) {
            auto cur = s.top();
            s.pop();
            d = max(d, cur.second);
            for (auto child : cur.first->children)
                s.push(pair(child, cur.second + 1));
        }
        return d;
    }
}; */

/* bfs */
class Solution {
public:
    int maxDepth(Node* root) {
        if (root == nullptr)
            return 0;
        int d = 1, cnt = 1;
        queue<Node*> q;
        q.push(root);
        while (!q.empty()) {
            auto cur = q.front();
            q.pop();
            for (auto child : cur->children)
                q.push(child);
            if (--cnt == 0) {
                cnt = q.size();
                if (cnt > 0)
                    ++d;
            }
        }
        return d;
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