/* 
* coding: utf-16 -*- 
* File    : LeetCode_116.java
* Author  : MeteorDream
* Time    : 2021/07/29 12:49:03
* language: Java
* Software: Visual Studio Code
* */

/**
 *[116. 填充每个节点的下一个右侧节点指针](https://leetcode-cn.com/problems/populating-next-right-pointers-in-each-node/)
 * 
 * 难度: 中等

 * 题解：https://leetcode-cn.com/problems/populating-next-right-pointers-in-each-node/solution/tian-chong-mei-ge-jie-dian-de-xia-yi-ge-3f7ak/
 * */

// import java.util.*;

public class LeetCode_116 {
    public static void main(String[] args) {
        LeetCode_116 LC = new LeetCode_116();

        Solution ss = LC.new Solution();

        System.out.println(LC + "Finish!");
        System.out.println(ss + "Finish!");
    }

    class Node {
        public int val;
        public Node left;
        public Node right;
        public Node next;

        public Node() {
        }

        public Node(int _val) {
            val = _val;
        }

        public Node(int _val, Node _left, Node _right, Node _next) {
            val = _val;
            left = _left;
            right = _right;
            next = _next;
        }
    };

    class Solution {
        public Node connect(Node root) {
            // 递归
            if (root != null) {
                if (root.left != null) {
                    root.left.next = root.right;
                    if (root.next != null) {
                        root.right.next = root.next.left;
                    }
                    connect(root.left);
                    connect(root.right);
                }
            }
            return root;
        }
    }

    public Node connect(Node root) {
        // 迭代
        Node start = root; // 记录每层头结点
        while (start != null) {
            Node cur = start;
            start = null;
            while (cur != null) {
                if (cur.left != null) {
                    cur.left.next = cur.right;
                    if (start == null)
                        start = cur.left;
                    if (cur.next != null)
                        cur.right.next = cur.next.left;
                }
                cur = cur.next;
            }
        }
        return root;
    }
}