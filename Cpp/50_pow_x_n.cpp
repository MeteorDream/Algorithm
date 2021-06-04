/*     -*- coding: utf-8 -*-     */
/* File    : 50_pow_x_n.cpp */
/* Author  : MeteorDream         */
/* Time    : 2021/05/29 19:14:58 */
/* language: C/C++               */
/* Software: Visual Studio Code  */

#include "LeetCode.h"

#ifdef __050__

/* 
[50. Pow(x, n)](https://leetcode-cn.com/problems/powx-n/)

难度: 中等

*/

class Solution {
public:
    /* // 暴力(估计会TLE，不测试了) 
    double myPow(double x, int n) {
        double ans = 1;
        for (int t = n >= 0 ? n : -n; t > 0; --t) {
            ans *= x;
        }
        return n > 0 ? ans : (1 / ans);
    }*/

    /* // 快速幂 */
    double myPow(double x, int n) {
        double ans = 1, s = x;
        long t = n;
        for (t = t >= 0 ? t : -t; t > 0; t >>= 1) {
            if (t & 1)
                ans *= s;
            s *= s;
        }
        return n >= 0 ? ans : 1 / ans;
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