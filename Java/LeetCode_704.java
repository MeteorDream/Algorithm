/* 
* coding: utf-16 -*- 
* File    : LeetCode_704.java
* Author  : MeteorDream
* Time    : 2021/07/22 22:15:21
* language: Java
* Software: Visual Studio Code
* */

/**
 *[704. 二分查找](https://leetcode-cn.com/problems/binary-search/)
 * 
 * 难度: 简单

 * 题解：https://leetcode-cn.com/problems/binary-search/solution/er-fen-cha-zhao-er-fen-cha-zhao-by-meteo-mt0f/
 * */

// import java.util.*;

public class LeetCode_704 {
    public static void main(String[] args) {
        LeetCode_704 s = new LeetCode_704();

        System.out.println(s + "Finish!");
    }

    /* 顺序查找 
    public int search(int[] nums, int target) {
        int n = nums.length;
        for (int i = 0; i < n; ++i) {
            if (nums[i] == target)
                return i;
            else if (nums[i] > target)
                return -1;
        }
        return -1;
    }*/

    /* 二分查找 */
    public int search(int[] nums, int target) {
        int left = 0, right = nums.length - 1;
        while (left <= right) {
            int mid = left + (right - left >> 1);
            if (nums[mid] == target)
                return mid;
            else if (nums[mid] < target) {
                left = mid + 1;
            } else
                right = mid - 1;
        }
        return -1;
    }
}