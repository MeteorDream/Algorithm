/* 
* coding: utf-16 -*- 
* File    : LeetCode_429.java
* Author  : MeteorDream
* Time    : 2021/06/28 12:38:19
* language: Java
* Software: Visual Studio Code
* */

/**
 *[429. N 叉树的层序遍历](https://leetcode-cn.com/problems/n-ary-tree-level-order-traversal/)
 * 
 * 难度: 中等
 * */

import java.util.*;

public class LeetCode_429 {
    public static void main(String[] args) {
        LeetCode_429 s = new LeetCode_429();

        System.out.println(s + "Finish!");
    }

    public List<List<Integer>> levelOrder(Node root) {
        List<List<Integer>> value = new ArrayList<>();
        Deque<Node> q = new ArrayDeque<>();
        if (root != null)
            q.addLast(root);
        while (!q.isEmpty()) {
            Deque<Node> next = new ArrayDeque<>();
            List<Integer> nd = new ArrayList<>();
            while (!q.isEmpty()) {
                Node cur = q.pollFirst();
                nd.add(cur.val);
                for (Node chd : cur.children) {
                    if (chd != null)
                        next.add(chd);
                }
            }
            q = next;
            value.add(nd);
        }
        return value;
    }
}
