# -----------------  测试用，提交前注释掉！ --------------------
# import sys

# sys.stdin = open('in2.dat', 'r')
# sys.stdout = open('out2.dat', 'w')

# -------------------------------------------------------------

from collections import defaultdict

def main():
    n = int(input())
    arr = list(map(int, input().split()))
    arr.append(0)

    cnt = defaultdict(list)
    ans, pre = 0, 0

    x = arr[0]

    for i, a in enumerate(arr):
        cnt[a].append(i)
        if a > 0 and pre == 0:
            ans += 1
        pre = a
        x = max(a, x)

    cur = ans
    for i in range(1, x + 1):
        for idx in cnt[i]:
            if arr[idx - 1] == 0 and arr[idx + 1] == 0:
                cur -= 1
            elif arr[idx - 1] == 0 or arr[idx + 1] == 0:
                pass
            else:
                cur += 1
            arr[idx] = 0
        ans = max(ans, cur)
    print(ans)

main()