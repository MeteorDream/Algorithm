/* 
* coding: utf-16 -*- 
* File    : LeetCode_1833.java
* Author  : MeteorDream
* Time    : 2021/07/02 14:43:39
* language: Java
* Software: Visual Studio Code
* */

/**
 *[1833. 雪糕的最大数量](https://leetcode-cn.com/problems/maximum-ice-cream-bars/)
 * 
 * 难度: 中等

 * 题解：
 * */

import java.util.*;

public class LeetCode_1833 {
    public static void main(String[] args) {
        LeetCode_1833 s = new LeetCode_1833();

        System.out.println(s + "Finish!");
    }

    public int maxIceCream(int[] costs, int coins) {
        Arrays.sort(costs);
        int cnt = 0;
        for (int c : costs) {
            if (coins < c)
                break;
            else {
                coins -= c;
                ++cnt;
            }
        }
        return cnt;
    }
}