#include <bits/stdc++.h>
using namespace std;

int n, tmp;
int a, b;
int pre;

int main(){

    // freopen("in.in", "r", stdin);
    // freopen("out.out", "w", stdout);

    scanf("%d", &n);
    scanf("%d", &tmp);
    a = tmp, b = tmp; // a min , b max
    pre = tmp;
    for (int i = 1; i < n; ++i) {
        scanf("%d", &tmp);
        if (pre < tmp) {
            pre = tmp;
            a += pre;
        }
        b += pre;
    }
    printf("%d\n%d", b, a);
    return 0;
}