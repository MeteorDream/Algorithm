/* 
* coding: utf-16 -*- 
* File    : LeetCode_516.java
* Author  : MeteorDream
* Time    : 2021/08/09 17:30:21
* language: Java
* Software: Visual Studio Code
* */

/**
 *[516. 最长回文子序列](https://leetcode-cn.com/problems/longest-palindromic-subsequence/)
 * 
 * 难度: 中等

 * 题解：
 * */

// import java.util.*;

public class LeetCode_516 {
    public static void main(String[] args) {
        LeetCode_516 LC = new LeetCode_516();

        Solution ss = LC.new Solution();

        System.out.println(LC + "Finish!");
        System.out.println(ss + "Finish!");
    }

    class Solution {
        public int longestPalindromeSubseq(String _s) {
            char[] s = _s.toCharArray();
            int n = s.length;
            int[][] dp = new int[n][n];
            // 初始化
            for (int i = 0; i < n; ++i) {
                dp[i][i] = 1;
            }
            for (int i = n - 1; i >= 0; --i) {
                for (int j = i + 1; j < n; ++j) {
                    if (s[i] == s[j])
                        dp[i][j] = dp[i + 1][j - 1] + 2;
                    else
                        dp[i][j] = Math.max(dp[i + 1][j], dp[i][j - 1]);
                }
            }
            return dp[0][n - 1];
        }
    }
}