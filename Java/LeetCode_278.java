/* 
* coding: utf-16 -*- 
* File    : LeetCode_278.java
* Author  : MeteorDream
* Time    : 2021/06/13 16:36:17
* language: Java
* Software: Visual Studio Code
* */

/* [278. 第一个错误的版本](https://leetcode-cn.com/problems/first-bad-version/) */

// import java.util.*;

public class LeetCode_278 {
    public static void main(String[] args) {
        LeetCode_278 s = new LeetCode_278();

        System.out.println(s + "Finish!");
    }

    /* The isBadVersion API is defined in the parent class VersionControl.
      boolean isBadVersion(int version); */
    // 只是为了语法检查不报错随便写的API
    public boolean isBadVersion(int version) {
        return true;
    }

    public int firstBadVersion(int n) {
        //查找第一个 isBadVision(i) 值为 true 的值 i
        int left = 1, right = n;
        while (left < right) {
            int mid = left + (right - left) / 2;
            if (isBadVersion(mid))
                right = mid;
            else
                left = mid + 1;
        }
        return left;
    }
}