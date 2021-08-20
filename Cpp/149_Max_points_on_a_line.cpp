/*     -*- coding: utf-8 -*-     */
/* File    : 149_Max_points_on_a_line.cpp */
/* Author  : MeteorDream         */
/* Time    : 2021/06/24 17:26:34 */
/* language: C/C++               */
/* Software: Visual Studio Code  */

#include "LeetCode.h"

#ifdef __149__

/* 
[149. 直线上最多的点数](https://leetcode-cn.com/problems/max-points-on-a-line/)

难度: 困难

*/

/* 暴力解法 
class Solution {
public:
    int maxPoints(vector<vector<int>>& points) {
        int n = points.size(), ans = 1;
        for (int i = 0; i < n - 1; ++i) {
            int x1 = points[i][0], y1 = points[i][1];
            for (int j = i + 1; j < n; ++j) {
                int cnt = 0, x2 = points[j][0], y2 = points[j][1];
                if (x1 == x2) {
                    for (int k = 0; k < n; ++k)
                        if (points[k][0] == x2)
                            ++cnt;
                }
                else {
                    int k1 = y2 - y1, k2 = x2 - x1;    // 斜率的分数形式
                    int b = y2 * k2 - x2 * k1;         // 截距与斜率通分，只记录分子就行
                    for (int k = 0; k < n; ++k)
                        if (points[k][1] * k2 == k1 * points[k][0] + b)
                            ++cnt;
                }
                if (cnt > ans)
                    ans = cnt;
            }
        }
        return ans;
    }
};*/

/* 哈希优化 */
class Solution {
public:
    int maxPoints(vector<vector<int>>& points) {
        int n = points.size(), ans = 0;
        for (int i = 0; i < n - 1; ++i) {
            int x1 = points[i][0], y1 = points[i][1], cnt = 0;
            unordered_map<string, int> h;
            for (int j = i + 1; j < n; ++j) {
                int x2 = points[j][0] - x1, y2 = points[j][1] - y1;
                string k;
                if (x2 == 0)
                    k = "inf";
                else {
                    int s = gcd(x2, y2);    // 斜率的分数形式
                    k = to_string(x2 / s) + "_" + to_string(y2 / s);
                }
                ++h[k];
                if (h[k] > ans)
                    ans = h[k];
            }
        }
        return ans + 1;
    }

    int gcd(int x, int y) {
        return y == 0 ? x : gcd(y, x % y);
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