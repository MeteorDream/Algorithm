/* 
* coding: utf-16 -*- 
* File    : LeetCode_138.java
* Author  : MeteorDream
* Time    : 2021/07/22 10:35:07
* language: Java
* Software: Visual Studio Code
* */

/**
 *[138. 复制带随机指针的链表](https://leetcode-cn.com/problems/copy-list-with-random-pointer/)
 * 
 * 难度: 中等

 * 题解：
 * */

import java.util.*;

public class LeetCode_138 {
    public static void main(String[] args) {
        LeetCode_138 s = new LeetCode_138();

        System.out.println(s + "Finish!");
    }

    class Node {
        int val;
        Node next;
        Node random;

        public Node(int val) {
            this.val = val;
            this.next = null;
            this.random = null;
        }
    }

    /* 哈希表 */
    public Node copyRandomList1(Node head) {
        Map<Node, Node> s = new HashMap<>();
        Node dummy = new Node(0);
        // 复制 原链表 各个结点的 val 和 next
        for (Node p = head, q = dummy; p != null; p = p.next) {
            Node tmp = new Node(p.val);
            s.put(p, tmp);
            q.next = tmp;
            q = tmp;
        }
        // 复制原链表 的random
        for (Node p = head, q = dummy.next; p != null; p = p.next, q = q.next) {
            q.random = s.get(p.random);
        }
        return dummy.next;
    }

    /* 有丝分裂 */
    public Node copyRandomList(Node head) {
        Node dummy = new Node(0);
        // 复制一个结点插入在原结点后面
        for (Node p = head; p != null; p = p.next) {
            Node tmp = new Node(p.val);
            tmp.next = p.next;
            p.next = tmp;
            p = tmp;
        }
        // 将复制结点的 random 指针指向新复制出的结点
        for (Node p = head; p != null; p = p.next.next) {
            if (p.random != null)
                p.next.random = p.random.next;
        }
        // 分离原链表和新复制的链表
        for (Node p = head, q = dummy; p != null; p = p.next) {
            q.next = p.next;
            q = q.next;
            p.next = q.next;
        }
        return dummy.next;
    }
}