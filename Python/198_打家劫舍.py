# -*- coding: utf-8 -*-
# File    : 198_打家劫舍.py
# Author  : MeteorDream
# Time    : 2021/05/06 18:50:40
# language: Python
# Software: Visual Studio Code

import time
import math
import sys
import os
from typing import List
from functools import lru_cache

"""
[198. 打家劫舍](https://leetcode-cn.com/problems/house-robber)

难度: 中等

<!--more-->

你是一个专业的小偷，计划偷窃沿街的房屋。每间房内都藏有一定的现金，影响你偷窃的唯一制约因素就是相邻的房屋装有相互连通的防盗系统，**如果两间相邻的房屋在同一晚上被小偷闯入，系统会自动报警**。

给定一个代表每个房屋存放金额的非负整数数组，计算你 **不触动警报装置的情况下** ，一夜之内能够偷窃到的最高金额。

$\quad$

示例 1：

> 输入：[1,2,3,1]
> 输出：4
> 解释：偷窃 1 号房屋 (金额 = 1) ，然后偷窃 3 号房屋 (金额 = 3)。
> $\qquad$ 偷窃到的最高金额 = 1 + 3 = 4 。

示例 2：

> 输入：[2,7,9,3,1]
> 输出：12
> 解释：偷窃 1 号房屋 (金额 = 2), 偷窃 3 号房屋 (金额 = 9)，接着偷窃 5 号房屋 (金额 = 1)。
> $\qquad$ 偷窃到的最高金额 = 2 + 9 + 1 = 12 。

提示：

- 1 <= nums.length <= 100
- 0 <= nums[i] <= 400
"""


class Solution:
    # # 朴素dfs
    # def rob(self, nums: List[int]) -> int:
    #     n = len(nums)

    #     # 返回第i个房屋及之后能偷窃到的最大值，issteal标志第i - 1个房屋是否偷窃
    #     def dfs(i, issteal):
    #         # i越界，没房屋可供偷窃，只能空手而归了>_<
    #         if i >= n:
    #             return 0
    #         # 前一个偷过了，那这个就不能偷了！去下一家看看~
    #         elif issteal:
    #             return dfs(i + 1, False)
    #         # 前一个没偷过，那么这个可偷可不偷，两者取大的那个
    #         else:
    #             return max(dfs(i + 1, True) + nums[i], dfs(i + 1, False))

    #     return dfs(0, False)

    # # 记忆化dfs
    # def rob(self, nums: List[int]) -> int:
    #     n = len(nums)

    #     # 返回第i个房屋及之后能偷窃到的最大值，issteal标志第i - 1个房屋是否偷窃
    #     @lru_cache(None)
    #     def dfs(i, issteal):
    #         # i越界，没房屋可供偷窃，只能空手而归了>_<
    #         if i >= n:
    #             return 0
    #         # 前一个偷过了，那这个就不能偷了！去下一家看看~
    #         elif issteal:
    #             return dfs(i + 1, False)
    #         # 前一个没偷过，那么这个可偷可不偷，两者取大的那个
    #         else:
    #             return max(dfs(i + 1, True) + nums[i], dfs(i + 1, False))

    #     return dfs(0, False)

    # # 动态规划
    # def rob(self, nums: List[int]) -> int:
    #     n = len(nums)
    #     dp = [nums[0], max(nums[0], nums[1] if n > 1 else 0)]
    #     for i in range(2, n):
    #         dp.append(max(dp[i - 1], dp[i - 2] + nums[i]))
    #     return dp[-1]

    # 动态规划+滚动数组
    def rob(self, nums: List[int]) -> int:
        n = len(nums)
        # x, y 分别表示前i - 1， i个房屋所能偷到的最大值
        x, y = nums[0], max(nums[0], nums[1] if n > 1 else 0)
        for i in range(2, n):
            x, y = y, max(x + nums[i], y)
        return y


if __name__ == "__main__":
    start = time.perf_counter()

    s = Solution()

    nums = [1, 2, 3, 1]
    # 4
    print(s.rob(nums))

    nums = [2, 7, 9, 3, 1]
    # 12
    print(s.rob(nums))

    end = time.perf_counter()
    print("Running Time: {:,.2f}μs".format((end - start) * 10 ** 6))
