/*  -*- coding: utf-8 -*-
 * File    : 160_Intersection_of_two_linked_lists.cpp
 * Author  : MeteorDream
 * Time    : 2021/07/21 02:47:07
 * language: C/C++
 * Software: Visual Studio Code
*/

#include "LeetCode.h"

#ifdef __160__

/* 
[160. 相交链表](https://leetcode-cn.com/problems/intersection-of-two-linked-lists/)

难度: 简单

题解：https://leetcode-cn.com/problems/intersection-of-two-linked-lists/solution/xiang-jiao-lian-biao-wu-chong-jie-fa-by-j73p5/

*/

/* 暴力 
class Solution {
public:
    ListNode* getIntersectionNode(ListNode* headA, ListNode* headB) {
        for (ListNode* p = headA; p != nullptr; p = p->next) {
            for (ListNode* q = headB; q != nullptr; q = q->next) {
                if (p == q)
                    return p;
            }
        }
        return nullptr;
    }
};*/

/* 哈希表 
class Solution {
public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        unordered_set<ListNode *> s;
        for (ListNode *p = headA; p != nullptr; p = p->next) {
            s.emplace(p);
        }
        for (ListNode *p = headB; p != nullptr; p = p->next) {
            if (s.find(p) != s.end())
                return p;
        }
        return nullptr;
    }
};*/

/* 栈 
class Solution {
public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        stack<ListNode *> s1, s2;
        for (ListNode *p = headA; p != nullptr; p = p->next) {
            s1.push(p);
        }
        for (ListNode *p = headB; p != nullptr; p = p->next) {
            s2.push(p);
        }
        ListNode *ans = nullptr;
        for ( ; !s1.empty() && !s2.empty() && s1.top() == s2.top(); s1.pop(), s2.pop())
            ans = s1.top();
        return ans;
    }
};*/

/* 计算长度 
class Solution {
public:
    ListNode* getIntersectionNode(ListNode* headA, ListNode* headB) {
        int size1 = 1, size2 = 1;
        ListNode *p, *q;

        if (!headA || !headB) return NULL;

        // 计算链表长度
        for (p = headA; p->next != NULL; p = p->next, size1++)
            ;
        for (p = headB; p->next != NULL; p = p->next, size2++)
            ;

        // 长链表先走，但不确定AB谁长，所以要写两个循环，但实际上有至少一个循环不会执行
        p = headA;
        q = headB;
        for (int i = 0; i < size1 - size2; i++, p = p->next)
            ;
        for (int i = 0; i < size2 - size1; i++, q = q->next)
            ;

        for (; p && q && p != q; p = p->next, q = q->next)
            ;

        return p;
    }
};*/

/* 走过彼此的路 */
class Solution {
public:
    ListNode* getIntersectionNode(ListNode* headA, ListNode* headB) {
        ListNode *p, *q;

        for (p = headA, q = headB; p != q;) {
            if (p != NULL)
                p = p->next;
            else
                p = headB;
            if (q != NULL)
                q = q->next;
            else
                q = headA;
        }

        return p;
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