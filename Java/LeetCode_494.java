/* 
* coding: utf-16 -*- 
* File    : LeetCode_494.java
* Author  : MeteorDream
* Time    : 2021/06/07 17:54:06
* language: Java
* Software: Visual Studio Code
* */

/* [494. 目标和](https://leetcode-cn.com/problems/target-sum/) */

import java.util.*;

public class LeetCode_494 {
    public static void main(String[] args) {
        LeetCode_494 s = new LeetCode_494();

        int[] nums = new int[] { 1, 1, 1, 1, 1 };
        s.findTargetSumWays(nums, 3);

        System.out.println(s + "Finish!");
    }

    /* // 深度优先搜索(居然能过，729 ms) 
    public int findTargetSumWays(int[] nums, int target) {
        return dfs(nums, 0, 0, target);
    }
    
    public int dfs(int[] nums, int i, int s, int target) {
        // 结束dfs，根据结果返回答案
        if (i == nums.length) {
            if (s == target)
                return 1;
            else
                return 0;
        } else {
            return dfs(nums, i + 1, s + nums[i], target) + dfs(nums, i + 1, s - nums[i], target);
        }
    }*/

    /* // 记忆化深度优先搜索(14 ms) 
    private int[] nums;
    private int target;
    private static int[][] memory = new int[1007][2007];
    
    public int findTargetSumWays(int[] nums, int target) {
        this.nums = nums;
        this.target = target;
        for (int i = 0; i < nums.length; ++i) {
            for (int j = 0; j < 2007; ++j) {
                memory[i][j] = -1;
            }
        }
        return dfs(0, 0);
    }
    
    public int dfs(int i, int s) {
        int t = s + 1000;
        if (i == nums.length) {
            if (s == target)
                return 1;
            else
                return 0;
        } else if (memory[i][t] == -1) {
            memory[i][t] = dfs(i + 1, s + nums[i]) + dfs(i + 1, s - nums[i]);
        }
        return memory[i][t];
    }*/

    /* // 广度优先搜索(74 ms)
    public int findTargetSumWays(int[] nums, int target) {
        Map<Integer, Integer> q = new HashMap<>();
        if (nums[0] == 0)
            q.put(0, 2);
        else {
            q.put(nums[0], 1);
            q.put(-nums[0], 1);
        }
        for (int i = 1; i < nums.length; ++i) {
            Map<Integer, Integer> tmp = q;
            q = new HashMap<>();
            for (int k : tmp.keySet()) {
                int v = tmp.get(k);
                q.put(k + nums[i], v + q.getOrDefault(k + nums[i], 0));
                q.put(k - nums[i], v + q.getOrDefault(k - nums[i], 0));
            }
        }
        return q.getOrDefault(target, 0);
    } */

    /* // 动态规划 */
    // dp[i][j] 表示前 i 个 和为 j 的方案数
    public int findTargetSumWays(int[] nums, int target) {
        int n = nums.length, s = 0;
        for (int i : nums)
            s += Math.abs(i);
        if (target > s)
            return 0;
        int[][] dp = new int[n + 1][2 * s + 1];
        dp[0][s] = 1;
        for (int i = 1; i <= n; ++i) {
            int tmp = nums[i - 1];
            for (int j = -s; j <= s; ++j) {
                if ((j - tmp) + s >= 0)
                    dp[i][j + s] += dp[i - 1][(j - tmp) + s];
                if ((j + tmp) + s <= 2 * s)
                    dp[i][j + s] += dp[i - 1][(j + tmp) + s];
            }
        }
        return dp[n][target + s];
    }
}