// #include <bits/stdc++.h>
#include <cstdio>
#include <iostream>
using namespace std;

#define MAXN 100007
using ll = long long;    // 64 bits

// https://www.luogu.com.cn/problem/P3373

// 在模板的基础上添加了乘法和取模功能

// 线段树可以在 O(log N) 的时间复杂度内实现单点修改、区间修改、区间查询（区间求和，求区间最大值，求区间最小值）等操作
// 注意：为了保持树中孩子结点和父节点的下标对应关系，线段树的下标从 1 开始
// 模板中的是区间求和

// 源数组
ll nums[100007];

// 模
ll p;

// 分别存 值
ll val[MAXN * 4];
// 懒惰标记
ll tag[MAXN * 4], mtag[MAXN * 4];

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
    val[idx] = (val[lc(idx)] + val[rc(idx)]) % p;
}

// 更新懒惰标记
inline void update_tag(ll idx, ll left, ll right, ll k, ll m) {
    if (k != 0) {
        tag[idx] += k;
        val[idx] += k * (right - left + 1);
        tag[idx] %= p;
    }
    if (m != 1) {
        mtag[idx] *= m;
        val[idx] *= m;
        mtag[idx] %= p;
    }
    val[idx] %= p;
}

// 下传懒惰标记
inline void push_down(ll idx, ll left, ll right) {
    if (left == right) return;
    ll mid = left + (right - left >> 1);
    update_tag(lc(idx), left, mid, tag[idx], mtag[idx]);
    update_tag(rc(idx), mid + 1, right, tag[idx], mtag[idx]);
    tag[idx] = 0, mtag[idx] = 1;
}

// 当前根下标为 idx，递归对 [left, right] 区间建树
// 调用: build(1, 1, n) - 注意数组也要从下标 1 开始
void build(ll idx, ll left, ll right) {
    if (left == right) {
        val[idx] = nums[left];
    }
    else {
        tag[idx] = 0, mtag[idx] = 1;
        ll mid = left + (right - left >> 1);
        build(lc(idx), left, mid);
        build(rc(idx), mid + 1, right);
        push_up(idx);
    }
}

// 更新区间 [left, right], 当前区间 [cur_left, cur_right], 修改变化量
// 调用: update(1, 1, n, left, right)
void update(ll idx, ll cur_left, ll cur_right, ll left, ll right, ll c, ll m) {
    if (left != right) {
        if (tag[idx] != 0 || mtag[idx] != 1) push_down(idx, cur_left, cur_right);
        push_up(idx);
    }
    if (left <= cur_left && right >= cur_right) {
        if (c != 0) {
            val[idx] += c * (cur_right - cur_left + 1);
            tag[idx] += c;
            tag[idx] %= p;
        }
        if (m != 1) {
            val[idx] *= m;
            mtag[idx] *= m;
            mtag[idx] %= p;
        }
        val[idx] %= p;
    }
    else {
        ll mid = cur_left + (cur_right - cur_left >> 1);
        if (left <= mid) update(lc(idx), cur_left, mid, left, right, c, m);
        if (right > mid) update(rc(idx), mid + 1, cur_right, left, right, c, m);
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
    return ans % p;
}

/**
 * 输出线段树存储的数组
 * 
 * @param size: 数组长度
 * @param idx 当前下标
 * @param left, right 当前范围
 * @param t 下传的懒惰标记
 * 
 * 调用方式: print_nums(n, 1, 1, n, 0), putchar('\n');
 */
ll print_nums(ll size, ll idx, ll left, ll right, ll t1, ll t2) {
    if (left == right) {
        printf("%lld ", (val[idx] * t2 + t1) % p);
        return 1;
    }
    ll mid = left + (right - left >> 1);
    ll cnt = 0;
    if (cnt < size) cnt += print_nums(size - cnt, lc(idx), left, mid, (t1 * mtag[idx] + tag[idx]) % p, (t2 * mtag[idx]) % p);
    if (cnt < size) cnt += print_nums(size - cnt, rc(idx), mid + 1, right, (t1 * mtag[idx] + tag[idx]) % p, (t2 * mtag[idx]) % p);
    return cnt;
}

/**
 * @brief 输出整颗线段树（层序遍历）
 * 
 * @return int 
 */
void print_tree(ll size) {
    printf("---------- Tree ----------\n");
    ll cur = 1, idx = 1;
    while (cur <= size) {
        for (int i = 0; i < cur; ++i) {
            printf("(%lld, %lld, %lld) ", val[idx], tag[idx], mtag[idx]);
            idx++;
        }
        cur *= 2;
        putchar('\n');
    }
    printf("---------- end ----------\n");
}

int main() {
    /* 需要注释掉的部分 */
    freopen("./Problems/P3373_2.in", "r", stdin);    // 输入流重定向
    freopen("luogu.out", "w", stdout);               // 输出流重定向

    ll n, m;

    ll t, x, y, k;

    scanf("%lld%lld%lld", &n, &m, &p);

    for (int i = 1; i <= n; ++i) scanf("%lld", &nums[i]);

    build(1, 1, n);

    for (int i = 0; i < m; ++i) {
        scanf("%lld", &t);
        if (t == 3) {
            scanf("%lld%lld", &x, &y);
            printf("%lld\n", query(1, 1, n, x, y));
        }
        else {
            scanf("%lld%lld%lld", &x, &y, &k);
            if (t == 2)
                update(1, 1, n, x, y, k, 1);
            else
                update(1, 1, n, x, y, 0, k);
        }
    }

    return 0;
}