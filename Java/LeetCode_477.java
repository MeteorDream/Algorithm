/* 
* coding: utf-16 -*- 
* File    : LeetCode_477_total_hamming_distance.java
* Author  : MeteorDream
* Time    : 2021/05/28 01:29:53
* language: Java
* Software: Visual Studio Code
* */

/* [477. 汉明距离总和](https://leetcode-cn.com/problems/total-hamming-distance/) */

public class LeetCode_477 {
    public static void main(String[] args) {
        LeetCode_477 s = new LeetCode_477();

        System.out.println(s + "Finish!");
    }

    public int totalHammingDistance(int[] nums) {
        int n = nums.length, ans = 0;
        for (int i = 0; i < 32; ++i) {
            int c = 0; //统计第i位为1的数量
            for (int num : nums)
                if ((num & (1 << i)) > 0)
                    ++c;
            ans += c * (n - c);
        }
        return ans;
    }
}