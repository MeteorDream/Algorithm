/* 
* coding: utf-16 -*- 
* File    : LeetCode_218.java
* Author  : MeteorDream
* Time    : 2021/07/13 19:51:05
* language: Java
* Software: Visual Studio Code
* */

/**
 *[218. 天际线问题](https://leetcode-cn.com/problems/the-skyline-problem/)
 * 
 * 难度: 困难

 * 题解：https://leetcode-cn.com/problems/the-skyline-problem/solution/tian-ji-xian-wen-ti-shun-xu-sao-miao-ji-zj0ox/
 * */

import java.util.*;

public class LeetCode_218 {
    public static void main(String[] args) {
        LeetCode_218 s = new LeetCode_218();

        System.out.println(s + "Finish!");
    }

    public List<List<Integer>> getSkyline(int[][] buildings) {
        List<List<Integer>> ans = new ArrayList<>();
        PriorityQueue<int[]> s = new PriorityQueue<>(new Comparator<int[]>() {
            @Override
            public int compare(int[] a, int[] b) {
                if (a[0] == b[0])
                    return a[1] - b[1];
                else
                    return b[0] - a[0];
            }
        });
        int cur = 0;
        for (int[] b : buildings) {
            while (!s.isEmpty() && s.peek()[1] < b[0]) {
                int[] r = s.poll();
                if (r[1] >= cur) {
                    if (s.isEmpty() || r[0] != s.peek()[0]) {
                        while (!s.isEmpty() && r[1] > s.peek()[1])
                            s.poll();
                        r[0] = s.isEmpty() ? 0 : s.peek()[0];
                        // 避免右端点重复
                        if (r[1] == ans.get(ans.size() - 1).get(0))
                            ans.get(ans.size() - 1).set(1, Math.min(ans.get(ans.size() - 1).get(1), r[0]));
                        else {
                            List<Integer> tmp = new ArrayList<>(2);
                            tmp.add(r[1]);
                            tmp.add(r[0]);
                            ans.add(tmp);
                        }
                    }
                    cur = r[1];
                }
            }
            if (s.isEmpty() || b[2] > s.peek()[0]) {
                // 避免左端点重复的问题
                if (!ans.isEmpty() && b[0] == ans.get(ans.size() - 1).get(0))
                    ans.get(ans.size() - 1).set(1, b[2]);
                else {
                    List<Integer> tmp = new ArrayList<>(2);
                    tmp.add(b[0]);
                    tmp.add(b[2]);
                    ans.add(tmp);
                }
            }
            s.add(new int[] { b[2], b[1] });
        }
        while (!s.isEmpty()) {
            int[] r = s.poll();
            if (r[1] >= cur) {
                if (s.isEmpty() || r[0] != s.peek()[0]) {
                    while (!s.isEmpty() && r[1] > s.peek()[1])
                        s.poll();
                    r[0] = s.isEmpty() ? 0 : s.peek()[0];
                    // 避免右端点重复
                    if (r[1] == ans.get(ans.size() - 1).get(0))
                        ans.get(ans.size() - 1).set(1, Math.min(ans.get(ans.size() - 1).get(1), r[0]));
                    else {
                        List<Integer> tmp = new ArrayList<>(2);
                        tmp.add(r[1]);
                        tmp.add(r[0]);
                        ans.add(tmp);
                    }
                }
                cur = r[1];
            }
        }
        return ans;
    }
}