/* 
* coding: utf-16 -*- 
* File    : LeetCode_589.java
* Author  : MeteorDream
* Time    : 2021/06/29 14:44:57
* language: Java
* Software: Visual Studio Code
* */

/**
 *[589. N 叉树的前序遍历](https://leetcode-cn.com/problems/n-ary-tree-preorder-traversal/)
 * 
 * 难度: 简单
 * */

import java.util.*;

public class LeetCode_589 {
    public static void main(String[] args) {
        LeetCode_589 s = new LeetCode_589();

        System.out.println(s + "Finish!");
    }

    /* 递归
    List<Integer> value;
    
    public void dfs(Node root) {
        value.add(root.val);
        for (Node child : root.children) {
            dfs(child);
        }
    }
    
    public List<Integer> preorder(Node root) {
        value = new ArrayList<>();
        if (root == null)
            return value;
        dfs(root);
        return value;
    } */

    /* 迭代 */
    public List<Integer> preorder(Node root) {
        List<Integer> value = new ArrayList<>();
        Deque<Node> s = new ArrayDeque<>();
        if (root != null)
            s.addLast(root);
        while (!s.isEmpty()) {
            Node cur = s.pollLast();
            value.add(cur.val);
            for (int i = cur.children.size() - 1; i >= 0; --i)
                s.addLast(cur.children.get(i));
        }
        return value;
    }
}