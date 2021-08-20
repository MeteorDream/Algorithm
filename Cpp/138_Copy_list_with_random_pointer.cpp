/*  -*- coding: utf-8 -*-
 * File    : 138_Copy_list_with_random_pointer.cpp
 * Author  : MeteorDream
 * Time    : 2021/07/22 12:52:56
 * language: C/C++
 * Software: Visual Studio Code
*/

#include "LeetCode.h"

#ifdef __138__

/* 
[138. 复制带随机指针的链表](https://leetcode-cn.com/problems/copy-list-with-random-pointer/)

难度: 中等

题解：


*/

// Definition for a Node.
class Node {
public:
    int val;
    Node* next;
    Node* random;

    Node(int _val) {
        val = _val;
        next = NULL;
        random = NULL;
    }
};

/* 哈希表 
class Solution {
public:
    Node* copyRandomList(Node* head) {
        unordered_map<Node*, Node*> s;
        Node* dummy = new Node(0);
        // 复制 原链表 各个结点的 val 和 next
        for (Node *p = head, *q = dummy; p != nullptr; p = p->next) {
            q->next = new Node(p->val);
            q = q->next;
            s[p] = q;
        }
        // 复制原链表 的random
        for (Node *p = head, *q = dummy->next; p != nullptr; p = p->next, q = q->next) {
            if (p->random != nullptr)
                q->random = s[p->random];
        }
        Node* tmp = dummy->next;
        delete dummy;
        return tmp;
    }
};*/

/* 有丝分裂 */
class Solution {
public:
    Node* copyRandomList(Node* head) {
        Node* dummy = new Node(0);

        // 复制一个结点插入在原结点后面
        for (Node* p = head; p != nullptr; p = p->next) {
            Node* tmp = new Node(p->val);
            tmp->next = p->next;
            p->next = tmp;
            p = tmp;
        }
        // 将复制结点的 random 指针指向新复制出的结点
        for (Node* p = head; p != nullptr; p = p->next->next) {
            if (p->random != nullptr)
                p->next->random = p->random->next;
        }
        // 分离原链表和新复制的链表
        for (Node *p = head, *q = dummy; p != nullptr; p = p->next) {
            q->next = p->next;
            q = q->next;
            p->next = q->next;
        }

        Node* tmp = dummy->next;
        delete dummy;
        return tmp;
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