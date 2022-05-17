/*  -*- coding: utf-8 -*-
 * File    : 953.cpp
 * Author  : MeteorDream
 * Time    : 2022/05/17 17:48:06
 * language: C/C++
 * Software: Visual Studio Code
 */

#include "LeetCode.h"

#ifdef __953__

/*
[953. 验证外星语词典](https://leetcode.cn/problems/verifying-an-alien-dictionary/)

难度: 简单

题解：[【验证外星语词典】简单模拟](https://leetcode.cn/problems/verifying-an-alien-dictionary/solution/yan-zheng-wai-xing-yu-ci-dian-by-meteord-xewi/)


*/

class Solution
{
public:
    bool isAlienSorted(vector<string> &words, string order)
    {
        unordered_map<char, int> ord_map;
        for (int i = 0; i < 26; ++i)
            ord_map[order[i]] = i;
        string pre = "";
        for (string &cur : words)
        {
            bool tag = true;
            int n = min(cur.size(), pre.size());
            for (int i = 0; i < n; ++i)
            {
                if (cur[i] != pre[i])
                {
                    if (ord_map[cur[i]] < ord_map[pre[i]])
                        return false;
                    else
                    {
                        tag = false;
                        break;
                    }
                }
            }
            if (tag && cur.size() < pre.size())
                return false;
            pre = cur;
        }
        return true;
    }
};

int Submit()
{
    Solution s;

    /* 输入 */
    cout << "输入:" << endl;

    /* 输出 */
    cout << "输出:" << endl;

    return 0;
}

#endif