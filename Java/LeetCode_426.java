/* 
* coding: utf-16 -*- 
* File    : LeetCode_426.java
* Author  : MeteorDream
* Time    : 2021/06/14 19:00:38
* language: Java
* Software: Visual Studio Code
* */

/**
* [426. 将二叉搜索树转化为排序的双向链表](https://leetcode-cn.com/problems/convert-binary-search-tree-to-sorted-doubly-linked-list/)
* [剑指 Offer 36. 二叉搜索树与双向链表](https://leetcode-cn.com/problems/er-cha-sou-suo-shu-yu-shuang-xiang-lian-biao-lcof/)
 * 难度: 中等
 * */

import java.util.*;

public class LeetCode_426 {
    public static void main(String[] args) {
        LeetCode_426 s = new LeetCode_426();

        System.out.println(s + "Finish!");
    }

    class Node {
        public int val;
        public Node left, right;
    }

    /* // 迭代 */
    public Node treeToDoublyList(Node root) {
        if (root == null)
            return null;
        Stack<Node> s = new Stack<>();
        Node head = root, pre = null;
        while (head != null) {
            s.push(head);
            head = head.left;
        }
        head = s.peek();
        while (!s.empty()) {
            Node cur = s.pop();
            cur.left = pre;
            if (pre != null)
                pre.right = cur;
            pre = cur;
            cur = cur.right;
            while (cur != null) {
                s.push(cur);
                cur = cur.left;
            }
        }
        head.left = pre;
        pre.right = head;
        return head;
    }

    /* // 递归修改
    private Node pre, head;
    
    public Node treeToDoublyList(Node root) {
        if (root == null)
            return null;
        pre = null;
        dfs(root);
        head.left = pre;
        pre.right = head;
        return head;
    }
    
    public void dfs(Node root) {
        if (root != null) {
            dfs(root.left);
            if (pre == null)
                head = root;
            else {
                pre.right = root;
                root.left = pre;
            }
            pre = root;
            dfs(root.right);
        }
    } */
}