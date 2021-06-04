# -*- coding: utf-8 -*-
# File    : 50_Pow(x,n).py
# Author  : MeteorDream
# Time    : 2021/05/29 20:50:31
# language: Python
# Software: Visual Studio Code

import time
from typing import List

# [50. Pow(x, n)](https://leetcode-cn.com/problems/powx-n/)


class Solution:
    # 快速幂
    def myPow(self, x: float, n: int) -> float:
        t = n if n > 0 else -n
        ans = 1
        while t != 0:
            if t & 1:
                ans *= x
            x *= x
            t >>= 1
        return ans if n >= 0 else 1 / ans


if __name__ == "__main__":
    start = time.perf_counter()

    s = Solution()
    print(s.myPow(2, 10))

    end = time.perf_counter()
    print("Running Time: {:,.2f}μs".format((end - start) * 10 ** 6))
