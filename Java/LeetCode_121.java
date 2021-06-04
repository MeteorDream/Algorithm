/* 
* coding: utf-16 -*- 
* File    : LeetCode_121.java
* Author  : MeteorDream
* Time    : 2021/05/31 21:20:03
* language: Java
* Software: Visual Studio Code
* */

/* [121. 买卖股票的最佳时机](https://leetcode-cn.com/problems/best-time-to-buy-and-sell-stock/) */

// import java.util.*;

public class LeetCode_121 {
    public static void main(String[] args) {
        LeetCode_121 s = new LeetCode_121();

        System.out.println(s + "Finish!");
    }

    // 动态规划
    public int maxProfit(int[] prices) {
        if (prices.length < 2)
            return 0;
        int ans = 0, buy = prices[0];
        for (int p : prices) {
            if (p < buy)
                buy = p;
            else
                ans = Math.max(ans, p - buy);
        }
        return ans;
    }
}