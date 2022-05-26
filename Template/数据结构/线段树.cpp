#include <cstdio>
#include <iostream>
using namespace std;

#define MAXN 100007
using ll = long long;    // 64 bits

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
ll print_nums(ll size, ll idx, ll left, ll right, ll t) {
    if (left == right) {
        printf("%lld ", val[idx] + t);
        return 1;
    }
    ll mid = left + (right - left >> 1);
    ll cnt = 0;
    if (cnt < size) cnt += print_nums(size - cnt, lc(idx), left, mid, t + tag[idx]);
    if (cnt < size) cnt += print_nums(size - cnt, rc(idx), mid + 1, right, t + tag[idx]);
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
            printf("(%lld, %lld) ", val[idx], tag[idx]);
            idx++;
        }
        cur *= 2;
        putchar('\n');
    }
    printf("---------- end ----------\n");
}