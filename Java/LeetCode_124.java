/* 
* coding: utf-16 -*- 
* File    : LeetCode_124.java
* Author  : MeteorDream
* Time    : 2021/06/30 21:53:33
* language: Java
* Software: Visual Studio Code
* */

/**
 *[124. 二叉树中的最大路径和](https://leetcode-cn.com/problems/binary-tree-maximum-path-sum/)
 * 
 * 难度: 困难

 * 题解：答案千篇一律，没有创新点，不写了
 * */

// import java.util.*;

public class LeetCode_124 {
    public static void main(String[] args) {
        LeetCode_124 s = new LeetCode_124();

        System.out.println(s + "Finish!");
    }

    private int maxPath = -2021;

    private int dfs(TreeNode root) {
        // 返回单向最大路径
        if (root == null)
            return 0;
        else {
            // 左右子树的单向最大路径，如果为负数，那么就不取经过子树
            int left = Math.max(0, dfs(root.left));
            int right = Math.max(0, dfs(root.right));
            // 经过根节点的最大路径和
            maxPath = Math.max(maxPath, root.val + left + right);
            return Math.max(left, right) + root.val;
        }
    }

    public int maxPathSum(TreeNode root) {
        maxPath = -2021;
        dfs(root);
        return maxPath;
    }
}