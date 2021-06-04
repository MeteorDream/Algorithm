/*     -*- coding: utf-8 -*-     */
/* File    : 343_integer_break.cpp */
/* Author  : MeteorDream         */
/* Time    : 2021/05/28 21:54:48 */
/* language: C/C++               */
/* Software: Visual Studio Code  */

#include "LeetCode.h"

#ifdef __343__

/* 
[343. 整数拆分](https://leetcode-cn.com/problems/integer-break/)

难度: 中等
*/

class Solution {
public:
    int integerBreak(int n) {
        // 根据数学推导，尽量拆分成3
        if (n <= 3) {
            return n - 1;
        }
        int a = n / 3;
        int b = n % 3;
        if (b == 0) {
            return (int)pow(3, a);
        }
        else if (b == 1) {
            return (int)pow(3, a - 1) * 4;
        }
        else {
            return (int)pow(3, a) * 2;
        }
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