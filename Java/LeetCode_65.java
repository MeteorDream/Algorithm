/* 
* coding: utf-16 -*- 
* File    : LeetCode_65.java
* Author  : MeteorDream
* Time    : 2021/05/29 21:57:13
* language: Java
* Software: Visual Studio Code
* */

/* [65. 有效数字](https://leetcode-cn.com/problems/valid-number/) */

import java.util.*;

public class LeetCode_65 {
    public static void main(String[] args) {
        LeetCode_65 s = new LeetCode_65();

        String[] ss = { "+.1", ".1e-000" };

        for (String sss : ss) {
            System.out.println(s.isNumber(sss));
        }

        System.out.println(s + "Finish!");
    }

    /* // 模拟
    public boolean isNumber(String s) {
    
        char[] ss = s.toCharArray();
        int n = ss.length;
    
        // 先检测是否有 e
        int e = n;
        for (int i = 0; i < n; ++i) {
            if (ss[i] == 'e' || ss[i] == 'E') {
                if (e != n) // 两个 e 不合法
                    return false;
                else
                    e = i;
            }
        }
    
        // e 前面没东西，不合法
        if (e == 0)
            return false;
    
        // 然后检查 e 前面 是否有小数点
        int dot = e;
        for (int i = 0; i < e; ++i) {
            if (ss[i] == '.') {
                if (dot != e) // 两个小数点 不合法
                    return false;
                else
                    dot = i;
            }
        }
    
        int c = 0;
        // 没有小数点，那就是整数
        if (dot == e) {
            // 整数第一位可能是符号位
            if (ss[c] == '+' || ss[c] == '-') {
                ++c;
                // 只有一个符号位也是不行的
                if (c == dot)
                    return false;
            }
            // 剩下部分应该全是数字
            while (c < dot) {
                int tmp = ss[c++] - '0';
                if (tmp < 0 || tmp > 9)
                    return false;
            }
        }
        // 有小数点那就是小数了，范围是 [c,e)
        else {
            // 小数第一位可能是符号位
            if (ss[c] == '+' || ss[c] == '-')
                ++c;
            // 先考虑第三种情况：一个点 '.' ，后面跟着至少一位数字
            if (c == dot) {
                // 小数点后面没有数字，不合法！
                if ((c++) + 1 == e)
                    return false;
                while (c < e) {
                    int ttt = ss[c++] - '0';
                    if (ttt < 0 || ttt > 9)
                        return false;
                }
            }
            // 情况2：至少一位数字，后面跟着一个点 '.'
            // 情况3：至少一位数字，后面跟着一个点 '.' ，后面再跟着至少一位数字
            else {
                // [c, dot) 应该都是数字
                while (c < dot) {
                    int ttt = ss[c++] - '0';
                    if (ttt < 0 || ttt > 9)
                        return false;
                }
                // (dot,e) 也应该是数字
                c = dot + 1;
                while (c < e) {
                    int ttt = ss[c++] - '0';
                    if (ttt < 0 || ttt > 9)
                        return false;
                }
            }
        }
    
        // e 后面肯定是整数
        // e 是字符串最后一位，不行!
        if (++e == n)
            return false;
        // 整数可能有一位符号位
        if (e < n && (ss[e] == '+' || ss[e] == '-')) {
            // 只有一个符号位也是不行的
            if (++e == n)
                return false;
        }
        // 剩下的应该全部是数字
        while (e < n) {
            int sss = ss[e++] - '0';
            if (sss < 0 || sss > 9)
                return false;
        }
    
        return true;
    } */

    /* // DFA(有限状态自动机) */
    // 有效数字组成： (整数 | 小数) (e 指数整数)
    // 整数 = 符号 + 数字
    // 小数 = 符号 + 数字 + 小数点 + 数字 (小数点细分为前面有数字的小数点和前面没数字的小数点)
    // 
    // 0起始状态：符号、整数数字、前面无数字的小数点
    // 1符号：整数数字、前面无数字的小数点
    // 2整数数字：整数数字、前面有数字的小数点、e/E、终止态
    // 3前面无数字的小数点：小数数字
    // 4前面有数字的小数点：小数数字、e/E、终止态
    // 5小数数字：小数数字、e/E、终止态
    // 6 e/E：指数符号、指数数字
    // 7指数符号：指数数字
    // 8指数数字：指数数字、终止态
    // 9终止态：-1错误态
    class DFA {
        public int state; // 初始状态
        public Set<Integer> end = new HashSet<>(10);

        public DFA() {
            state = 0;
            end.add(2);
            end.add(4);
            end.add(5);
            end.add(8);
        }

        public boolean get_char(char s) {
            int num = s - '0';
            if (s == '+' || s == '-') {
                if (state == 0)
                    state = 1; // 符号
                else if (state == 6)
                    state = 7; // 指数符号
                else
                    return false; // 错误态
            } else if (num >= 0 && num <= 9) {
                if (state < 3)
                    state = 2; // 整数数字
                else if (state < 6)
                    state = 5; // 小数数字
                else if (state < 9)
                    state = 8; // 指数数字
                else
                    return false; // 错误态
            } else if (s == 'e' || s == 'E') {
                if (state == 2 || state == 4 || state == 5)
                    state = 6;
                else
                    return false;
            } else if (s == '.') {
                if (state < 2)
                    state = 3; // 前面无数字的小数点
                else if (state == 2)
                    state = 4; // 前面有数字的小数点
                else
                    return false;
            } else
                return false;
            return true;
        }
    }

    public boolean isNumber(String s) {
        DFA dfa = new DFA();
        char[] st = s.toCharArray();
        for (char ss : st) {
            if (!dfa.get_char(ss))
                return false;
        }
        return dfa.end.contains(dfa.state);
    }

}