# -*- coding: utf-8 -*-
# File    : 525_连续数组.py
# Author  : MeteorDream
# Time    : 2021/06/03 17:08:01
# language: Python
# Software: Visual Studio Code

import time
from typing import List

# [525. 连续数组](https://leetcode-cn.com/problems/contiguous-array/)


class Solution:
    def findMaxLength(self, nums: List[int]) -> int:
        # 前缀和
        # 1. 预处理数组，将 0 改为 -1，使得 0 和 1 数量相等的子数组和为 0
        # 2. 使用 HashMap 记录(前缀和,下标)，一次遍历计算得结果
        n, ans, s, st = len(nums), 0, 0, {0: -1}
        for i in range(n):
            s += 1 if nums[i] == 1 else -1
            if s in st:
                if i - st[s] > ans:
                    ans = i - st[s]
            else:
                st[s] = i
        return ans


if __name__ == "__main__":
    start = time.perf_counter()

    end = time.perf_counter()
    print("Running Time: {:,.2f}μs".format((end - start) * 10 ** 6))
