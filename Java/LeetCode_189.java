/* 
* coding: utf-16 -*- 
* File    : LeetCode_189.java
* Author  : MeteorDream
* Time    : 2021/07/24 00:01:56
* language: Java
* Software: Visual Studio Code
* */

/**
 *[189. 旋转数组](https://leetcode-cn.com/problems/rotate-array/)
 * 
 * 难度: 中等

 * 题解：
 * */

// import java.util.*;

public class LeetCode_189 {
    public static void main(String[] args) {
        LeetCode_189 s = new LeetCode_189();

        System.out.println(s + "Finish!");
    }

    /* 新开数组复制 
    public void rotate(int[] nums, int k) {
        int n = nums.length;
        int[] s = new int[n];
        k %= n;
        for (int i = 0; i < n; ++i)
            s[(i + k) % n] = nums[i];
        for (int i = 0; i < n; ++i)
            nums[i] = s[i];
    }*/

    /* 循环替换 
    public void rotate(int[] nums, int k) {
        int n = nums.length, cnt = 0;
        k %= n;
        for (int i = 0; i < n; ++i) {
            int prev = nums[i];
            for (int j = (i + k) % n; j != i; j = (j + k) % n) {
                int tmp = nums[j];
                nums[j] = prev;
                prev = tmp;
                ++cnt;
            }
            int tmp = nums[i];
            nums[i] = prev;
            prev = tmp;
            ++cnt;
            if (cnt == n)
                break;
        }
    }*/

    /* 循环替换 */
    private void rev(int[] nums, int i, int j) {
        for (; i < j; ++i, --j) {
            int tmp = nums[i];
            nums[i] = nums[j];
            nums[j] = tmp;
        }
    }

    public void rotate(int[] nums, int k) {
        int n = nums.length;
        k %= n;
        rev(nums, 0, n - 1);
        rev(nums, 0, k - 1);
        rev(nums, k, n - 1);
    }
}