/*     -*- coding: utf-8 -*-     */
/* File    : 105_construct_binary_tree_from_preorder_and_inorder_traversal.cpp */
/* Author  : MeteorDream         */
/* Time    : 2021/05/27 23:05:05 */
/* language: C/C++               */
/* Software: Visual Studio Code  */

#include "LeetCode.h"

#ifdef __105__

/* 
[105. 从前序与中序遍历序列构造二叉树](https://leetcode-cn.com/problems/construct-binary-tree-from-preorder-and-inorder-traversal/)

难度: 中等

*/

/* 递归解法 */
// class Solution {
// public:
//     TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
//         int n = preorder.size();
//         unordered_map<int, int> ind;
//         ind.reserve(n * 2);
//         for (int i = 0; i < n; ++i)
//             ind.emplace(inorder[i], i);
//         return build(preorder, 0, n - 1, inorder, 0, n - 1, ind);
//     }

//     /* 根据 preorder [i,j] 范围内 和 inorder [x,y] 范围内 的元素建树 */
//     TreeNode* build(vector<int>& preorder, int i, int j, vector<int>& inorder, int x, int y, unordered_map<int, int>& ind) {
//         /* 若 i > j 则树空 */
//         if (i > j)
//             return nullptr;
//         /* 若 i == j 则该树只有一个根结点 */
//         else if (i == j)
//             return new TreeNode(preorder[i]);
//         /* 前序 preorder 的第一个值是根结点的值 */
//         int val = preorder[i];
//         TreeNode* root = new TreeNode(val);
//         /* 在中序 inorder 查找根结点所在值 */
//         int z = ind[val];
//         /* 递归创建左子树和右子树 */
//         root->left = build(preorder, i + 1, i + z - x, inorder, x, z - 1, ind);
//         root->right = build(preorder, i + z - x + 1, j, inorder, z + 1, y, ind);
//         return root;
//     }
// };

/* 迭代解法 */
class Solution {
public:
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        int n = preorder.size();
        if (n == 0)
            return nullptr;
        TreeNode* root = new TreeNode(preorder[0]);
        stack<TreeNode*> st;
        st.emplace(root);
        int i = 0;
        for (int j = 1; j < n; ++j) {
            TreeNode* tmp = st.top();
            if (tmp->val == inorder[i]) {
                while (!st.empty() && st.top()->val == inorder[i]) {
                    tmp = st.top();
                    st.pop();
                    ++i;
                }
                tmp->right = new TreeNode(preorder[j]);
                st.emplace(tmp->right);
            }
            else {
                tmp->left = new TreeNode(preorder[j]);
                st.emplace(tmp->left);
            }
        }
        return root;
    }
};

int Submit() {
    Solution s;

    /* 输入 */
    cout << "输入:" << endl;
    vector<int> s1{3, 9, 8, 5, 4, 10, 20, 15, 7};
    vector<int> s2{4, 5, 8, 10, 9, 3, 15, 20, 7};

    /* 输出 */
    cout << "输出:" << endl;
    s.buildTree(s1, s2);

    return 0;
}

#endif