/* 
* coding: utf-16 -*- 
* File    : LeetCode_743.java
* Author  : MeteorDream
* Time    : 2021/07/21 10:40:32
* language: Java
* Software: Visual Studio Code
* */

/**
 *[743. 网络延迟时间](https://leetcode-cn.com/problems/network-delay-time/)
 * 
 * 难度: 中等

 * 题解：https://leetcode-cn.com/problems/network-delay-time/solution/wang-luo-yan-chi-shi-jian-dan-yuan-zui-d-m1m3/
 * */

import java.util.*;

public class LeetCode_743 {
    public static void main(String[] args) {
        LeetCode_743 s = new LeetCode_743();

        int[][] g = new int[][] { { 2, 1, 1 }, { 2, 3, 1 }, { 3, 4, 1 } };
        int n = 4, k = 2;
        // System.out.println(s.networkDelayTime(g, n, k));

        g = new int[][] { { 1, 2, 1 }, { 2, 1, 3 } };
        n = 2;
        k = 2;
        System.out.println(s.networkDelayTime(g, n, k));

        System.out.println(s + " Finish!");
    }

    static int INTMAX = 0x3f3f3f3f;

    /* DFS 
    Map<Integer, Map<Integer, Integer>> mp;
    int[] r;
    
    private void dfs(int i, int t) {
        // 在 t 时间到达 i 结点
        if (t < r[i]) {
            r[i] = t;
            if (mp.containsKey(i))
                for (int v : mp.get(i).keySet())
                    dfs(v, t + mp.get(i).get(v));
        }
    }
    
    public int networkDelayTime(int[][] times, int n, int k) {
        // 建图 - 邻接表
        mp = new HashMap<>();
        for (int[] edg : times) {
            if (!mp.containsKey(edg[0]))
                mp.put(edg[0], new HashMap<>());
            mp.get(edg[0]).put(edg[1], edg[2]);
        }
        // 记录结点最早收到信号的时间 
        r = new int[n + 1];
        for (int i = 1; i <= n; ++i)
            r[i] = INTMAX;
    
        dfs(k, 0);
    
        int minT = -1;
        for (int i = 1; i <= n; ++i)
            minT = Math.max(minT, r[i]);
        return minT == INTMAX ? -1 : minT;
    }*/

    /* BFS 
    public int networkDelayTime(int[][] times, int n, int k) {
        // 建图 - 邻接表
        Map<Integer, Map<Integer, Integer>> mp = new HashMap<>();
        for (int[] edg : times) {
            if (!mp.containsKey(edg[0]))
                mp.put(edg[0], new HashMap<>());
            mp.get(edg[0]).put(edg[1], edg[2]);
        }
        // 记录结点最早收到信号的时间 
        int[] r = new int[n + 1];
        for (int i = 1; i <= n; ++i)
            r[i] = INTMAX;
        r[k] = 0;
    
        // 队列中存放 [结点，收到信号时间]
        Deque<int[]> s = new ArrayDeque<>();
        s.addLast(new int[] { k, 0 });
    
        while (!s.isEmpty()) {
            int[] cur = s.pollFirst();
            if (mp.containsKey(cur[0])) {
                for (int v : mp.get(cur[0]).keySet()) {
                    int t = mp.get(cur[0]).get(v) + cur[1];
                    if (t < r[v]) {
                        r[v] = t;
                        s.addLast(new int[] { v, t });
                    }
                }
            }
        }
    
        int minT = -1;
        for (int i = 1; i <= n; ++i)
            minT = Math.max(minT, r[i]);
        return minT == INTMAX ? -1 : minT;
    }*/

    /* Dijkstra 
    public int networkDelayTime(int[][] times, int n, int k) {
        // 建图 - 邻接表
        Map<Integer, Map<Integer, Integer>> mp = new HashMap<>();
        for (int[] edg : times) {
            if (!mp.containsKey(edg[0]))
                mp.put(edg[0], new HashMap<>());
            mp.get(edg[0]).put(edg[1], edg[2]);
        }
        // 记录结点最早收到信号的时间 
        int[] r = new int[n + 1];
        for (int i = 1; i <= n; ++i)
            r[i] = INTMAX;
        r[k] = 0;
    
        // 记录已经找到最短路的结点
        Set<Integer> s = new HashSet<>();
    
        while (true) {
            // 待查集中查找最近结点
            int cur = -1, tim = INTMAX;
            for (int i = 1; i <= n; ++i) {
                if (r[i] < tim && !s.contains(i)) {
                    cur = i;
                    tim = r[i];
                }
            }
            if (cur == -1)
                break;
    
            // 将最近结点加入已查集合并更新
            s.add(cur);
            if (mp.containsKey(cur)) {
                for (int v : mp.get(cur).keySet()) {
                    r[v] = Math.min(r[v], mp.get(cur).get(v) + tim);
                }
            }
        }
    
        int minT = -1;
        for (int i = 1; i <= n; ++i)
            minT = Math.max(minT, r[i]);
        return minT == INTMAX ? -1 : minT;
    }*/

    /* Dijkstra优先队列优化 
    public int networkDelayTime(int[][] times, int n, int k) {
        // 建图 - 邻接表
        Map<Integer, Map<Integer, Integer>> mp = new HashMap<>();
        for (int[] edg : times) {
            if (!mp.containsKey(edg[0]))
                mp.put(edg[0], new HashMap<>());
            mp.get(edg[0]).put(edg[1], edg[2]);
        }
        // 记录结点最早收到信号的时间 
        int[] r = new int[n + 1];
        for (int i = 1; i <= n; ++i)
            r[i] = INTMAX;
    
        // 队列中存放 [结点，收到信号时间]
        PriorityQueue<int[]> s = new PriorityQueue<>((a, b) -> a[1] - b[1]);
        s.add(new int[] { k, 0 });
    
        while (!s.isEmpty()) {
            int[] cur = s.poll();
            if (r[cur[0]] != INTMAX)
                continue;
            r[cur[0]] = cur[1];
            if (mp.containsKey(cur[0])) {
                for (int v : mp.get(cur[0]).keySet()) {
                    // 仅当结点未收到才更新并入队
                    s.add(new int[] { v, mp.get(cur[0]).get(v) + cur[1] });
                }
            }
        }
    
        int minT = -1;
        for (int i = 1; i <= n; ++i)
            minT = Math.max(minT, r[i]);
        return minT == INTMAX ? -1 : minT;
    }*/

    /* 朴素 BF 
    public int networkDelayTime(int[][] times, int n, int k) {
        // 记录结点最早收到信号的时间 
        int[] r = new int[n + 1];
        for (int i = 1; i <= n; ++i)
            r[i] = INTMAX;
        r[k] = 0;
    
        // n - 1 次松弛操作
        for (int i = 1; i < n; ++i) {
            boolean t = false;
            for (int[] edg : times) {
                if (r[edg[1]] > r[edg[0]] + edg[2]) {
                    r[edg[1]] = r[edg[0]] + edg[2];
                    t = true;
                }
            }
            if (!t)
                break;
        }
    
        int minT = -1;
        for (int i = 1; i <= n; ++i)
            minT = Math.max(minT, r[i]);
        return minT == INTMAX ? -1 : minT;
    }*/

    /* SPFA */
    public int networkDelayTime(int[][] times, int n, int k) {
        // 建图 - 邻接表
        Map<Integer, Map<Integer, Integer>> mp = new HashMap<>();
        for (int[] edg : times) {
            if (!mp.containsKey(edg[0]))
                mp.put(edg[0], new HashMap<>());
            mp.get(edg[0]).put(edg[1], edg[2]);
        }
        // 记录结点最早收到信号的时间 
        int[] r = new int[n + 1];
        for (int i = 1; i <= n; ++i)
            r[i] = INTMAX;
        r[k] = 0;

        Set<Integer> s = new HashSet<>();
        Deque<Integer> d = new ArrayDeque<>();
        s.add(k);
        d.add(k);

        while (!d.isEmpty()) {
            int cur = d.pollFirst();
            s.remove(cur);
            if (mp.containsKey(cur)) {
                for (int v : mp.get(cur).keySet()) {
                    int tim = r[cur] + mp.get(cur).get(v);
                    if (r[v] > tim) {
                        r[v] = tim;
                        if (!s.contains(v)) {
                            s.add(v);
                            d.addLast(v);
                        }
                    }
                }
            }
        }

        int minT = -1;
        for (int i = 1; i <= n; ++i)
            minT = Math.max(minT, r[i]);
        return minT == INTMAX ? -1 : minT;
    }

    /* Floyd 
    public int networkDelayTime(int[][] times, int n, int k) {
        // 建图 - 邻接矩阵
        int[][] g = new int[n + 1][n + 1];
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= n; ++j)
                g[i][j] = INTMAX;
        for (int[] edg : times)
            g[edg[0]][edg[1]] = edg[2];
        for (int i = 1; i <= n; ++i)
            g[i][i] = 0;
    
        for (int s = 1; s <= n; ++s) {
            for (int i = 1; i <= n; ++i) {
                for (int j = 1; j <= n; ++j) {
                    g[i][j] = Math.min(g[i][j], g[i][s] + g[s][j]);
                }
            }
        }
    
        int minT = -1;
        for (int i = 1; i <= n; ++i)
            minT = Math.max(minT, g[k][i]);
        return minT == INTMAX ? -1 : minT;
    }*/

}