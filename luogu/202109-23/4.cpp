#include <bits/stdc++.h>
using namespace std;

int n, k;    // n <= 16, k <= 5
double p[17];

// state 状态、硬币数量, 表示概率
double dp[(1 << 16) + 7][100];

int count(int x) {
    int cnt = 0;
    while (x != 0) {
        x &= x - 1;
        ++cnt;
    }
    return cnt;
}

int collect_card() {
    freopen("in.in", "r", stdin);
    freopen("out.out", "w", stdout);

    scanf("%d %d", &n, &k);
    for (int i = 0; i < n; ++i) {
        scanf("%lf", &p[i]);
    }
    if (n == 1) {
        printf("%d", 1);
        return 0;
    }
    if (k == 1) {
        printf("%d", n);
        return 0;
    }
    memset(dp, 0, sizeof(dp));
    int mxy = (n - 1) * k;     // 最大硬币数量
    int end = (1 << n) - 1;    // 最终状态
    double ans = 0;
    dp[0][0] = 1.0;
    double lvcnt = 0;
    for (int state = 0; state <= end; ++state) {
        int cnt = count(state);
        for (int coin = 0; coin <= mxy; ++coin) {
            printf("%.10lf ", dp[state][coin]);
            for (int i = 0; i < n; ++i) {
                int k = (1 << i);
                if (state & k == 0) {
                    dp[state | k][coin] += dp[state][coin] * p[i];
                }
                else {
                    dp[state][coin + 1] += dp[state][coin] * p[i];
                }
            }
            if (cnt + coin / k == n) {
                ans += (cnt + coin) * dp[state][coin];
            }
            else if (cnt + coin / k > n)
                break;
        }
        putchar('\n');
    }
    // for (int state = 1; state <= end; ++state) {
    //     int cnt = count(state);
    //     for (int coin = 0; coin <= mxy; coin++) {
    //         // 上一步同样是抽牌
    //         for (int i = 0; i < n; ++i) {
    //             if ((state & (1 << i)) != 0) {
    //                 if (coin > 0 && cnt < n) {  // 抽到重复的牌
    //                     dp[state][coin] += dp[state][coin - 1] * p[i];
    //                 }
    //                 if (!(cnt == 1 && coin > 0)) {  // 新入手的牌
    //                     dp[state][coin] += dp[state ^ (1 << i)][coin] * p[i];
    //                 }
    //             }
    //         }
    //         if (cnt + coin / k == n) {
    //             ans += (cnt + coin) * dp[state][coin];
    //             lvcnt += dp[state][coin];
    //             // printf("state = %d(%d), coin = %d, lv = %10lf\n", state, cnt, coin, dp[state][coin]);
    //         }
    //         else if (cnt + coin / k > n) break;

    //         printf("%.10lf ", dp[state][coin]);
    //     }
    //     putchar('\n');
    // }

    printf("%lf %lf", ans, lvcnt);
    return 0;
}

int main() {
    for (int i = 0; i < 2; ++i) {
        collect_card();
        putchar('\n');
    }
    return 0;
}