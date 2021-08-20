/* 
* coding: utf-16 -*- 
* File    : LeetCode_120.java
* Author  : MeteorDream
* Time    : 2021/08/05 10:58:45
* language: Java
* Software: Visual Studio Code
* */

/**
 *[120. 三角形最小路径和](https://leetcode-cn.com/problems/triangle/)
 * 
 * 难度: 中等

 * 题解：
 * */

import java.util.*;

public class LeetCode_120 {
    public static void main(String[] args) {
        LeetCode_120 LC = new LeetCode_120();

        Solution ss = LC.new Solution();

        System.out.println(LC + "Finish!");
        System.out.println(ss + "Finish!");
    }

    /* 动态规划 */
    class Solution {
        public int minimumTotal(List<List<Integer>> tri) {
            int n = tri.size();
            int[] dp = new int[n];
            Arrays.fill(dp, 0x7fffffff);
            dp[0] = tri.get(0).get(0);
            for (int i = 1; i < n; ++i) {
                for (int j = i; j > 0; --j) {
                    dp[j] = Math.min(dp[j], dp[j - 1]) + tri.get(i).get(j);
                }
                dp[0] += tri.get(i).get(0);
            }
            int ans = 0x7fffffff;
            for (int val : dp) {
                ans = Math.min(ans, val);
            }
            return ans;
        }
    }
}
