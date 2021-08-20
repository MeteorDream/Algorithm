/*     -*- coding: utf-8 -*-     */
/* File    : 483_Smallest_good_base.cpp */
/* Author  : MeteorDream         */
/* Time    : 2021/06/18 15:12:57 */
/* language: C/C++               */
/* Software: Visual Studio Code  */

#include "LeetCode.h"

#ifdef __483__

/* 
[483. 最小好进制](https://leetcode-cn.com/problems/smallest-good-base/)

难度: 困难


*/

/* 二分法
class Solution {
public:
    string smallestGoodBase(string n) {
        long num = stol(n);
        // 枚举 k进制 中 1 的个数，最多为 二进制 时的位数
        for (int i = (int)(log(num) / log(2) + 1); i > 2; --i) {
            // k^0 + k^1 + …… + k^(i-1) = n -- 通过二分法计算 k
            long left = 2, right = num - 1;
            while (left <= right) {
                long mid = left + (right - left) / 2;
                // MaxVal 用于反向溢出判断，一旦溢出，说明比num大，设为num+1即可
                long s = 0, MaxVal = num / mid + 1;
                for (int j = 0; j < i; ++j) {
                    if (s < MaxVal)
                        s = s * mid + 1;
                    else {
                        s = num + 1;
                        break;
                    }
                }
                if (s == num)
                    return to_string(mid);
                else if (s > num)
                    right = mid - 1;
                else
                    left = mid + 1;
            }
        }
        return to_string(num - 1);
    }
}; */

/* 数学方法 */
class Solution {
public:
    string smallestGoodBase(string n) {
        long num = stol(n);
        // 枚举 k进制 中 1 的个数，最多为 二进制 时的位数
        for (int i = (int)(log(num) / log(2) + 1); i > 2; --i) {
            // k^0 + k^1 + …… + k^(i-1) = n -- 数学方法解方程计算 k
            long k = powl(num, 1.0 / (i - 1));
            // 检查 k 进制数 (11…11) (i个1)是否是n
            long res = 0;
            for (int j = 0; j < i; ++j)
                res = res * k + 1;
            if (res == num)
                return to_string(k);
        }
        return to_string(num - 1);
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