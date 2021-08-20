/* 
* coding: utf-16 -*- 
* File    : LeetCode_483.java
* Author  : MeteorDream
* Time    : 2021/06/18 12:05:51
* language: Java
* Software: Visual Studio Code
* */

/**
 *[483. 最小好进制](https://leetcode-cn.com/problems/smallest-good-base/)
 * 
 * 难度: 困难
 * */

// import java.util.*;

public class LeetCode_483 {
    public static void main(String[] args) {
        LeetCode_483 s = new LeetCode_483();

        s.smallestGoodBase("13");
        // s.smallestGoodBase("2251799813685247");

        System.out.println(s + "Finish!");
    }

    /* 二分 */
    public String smallestGoodBase(String n) {
        long num = Long.parseLong(n);
        // 枚举 k进制 中 1 的个数，最多为 二进制 时的位数
        for (int i = (int) (Math.log(num) / Math.log(2) + 1); i > 2; --i) {
            // k^0 + k^1 + …… + k^(i-1) = n -- 通过二分法计算 k
            long left = 2, right = num - 1;
            while (left <= right) {
                long mid = (left + right) / 2;
                // MaxVal 用于反向溢出判断，一旦溢出，说明比num大，设为num+1即可
                long s = 0, MaxVal = num / mid + 1;
                for (int j = 0; j < i; ++j)
                    if (s < MaxVal)
                        s = s * mid + 1;
                    else {
                        s = num + 1;
                        break;
                    }
                if (s == num)
                    return Long.toString(mid);
                else if (s > num)
                    right = mid - 1;
                else
                    left = mid + 1;
            }
        }
        return Long.toString(num - 1);
    }

    /* 数学方法
    public String smallestGoodBase(String n) {
        long num = Long.parseLong(n);
        // 枚举 k进制 中 1 的个数，最多为 二进制 时的位数
        for (int i = (int) (Math.log(num) / Math.log(2) + 1); i > 2; --i) {
            // k^0 + k^1 + …… + k^(i-1) = n -- 解方程计算 k
            // k < n^(1/(i - 1)) < k +1
            long k = (long) Math.pow(num, 1.0 / (i - 1));
            // 检查 k 进制数 (11…11) (i个1)是否是n
            long res = 0;
            for (int j = 0; j < i; ++j)
                res = res * k + 1;
            if (res == num)
                return Long.toString(k);
        }
        return Long.toString(num - 1);
    } */
}