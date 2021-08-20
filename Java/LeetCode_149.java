/* 
* coding: utf-16 -*- 
* File    : LeetCode_149.java
* Author  : MeteorDream
* Time    : 2021/06/24 19:02:01
* language: Java
* Software: Visual Studio Code
* */

/**
 *[149. 直线上最多的点数](https://leetcode-cn.com/problems/max-points-on-a-line/)
 * 
 * 难度: 困难
 * */

import java.util.*;

public class LeetCode_149 {
    public static void main(String[] args) {
        LeetCode_149 s = new LeetCode_149();

        System.out.println(s + "Finish!");
    }

    /* 暴力枚举
    public int maxPoints(int[][] points) {
        int n = points.length, ans = 1;
        for (int i = 0; i < n - 1; ++i) {
            int x1 = points[i][0], y1 = points[i][1];
            for (int j = i + 1; j < n; ++j) {
                int cnt = 0, x2 = points[j][0], y2 = points[j][1];
                if (x1 == x2) {
                    for (int k = 0; k < n; ++k)
                        if (points[k][0] == x2)
                            ++cnt;
                } else {
                    int k1 = y2 - y1, k2 = x2 - x1; // 斜率的分数形式
                    int b = y2 * k2 - x2 * k1; // 截距与斜率通分，只记录分子就行
                    for (int k = 0; k < n; ++k)
                        if (points[k][1] * k2 == k1 * points[k][0] + b)
                            ++cnt;
                }
                if (cnt > ans)
                    ans = cnt;
            }
        }
        return ans;
    } */

    /* 哈希优化 */
    public int maxPoints(int[][] points) {
        int n = points.length, ans = 0;
        for (int i = 0; i < n - 1; ++i) {
            int x1 = points[i][0], y1 = points[i][1];
            HashMap<String, Integer> h = new HashMap<>();
            for (int j = i + 1; j < n; ++j) {
                int x2 = points[j][0] - x1, y2 = points[j][1] - y1;
                String k;
                if (x2 == 0)
                    k = "inf";
                else {
                    int s = gcd(x2, y2); // 斜率的分数形式
                    k = Integer.toString(x2 / s) + "_" + Integer.toString(y2 / s);
                }
                h.put(k, h.getOrDefault(k, 0) + 1);
                if (h.get(k) > ans)
                    ans = h.get(k);
            }
        }
        return ans + 1;

    }

    private int gcd(int x, int y) {
        return y == 0 ? x : gcd(y, x % y);
    }
}