/* 
* coding: utf-16 -*- 
* File    : LeetCode_931.java
* Author  : MeteorDream
* Time    : 2021/08/05 11:00:17
* language: Java
* Software: Visual Studio Code
* */

/**
 *[931. 下降路径最小和](https://leetcode-cn.com/problems/minimum-falling-path-sum/)
 * 
 * 难度: 中等

 * 题解：和120差不多，换汤不换药
 * */

import java.util.*;

public class LeetCode_931 {
    public static void main(String[] args) {
        LeetCode_931 LC = new LeetCode_931();

        Solution ss = LC.new Solution();

        System.out.println(LC + "Finish!");
        System.out.println(ss + "Finish!");
    }

    class Solution {
        public int minFallingPathSum(int[][] matrix) {
            int n = matrix.length;
            if (n == 1)
                return matrix[0][0];
            int[][] dp = matrix.clone();

            for (int i = 1; i < n; ++i) {
                // 第一行和最后一行单独处理
                dp[i][0] += Math.min(dp[i - 1][0], dp[i - 1][1]);
                dp[i][n - 1] += Math.min(dp[i - 1][n - 1], dp[i - 1][n - 2]);
                for (int j = 1; j < n - 1; ++j) {
                    dp[i][j] += Math.min(dp[i - 1][j], Math.min(dp[i - 1][j + 1], dp[i - 1][j - 1]));
                }
            }

            int ans = dp[n - 1][0];
            for (int s : dp[n - 1])
                ans = Math.min(ans, s);
            return ans;
        }
    }

    public int minFallingPathSum(int[][] matrix) {
        int n = matrix.length;
        int[][] dp = new int[n][n + 2];
        for (int[] s : dp)
            Arrays.fill(s, 0x3f3f3f3f);

        for (int i = 0; i < n; ++i) {
            dp[0][i + 1] = matrix[0][i];
        }

        for (int i = 1; i < n; ++i) {
            for (int j = 0; j < n - 1; ++j) {
                dp[i][j + 1] = matrix[i][j] + Math.min(dp[i - 1][j], Math.min(dp[i - 1][j + 1], dp[i - 1][j + 2]));
            }
        }

        int ans = dp[n - 1][0];
        for (int s : dp[n - 1])
            ans = Math.min(ans, s);
        return ans;
    }
}