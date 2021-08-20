/*  -*- coding: utf-8 -*-
 * File    : 124_Binary_tree_maximum_path_sum.cpp
 * Author  : MeteorDream
 * Time    : 2021/06/30 22:04:37
 * language: C/C++
 * Software: Visual Studio Code
*/

#include "LeetCode.h"

#ifdef __124__

/* 
[124. 二叉树中的最大路径和](https://leetcode-cn.com/problems/binary-tree-maximum-path-sum/)

难度: 困难

题解：答案千篇一律，没有创新点

*/

class Solution {
public:
    int maxPath;

    int dfs(TreeNode* root) {
        // 返回单向最大路径
        if (root == nullptr)
            return 0;
        else {
            int left = max(0, dfs(root->left));
            int right = max(0, dfs(root->right));
            maxPath = max(maxPath, root->val + left + right);
            return max(left, right) + root->val;
        }
    }

    int maxPathSum(TreeNode* root) {
        maxPath = -2021;
        dfs(root);
        return maxPath;
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