/* 
* coding: utf-16 -*- 
* File    : LeetCode_994.java
* Author  : MeteorDream
* Time    : 2021/07/30 15:41:37
* language: Java
* Software: Visual Studio Code
* */

/**
 *[994. 腐烂的橘子](https://leetcode-cn.com/problems/rotting-oranges/)
 * 
 * 难度: 中等

 * 题解：
 * */

import java.util.*;

public class LeetCode_994 {
    public static void main(String[] args) {
        LeetCode_994 LC = new LeetCode_994();

        Solution ss = LC.new Solution();

        System.out.println(LC + "Finish!");
        System.out.println(ss + "Finish!");
    }

    class Solution {

    }

    static int[][] dir = new int[][] { { 0, 1 }, { 0, -1 }, { 1, 0 }, { -1, 0 } };

    /* 多源BFS */
    public int orangesRotting(int[][] grid) {
        int n = grid.length, m = grid[0].length;
        int cnt = 0; // 橘子的个数

        Deque<int[]> s = new ArrayDeque<>();
        Set<Integer> vis = new HashSet<>();

        // 将所有值为 0 的点作为源点
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (grid[i][j] == 2) {
                    s.addLast(new int[] { i, j, 0 });
                    vis.add(i * 32 + j);
                }
                if (grid[i][j] != 0)
                    ++cnt;
            }
        }

        // 多源BFS
        int tim = 0;
        while (!s.isEmpty()) {
            int[] cur = s.pollFirst();
            int x = cur[0], y = cur[1], step = cur[2];
            if (step > tim)
                tim = step;
            --cnt;
            for (int[] d : dir) {
                int dx = x + d[0], dy = y + d[1];
                if (dx >= 0 && dx < n && dy >= 0 && dy < m && grid[dx][dy] == 1) {
                    int k = dx * 32 + dy;
                    if (!vis.contains(k)) {
                        s.addLast(new int[] { dx, dy, step + 1 });
                        vis.add(k);
                    }
                }
            }
        }

        return cnt == 0 ? tim : -1;
    }
}