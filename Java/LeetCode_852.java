/* 
* coding: utf-16 -*- 
* File    : LeetCode_852.java
* Author  : MeteorDream
* Time    : 2021/06/15 11:18:10
* language: Java
* Software: Visual Studio Code
* */

/**
 *[852. 山脉数组的峰顶索引](https://leetcode-cn.com/problems/peak-index-in-a-mountain-array/)
 * 难度: 简单
 * */

// import java.util.*;

public class LeetCode_852 {
    public static void main(String[] args) {
        LeetCode_852 s = new LeetCode_852();

        System.out.println(s + "Finish!");
    }

    /* // 顺序查找 
    public int peakIndexInMountainArray(int[] arr) {
        int n = arr.length - 1;
        for (int i = 1; i < n; ++i) {
            if (arr[i] > arr[i + 1])
                return i;
        }
        return n;
    }*/

    /* // 二分查找
    public int peakIndexInMountainArray(int[] arr) {
        int left = 1, right = arr.length - 1;
        while (left < right) {
            int mid = left + (right - left) / 2;
            if (arr[mid] > arr[mid + 1])
                right = mid;
            else
                left = mid + 1;
        }
        return left;
    } */

    /* // 三分查找
    public int peakIndexInMountainArray(int[] arr) {
        int left = 1, right = arr.length - 1;
        while (left < right) {
            int m = (right - left) / 3;
            int m1 = left + m, m2 = right - m;
            if (arr[m1] > arr[m2])
                right = m2 - 1;
            else
                left = m1 + 1;
        }
        return left;
    } */

    /* // 三分查找2 */
    public int peakIndexInMountainArray(int[] arr) {
        int left = 1, right = arr.length - 2;
        while (left < right) {
            int m = (right - left) / 3;
            int m1 = left + m, m2 = right - m;
            if (arr[m1] > arr[m1 + 1])
                right = m1;
            else if (arr[m2] < arr[m2 + 1])
                left = m2 + 1;
            else {
                left = m1 + 1;
                right = m2;
            }
        }
        return left;
    }
}