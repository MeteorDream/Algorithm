using namespace std;

long quickpow(int x, int n, int mod) {
    // x ^ n % mod 快速幂
    long ans = 1;
    while (n != 0) {
        if (n & 1 == 1)
            ans = ans * x % mod;
        x = x * x % mod;
        n >>= 1;
    }
    return ans;
}

bool isprime(int x) {
    if (x < 3) return x == 2;
    if (x % 2 == 0) return false;
    int s[] = {2, 3, 5, 7, 11, 13, 17};
    int d = x - 1, r = 0;
    while (d % 2 == 0) {
        d >>= 1;
        ++r;
    }
    for (int b : s) {
        long y = quickpow(b, d, x);
        if (y == 1 || y == 0 || y == x - 1) continue;
        for (int i = 0; i < r; ++i) {
            y = y * y % x;
            if (y == x - 1 && i != r - 1) {
                y = 1;
                break;
            }
            if (y == 1) return false;
        }
        if (y != 1) return false;
    }
    return true;
}