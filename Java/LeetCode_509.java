import java.util.Arrays;

/* 
* coding: utf-16 -*- 
* File    : LeetCode_509.java
* Author  : MeteorDream
* Time    : 2021/07/24 15:08:18
* language: Java
* Software: Visual Studio Code
* */

/**
 *[509. 斐波那契数](https://leetcode-cn.com/problems/fibonacci-number/)
 * 
 * 难度: 简单

 * 题解：
 * */

// import java.util.*;

public class LeetCode_509 {
    public static void main(String[] args) {
        LeetCode_509 LC = new LeetCode_509();

        Solution ss = LC.new Solution();

        int[] ans = new int[47];
        for (int i = 0; i < 47; ++i)
            ans[i] = LC.fib(i);

        System.out.println(Arrays.toString(ans));

        System.out.println(LC + "Finish!");
        System.out.println(ss + "Finish!");
    }

    /* 经典递归 */
    class Solution {
        public int fib(int n) {
            return n > 1 ? fib(n - 1) + fib(n - 2) : n;
        }
    }

    /* 记忆化 
    private int[] cache = new int[32];
    
    public int fib(int n) {
        if (n <= 1)
            return n;
        else if (cache[n] == 0)
            cache[n] = fib(n - 1) + fib(n - 2);
        return cache[n];
    }*/

    /* 打表1 
    private static int[] cache = new int[32];
    
    public int fib(int n) {
        if (n <= 1)
            return n;
        else if (cache[n] == 0)
            cache[n] = fib(n - 1) + fib(n - 2);
        return cache[n];
    }*/

    /* 打表2 
    private static int[] cache = { 0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233, 377, 610, 987, 1597, 2584, 4181, 6765, 10946, 17711, 28657, 46368, 75025, 121393, 196418, 317811, 514229, 832040, 1346269 };
    
    public int fib(int n) {
        return cache[n];
    }*/

    /* 动态规划 
    public int fib(int n) {
        int a = 0, b = 1;
        for (int i = 0; i < n; ++i) {
            b += a;
            a = b - a;
        }
        return a;
    }*/

    /* 矩阵快速幂 */
    private int[] matrix(int[] a, int[] b) {
        return new int[] { a[0] * b[0] + a[1] * b[2], a[0] * b[1] + a[1] * b[3], a[2] * b[0] + a[3] * b[2],
                a[2] * b[1] + a[3] * b[3] };
    }

    public int fib(int n) {
        int[] s = new int[] { 1, 0, 0, 1 }, f = new int[] { 1, 1, 1, 0 };
        for (int cnt = n; cnt != 0; cnt >>= 1) {
            if ((cnt & 1) == 1)
                s = matrix(s, f);
            f = matrix(f, f);
        }
        return s[2];
    }
}