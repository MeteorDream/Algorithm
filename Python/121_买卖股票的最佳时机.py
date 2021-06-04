# -*- coding: utf-8 -*-
# File    : 121_买卖股票的最佳时机.py
# Author  : MeteorDream
# Time    : 2021/05/31 21:25:56
# language: Python
# Software: Visual Studio Code

import time
import math
import sys
import os
from typing import List
from functools import cache  # 装饰器，用于缓存递归函数中间值
from TreeNodeAndLinkNode import *  # 二叉树结点和链表结点

# [121. 买卖股票的最佳时机](https://leetcode-cn.com/problems/best-time-to-buy-and-sell-stock/)


class Solution:
    # 动态规划
    def maxProfit(self, prices: List[int]) -> int:
        # 如果买卖期只有一天当然是赚不到钱的
        if len(prices) < 2:
            return 0
        ans, buy = 0, prices[0]
        for p in prices:
            if p < buy:
                buy = p
            else:
                ans = max(ans, p - buy)
        return ans


if __name__ == "__main__":
    start = time.perf_counter()

    end = time.perf_counter()
    print("Running Time: {:,.2f}μs".format((end - start) * 10 ** 6))
