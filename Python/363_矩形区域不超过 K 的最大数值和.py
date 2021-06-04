# -*- coding: utf-8 -*-
# File    : 363_矩形区域不超过 K 的最大数值和.py
# Author  : MeteorDream
# Time    : 2021/04/22 10:45:35
# language: Python
# Software: Visual Studio Code

import time, math, sys, os
from typing import List

class Solution:
    def maxSumSubmatrix(self, matrix: List[List[int]],
 k: int) -> int:
        m, n = len(matrix), len(matrix[0])
        dp = [[0 for i in range(n + 1)] for j in range(m + 1)]
                
        ans = -1000000
        for i in range(m):
            for j in range(n):
                dp[i + 1][j + 1] = dp[i + 1][j] + dp[i][j + 1] - dp[i][j] + matrix[i][j]
                if ans < dp[i + 1][j + 1] <= k:
                    ans = dp[i + 1][j + 1]
        
        if ans == k:
            return k

        for i in range(1, m + 1):
            for j in range(i + 1, m + 1):
                for t in range(1, n+ 1):
                    for u in range(t + 1, n + 1):
                        tmp = dp[j][u] - dp[i - 1][u] - dp[j][t - 1] + dp[i - 1][t - 1]
                        if ans < tmp <= k:
                            ans = tmp
                if ans == k:
                    return k
        
        return ans

if __name__ == "__main__":
    start = time.perf_counter()

    s = Solution()

    matrix = [[2,2,-1]]

    print(s.maxSumSubmatrix(matrix, 0))

    end = time.perf_counter()
    print("Running Time: {:,.2f}μs".format((end - start) * 10 ** 6))
