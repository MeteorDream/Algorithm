/* 
* coding: utf-16 -*- 
* File    : LeetCode_542.java
* Author  : MeteorDream
* Time    : 2021/07/30 13:05:46
* language: Java
* Software: Visual Studio Code
* */

/**
 *[542. 01 矩阵](https://leetcode-cn.com/problems/01-matrix/)
 * 
 * 难度: 中等

 * 题解：
 * */

import java.util.*;

public class LeetCode_542 {
    public static void main(String[] args) {
        LeetCode_542 LC = new LeetCode_542();

        Solution ss = LC.new Solution();

        int[][] mat = new int[][] { { 0, 0, 0 }, { 0, 1, 0 }, { 1, 1, 1 } };
        LC.updateMatrix(mat);

        System.out.println(LC + "Finish!");
        System.out.println(ss + "Finish!");
    }

    class Solution {
        /* 动态规划 */
        public int[][] updateMatrix(int[][] mat) {
            int n = mat.length, m = mat[0].length;
            int[][] ans = new int[n][m];
            int MAXVAL = n + m;

            for (int[] i : ans)
                Arrays.fill(i, MAXVAL);

            // 初始化最左和最上
            if (mat[0][0] == 0)
                ans[0][0] = 0;
            for (int i = 1; i < n; ++i) {
                if (mat[i][0] == 0)
                    ans[i][0] = 0;
                else
                    ans[i][0] = ans[i - 1][0] + 1;
            }
            for (int i = 1; i < m; ++i) {
                if (mat[0][i] == 0)
                    ans[0][i] = 0;
                else
                    ans[0][i] = ans[0][i - 1] + 1;
            }

            // 从左上向右下
            for (int i = 1; i < n; ++i) {
                for (int j = 1; j < m; ++j) {
                    if (mat[i][j] == 0)
                        ans[i][j] = 0;
                    else
                        ans[i][j] = Math.min(ans[i - 1][j], ans[i][j - 1]) + 1;
                }
            }

            // 初始化最右和最下
            for (int i = n - 2; i >= 0; --i) {
                if (mat[i][m - 1] == 1)
                    ans[i][m - 1] = Math.min(ans[i][m - 1], ans[i + 1][m - 1] + 1);
            }
            for (int i = m - 2; i >= 0; --i) {
                if (mat[n - 1][i] == 1)
                    ans[n - 1][i] = Math.min(ans[n - 1][i], ans[n - 1][i + 1] + 1);
            }

            // 从右下向左上
            for (int i = n - 2; i >= 0; --i) {
                for (int j = m - 2; j >= 0; --j) {
                    if (mat[i][j] == 1)
                        ans[i][j] = Math.min(ans[i][j], Math.min(ans[i + 1][j], ans[i][j + 1]) + 1);
                }
            }

            return ans;
        }
    }

    static int[][] dir = new int[][] { { 0, 1 }, { 0, -1 }, { 1, 0 }, { -1, 0 } };

    /* 多源BFS */
    public int[][] updateMatrix(int[][] mat) {
        int n = mat.length, m = mat[0].length;
        int[][] ans = new int[n][m];

        Deque<int[]> s = new ArrayDeque<>();
        Set<String> vis = new HashSet<>();

        // 将所有值为 0 的点作为源点
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (mat[i][j] == 0) {
                    s.addLast(new int[] { i, j, 0 });
                    vis.add(Integer.toString(i) + '_' + Integer.toString(j));
                }
            }
        }

        // 多源BFS
        while (!s.isEmpty()) {
            int[] cur = s.pollFirst();
            int x = cur[0], y = cur[1], step = cur[2];
            ans[x][y] = step;
            for (int[] d : dir) {
                int dx = x + d[0], dy = y + d[1];
                if (dx >= 0 && dx < n && dy >= 0 && dy < m) {
                    String k = Integer.toString(dx) + '_' + Integer.toString(dy);
                    if (!vis.contains(k)) {
                        s.addLast(new int[] { dx, dy, step + 1 });
                        vis.add(k);
                    }
                }
            }
        }

        return ans;
    }
}