/* 
* coding: utf-16 -*- 
* File    : LeetCode_909.java
* Author  : MeteorDream
* Time    : 2021/06/27 17:56:37
* language: Java
* Software: Visual Studio Code
* */

/**
 *[909. 蛇梯棋](https://leetcode-cn.com/problems/snakes-and-ladders/)
 * 
 * 难度: 中等
 * */

import java.util.*;

public class LeetCode_909 {
    public static void main(String[] args) {
        LeetCode_909 s = new LeetCode_909();

        System.out.println(s + "Finish!");
    }

    /* 朴素bfs */
    public int snakesAndLadders(int[][] board) {
        int n = board.length;
        // 预处理棋盘
        Map<Integer, Integer> jump = new HashMap<>();
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (board[i][j] != -1)
                    jump.put(trans(i, j, n), board[i][j]);
            }
        }

        int target = n * n;
        Queue<Integer> q = new ArrayDeque<>();
        Map<Integer, Integer> turn = new HashMap<>();
        q.add(1);
        turn.put(1, 0);
        while (!q.isEmpty()) {
            int start = q.poll();
            int tim = turn.get(start) + 1;
            for (int i = 1; i <= 6; ++i) {
                int next = start + i;
                if (jump.containsKey(next))
                    next = jump.get(next);
                if (!turn.containsKey(next)) {
                    if (next == target)
                        return tim;
                    q.add(next);
                    turn.put(next, tim);
                }
            }
        }
        return -1;
    }

    private int trans(int i, int j, int n) {
        // 将矩阵坐标转换为棋盘数字
        i = n - 1 - i;
        int num = i * n;
        if (i % 2 == 1)
            return num + n - j;
        else
            return num + j + 1;
    }
}