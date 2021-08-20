/*  -*- coding: utf-8 -*-
 * File    : 743_Network_delay_time.cpp
 * Author  : MeteorDream
 * Time    : 2021/07/21 14:19:58
 * language: C/C++
 * Software: Visual Studio Code
*/

#include "LeetCode.h"

#ifdef __743__

/* 
[743. 网络延迟时间](https://leetcode-cn.com/problems/network-delay-time/)

难度: 中等

题解：https://leetcode-cn.com/problems/network-delay-time/solution/wang-luo-yan-chi-shi-jian-dan-yuan-zui-d-m1m3/


*/

#    define MAXVALUE 0x3f3f3f3f

/* DFS 
class Solution {
public:
    vector<unordered_map<int, int>> mp;
    int networkDelayTime(vector<vector<int>>& times, int n, int k) {
        // 建图 - 邻接表
        mp.resize(n + 1);
        for (auto& edg : times) {
            mp[edg[0]][edg[1]] = edg[2];
        }
        // 记录结点最早收到信号的时间
        vector<int> r(n + 1, MAXVALUE);

        dfs(r, k, 0);

        int minT = -1;
        for (int i = 1; i <= n; ++i)
            minT = max(minT, r[i]);
        return minT == MAXVALUE ? -1 : minT;
    }

    void dfs(vector<int>& r, int i, int t) {
        if (r[i] > t) {
            r[i] = t;
            for (auto& cur : mp[i]) {
                dfs(r, cur.first, cur.second + t);
            }
        }
    }
};*/

/* BFS 
class Solution {
public:
    vector<unordered_map<int, int>> mp;
    int networkDelayTime(vector<vector<int>>& times, int n, int k) {
        // 建图 - 邻接表
        mp.resize(n + 1);
        for (auto& edg : times) {
            mp[edg[0]][edg[1]] = edg[2];
        }
        // 记录结点最早收到信号的时间
        vector<int> r(n + 1, MAXVALUE);
        r[k] = 0;
        // 队列中存放 [结点，收到信号时间]
        queue<pair<int, int>> s;
        s.emplace(pair(k, 0));

        while (!s.empty()) {
            auto& cur = s.front();
            for (auto& edg : mp[cur.first]) {
                int tim = edg.second + cur.second;
                // 仅当结点收到时间比记录时间更早才更新并入队
                if (tim < r[edg.first]) {
                    r[edg.first] = tim;
                    s.emplace(pair(edg.first, tim));
                }
            }
            s.pop();
        }

        int minT = -1;
        for (int i = 1; i <= n; ++i)
            minT = max(minT, r[i]);
        return minT == MAXVALUE ? -1 : minT;
    }
};*/

/* Dijkstra 
class Solution {
public:
    vector<unordered_map<int, int>> mp;
    int networkDelayTime(vector<vector<int>>& times, int n, int k) {
        // 建图 - 邻接表
        mp.resize(n + 1);
        for (auto& edg : times) {
            mp[edg[0]][edg[1]] = edg[2];
        }
        // 记录结点最早收到信号的时间
        vector<int> r(n + 1, MAXVALUE);
        r[k] = 0;

        // 记录已经找到最短路的结点
        unordered_set<int> s;

        while (true) {
            // 待查集中查找最近结点
            int cur = -1, tim = MAXVALUE;
            for (int i = 1; i <= n; ++i) {
                if (r[i] < tim && s.find(i) == s.end()) {
                    cur = i;
                    tim = r[i];
                }
            }

            if (cur == -1) break;

            // 将最近结点加入已查集合并更新
            s.emplace(cur);
            for (auto& edg : mp[cur]) {
                r[edg.first] = min(r[edg.first], edg.second + tim);
            }
        }

        int minT = -1;
        for (int i = 1; i <= n; ++i)
            minT = max(minT, r[i]);
        return minT == MAXVALUE ? -1 : minT;
    }
};*/

/* Dijkstra 堆优化 
class Solution {
public:
    vector<unordered_map<int, int>> mp;
    int networkDelayTime(vector<vector<int>>& times, int n, int k) {
        // 建图 - 邻接表
        mp.resize(n + 1);
        for (auto& edg : times) {
            mp[edg[0]][edg[1]] = edg[2];
        }
        // 记录结点最早收到信号的时间
        vector<int> r(n + 1, MAXVALUE);

        // 优先队列中存放 [收到信号时间，结点]
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> s;
        s.emplace(pair(0, k));

        while (!s.empty()) {
            auto cur = s.top();
            s.pop();
            if (r[cur.second] != MAXVALUE) continue;
            r[cur.second] = cur.first;

            for (auto& edg : mp[cur.second]) {
                if (r[edg.first] == MAXVALUE) {
                    s.emplace(pair(edg.second + cur.first, edg.first));
                }
            }
        }

        int minT = -1;
        for (int i = 1; i <= n; ++i)
            minT = max(minT, r[i]);
        return minT == MAXVALUE ? -1 : minT;
    }
};*/

/* 朴素BF 
class Solution {
public:
    vector<unordered_map<int, int>> mp;
    int networkDelayTime(vector<vector<int>>& times, int n, int k) {
        // 记录结点最早收到信号的时间
        vector<int> r(n + 1, MAXVALUE);
        r[k] = 0;

        // n - 1 次松弛操作
        for (int i = 1; i < n; ++i) {
            bool t = false;
            for (auto& edg : times) {
                if (r[edg[1]] > r[edg[0]] + edg[2]) {
                    r[edg[1]] = r[edg[0]] + edg[2];
                    t = true;
                }
            }
            if (!t) break;
        }

        int minT = -1;
        for (int i = 1; i <= n; ++i)
            minT = max(minT, r[i]);
        return minT == MAXVALUE ? -1 : minT;
    }
};*/

/* SPFA 
class Solution {
public:
    vector<unordered_map<int, int>> mp;
    int networkDelayTime(vector<vector<int>>& times, int n, int k) {
        // 建图 - 邻接表
        mp.resize(n + 1);
        for (auto& edg : times) {
            mp[edg[0]][edg[1]] = edg[2];
        }
        // 记录结点最早收到信号的时间
        vector<int> r(n + 1, MAXVALUE);
        r[k] = 0;

        queue<int> d;
        d.emplace(k);
        unordered_set<int> s;
        s.emplace(k);

        while (!d.empty()) {
            int cur = d.front();
            d.pop();
            s.erase(cur);
            for (auto& edg : mp[cur]) {
                if (r[edg.first] > r[cur] + edg.second) {
                    r[edg.first] = r[cur] + edg.second;
                    if (s.find(edg.first) == s.end()) {
                        d.emplace(edg.first);
                        s.emplace(edg.first);
                    }
                }
            }
        }

        int minT = -1;
        for (int i = 1; i <= n; ++i)
            minT = max(minT, r[i]);
        return minT == MAXVALUE ? -1 : minT;
    }
};*/

/* Floyd */
class Solution {
public:
    vector<unordered_map<int, int>> mp;
    int networkDelayTime(vector<vector<int>>& times, int n, int k) {
        // 建图 - 邻接矩阵
        vector<vector<int>> mp(n + 1, vector<int>(n + 1, MAXVALUE));
        for (int i = 1; i <= n; ++i)
            mp[i][i] = 0;
        for (auto& edg : times) {
            mp[edg[0]][edg[1]] = edg[2];
        }
        for (int s = 1; s <= n; ++s) {
            for (int i = 1; i <= n; ++i) {
                for (int j = 1; j <= n; ++j) {
                    mp[i][j] = min(mp[i][j], mp[i][s] + mp[s][j]);
                }
            }
        }

        int minT = -1;
        for (int i = 1; i <= n; ++i)
            minT = max(minT, mp[k][i]);
        return minT == MAXVALUE ? -1 : minT;
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