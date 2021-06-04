/* 
* coding: utf-16 -*- 
* File    : LeetCode_8.java
* Author  : MeteorDream
* Time    : 2021/05/31 22:59:07
* language: Java
* Software: Visual Studio Code
* */

/* [8. 字符串转换整数 (atoi)](https://leetcode-cn.com/problems/string-to-integer-atoi/) */

import java.util.*;

public class LeetCode_8 {
    public static void main(String[] args) {
        LeetCode_8 s = new LeetCode_8();

        s.myAtoi("+-12");

        System.out.println(s + "Finish!");
    }

    /* // 模拟 
    public int myAtoi(String s) {
        long ans = 0;
        char[] ss = s.toCharArray();
        int i = 0, n = s.length();
        while (i < n && ss[i] == ' ')
            ++i;
        int zf = 1;
        if (i < n && ss[i] == '+')
            ++i;
        else if (i < n && ss[i] == '-') {
            ++i;
            zf = -1;
        }
        while (i < n) {
            int tmp = ss[i++] - '0';
            if (tmp >= 0 && tmp <= 9)
                ans = ans * 10 + zf * tmp;
            else
                break;
            if (ans > 2147483647) {
                return 2147483647;
            } else if (ans < -2147483648)
                return -2147483648;
        }
        return (int) ans;
    }*/

    // DFA(确定优先状态自动机)
    // 状态    |  转移状态
    // 初始状态 |  空格、正负号、数字0-9
    // 空格    |   空格、正负号、数字0-9
    // 正负号   |  数字0-9
    // 数字    |   数字0-9
    class DFA {
        private String cur; // 当前状态
        private HashMap<String, String[]> trans = new HashMap<>(10);
        private long ans;
        private int sign;

        public DFA() {
            cur = "start";
            ans = 0;
            sign = 1;
            trans.put("start", new String[] { "space", "sign", "number" });
            trans.put("space", new String[] { "space", "sign", "number" });
            trans.put("sign", new String[] { "number" });
            trans.put("number", new String[] { "number" });
        }

        public boolean get_char(char s) {
            // 输入一个字符串，如转移到最终状态则返回 false
            String next = new String();
            int num = s - '0';
            if (s == ' ')
                next = "space";
            else if (s == '+')
                next = "sign";
            else if (s == '-')
                next = "sign";
            else if (num >= 0 && num <= 9)
                next = "number";
            else
                next = "end";
            // 转移到最终状态，返回
            if (next == "end")
                return false;
            boolean tag = false; // 标记是否转移成功
            for (String r : trans.get(cur))
                if (r == next)
                    tag = true;
            if (!tag) // 转移失败，进入最终状态
                return false;
            cur = next;
            if (s == '-')
                sign = -1;
            else if (num >= 0 && num <= 9) {
                ans = ans * 10 + sign * num;
                if (ans > Integer.MAX_VALUE) {
                    ans = Integer.MAX_VALUE;
                    return false;
                } else if (ans < Integer.MIN_VALUE) {
                    ans = Integer.MIN_VALUE;
                    return false;
                }
            }
            return true;
        }

        public int get_ans() {
            // 返回答案
            return (int) ans;
        }
    }

    public int myAtoi(String s) {
        DFA dfa = new DFA();
        char[] ss = s.toCharArray();
        for (char sss : ss) {
            if (!dfa.get_char(sss))
                return dfa.get_ans();
        }
        return dfa.get_ans();
    }
}