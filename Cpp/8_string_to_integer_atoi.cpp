/*     -*- coding: utf-8 -*-     */
/* File    : 8_string_to_integer_atoi.cpp */
/* Author  : MeteorDream         */
/* Time    : 2021/05/31 22:12:39 */
/* language: C/C++               */
/* Software: Visual Studio Code  */

#include "LeetCode.h"

#ifdef __008__

/* 
[8. 字符串转换整数 (atoi)](https://leetcode-cn.com/problems/string-to-integer-atoi/)

难度: 中等
*/

/* // 模拟 
class Solution {
public:
    int myAtoi(string s) {
        // 使用 long 避免溢出
        // 如果禁止用 long 则反向判断(ans * 10 + n < Int_MAX => ans < (Int_Max - n) / 10 )
        long ans = 0;
        int i = 0, n = s.size();
        //  去除前导0
        while (i < n && s[i] == ' ')
            ++i;
        // 设置符号位
        int zf = 1;
        if (i < n && s[i] == '+')
            ++i;
        else if (i < n && s[i] == '-') {
            ++i;
            zf = -1;
        }
        while (i < n) {
            // 判断是否是数字
            int tmp = s[i++] - '0';
            if (tmp >= 0 && tmp <= 9)
                ans = ans * 10 + zf * tmp;
            else
                break;
            // 检查是否溢出
            if (ans > 2147483647) {
                return 2147483647;
            }
            else if (ans < -2147483648)
                return -2147483648;
        }
        return (int)ans;
    }
};*/

/* DFA(优先状态自动机) */
class DFA {
public:
    DFA() {
        cur = "start";
        ans = 0;
        sign = 1;
        trans.emplace("start", vector<string>{"space", "sign", "number"});
        trans.emplace("space", vector<string>{"space", "sign", "number"});
        trans.emplace("sign", vector<string>{"number"});
        trans.emplace("number", vector<string>{"number"});
    }

    bool get_char(char s) {
        // 输入一个字符串，如转移到最终状态则返回 false
        string next;
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
        bool tag = false;    // 标记是否转移成功
        for (string r : trans[cur])
            if (r == next)
                tag = true;
        if (!tag)    // 转移失败，进入最终状态
            return false;
        cur = next;
        if (s == '-')
            sign = -1;
        else if (num >= 0 && num <= 9) {
            ans = ans * 10 + sign * num;
            if (ans > 2147483647) {
                ans = 2147483647;
                return false;
            }
            else if (ans < -2147483648) {
                ans = -2147483648;
                return false;
            }
        }
        return true;
    }

    int get_answer() {
        return (int)ans;
    }

private:
    string cur;    // 当前状态
    unordered_map<string, vector<string>> trans;
    long ans;
    int sign;
};

class Solution {
public:
    int myAtoi(string s) {
        DFA dfs;
        for (char ss : s)
            if (!dfs.get_char(ss))
                return dfs.get_answer();
        return dfs.get_answer();
    }
};

int Submit() {
    Solution s;

    /* 输入 */
    cout << "输入:" << endl;

    /* 输出 */
    cout << "输出:" << endl;
    cout << s.myAtoi("   -42") << endl;

    return 0;
}

#endif