# -*- coding: utf-8 -*-
# File    : 368. 最大整除子集.py
# Author  : MeteorDream
# Time    : 2021/04/23 10:40:52
# language: Python
# Software: Visual Studio Code

import time, math, sys, os
from typing import List

class Solution:
    # 方法一：并查集
    # def largestDivisibleSubset(self, nums: List[int]) -> List[int]:
    #     n = len(nums)
    #     nums.sort()
    #     s = [i for i in range(n)]
    #     level = [0 for i in range(n)]

    #     # 并查集，查找level最高的父节点
    #     for i in range(n):
    #         for j in range(n):
    #             if i != j and nums[i] % nums[j] == 0 and level[i] <= level[j]:
    #                 s[i] = j
    #                 level[i] = level[j] + 1

    #     # 查找level最高的下标
    #     ind = 0
    #     for i in range(n):
    #         if level[i] > level[ind]:
    #             ind = i

    #     # 根据查找到的下标和并查集溯源数组
    #     ans = list()
    #     while s[ind] != ind:
    #         ans.append(nums[ind])
    #         ind = s[ind]
    #     ans.append(nums[ind])
    #     return ans

    # 暴力，超时了
    def largestDivisibleSubset(self, nums: List[int]) -> List[int]:
        ans = list()
        n = len(nums)

        nums.sort()

        for i in range(n):
            t = len(ans)
            ans.append([nums[i]])
            for j in range(t):
                if nums[i] % ans[j][-1] == 0:
                    ans.append(ans[j] + [nums[i]])
        
        ind = 0
        for i in range(len(ans)):
            if len(ans[ind]) < len(ans[i]):
                ind = i

        return ans[ind]


if __name__ == "__main__":
    start = time.perf_counter()

    s = Solution()

    nums = [1,2,3]
    print(s.largestDivisibleSubset(nums))
    nums = [1,2,4,8]
    print(s.largestDivisibleSubset(nums))
    nums = [4,8,10,240]
    print(s.largestDivisibleSubset(nums))
    nums = [3,4,8,16]
    print(s.largestDivisibleSubset(nums))

    end = time.perf_counter()
    print("Running Time: {:,.2f}μs".format((end - start) * 10 ** 6))
