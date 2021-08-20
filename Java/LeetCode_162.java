/* 
* coding: utf-16 -*- 
* File    : LeetCode_162.java
* Author  : MeteorDream
* Time    : 2021/06/16 10:44:54
* language: Java
* Software: Visual Studio Code
* */

/**
 *[162. 寻找峰值](https://leetcode-cn.com/problems/find-peak-element/)
 *
 * 难度: 中等
 * */

// import java.util.*;

public class LeetCode_162 {
    public static void main(String[] args) {
        LeetCode_162 s = new LeetCode_162();

        System.out.println(s + "Finish!");
    }

    /* // 顺序搜索
    public int findPeakElement(int[] nums) {
        int n = nums.length;
        if (n == 1 || nums[0] > nums[1])
            return 0;
        for (int i = 1; i < n - 1; ++i)
            if (nums[i] > nums[i - 1] && nums[i] > nums[i + 1])
                return i;
        return n - 1;
    } */

    /* // 二分搜索 */
    public int findPeakElement(int[] nums) {
        int n = nums.length;
        if (n == 1 || nums[0] > nums[1])
            return 0;
        if (nums[n - 1] > nums[n - 2])
            return n - 1;
        int left = 1, right = n - 2;
        while (left < right) {
            int mid = left + (right - left) / 2;
            if (nums[mid] > nums[mid + 1])
                right = mid;
            else
                left = mid + 1;
        }
        return left;
    }
}