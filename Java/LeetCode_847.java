/* 
* coding: utf-16 -*- 
* File    : LeetCode_847.java
* Author  : MeteorDream
* Time    : 2021/08/06 19:24:35
* language: Java
* Software: Visual Studio Code
* */

/**
 *[847. 访问所有节点的最短路径](https://leetcode-cn.com/problems/shortest-path-visiting-all-nodes/)
 * 
 * 难度: 困难

 * 题解：
 * */

import java.util.*;

public class LeetCode_847 {
    public static void main(String[] args) {
        LeetCode_847 LC = new LeetCode_847();

        Solution ss = LC.new Solution();

        System.out.println(LC + "Finish!");
        System.out.println(ss + "Finish!");
    }

    class Solution {
        int MAXVAL = 0x3f3f3f3f;

        public int shortestPathLength(int[][] graph) {
            int n = graph.length, END = (1 << n) - 1;
            // 队列中存放 最后到达的结点，状态，步数
            Deque<int[]> s = new ArrayDeque<>();
            // 集合中存放状态+结点的映射，用于避免重复的访问如a->b->a->b
            Set<Integer> vis = new HashSet<>();
            for (int i = 0; i < n; ++i) {
                s.addLast(new int[] { i, 1 << i, 0 });
            }
            while (!s.isEmpty()) {
                int[] cur = s.pollFirst();
                int nod = cur[0], state = cur[1], step = cur[2];
                if (state == END)
                    return step;
                for (int next : graph[nod]) {
                    int tmp = state | (1 << (next + 13));
                    if (!vis.contains(tmp)) {
                        vis.add(tmp);
                        int st = (state | (1 << next));
                        if (st == END)
                            return step + 1;
                        s.addLast(new int[] { next, st, step + 1 });
                    }
                }
            }
            return -1;
        }
    }

}