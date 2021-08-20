/* 
* coding: utf-16 -*- 
* File    : LeetCode_1818.java
* Author  : MeteorDream
* Time    : 2021/07/14 12:53:12
* language: Java
* Software: Visual Studio Code
* */

/**
 *[1818. 绝对差值和](https://leetcode-cn.com/problems/minimum-absolute-sum-difference/)
 * 
 * 难度: 中等

 * 题解：https://leetcode-cn.com/problems/minimum-absolute-sum-difference/solution/jue-dui-chai-zhi-he-mei-ju-er-fen-by-met-8ec4/
 * */

import java.util.*;

public class LeetCode_1818 {
    public static void main(String[] args) {
        LeetCode_1818 s = new LeetCode_1818();

        System.out.println(s + "Finish!");
    }

    public int minAbsoluteSumDiff(int[] nums1, int[] nums2) {
        int n = nums1.length;
        int[] st = nums1.clone();
        Arrays.sort(st);
        long s = 0, mx = 0;
        for (int i = 0; i < n; ++i) {
            int x = nums1[i], y = nums2[i];
            int z = Math.abs(x - y);
            s += z;
            int left = 0, right = n - 1;
            while (left < right) {
                int mid = left + right >> 1;
                if (st[mid] < y)
                    left = mid + 1;
                else
                    right = mid;
            }
            mx = Math.max(mx, z - Math.min(Math.abs(st[left] - y), (left - 1 > 0 ? Math.abs(st[left - 1] - y) : z)));
        }
        return (int) ((s - mx) % 1000000007);
    }
}