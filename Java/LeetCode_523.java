/* 
* coding: utf-16 -*- 
* File    : LeetCode_523.java
* Author  : MeteorDream
* Time    : 2021/06/02 09:59:00
* language: Java
* Software: Visual Studio Code
* */

/* [523. 连续的子数组和](https://leetcode-cn.com/problems/continuous-subarray-sum/) */

import java.util.*;

public class LeetCode_523 {
    public static void main(String[] args) {
        LeetCode_523 s = new LeetCode_523();

        int[] nums = { 23, 2, 4, 6, 6 };
        int k = 7;
        s.checkSubarraySum(nums, k);

        System.out.println(s + "Finish!");
    }

    /* // 前缀和+HashMap */
    public boolean checkSubarraySum(int[] nums, int k) {
        int n = nums.length, sum = 0;
        Map<Integer, Integer> s = new HashMap<>();
        s.put(0, -1);
        for (int i = 0; i < n; ++i) {
            sum = (sum + nums[i]) % k;
            if (!s.containsKey(sum))
                s.put(sum, i);
            else if (s.get(sum) + 1 < i)
                return true;
        }
        return false;
    }
}