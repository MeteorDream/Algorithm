// #include <bits/stdc++.h>
#include <cstdio>
#include <iostream>
using namespace std;

#define MAXN 100007
using ll = long long;    // 64 bits

// https://www.luogu.com.cn/problem/P3372

// 线段树可以在 O(log N) 的时间复杂度内实现单点修改、区间修改、区间查询（区间求和，求区间最大值，求区间最小值）等操作
// 注意：为了保持树中孩子结点和父节点的下标对应关系，线段树的下标从 1 开始
// 模板中的是区间求和

// 源数组
ll nums[100007];

// 分别存 值，懒惰标记
ll val[MAXN * 4], tag[MAXN * 4];

// 左孩子结点下标
inline ll lc(ll x) {
    return x << 1;
}

// 右孩子结点下标
inline ll rc(ll x) {
    return x << 1 | 1;
}

// 向上合并
inline void push_up(ll idx) {
    val[idx] = val[lc(idx)] + val[rc(idx)];
}

// 更新懒惰标记
inline void update_tag(ll idx, ll left, ll right, ll k) {
    tag[idx] += k;
    val[idx] += k * (right - left + 1);
}

// 下传懒惰标记
inline void push_down(ll idx, ll left, ll right) {
    ll mid = left + (right - left >> 1);
    update_tag(lc(idx), left, mid, tag[idx]);
    update_tag(rc(idx), mid + 1, right, tag[idx]);
    tag[idx] = 0;
}

// 当前根下标为 idx，递归对 [left, right] 区间建树
// 调用: build(1, 1, n) - 注意数组也要从下标 1 开始
void build(ll idx, ll left, ll right) {
    if (left == right) {
        val[idx] = nums[left];
    }
    else {
        tag[idx] = 0;
        ll mid = left + (right - left >> 1);
        build(lc(idx), left, mid);
        build(rc(idx), mid + 1, right);
        push_up(idx);
    }
}

// 更新区间 [left, right], 当前区间 [cur_left, cur_right], 修改变化量
// 调用: update(1, 1, n, left, right)
void update(ll idx, ll cur_left, ll cur_right, ll left, ll right, ll c) {
    if (left <= cur_left && right >= cur_right) {
        val[idx] += c * (cur_right - cur_left + 1);
        tag[idx] += c;
    }
    else {
        ll mid = cur_left + (cur_right - cur_left >> 1);
        if (tag[idx] != 0) push_down(idx, cur_left, cur_right);
        if (left <= mid) update(lc(idx), cur_left, mid, left, right, c);
        if (right > mid) update(rc(idx), mid + 1, cur_right, left, right, c);
        push_up(idx);
    }
}

// 区间查询 [left, right] 是查询区间，当前区间 [cur_left, cur_right]
// 调用: query(1, 1, n, left, right)
ll query(ll idx, ll cur_left, ll cur_right, ll left, ll right) {
    if (left <= cur_left && right >= cur_right) return val[idx];
    ll mid = cur_left + (cur_right - cur_left >> 1), ans = 0;
    push_down(idx, cur_left, cur_right);
    if (left <= mid) ans += query(lc(idx), cur_left, mid, left, right);
    if (right > mid) ans += query(rc(idx), mid + 1, cur_right, left, right);
    return ans;
}

int main() {
    ll n, m;

    ll t, x, y, k;

    scanf("%lld%lld", &n, &m);

    for (int i = 1; i <= n; ++i) scanf("%lld", &nums[i]);

    build(1, 1, n);

    for (int i = 0; i < m; ++i) {
        scanf("%lld", &t);
        if (t == 1) {
            scanf("%lld%lld%lld", &x, &y, &k);
            update(1, 1, n, x, y, k);
        }
        else {
            scanf("%lld%lld", &x, &y);
            printf("%lld\n", query(1, 1, n, x, y));
        }
    }

    return 0;
}