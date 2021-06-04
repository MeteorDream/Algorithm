# -*- coding: utf-8 -*-
# File    : 1011. 在 D 天内送达包裹的能力.py
# Author  : MeteorDream
# Time    : 2021/04/26 11:57:53
# language: Python
# Software: Visual Studio Code

import time
from typing import List


class Solution:
    # # 贪心算法，错误，局部最优最终得到的不是全局最优
    # # 反例[3,2,2,4,1,4], 3
    # def shipWithinDays(self, weights: List[int], D: int) -> int:
    #     n = len(weights)
    #     heigh = max(weights)
    #     while n > D:
    #         i, ind, w = 0, 0, weights[0] + weights[1]
    #         while i < n - 1:
    #             tmp = weights[i] + weights[i + 1]
    #             w = weights[ind] + weights[ind + 1]
    #             if tmp < heigh:
    #                 weights[i] += weights[i + 1]
    #                 weights.pop(i + 1)
    #                 n -= 1
    #                 continue
    #             if tmp < w:
    #                 ind, w = i, tmp
    #             i += 1
    #         if not n <= D:
    #             weights[ind] += weights[ind + 1]
    #             weights.pop(ind + 1)
    #             n -= 1
    #             heigh = w
    #     return heigh

    # 二分每天的运输量
    def shipWithinDays(self, weights: List[int], D: int) -> int:
        n = len(weights)
        left, right = weights[0], 0

        # 左端点取最大值，右端点取weights的和
        for i in range(n):
            if weights[i] > left:
                left = weights[i]
            right += weights[i]

        while left < right:
            mid = left + (right - left) // 2
            cur, day = 0, 1
            for i in range(n):
                if cur + weights[i] > mid:
                    cur = weights[i]
                    day += 1
                else:
                    cur += weights[i]
            if day <= D:
                right = mid
            else:
                left = mid + 1
        return right


if __name__ == "__main__":
    start = time.perf_counter()

    s = Solution()

    print(s.shipWithinDays([1, 2, 3, 4, 5, 6, 7, 8, 9, 10], 5))
    print(s.shipWithinDays([3, 2, 2, 4, 1, 4], 3))

    end = time.perf_counter()
    print("Running Time: {:,.2f}μs".format((end - start) * 10 ** 6))
