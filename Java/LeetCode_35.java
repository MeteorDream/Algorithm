/* 
* coding: utf-16 -*- 
* File    : LeetCode_35.java
* Author  : MeteorDream
* Time    : 2021/07/22 21:50:50
* language: Java
* Software: Visual Studio Code
* */

/**
 *[35. 搜索插入位置](https://leetcode-cn.com/problems/search-insert-position/)
 * 
 * 难度: 简单

 * 题解：https://leetcode-cn.com/problems/search-insert-position/solution/sou-suo-cha-ru-wei-zhi-jian-dan-er-fen-m-3bla/
 * */

// import java.util.*;

public class LeetCode_35 {
    public static void main(String[] args) {
        LeetCode_35 s = new LeetCode_35();

        System.out.println(s + "Finish!");
    }

    /* 顺序搜索 
    public int searchInsert(int[] nums, int target) {
        int n = nums.length;
        for (int i = 0; i < n; ++i) {
            if (nums[i] >= target)
                return i;
        }
        return n;
    }*/

    /* 二分搜索 */
    public int searchInsert(int[] nums, int target) {
        int left = 0, right = nums.length;
        while (left < right) {
            int mid = left + (right - left >> 1);
            if (nums[mid] < target)
                left = mid + 1;
            else
                right = mid;
        }
        return left;
    }
}