/* 
* coding: utf-16 -*- 
* File    : LeetCode_343.java
* Author  : MeteorDream
* Time    : 2021/05/28 21:10:18
* language: Java
* Software: Visual Studio Code
* */

/* [343. 整数拆分](https://leetcode-cn.com/problems/integer-break/) */

// import java.util.*;

public class LeetCode_343 {
    public static void main(String[] args) {
        LeetCode_343 s = new LeetCode_343();

        System.out.println(s + "Finish!");
    }

    public int integerBreak(int n) {
        // 根据数学推导，尽量拆分成3
        if (n <= 3) {
            return n - 1;
        }
        int a = n / 3;
        int b = n % 3;
        if (b == 0) {
            return (int) Math.pow(3, a);
        } else if (b == 1) {
            return (int) Math.pow(3, a - 1) * 4;
        } else {
            return (int) Math.pow(3, a) * 2;
        }
    }

}