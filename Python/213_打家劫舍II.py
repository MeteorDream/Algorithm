# -*- coding: utf-8 -*-
# File    : 213_打家劫舍II.py
# Author  : MeteorDream
# Time    : 2021/05/07 10:43:51
# language: Python
# Software: Visual Studio Code

import time
import math
import sys
import os
from typing import List
from functools import lru_cache

"""
[213. 打家劫舍 II](https://leetcode-cn.com/problems/house-robber-ii)

难度: 中等

你是一个专业的小偷，计划偷窃沿街的房屋，每间房内都藏有一定的现金。这个地方所有的房屋都 **围成一圈** ，这意味着第一个房屋和最后一个房屋是紧挨着的。同时，相邻的房屋装有相互连通的防盗系统，**如果两间相邻的房屋在同一晚上被小偷闯入，系统会自动报警** 。

给定一个代表每个房屋存放金额的非负整数数组，计算你 **在不触动警报装置的情况下** ，今晚能够偷窃到的最高金额。

$\quad$

示例 1：

> **输入：** nums = [2,3,2]
> **输出：** 3
> **解释：** 你不能先偷窃 1 号房屋（金额 = 2），然后偷窃 3 号房屋（金额 = 2）, 因为他们是相邻的。

示例 2：

> **输入：** nums = [1,2,3,1]
> **输出：** 4
> **解释：** 你可以先偷窃 1 号房屋（金额 = 1），然后偷窃 3 号房屋（金额 = 3）。  
> $\qquad$ 偷窃到的最高金额 = 1 + 3 = 4 。

示例 3：

> **输入：** nums = [0]
> **输出：** 0

提示：

- 1 <= nums.length <= 100
- 0 <= nums[i] <= 1000
"""


class Solution:
    # 动态规划+记忆化dfs
    def rob(self, nums: List[int]) -> int:
        n = len(nums)
        # x, y 分别表示前i - 1， i个房屋所能偷到的最大值
        x, y = nums[0], max(nums[0], nums[1] if n > 1 else 0)
        for i in range(2, n - 1):
            x, y = y, max(x + nums[i], y)

        # 返回第i个房屋及之后能偷窃到的最大值，issteal标志第i - 1个房屋是否偷窃
        @lru_cache(None)
        def dfs(i, issteal):
            # i越界，没房屋可供偷窃，只能空手而归了>_<
            if i >= n:
                return 0
            # 前一个偷过了，那这个就不能偷了！去下一家看看~
            elif issteal:
                return dfs(i + 1, False)
            # 前一个没偷过，那么这个可偷可不偷，两者取大的那个
            else:
                return max(dfs(i + 1, True) + nums[i], dfs(i + 1, False))

        return max(dfs(1, False), y)

# class Solution:
#     # 两次动态规划
#     def rob(self, nums: List[int]) -> int:
#         n = len(nums)
#         # x, y 分别表示前i - 1， i个房屋所能偷到的最大值
#         x, y = nums[0], max(nums[0], nums[1] if n > 1 else 0)
#         for i in range(2, n - 1):
#             x, y = y, max(x + nums[i], y)
#         ans = y
#         # x, y 分别表示前i - 1， i个房屋所能偷到的最大值
#         x, y = 0, max(0, nums[1] if n > 1 else 0)
#         for i in range(2, n):
#             x, y = y, max(x + nums[i], y)

#         return max(ans, y)


if __name__ == "__main__":
    start = time.perf_counter()

    s = Solution()

    nums = [2, 3, 2]  # 3
    print(s.rob(nums))

    nums = [1, 2, 3, 1]  # 4
    print(s.rob(nums))

    nums = [1, 2]  # 2
    print(s.rob(nums))

    nums = [0]  # 0
    print(s.rob(nums))

    end = time.perf_counter()
    print("Running Time: {:,.2f}μs".format((end - start) * 10 ** 6))
