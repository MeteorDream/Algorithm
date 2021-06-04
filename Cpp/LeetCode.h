/*     -*- coding: utf-8 -*-     */
/* File    : LeetCode.h */
/* Author  : MeteorDream         */
/* Time    : 2021/04/28 10:47:57 */
/* language: C/C++               */
/* Software: Visual Studio Code  */

#ifndef __LEETCODE_H__
#define __LEETCODE_H__

/*
#include "文件名"：先搜寻当前目录，如果搜寻不到头文件，再去搜寻系统头文件所在目录。
#include <文件名>：搜寻系统头文件所在的目录。
*/

// #include <bits/stdc++.h>

#include "main.h"

/* 这里定义题号控制运行的文件 */
#define __525__

// #define random(x) (rand() % x) //随机生成范围在[0, x-1]之间的随机数

class Solution;

// LeetCode 做题测试程序
int Submit();
// 周赛debug程序
int Contest();

/* Definition for singly-linked list. */
struct ListNode {
    int val;
    ListNode* next;
    ListNode()
        : val(0), next(nullptr) {}
    ListNode(int x)
        : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next)
        : val(x), next(next) {}
};

struct List {
    /* 空的头结点 */
    ListNode* head;
    List()
        : head(new ListNode(0)) {}
    List(vector<int>& nums) {
        head = new ListNode(0);
        ListNode* p = head;
        for (int i = 0; i < nums.size(); p = p->next)
            p->next = new ListNode(nums[i++]);
    }
    ~List() {
        destory();
    }
    void setList(vector<int>& nums) {
        if (head != nullptr || head->next != nullptr) destory();
        head = new ListNode(0);
        ListNode* p = head;
        for (int i = 0; i < nums.size(); p = p->next)
            p->next = new ListNode(nums[i]);
    }
    void destory() {
        ListNode* p;
        p = head;
        while (head) {
            p = head;
            head = head->next;
            delete p;
        }
        head = nullptr;
    }
};

/* Definition for a binary tree node. */
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode()
        : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x)
        : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right)
        : val(x), left(left), right(right) {}
};

/* 构建二叉树 */
struct Tree {
    TreeNode* root = nullptr;
    Tree()
        : root(nullptr) {}
    Tree(vector<int>& nums) {
        root = CreateTree(nums);
    }
    ~Tree() {
        DeleteTree();
    }
    // 根据数组创建二叉树(用-1代替空结点)
    TreeNode* CreateTree(vector<int>& nums) {
        if (root != nullptr) DeleteTree();
        int n = nums.size(), i = 1;
        queue<TreeNode*> s;
        TreeNode* p;

        if (n == 0) return nullptr;

        root = new TreeNode(nums[0]);
        s.emplace(root);

        while (i < n) {
            p = s.front();
            s.pop();
            if (nums[i] != -1) {
                p->left = new TreeNode(nums[i++]);
                s.emplace(p->left);
            }
            else
                ++i;
            if (i < n) {
                if (nums[i] != -1) {
                    p->right = new TreeNode(nums[i++]);
                    s.emplace(p->right);
                }
                else
                    ++i;
            }
            else
                break;
        }

        return root;
    }
    // 删除二叉树
    void DeleteTree() {
        if (root == nullptr) return;
        queue<TreeNode*> q;
        TreeNode* cur;

        q.emplace(root);
        root = nullptr;

        while (!q.empty()) {
            cur = q.front();
            q.pop();
            if (cur->left != nullptr) q.emplace(cur->left);
            if (cur->right != nullptr) q.emplace(cur->right);
            delete cur;
        }
    }
};

#endif