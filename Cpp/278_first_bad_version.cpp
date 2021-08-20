/*     -*- coding: utf-8 -*-     */
/* File    : 278_first_bad_version.cpp */
/* Author  : MeteorDream         */
/* Time    : 2021/06/13 10:11:24 */
/* language: C/C++               */
/* Software: Visual Studio Code  */

#include "LeetCode.h"

#ifdef __278__

/* 
278. 第一个错误的版本

难度: 简单
*/

// The API isBadVersion is defined for you.
// 随手写的API，只是为了语法检查不报错
bool isBadVersion(int version) {
    return true;
}

/* // 简单手动二分*/
class Solution {
public:
    int firstBadVersion(int n) {
        int left = 1, right = n;
        //查找第一个 isBadVision(i) 值为 true 的值 i
        while (left < right) {
            int mid = left + (right - left) / 2;
            if (isBadVersion(mid))
                right = mid;
            else
                left = mid + 1;
        }
        return right;
    }
};

int Submit() {
    Solution s;

    /* 输入 */
    cout << "输入:" << endl;

    /* 输出 */
    cout << "输出:" << endl;
    cout << s.firstBadVersion(10) << endl;

    return 0;
}

#endif