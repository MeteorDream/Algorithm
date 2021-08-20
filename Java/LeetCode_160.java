/* 
* coding: utf-16 -*- 
* File    : LeetCode_160.java
* Author  : MeteorDream
* Time    : 2021/07/21 02:34:07
* language: Java
* Software: Visual Studio Code
* */

/**
 *[160. 相交链表](https://leetcode-cn.com/problems/intersection-of-two-linked-lists/)
 * 
 * 难度: 简单

 * 题解：https://leetcode-cn.com/problems/intersection-of-two-linked-lists/solution/xiang-jiao-lian-biao-wu-chong-jie-fa-by-j73p5/
 * */

import java.util.*;

public class LeetCode_160 {
    public static void main(String[] args) {
        LeetCode_160 s = new LeetCode_160();

        System.out.println(s + "Finish!");
    }

    /* 暴力 
    public ListNode getIntersectionNode(ListNode headA, ListNode headB) {
        for (ListNode p = headA; p != null; p = p.next) {
            for (ListNode q = headB; q != null; q = q.next) {
                if (p == q)
                    return p;
            }
        }
        return null;
    }*/

    /* 哈希表 */
    public ListNode getIntersectionNode2(ListNode headA, ListNode headB) {
        Set<ListNode> s = new HashSet<>();
        for (ListNode p = headA; p != null; p = p.next) {
            s.add(p);
        }
        for (ListNode p = headB; p != null; p = p.next) {
            if (s.contains(p))
                return p;
        }
        return null;
    }

    /* 栈 
    public ListNode getIntersectionNode(ListNode headA, ListNode headB) {
        Deque<ListNode> s1 = new ArrayDeque<ListNode>(), s2 = new ArrayDeque<ListNode>();
        for (ListNode p = headA; p != null; p = p.next)
            s1.addLast(p);
        for (ListNode p = headB; p != null; p = p.next)
            s2.addLast(p);
        ListNode ans = null;
        while (!s1.isEmpty() && !s2.isEmpty() && s1.peekLast() == s2.peekLast()) {
            s1.pollLast();
            ans = s2.pollLast();
        }
        return ans;
    }*/

    /* 计算长度 
    public ListNode getIntersectionNode(ListNode headA, ListNode headB) {
        int s1 = 0, s2 = 0;
        for (ListNode p = headA; p != null; p = p.next) ++s1;
        for (ListNode p = headB; p != null; p = p.next) ++s2;
        ListNode p = headA, q = headB;
        while (s1 < s2) {
            q = q.next;
            --s2;
        }
        while (s1 > s2) {
            p = p.next;
            --s1;
        }
        while (p != null && q != null) {
            if (p == q)
                return p;
            p = p.next; q = q.next;
        }
        return null;
    }*/

    /* 走过彼此的路 */
    public ListNode getIntersectionNode(ListNode headA, ListNode headB) {
        ListNode p = headA, q = headB;
        while (p != q) {
            p = p == null ? headB : p.next;
            q = q == null ? headA : q.next;
        }
        return p;
    }
}