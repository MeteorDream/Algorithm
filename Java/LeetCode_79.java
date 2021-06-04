/* 
* coding: utf-16 -*- 
* File    : LeetCode_79.java
* Author  : MeteorDream
* Time    : 2021/05/28 16:28:33
* language: Java
* Software: Visual Studio Code
* */

/* [79. 单词搜索](https://leetcode-cn.com/problems/word-search/) */

import java.util.*;

public class LeetCode_79 {
    public static void main(String[] args) {
        LeetCode_79 s = new LeetCode_79();

        char[] s1 = { 'A', 'B', 'C', 'E' };
        char[] s2 = { 'S', 'F', 'C', 'S' };
        char[] s3 = { 'A', 'D', 'E', 'E' };
        char[][] ss = { s1, s2, s3 };

        System.out.println(s.exist(ss, "SEE"));

        System.out.println(s + "Finish!");
    }

    // 回溯 + dfs
    public boolean exist(char[][] board, String word) {
        int n = board.length, m = board[0].length;
        // 预处理
        char[] s = word.toCharArray();
        HashMap<Character, Integer> check = new HashMap<>();
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j)
                check.put(board[i][j], check.getOrDefault(board[i][j], 0) + 1);
        for (char ss : s) {
            check.put(ss, check.getOrDefault(ss, 0) - 1);
            if (check.get(ss) < 0)
                return false;
        }
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j)
                if (dfs(board, s, i, j, 0))
                    return true;
        return false;
    }

    public boolean dfs(char[][] board, char[] word, int i, int j, int k) {
        //  word 查询完了说明查找到了!
        if (k == word.length)
            return true;
        // 越界返回 false
        else if (i < 0 || i >= board.length || j < 0 || j >= board[0].length)
            return false;
        // 不匹配返回 false
        else if (board[i][j] != word[k])
            return false;
        else {
            // 匹配，则先做标记，然后递归查询，最后恢复现场
            char tmp = board[i][j];
            board[i][j] = '#';
            if (dfs(board, word, i + 1, j, k + 1) || dfs(board, word, i, j + 1, k + 1)
                    || dfs(board, word, i - 1, j, k + 1) || dfs(board, word, i, j - 1, k + 1)) {
                board[i][j] = tmp;
                return true;
            } else {
                board[i][j] = tmp;
                return false;
            }
        }
    }
}