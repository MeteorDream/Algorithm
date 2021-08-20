/*  -*- coding: utf-8 -*-
 * File    : 590_N_ary_tree_postorder_traversal.cpp
 * Author  : MeteorDream
 * Time    : 2021/06/29 16:56:08
 * language: C/C++
 * Software: Visual Studio Code
*/

#include "LeetCode.h"

#ifdef __590__

/* 
[590. N 叉树的后序遍历](https://leetcode-cn.com/problems/n-ary-tree-postorder-traversal/)

难度: 简单


*/

/* 递归
class Solution {
public:
    vector<int> value;
    void dfs(Node* root) {
        for (auto child : root->children)
            dfs(child);
        value.emplace_back(root->val);
    }

    vector<int> postorder(Node* root) {
        if (root != nullptr)
            dfs(root);
        return value;
    }
}; */

/* 迭代 */
class Solution {
public:
    vector<int> postorder(Node* root) {
        vector<int> value;
        stack<pair<Node*, int>> s;
        auto cur = pair(root, 0);
        while (!s.empty() || cur.first != nullptr) {
            while (cur.first != nullptr) {
                s.push(cur);
                if (cur.first->children.size() > 0)
                    cur = pair(cur.first->children[0], 0);
                else
                    cur.first = nullptr;
            }
            cur = s.top();
            s.pop();
            if (cur.first->children.size() == 0 || cur.second >= cur.first->children.size()) {
                value.emplace_back(cur.first->val);
                cur.first = nullptr;
            }
            else {
                ++cur.second;
                s.push(cur);
                if (cur.second < cur.first->children.size())
                    cur = pair(cur.first->children[cur.second], 0);
                else
                    cur.first = nullptr;
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