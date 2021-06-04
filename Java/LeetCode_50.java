/* 
* coding: utf-16 -*- 
* File    : LeetCode_50.java
* Author  : MeteorDream
* Time    : 2021/05/29 20:33:53
* language: Java
* Software: Visual Studio Code
* */

/* [50. Pow(x, n)](https://leetcode-cn.com/problems/powx-n/) */

// import java.util.*;

public class LeetCode_50 {
    public static void main(String[] args) {
        LeetCode_50 s = new LeetCode_50();

        System.out.println(s + "Finish!");
    }

    /* // 暴力(估计会TLE，不测试了) 
    double myPow(double x, int n) {
        double ans = 1;
        for (int t = n >= 0 ? n : -n; t > 0; --t) {
            ans *= x;
        }
        return n > 0 ? ans : (1 / ans);
    }*/

    /* // 快速幂 */
    double myPow(double x, int n) {
        double ans = 1, s = x;
        long t = n;
        for (t = t >= 0 ? t : -t; t > 0; t >>= 1) {
            if ((t & 1) == 1)
                ans *= s;
            s *= s;
        }
        return n >= 0 ? ans : 1 / ans;
    }
}