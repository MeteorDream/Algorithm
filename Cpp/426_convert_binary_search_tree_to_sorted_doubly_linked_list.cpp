/*     -*- coding: utf-8 -*-     */
/* File    : 426_convert_binary_search_tree_to_sorted_doubly_linked_list.cpp */
/* Author  : MeteorDream         */
/* Time    : 2021/06/14 19:33:02 */
/* language: C/C++               */
/* Software: Visual Studio Code  */

#include "LeetCode.h"

#ifdef __426__

/* 
* [426. 将二叉搜索树转化为排序的双向链表](https://leetcode-cn.com/problems/convert-binary-search-tree-to-sorted-doubly-linked-list/)
* [剑指 Offer 36. 二叉搜索树与双向链表](https://leetcode-cn.com/problems/er-cha-sou-suo-shu-yu-shuang-xiang-lian-biao-lcof/)
 

难度: 中等
*/

// Definition for a Node.
class Node {
public:
    int val;
    Node* left;
    Node* right;

    Node() {}

    Node(int _val) {
        val = _val;
        left = NULL;
        right = NULL;
    }

    Node(int _val, Node* _left, Node* _right) {
        val = _val;
        left = _left;
        right = _right;
    }
};

/* // 递归
class Solution {
public:
    Node *head, *pre;
    Node* treeToDoublyList(Node* root) {
        if (root == nullptr)
            return nullptr;
        pre = nullptr;
        dfs(root);
        head->left = pre;
        pre->right = head;
        return head;
    }

    void dfs(Node* root) {
        if (root != nullptr) {
            dfs(root->left);
            if (pre == nullptr)
                head = root;
            else {
                pre->right = root;
                root->left = pre;
            }
            pre = root;
            dfs(root->right);
        }
    }
}; */

/* // 迭代 */
class Solution {
public:
    Node* treeToDoublyList(Node* root) {
        if (root == nullptr)
            return nullptr;
        stack<Node*> s;
        Node *pre = root, *head;
        while (pre != nullptr) {
            s.push(pre);
            pre = pre->left;
        }
        head = s.top();
        pre = nullptr;
        while (!s.empty()) {
            Node* cur = s.top();
            s.pop();
            if (pre != nullptr)
                pre->right = cur;
            cur->left = pre;
            pre = cur;
            cur = cur->right;
            while (cur != nullptr) {
                s.push(cur);
                cur = cur->left;
            }
        }
        head->left = pre;
        pre->right = head;
        return head;
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