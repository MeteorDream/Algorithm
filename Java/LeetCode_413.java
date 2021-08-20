/* 
* coding: utf-16 -*- 
* File    : LeetCode_413.java
* Author  : MeteorDream
* Time    : 2021/08/10 11:37:01
* language: Java
* Software: Visual Studio Code
* */

/**
 *[413. 等差数列划分](https://leetcode-cn.com/problems/arithmetic-slices/)
 * 
 * 难度: 中等

 * 题解：
 * */

// import java.util.*;

public class LeetCode_413 {
    public static void main(String[] args) {
        LeetCode_413 LC = new LeetCode_413();

        Solution ss = LC.new Solution();

        System.out.println(LC + "Finish!");
        System.out.println(ss + "Finish!");
    }

    class Solution {
        public int numberOfArithmeticSlices(int[] nums) {
            int n = nums.length;
            if (n < 3)
                return 0;
            int cnt = 0, ans = 0;
            for (int j = 2; j < n; j++) {
                if (nums[j] - nums[j - 1] != nums[j - 1] - nums[j - 2]) {
                    cnt = 0;
                } else {
                    cnt += 1;
                    ans += cnt;
                }
            }
            return ans;
        }
    }
}