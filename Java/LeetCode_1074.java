/* 
* coding: utf-16 -*- 
* File    : LeetCode_1074.java
* Author  : MeteorDream
* Time    : 2021/05/29 11:19:28
* language: Java
* Software: Visual Studio Code
* */

/* [1074. 元素和为目标值的子矩阵数量](https://leetcode-cn.com/problems/number-of-submatrices-that-sum-to-target/) */

import java.util.*;

public class LeetCode_1074 {
    public static void main(String[] args) {
        LeetCode_1074 s = new LeetCode_1074();

        System.out.println(s + "Finish!");
    }

    /* // 二维前缀和 暴力解法 
    static int[][] s = new int[107][107];
    
    public int numSubmatrixSumTarget(int[][] matrix, int target) {
        int n = matrix.length, m = matrix[0].length, ans = 0;
        // 二维前缀和
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j)
                s[i + 1][j + 1] = matrix[i][j] + s[i + 1][j] + s[i][j + 1] - s[i][j];
        // 暴力搜索
        for (int a = 1; a <= n; ++a)
            for (int b = 1; b <= m; ++b)
                for (int c = 1; c <= a; ++c)
                    for (int d = 1; d <= b; ++d)
                        if (s[a][b] - s[a][d - 1] - s[c - 1][b] + s[c - 1][d - 1] == target)
                            ++ans;
        return ans;
    }*/

    /* // 二维前缀和 hahsmap解法 */
    static int[][] s = new int[107][107];

    public int numSubmatrixSumTarget(int[][] matrix, int target) {
        int n = matrix.length, m = matrix[0].length, ans = 0;
        // 二维前缀和
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j)
                s[i + 1][j + 1] = matrix[i][j] + s[i + 1][j] + s[i][j + 1] - s[i][j];
        // 枚举三条边，第四条边透过hashmap查找
        for (int a = 1; a <= n; ++a) {
            for (int b = a; b <= n; ++b) {
                Map<Integer, Integer> ss = new HashMap<>();
                for (int c = 1; c <= m; ++c) {
                    int tmp = s[b][c] - s[a - 1][c];
                    if (tmp == target)
                        ++ans;
                    if (ss.containsKey(tmp - target))
                        ans += ss.get(tmp - target);
                    ss.put(tmp, ss.getOrDefault(tmp, 0) + 1);
                }
            }
        }
        return ans;
    }
}