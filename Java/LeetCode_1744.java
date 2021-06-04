/* 
* coding: utf-16 -*- 
* File    : LeetCode_1744.java
* Author  : MeteorDream
* Time    : 2021/06/01 11:22:37
* language: Java
* Software: Visual Studio Code
* */

/* [1744. 你能在你最喜欢的那天吃到你最喜欢的糖果吗？](https://leetcode-cn.com/problems/can-you-eat-your-favorite-candy-on-your-favorite-day/) */

// import java.util.*;

public class LeetCode_1744 {
    public static void main(String[] args) {
        LeetCode_1744 s = new LeetCode_1744();

        // int[] c = { 16, 38, 8, 41, 30, 31, 14, 45, 3, 2, 24, 23, 38, 30, 31, 17, 35, 4, 9, 42, 28, 18, 37, 18, 14, 46, 11, 13, 19, 3, 5, 39, 24, 48, 20, 29, 4, 19, 36, 11, 28, 49, 38, 16, 23, 24, 4, 22, 29, 35, 45, 38, 37, 40, 2, 37, 8, 41, 33, 8, 40, 27, 13, 4, 33, 5, 8, 14, 19, 35, 31, 8, 8 };
        // int[][] q = { { 43, 1054, 49 } };

        int[] c = { 46, 5, 47, 48, 43, 34, 15, 26, 11, 25, 41, 47, 15, 25, 16, 50, 32, 42, 32, 21, 36, 34, 50, 45, 46,
                15, 46, 38, 50, 12, 3, 26, 26, 16, 23, 1, 4, 48, 47, 32, 47, 16, 33, 23, 38, 2, 19, 50, 6, 19, 29, 3,
                27, 12, 6, 22, 33, 28, 7, 10, 12, 8, 13, 24, 21, 38, 43, 26, 35, 18, 34, 3, 14, 48, 50, 34, 38, 4, 50,
                26, 5, 35, 11, 2, 35, 9, 11, 31, 36, 20, 21, 37, 18, 34, 34, 10, 21, 8, 5 };
        int[][] q = { { 11, 387, 25 }, { 85, 54, 42 } };
        s.canEat(c, q);

        // int[] c = { 7, 11, 5, 3, 8 };
        // int[][] q = { { 2, 2, 6 } };
        // s.canEat(c, q);

        System.out.println(s + " Finish!");
    }

    // 前缀和
    public boolean[] canEat(int[] candiesCount, int[][] queries) {
        // candiesCount[i] 表示你拥有的第 i 类糖果的数目
        // queries[i] = [favoriteTypei, favoriteDayi, dailyCapi]
        // 即 喜欢的糖果下标， 喜欢的天数， 每天最多吃糖
        // 在每天吃 不超过 dailyCapi 颗糖果的前提下
        // 你可以在第 favoriteDayi 天吃到第 favoriteTypei 类糖果
        int n = candiesCount.length, m = queries.length;
        // s[i] 表示前 i-1 类糖果的数量和
        long[] s = new long[n + 1];
        boolean[] ans = new boolean[m];
        for (int i = 0; i < n; ++i)
            s[i + 1] = s[i] + candiesCount[i];
        for (int i = 0; i < m; ++i) {
            // min 表示喜欢那天最少要吃的糖果数量和最多能吃的糖果数量
            long min = queries[i][1], max = (long) queries[i][2] * (queries[i][1] + 1);
            // 只要(s[q], s[q + 1])与(min, max)区间有交集，即可在喜欢那天吃到喜欢的糖果
            ans[i] = (min < s[queries[i][0] + 1]) && (max > s[queries[i][0]]);
        }
        return ans;
    }
}