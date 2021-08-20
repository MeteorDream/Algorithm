import java.util.HashMap;

/* 
* coding: utf-16 -*- 
* File    : LeetCode_96.java
* Author  : MeteorDream
* Time    : 2021/06/29 23:37:24
* language: Java
* Software: Visual Studio Code
* */

/**
 *[96. 不同的二叉搜索树](https://leetcode-cn.com/problems/unique-binary-search-trees/)
 * 
 * 难度: 中等

 * 题解：https://leetcode-cn.com/problems/unique-binary-search-trees/solution/bu-tong-de-er-cha-sou-suo-shu-di-gui-don-klcp/
 * */

import java.util.*;

public class LeetCode_96 {
    public static void main(String[] args) {
        LeetCode_96 s = new LeetCode_96();

        System.out.println(s + "Finish!");
    }

    /* 递归 */
    private static Map<Integer, Integer> cache = new HashMap<>();

    private int dfs(int n) {
        if (n <= 1)
            return 1;
        else if (cache.containsKey(n))
            return cache.get(n);
        else {
            int c = 0;
            for (int i = 0; i < n; ++i)
                c += dfs(i) * dfs(n - i - 1);
            cache.put(n, c);
            return c;
        }
    }

    public int numTrees(int n) {
        return dfs(n);
    }

    /* 动态规划
    public int numTrees(int n) {
        int[] dp = new int[n + 1];
        dp[0] = 1;
        for (int i = 1; i <= n; ++i)
            for (int j = 0; j < i; ++j)
                dp[i] += dp[j] * dp[i - 1 - j];
        return dp[n];
    } */

    /* 数学 
    public int numTrees(int n) {
        long s = 1;
        for (int i = 1; i <= n; ++i)
            s = s * (4 * i - 2) / (i + 1);
        return (int) s;
    }*/

    /* 打表 
    private static int[] catalan = new int[] { 1, 1, 2, 5, 14, 42, 132, 429, 1430, 4862, 16796, 58786, 208012, 742900,
            2674440, 9694845, 35357670, 129644790, 477638700, 1767263190 };
    
    public int numTrees(int n) {
        return catalan[n];
    }*/
}