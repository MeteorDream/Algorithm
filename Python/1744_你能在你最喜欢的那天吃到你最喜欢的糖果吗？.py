# -*- coding: utf-8 -*-
# File    : 1744_你能在你最喜欢的那天吃到你最喜欢的糖果吗？.py
# Author  : MeteorDream
# Time    : 2021/06/01 16:45:03
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

# [1744. 你能在你最喜欢的那天吃到你最喜欢的糖果吗？](https://leetcode-cn.com/problems/can-you-eat-your-favorite-candy-on-your-favorite-day/)


class Solution:
    def canEat(self, candiesCount: List[int], queries: List[List[int]]) -> List[bool]:
        # candiesCount[i] 表示你拥有的第 i 类糖果的数目
        # queries[i] = [favoriteTypei, favoriteDayi, dailyCapi]
        # 即 喜欢的糖果下标， 喜欢的天数， 每天最多吃糖
        # 在每天吃 不超过 dailyCapi 颗糖果的前提下
        # 你可以在第 favoriteDayi 天吃到第 favoriteTypei 类糖果
        n, m = len(candiesCount), len(queries)
        # s[i] 表示前 i-1 类糖果的数量和
        s = [0 for _ in range(n + 1)]
        ans = [0 for _ in range(m)]
        for i in range(n):
            s[i + 1] = s[i] + candiesCount[i]
        for i in range(m):
            # min, max 表示喜欢那天最少要吃的糖果数量和最多能吃的糖果数量
            min, max = queries[i][1], queries[i][2] * (queries[i][1] + 1)
            # 只要(s[q], s[q + 1])与(min, max)区间有交集，即可在喜欢那天吃到喜欢的糖果
            ans[i] = (min < s[queries[i][0] + 1]) and (max > s[queries[i][0]])
        return ans


if __name__ == "__main__":
    start = time.perf_counter()

    end = time.perf_counter()
    print("Running Time: {:,.2f}μs".format((end - start) * 10 ** 6))
