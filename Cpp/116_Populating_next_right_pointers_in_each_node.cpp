/*  -*- coding: utf-8 -*-
 * File    : 116_Populating_next_right_pointers_in_each_node.cpp
 * Author  : MeteorDream
 * Time    : 2021/07/29 12:56:47
 * language: C/C++
 * Software: Visual Studio Code
*/

#include "LeetCode.h"

#ifdef __116__

/* 
[116. 填充每个节点的下一个右侧节点指针](https://leetcode-cn.com/problems/populating-next-right-pointers-in-each-node/)

难度: 中等

题解：https://leetcode-cn.com/problems/populating-next-right-pointers-in-each-node/solution/tian-chong-mei-ge-jie-dian-de-xia-yi-ge-3f7ak/


*/

// Definition for a Node.
class Node {
public:
    int val;
    Node* left;
    Node* right;
    Node* next;

    Node()
        : val(0), left(NULL), right(NULL), next(NULL) {}

    Node(int _val)
        : val(_val), left(NULL), right(NULL), next(NULL) {}

    Node(int _val, Node* _left, Node* _right, Node* _next)
        : val(_val), left(_left), right(_right), next(_next) {}
};

/* // 递归 
class Solution {
public:
    Node* connect(Node* root) {
        if (root != nullptr) {
            if (root->left != nullptr) {
                root->left->next = root->right;
                if (root->next != nullptr)
                    root->right->next = root->next->left;
                connect(root->left);
                connect(root->right);
            }
        }
        return root;
    }
};
*/

/* 迭代 */
class Solution {
public:
    Node* connect(Node* root) {
        Node* start = root;
        while (start != nullptr) {
            Node* cur = start;
            start = nullptr;
            while (cur != nullptr) {
                if (cur->left != nullptr) {
                    cur->left->next = cur->right;
                    if (start == nullptr) start = cur->left;
                    if (cur->next != nullptr)
                        cur->right->next = cur->next->left;
                }
                cur = cur->next;
            }
        }
        return root;
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