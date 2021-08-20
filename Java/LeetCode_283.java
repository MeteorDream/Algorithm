import java.util.Arrays;

/* 
* coding: utf-16 -*- 
* File    : LeetCode_283.java
* Author  : MeteorDream
* Time    : 2021/07/24 13:30:02
* language: Java
* Software: Visual Studio Code
* */

/**
 *[283. 移动零](https://leetcode-cn.com/problems/move-zeroes/)
 * 
 * 难度: 简单

 * 题解：
 * */

// import java.util.*;

public class LeetCode_283 {
    public static void main(String[] args) {
        LeetCode_283 LC = new LeetCode_283();
        Solution s = LC.new Solution();
        int[] nums = new int[] { 0, 1, 2, 3, 4, 5, 6, 7 };
        s.moveZeroes(nums);
        System.out.println(Arrays.toString(nums));
        System.out.println(LC + "Finish!");
    }

    /* 双指针 */
    class Solution {
        public void moveZeroes(int[] nums) {
            int n = nums.length;
            int i = 0, j = 0;
            for (; j < n; ++j)
                if (nums[j] != 0)
                    nums[i++] = nums[j];
            while (i < n)
                nums[i++] = 0;
        }
    }

}