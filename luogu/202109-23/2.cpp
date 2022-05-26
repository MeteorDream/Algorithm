#include <bits/stdc++.h>
using namespace std;

int n, tmp;
int nums[500007];

int check(int* nums, int n, int p) {
    // return the number of not zero
    int state = 0;  // 1 for hava nativate and 0 for 0
    int cnt = 0;
    for (int i = 0; i < n; ++i) {
        if (nums[i] >= p) {
            state = 1;
        }
        else {
            if (state == 1) {
                cnt ++;
            }
            state = 0;
        }
    }
    return state == 1 ? cnt + 1: cnt;
}

int main(){

    // freopen("in.in", "r", stdin);
    // freopen("out.out", "w", stdout);

    scanf("%d", &n);
    int mx = 0, ans = 0;
    for (int i = 0; i < n; ++i) {
        scanf("%d", &tmp);
        nums[i] = tmp;
        mx = max(mx, tmp);
    }
    if (mx == 0) return 0;
    for (int i = mx; i > 0; --i) {
        ans = max(ans, check(nums, n, i));
    }
    printf("%d", ans);
    return 0;
}