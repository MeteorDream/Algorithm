/*  -*- coding: utf-8 -*-
 * File    : 297_Serialize_and_deserialize_binary_tree.cpp
 * Author  : MeteorDream
 * Time    : 2021/06/30 12:18:55
 * language: C/C++
 * Software: Visual Studio Code
*/

#include "LeetCode.h"

#ifdef __297__

/* 
[297. 二叉树的序列化与反序列化](https://leetcode-cn.com/problems/serialize-and-deserialize-binary-tree/)

难度: 困难

题解：https://leetcode-cn.com/problems/serialize-and-deserialize-binary-tree/solution/er-cha-shu-de-xu-lie-hua-yu-fan-xu-lie-h-b684/


*/

class Codec {
public:
    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        if (root == nullptr)
            return "[]";

        queue<TreeNode*> s;
        string sb = "[";
        int cnt = 1;    // 表示队列中非空结点的数量

        s.push(root);

        while (true) {
            TreeNode* cur = s.front();
            s.pop();
            if (cur == nullptr)
                sb += "null";
            else {
                --cnt;
                sb += to_string(cur->val);
                s.push(cur->left);
                s.push(cur->right);
                if (cur->left != nullptr)
                    ++cnt;
                if (cur->right != nullptr)
                    ++cnt;
            }
            if (cnt == 0 || s.empty())
                return sb + ']';
            sb += ',';
        }
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        if (data.length() <= 2)
            return nullptr;

        vector<string> nums(1, "");
        for (int i = 1, p = 0; i < data.size() - 1; ++i) {
            if (data[i] == ',') {
                nums.emplace_back("");
                ++p;
            }
            else if (data[i] != ' ')
                nums[p] += data[i];
        }

        int n = nums.size(), p = 1;
        if (n == 1 && nums[0] == "null")
            return nullptr;
        queue<TreeNode*> q;
        TreeNode* root = new TreeNode(atol(nums[0].c_str()));
        q.push(root);
        while (p < n) {
            TreeNode* cur = q.front();
            q.pop();
            if (nums[p++] != "null") {
                cur->left = new TreeNode(atol(nums[p - 1].c_str()));
                q.push(cur->left);
            }
            if (p < n && nums[p++] != "null") {
                cur->right = new TreeNode(atol(nums[p - 1].c_str()));
                q.push(cur->right);
            }
        }
        return root;
    }
};

int Submit() {
    /* 输入 */
    cout << "输入:" << endl;

    /* 输出 */
    cout << "输出:" << endl;

    return 0;
}

#endif