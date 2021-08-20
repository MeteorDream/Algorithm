/* 
* coding: utf-16 -*- 
* File    : LeetCode_95.java
* Author  : MeteorDream
* Time    : 2021/06/30 00:10:56
* language: Java
* Software: Visual Studio Code
* */

/**
 *[95. 不同的二叉搜索树 II](https://leetcode-cn.com/problems/unique-binary-search-trees-ii/)
 * 
 * 难度: 中等

 * 题解：
 * */

import java.util.*;

public class LeetCode_95 {
    public static void main(String[] args) {
        LeetCode_95 s = new LeetCode_95();

        s.generateTrees(3);

        System.out.println(s + "Finish!");
    }

    private int[] nums = new int[] { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

    /* 分治、递归 
    private List<TreeNode> dfs(int start, int end) {
        List<TreeNode> forest = new ArrayList<>();
        if (start == end)
            forest.add(new TreeNode(nums[start]));
        else if (start > end)
            forest.add(null);
        else {
            // 枚举根节点
            for (int i = start; i <= end; ++i) {
                // 枚举左子树
                for (TreeNode left : dfs(start, i - 1)) {
                    // 枚举右子树
                    for (TreeNode right : dfs(i + 1, end)) {
                        forest.add(new TreeNode(nums[i], left, right));
                    }
                }
            }
        }
        return forest;
    }
    
    public List<TreeNode> generateTrees(int n) {
        return dfs(0, n - 1);
    }*/

    /* 动态规划1 */
    public List<TreeNode> generateTrees(int n) {
        // dp[i][j] 表示 范围为 [i,j] 的结点构成的二叉搜索树
        // 状态转移: 枚举 [i,j] 作为根节点
        // dp[i][j] = sum[TreeNode(k, dp[i][k - 1], dp[k + 1][j])] k = i ~ j
        List<List<List<TreeNode>>> dp = new ArrayList<>();

        dp.add(new ArrayList<>());
        for (int i = 0; i < n; ++i) {

        }

        List<TreeNode> ans = new ArrayList<>();
        return dp.get(1).get(n);
    }

}