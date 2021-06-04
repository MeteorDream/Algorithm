# -*- coding: utf-8 -*-
# File    : 279_完全平方数.py
# Author  : MeteorDream
# Time    : 2021/04/16 22:04:19
# language: Python
# Software: Visual Studio Code

import time, math, sys, os
from typing import List

class Solution:
    def numSquares(self, n: int) -> int:
        # 找完全平方数
        nums = list()
        i = 1
        while i * i < n:
            nums.append(i * i)
            i += 1
        print(nums)
        
        size = len(nums)
        dp = [0, 1]
        for i in range(2, n + 1):
            tmp = dp[i - 1] + 1
            for j in range(size):
                if not nums[j] > i:
                    tmp = min(tmp, dp[i - nums[j]] + 1)
                else:
                    break
            dp.append(tmp)
        print(dp)
        return dp[-1]

if __name__ == "__main__":
    start = time.perf_counter()

    s = Solution()

    print(s.numSquares(13))

    end = time.perf_counter()
    print("Running Time: {:,.2f}μs".format((end - start) * 10 ** 6))
