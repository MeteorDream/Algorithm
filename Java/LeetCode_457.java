/* 
* coding: utf-16 -*- 
* File    : LeetCode_457.java
* Author  : MeteorDream
* Time    : 2021/08/07 11:45:12
* language: Java
* Software: Visual Studio Code
* */

/**
 *[457. 环形数组是否存在循环](https://leetcode-cn.com/problems/circular-array-loop/)
 * 
 * 难度: 中等

 * 题解：
 * */

import java.util.*;

public class LeetCode_457 {
    public static void main(String[] args) {
        LeetCode_457 LC = new LeetCode_457();

        Solution ss = LC.new Solution();

        System.out.println(LC + "Finish!");
        System.out.println(ss + "Finish!");
    }

    class Solution {
        public boolean circularArrayLoop(int[] nums) {
            int n = nums.length;
            // 使用 vis 数组对每个下标进行标记
            // 如果下标为 i 的位置在第 idx 轮被标记，则有 vis[i] = idx
            int[] vis = new int[n];
            for (int start = 0, idx = 1; start < n; start++, idx++) {
                if (vis[start] != 0)
                    continue;
                int cur = start;
                boolean flag = nums[cur] > 0;
                while (true) {
                    int next = ((cur + nums[cur]) % n + n) % n;
                    if (next == cur)
                        break;
                    if (vis[next] != 0) {
                        // 如果 next 点已经被标记过，并且不是在本轮被标记，那么往后的通路必然都被标记，且无环，跳出   
                        if (vis[next] != idx)
                            break;
                        // 如果 next 点已被标记，并且是本来被标记，说明找到了环
                        else
                            return true;
                    }
                    if (flag && nums[next] < 0)
                        break;
                    if (!flag && nums[next] > 0)
                        break;
                    vis[next] = idx;
                    cur = next;
                }
            }
            return false;
        }
    }
}