/* 
* coding: utf-16 -*- 
* File    : LeetCode_167.java
* Author  : MeteorDream
* Time    : 2021/07/24 13:22:12
* language: Java
* Software: Visual Studio Code
* */

/**
 *[167. 两数之和 II - 输入有序数组](https://leetcode-cn.com/problems/two-sum-ii-input-array-is-sorted/)
 * 
 * 难度: 简单

 * 题解：
 * */

// import java.util.*;

public class LeetCode_167 {
    public static void main(String[] args) {
        LeetCode_167 s = new LeetCode_167();

        System.out.println(s + "Finish!");
    }

    /* 双指针 
    public int[] twoSum(int[] nums, int target) {
        for (int i = 0, j = nums.length - 1; i < j;) {
            int s = nums[i] + nums[j];
            if (s < target)
                ++i;
            else if (s > target)
                --j;
            else
                return new int[] { i + 1, j + 1 };
        }
        return new int[] { -1, -1 };
    }*/

    /* 双指针 + 二分 */
    public int[] twoSum(int[] nums, int target) {
        for (int i = 0, j = nums.length - 1; i < j;) {
            int s = nums[i] + nums[j];
            if (s < target) {
                int left = i + 1, right = j - 1;
                while (left < right) {
                    int mid = left + right >> 1;
                    int sum = nums[mid] + nums[j];
                    if (sum < target)
                        left = mid + 1;
                    else if (sum > target)
                        right = mid - 1;
                    else
                        return new int[] { mid + 1, j + 1 };
                }
                i = left;
            } else if (s > target) {
                int left = i + 1, right = j - 1;
                while (left < right) {
                    int mid = left + right >> 1;
                    int sum = nums[i] + nums[mid];
                    if (sum < target)
                        left = mid + 1;
                    else if (sum > target)
                        right = mid - 1;
                    else
                        return new int[] { i + 1, mid + 1 };
                }
                j = left;
            } else
                return new int[] { i + 1, j + 1 };
        }
        return new int[] { -1, -1 };
    }
}