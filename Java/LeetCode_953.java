/* 
* coding: utf-16 -*- 
* File    : 953.java
* Author  : MeteorDream
* Time    : 2022/05/17 17:49:48
* language: Java
* Software: Visual Studio Code
* */

/**
* [953. 验证外星语词典](https://leetcode.cn/problems/verifying-an-alien-dictionary/)
* 
* 难度: 简单
* 
* 题解：[【验证外星语词典】简单模拟](https://leetcode.cn/problems/verifying-an-alien-dictionary/solution/yan-zheng-wai-xing-yu-ci-dian-by-meteord-xewi/)
 * */

import java.util.*;

public class LeetCode_953 {
    public static void main(String[] args) {
        LeetCode_953 LC = new LeetCode_953();

        Solution ss = LC.new Solution();

        System.out.println(LC + "Finish!");
        System.out.println(ss + "Finish!");
    }

    class Solution {
        public boolean isAlienSorted(String[] words, String order) {
            Map<Character, Integer> ord_map = new HashMap<>();
            for (int i = 0; i < 26; ++i)
                ord_map.put(order.charAt(i), i);
            String pre = "";
            for (String cur : words) {
                boolean tag = true;
                int n = Math.min(cur.length(), pre.length());
                for (int i = 0; i < n; ++i) {
                    if (cur.charAt(i) != pre.charAt(i)) {
                        if (ord_map.get(cur.charAt(i)) < ord_map.get(pre.charAt(i)))
                            return false;
                        else {
                            tag = false;
                            break;
                        }
                    }
                }
                if (tag && cur.length() < pre.length())
                    return false;
                pre = cur;
            }
            return true;
        }
    }
}