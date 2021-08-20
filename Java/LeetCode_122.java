/* 
* coding: utf-16 -*- 
* File    : LeetCode_122.java
* Author  : MeteorDream
* Time    : 2021/06/18 23:57:52
* language: Java
* Software: Visual Studio Code
* */

/**
 * [122. 买卖股票的最佳时机 II](https://leetcode-cn.com/problems/best-time-to-buy-and-sell-stock-ii/)
 * 
 * 难度: 简单
 * */

// import java.util.*;

public class LeetCode_122 {
    public static void main(String[] args) {
        LeetCode_122 s = new LeetCode_122();

        System.out.println(s + "Finish!");
    }

    public int maxProfit(int[] prices) {
        int ans = 0, n = prices.length;
        for (int i = 1; i < n; ++i) {
            int d = prices[i] - prices[i - 1];
            if (d > 0)
                ans += d;
        }
        return ans;
    }
}