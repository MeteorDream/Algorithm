# --------------------测试用，提交前请注释掉----------------------

import sys

sys.stdin = open('in4.dat', 'r')
sys.stdout = open('out4.dat', 'w')

# -------------------------------------------------------------
from functools import lru_cache

def main():
    n, k = map(int, input().split())
    p = list(map(float, input().split()))
    from collections import defaultdict
    dp = defaultdict(float)

    @lru_cache(None)
    def dfs(x, y, z, *args):
        """x 枚硬币, 已经抽卡 y 次, 当前概率, 每张卡牌是否已经拥有"""
        q = sum(i == 0 for i in args)
        if q == 0 or x // k >= q:
            dp[args[0] * 1 + args[1] * 2 + args[2] * 4 + args[3] * 8, x] += z
            return z * y
        else:
            ans = 0
            for i, j in enumerate(p):
                if args[i] == 1:
                    ans += dfs(x + 1, y + 1, z * j, *args)
                else:
                    ans += dfs(x, y + 1, z * j, *(args[t] for t in range(i)), 1, *(args[t] for t in range(i + 1, n)))
            return ans
    
    state = [0 for _ in range(n)]
    # print(n, k, p)
    print(dfs(0, 0, 1, *state))
    pre = 0
    for i in sorted(dp.keys()):
        if pre != i[0]:
            print()
            pre = i[0]
        print(i, "{:.10f}".format(dp[i]), end = ',')
# --------------------测试用，提交前请注释掉----------------------
        
main()
# main()

# ---------------------------------------------------------------