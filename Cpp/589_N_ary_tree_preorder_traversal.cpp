/*  -*- coding: utf-8 -*-
 * File    : 589_N_ary_tree_preorder_traversal.cpp
 * Author  : MeteorDream
 * Time    : 2021/06/29 16:44:52
 * language: C/C++
 * Software: Visual Studio Code
*/

#include "LeetCode.h"

#ifdef __589__

/* 
[589. N 叉树的前序遍历](https://leetcode-cn.com/problems/n-ary-tree-preorder-traversal/)

难度: 简单


*/

/* 递归 
class Solution {
public:
    vector<int> value;
    void dfs(Node* root) {
        value.emplace_back(root->val);
        for (auto child : root->children)
            dfs(child);
    }
    vector<int> preorder(Node* root) {
        if (root != nullptr)
            dfs(root);
        return value;
    }
};*/

/* 迭代 */
class Solution {
public:
    vector<int> preorder(Node* root) {
        vector<int> value;
        stack<Node*> s;
        if (root != nullptr)
            s.push(root);
        while (!s.empty()) {
            Node* cur = s.top();
            s.pop();
            value.emplace_back(cur->val);
            for (int i = cur->children.size() - 1; i >= 0; --i)
                s.push(cur->children[i]);
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