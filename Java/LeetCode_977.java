/* 
* coding: utf-16 -*- 
* File    : LeetCode_977.java
* Author  : MeteorDream
* Time    : 2021/07/23 15:13:20
* language: Java
* Software: Visual Studio Code
* */

/**
 *[977. 有序数组的平方](https://leetcode-cn.com/problems/squares-of-a-sorted-array/)
 * 
 * 难度: 简单

 * 题解：https://leetcode-cn.com/problems/squares-of-a-sorted-array/solution/you-xu-shu-zu-de-ping-fang-gui-bing-pai-5r2ue/
 * */

import java.util.*;

public class LeetCode_977 {
    public static void main(String[] args) {
        LeetCode_977 s = new LeetCode_977();

        Arrays.sort(new int[2]);

        System.out.println(s + "Finish!");
    }

    /* 排序 
    public int[] sortedSquares(int[] nums) {
        int n = nums.length;
        int[] ans = new int[n];
        for (int i = 0; i < n; ++i)
            ans[i] = nums[i] * nums[i];
        Arrays.sort(ans);
        return ans;
    }*/

    /* 手动归并排序 
    public int[] sortedSquares(int[] nums) {
        int n = nums.length;
        int[] ans = new int[n];
        // 查找 下标最小的 0
        int left = 0, right = n;
        while (left < right) {
            int mid = left + right >> 1;
            if (nums[mid] < 0)
                left = mid + 1;
            else
                right = mid;
        }
        right = left--;
        // 归并
        for (int i = 0; i < n; ++i) {
            if (left < 0 || (right < n && -nums[left] > nums[right])) {
                ans[i] = nums[right] * nums[right];
                ++right;
            } else {
                ans[i] = nums[left] * nums[left];
                --left;
            }
        }
        return ans;
    }*/

    /* 双指针 */
    public int[] sortedSquares(int[] nums) {
        int n = nums.length;
        int[] ans = new int[n];
        // 归并
        int left = 0, right = n - 1;
        for (int i = n - 1; i >= 0; --i) {
            if (-nums[left] < nums[right]) {
                ans[i] = nums[right] * nums[right];
                --right;
            } else {
                ans[i] = nums[left] * nums[left];
                ++left;
            }
        }
        return ans;
    }
}