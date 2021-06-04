# -*- coding: utf-8 -*-
# File    : 477_汉明距离总和.py
# Author  : MeteorDream
# Time    : 2021/05/28 00:55:28
# language: Python
# Software: Visual Studio Code

import time
import math
import sys
import os
from typing import List
from functools import cache  # 装饰器，用于缓存递归函数中间值
from TreeNodeAndLinkNode import *  # 二叉树结点和链表结点

# [477. 汉明距离总和](https://leetcode-cn.com/problems/total-hamming-distance/)


class Solution:
    # 暴力，TLE，就不写了
    # 按位求值
    def totalHammingDistance(self, nums: List[int]) -> int:
        n, ans = len(nums), 0
        for i in range(32):
            c = 0  # 统计第i位为1的数量
            for num in nums:
                c += num & (1 << i) > 0
            ans += c * (n - c)
        return ans


if __name__ == "__main__":
    start = time.perf_counter()

    end = time.perf_counter()
    print("Running Time: {:,.2f}μs".format((end - start) * 10 ** 6))
