/* 
* coding: utf-16 -*- 
* File    : LeetCode_1846.java
* Author  : MeteorDream
* Time    : 2021/07/15 22:13:44
* language: Java
* Software: Visual Studio Code
* */

/**
 *[1846. 减小和重新排列数组后的最大元素](https://leetcode-cn.com/problems/maximum-element-after-decreasing-and-rearranging/)
 * 
 * 难度: 中等

 * 题解：https://leetcode-cn.com/problems/maximum-element-after-decreasing-and-rearranging/solution/jian-xiao-he-zhong-xin-pai-lie-shu-zu-ho-sv8z/
 * */

import java.util.*;

public class LeetCode_1846 {
    public static void main(String[] args) {
        LeetCode_1846 s = new LeetCode_1846();

        System.out.println(s + "Finish!");
    }

    /* 排序+贪心 
    public int maximumElementAfterDecrementingAndRearranging(int[] arr) {
        int n = arr.length;
        Arrays.sort(arr);
        arr[0] = 1;
        for (int i = 1; i < n; ++i) {
            if (arr[i] > arr[i - 1] + 1)
                arr[i] = arr[i - 1] + 1;
        }
        return arr[n - 1];
    }*/

    /* 计数排序 */
    public int maximumElementAfterDecrementingAndRearranging(int[] arr) {
        int n = arr.length;
        int[] s = new int[n + 1];
        for (int a : arr) {
            if (a > n)
                ++s[n];
            else
                ++s[a];
        }
        int cnt = 0, k = 0;
        for (int i = n; i > 0; --i) {
            if (s[i] != 0)
                k += s[i] - 1;
            else if (k != 0)
                k -= 1;
            else
                cnt += 1;
        }
        return n - cnt;
    }
}