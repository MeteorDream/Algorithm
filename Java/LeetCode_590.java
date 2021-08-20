/* 
* coding: utf-16 -*- 
* File    : LeetCode_590.java
* Author  : MeteorDream
* Time    : 2021/06/28 12:48:00
* language: Java
* Software: Visual Studio Code
* */

/**
 *[590. N 叉树的后序遍历](https://leetcode-cn.com/problems/n-ary-tree-postorder-traversal/)
 * 
 * 难度: 简单
 * */

import java.util.*;

public class LeetCode_590 {
    public static void main(String[] args) {
        LeetCode_590 s = new LeetCode_590();

        List<Node> chd = new ArrayList<>();
        chd.add(new Node(5, new ArrayList<Node>()));
        chd.add(new Node(6, new ArrayList<Node>()));
        Node root = new Node(3, chd);
        chd = new ArrayList<>();
        chd.add(root);
        chd.add(new Node(2, new ArrayList<Node>()));
        chd.add(new Node(4, new ArrayList<Node>()));
        root = new Node(1, chd);

        s.postorder(root);

        System.out.println(s + "Finish!");
    }

    /* 递归
    public List<Integer> postorder(Node root) {
        List<Integer> value = new ArrayList<>();
        post(root, value);
        return value;
    }
    
    private void post(Node root, List<Integer> value) {
        if (root != null) {
            for (Node cur : root.children) {
                if (cur != null)
                    post(cur, value);
            }
            value.add(root.val);
        }
    } */

    /* 迭代 */
    public List<Integer> postorder(Node root) {
        List<Integer> value = new ArrayList<>();
        // stack, child 记录遍历 对应结点已经遍历过的孩子数量
        Deque<Node> s = new ArrayDeque<>();
        Deque<Integer> child = new ArrayDeque<>();
        Node cur = root;
        int next;
        while (!s.isEmpty() || cur != null) {
            while (cur != null) {
                s.addLast(cur);
                child.add(0);
                if (cur.children.size() > 0) {
                    cur = cur.children.get(0);
                } else
                    cur = null;
            }
            cur = s.pollLast();
            next = child.pollLast();
            if (cur.children.size() == 0 || next >= cur.children.size()) {
                value.add(cur.val);
                cur = null;
            } else {
                s.addLast(cur);
                child.addLast(next + 1);
                if (next + 1 < cur.children.size())
                    cur = cur.children.get(next + 1);
                else
                    cur = null;
            }
        }
        return value;
    }
}