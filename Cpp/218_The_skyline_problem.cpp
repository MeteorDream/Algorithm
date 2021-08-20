/*  -*- coding: utf-8 -*-
 * File    : 218_The_skyline_problem.cpp
 * Author  : MeteorDream
 * Time    : 2021/07/13 18:36:01
 * language: C/C++
 * Software: Visual Studio Code
*/

#include "LeetCode.h"

#ifdef __218__

/* 
[218. 天际线问题](https://leetcode-cn.com/problems/the-skyline-problem/)

难度: 困难

题解：https://leetcode-cn.com/problems/the-skyline-problem/solution/tian-ji-xian-wen-ti-shun-xu-sao-miao-ji-zj0ox/


*/
class comp {
public:
    bool operator()(const pair<int, int>& a, const pair<int, int>& b) {
        if (a.first == b.first)
            return a.second > b.second;
        else
            return a.first < b.first;
    }
};

class Solution {
public:
    vector<vector<int>> getSkyline(vector<vector<int>>& buildings) {
        priority_queue<pair<int, int>, vector<pair<int, int>>, comp> s;
        vector<vector<int>> ans;
        int cur = 0;
        for (auto& b : buildings) {
            while (!s.empty() && s.top().second < b[0]) {
                pair<int, int> r = s.top();
                s.pop();
                if (r.second >= cur) {
                    if (s.empty() || r.first != s.top().first) {
                        while (!s.empty() && r.second > s.top().second)
                            s.pop();
                        r.first = s.empty() ? 0 : s.top().first;
                        // 避免右端点重复
                        if (r.second == ans[ans.size() - 1][0])
                            ans[ans.size() - 1][1] = min(ans[ans.size() - 1][1], r.first);
                        else
                            ans.emplace_back(vector<int>{r.second, r.first});
                    }
                    cur = r.second;
                }
            }
            if (s.empty() || b[2] > s.top().first) {
                // 避免左端点重复的问题
                if (!ans.empty() && b[0] == ans[ans.size() - 1][0])
                    ans[ans.size() - 1][1] = b[2];
                else
                    ans.emplace_back(vector<int>{b[0], b[2]});
            }
            s.emplace(pair<int, int>{b[2], b[1]});
        }
        while (!s.empty()) {
            pair<int, int> r = s.top();
            s.pop();
            if (r.second >= cur) {
                if (s.empty() || r.first != s.top().first) {
                    while (!s.empty() && r.second > s.top().second)
                        s.pop();
                    r.first = s.empty() ? 0 : s.top().first;
                    // 避免右端点重复
                    if (r.second == ans[ans.size() - 1][0])
                        ans[ans.size() - 1][1] = min(ans[ans.size() - 1][1], r.first);
                    else
                        ans.emplace_back(vector<int>{r.second, r.first});
                }
                cur = r.second;
            }
        }
        return ans;
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