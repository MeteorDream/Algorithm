/* 
* coding: utf-16 -*- 
* File    : LeetCode_752.java
* Author  : MeteorDream
* Time    : 2021/06/25 15:18:41
* language: Java
* Software: Visual Studio Code
* */

/**
 *[752. 打开转盘锁](https://leetcode-cn.com/problems/open-the-lock/)
 * 
 * 难度: 中等
 * */

import java.util.*;

public class LeetCode_752 {
    public static void main(String[] args) {
        LeetCode_752 s = new LeetCode_752();

        System.out.println(s + "Finish!");
    }

    /* 朴素bfs */
    public int openLock(String[] deadends, String target) {
        if (target == "0000")
            return 0;
        Set<String> dead = new HashSet<>();
        for (String s : deadends)
            dead.add(s);
        if (dead.contains("0000"))
            return -1;
        Deque<String> d = new ArrayDeque<>();
        Deque<Integer> t = new ArrayDeque<>();
        d.add("0000");
        t.add(1);
        while (!d.isEmpty()) {
            char[] cur = d.pollFirst().toCharArray();
            int tim = t.pollFirst();
            for (int i = 0; i < 4; ++i) {
                int num = cur[i] - '0';
                for (int j = -1; j != 3; j += 2) {
                    num = (num + j) % 10 + '0';
                    if (num == -1)
                        num = 9;
                    char[] next = cur.clone();
                    next[i] = (char) num;
                    String s = String.valueOf(next);
                    if (!dead.contains(s)) {
                        if (s == target)
                            return tim + 1;
                        dead.add(s);
                        d.add(s);
                        t.add(tim + 1);
                    }
                }
            }
        }
        return -1;
    }
}