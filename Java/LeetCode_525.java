/* 
* coding: utf-16 -*- 
* File    : LeetCode_525.java
* Author  : MeteorDream
* Time    : 2021/06/03 16:40:45
* language: Java
* Software: Visual Studio Code
* */

/* [525. 连续数组](https://leetcode-cn.com/problems/contiguous-array/) */

import java.util.*;

public class LeetCode_525 {
    public static void main(String[] args) {
        LeetCode_525 s = new LeetCode_525();

        System.out.println(s + "Finish!");
    }

    public int findMaxLength(int[] nums) {
        // 前缀和
        // 1. 预处理数组，将 0 改为 -1，使得 0 和 1 数量相等的子数组和为 0
        // 2. 使用 HashMap 记录(前缀和,下标)，一次遍历计算得结果
        int n = nums.length, ans = 0;
        Map<Integer, Integer> st = new HashMap<>();
        st.put(0, -1);
        int s = 0; // 前缀和
        for (int i = 0; i < n; ++i) {
            s += (nums[i] == 1 ? 1 : -1);
            if (st.containsKey(s)) {
                ans = Math.max(ans, i - st.get(s));
            } else {
                st.put(s, i);
            }
        }
        return ans;
    }
}