# -*- coding: utf-8 -*-
# File    : 523_连续的子数组和.py
# Author  : MeteorDream
# Time    : 2021/06/02 10:59:38
# language: Python
# Software: Visual Studio Code

import time
import math
import sys
import os
import re
from typing import List
from functools import cache  # 装饰器，用于缓存递归函数中间值
from TreeNodeAndLinkNode import *  # 二叉树结点和链表结点

# [523. 连续的子数组和](https://leetcode-cn.com/problems/continuous-subarray-sum/)


class Solution:
    # 前缀和+同余定理+哈希表
    def checkSubarraySum(self, nums: List[int], k: int) -> bool:
        n, s = len(nums), 0
        d = {0: -1}
        for i in range(n):
            s = (s + nums[i]) % k
            if s not in d:
                d[s] = i
            elif d[s] + 1 < i:
                return True
        return False


if __name__ == "__main__":
    start = time.perf_counter()

    end = time.perf_counter()
    print("Running Time: {:,.2f}μs".format((end - start) * 10 ** 6))
