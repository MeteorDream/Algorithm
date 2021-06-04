# -*- coding: utf-8 -*-
# File    : 1074_元素和为目标值的子矩阵数量.py
# Author  : MeteorDream
# Time    : 2021/05/29 11:28:11
# language: Python
# Software: Visual Studio Code

import time
from typing import List

# [1074. 元素和为目标值的子矩阵数量](https://leetcode-cn.com/problems/number-of-submatrices-that-sum-to-target/)


# class Solution:
#     # 二维前缀和 暴力解法
#     def numSubmatrixSumTarget(self, matrix: List[List[int]], target: int) -> int:
#         n, m, ans = len(matrix), len(matrix[0]), 0
#         # 二维前缀和
#         s = [[0 for i in range(m + 1)] for j in range(n + 1)]
#         for i in range(n):
#             for j in range(m):
#                 s[i + 1][j + 1] = matrix[i][j] + \
#                     s[i + 1][j] + s[i][j + 1] - s[i][j]
#         # 暴力搜索
#         for a in range(1, n+1):
#             for b in range(1, m + 1):
#                 for c in range(1, a + 1):
#                     for d in range(1, b + 1):
#                         if s[a][b] - s[a][d - 1] - s[c - 1][b] + s[c - 1][d - 1] == target:
#                             ans += 1
#         return ans

class Solution:
    # 二维前缀和 HashMap解法
    def numSubmatrixSumTarget(self, matrix: List[List[int]], target: int) -> int:
        n, m, ans = len(matrix), len(matrix[0]), 0
        # 二维前缀和
        s = [[0 for i in range(m + 1)] for j in range(n + 1)]
        for i in range(n):
            for j in range(m):
                s[i + 1][j + 1] = matrix[i][j] + \
                    s[i + 1][j] + s[i][j + 1] - s[i][j]
        # 枚举三条边，第四条边透过hashmap查找
        for a in range(1, n + 1):
            for b in range(a, n + 1):
                ss = {}
                for c in range(1, m + 1):
                    tmp = s[b][c] - s[a - 1][c]
                    if tmp == target:
                        ans += 1
                    if tmp - target in ss:
                        ans += ss[tmp - target]
                    if tmp in ss:
                        ss[tmp] += 1
                    else:
                        ss[tmp] = 1
        return ans


if __name__ == "__main__":
    start = time.perf_counter()

    end = time.perf_counter()
    print("Running Time: {:,.2f}μs".format((end - start) * 10 ** 6))
