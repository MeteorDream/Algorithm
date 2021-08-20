/* 
* coding: utf-16 -*- 
* File    : LeetCode_559.java
* Author  : MeteorDream
* Time    : 2021/06/29 14:54:58
* language: Java
* Software: Visual Studio Code
* */

/**
 *[559. N 叉树的最大深度](https://leetcode-cn.com/problems/maximum-depth-of-n-ary-tree/)
 * 
 * 难度: 简单
 * */

import java.util.*;

public class LeetCode_559 {
    public static void main(String[] args) {
        LeetCode_559 s = new LeetCode_559();

        System.out.println(s + "Finish!");
    }

    /* 递归
    public int maxDepth(Node root) {
        if (root == null)
            return 0;
        int d = 1;
        for (Node child : root.children) {
            d = Math.max(d, maxDepth(child) + 1);
        }
        return d;
    } */

    /* dfs
    public int maxDepth(Node root) {
        if (root == null)
            return 0;
        int d = 1;
        Deque<Node> s = new ArrayDeque<>();
        Deque<Integer> h = new ArrayDeque<>();
        s.addLast(root);
        h.addLast(1);
        while (!s.isEmpty()) {
            Node cur = s.pollLast();
            int cd = h.pollLast();
            d = Math.max(d, cd);
            for (Node child : cur.children) {
                s.addLast(child);
                h.addLast(cd + 1);
            }
        }
        return d;
    } */

    /* bfs */
    public int maxDepth(Node root) {
        if (root == null)
            return 0;
        int d = 1, last = 1;
        Deque<Node> s = new ArrayDeque<>();
        s.addLast(root);
        while (!s.isEmpty()) {
            Node cur = s.pollFirst();
            for (Node child : cur.children)
                s.addLast(child);
            if (--last == 0) {
                last = s.size();
                if (last > 0)
                    ++d;
            }
        }
        return d;
    }
}