/*     -*- coding: utf-8 -*-     */
/* File    : 374_guess_number_higher_or_lower.cpp */
/* Author  : MeteorDream         */
/* Time    : 2021/06/14 15:45:52 */
/* language: C/C++               */
/* Software: Visual Studio Code  */

#include "LeetCode.h"

#ifdef __374__

/* 
[374. 猜数字大小](https://leetcode-cn.com/problems/guess-number-higher-or-lower/)

难度: 简单

*/

class Solution {
public:
    // 简单基础的二分
    int guessNumber(int n) {
        int left = 1, right = n;
        while (left < right) {
            int mid = left + (right - left) / 2;
            int ans = guess(mid);
            if (ans == 0)
                return mid;
            else if (ans == -1)
                right = mid - 1;
            else
                left = mid + 1;
        }
        return left;
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