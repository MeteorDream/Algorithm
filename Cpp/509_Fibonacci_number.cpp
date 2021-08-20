/*  -*- coding: utf-8 -*-
 * File    : 509_Fibonacci_number.cpp
 * Author  : MeteorDream
 * Time    : 2021/07/24 15:41:47
 * language: C/C++
 * Software: Visual Studio Code
*/

#include "LeetCode.h"

#ifdef __509__

/* 
[509. 斐波那契数](https://leetcode-cn.com/problems/fibonacci-number/)

难度: 简单

题解：


*/

/* 经典递归 
class Solution {
public:
    int fib(int n) {
        return n > 1 ? fib(n - 1) + fib(n - 2) : n;
    }
};*/

/* 记忆化递归 
class Solution {
public:
    int cache[32];
    int fib(int n) {
        if (n <= 1)
            return n;
        else if (cache[n] == 0)
            cache[n] = fib(n - 1) + fib(n - 2);
        return cache[n];
    }
};*/

/* 打表1 
static int cache[32];
class Solution {
public:
    int fib(int n) {
        if (n <= 1)
            return n;
        else if (cache[n] == 0)
            cache[n] = fib(n - 1) + fib(n - 2);
        return cache[n];
    }
};*/

/* 打表2 
static int cache[] = {0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233, 377, 610, 987, 1597, 2584, 4181, 6765, 10946, 17711, 28657, 46368, 75025, 121393, 196418, 317811, 514229, 832040, 1346269};
class Solution {
public:
    int fib(int n) {
        return cache[n];
    }
};*/

/* 动态规划 
class Solution {
public:
    int fib(int n) {
        int a = 0, b = 1;
        for (int i = 0; i < n; ++i) {
            b += a;
            a = b - a;
        }
        return a;
    }
};*/

/* 矩阵快速幂 */
class Solution {
public:
    int fib(int n) {
        vector<int> s{1, 0, 0, 1}, f{1, 1, 1, 0};
        auto matrix = [&](const vector<int>& a, const vector<int>& b) -> vector<int> {
            return {a[0] * b[0] + a[1] * b[2], a[0] * b[1] + a[1] * b[3], a[2] * b[0] + a[3] * b[2], a[2] * b[1] + a[3] * b[3]};
        };
        for (; n != 0; n >>= 1) {
            if (n & 1) s = matrix(s, f);
            f = matrix(f, f);
        }
        return s[2];
    }
};

int Submit() {
    Solution s;

    /* 输入 */
    cout << "输入:" << endl;

    /* 输出 */
    cout << "输出:" << endl;

    return 0;
}

#endif