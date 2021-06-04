# -*- coding: utf-8 -*-
# File    : 403. 青蛙过河.py
# Author  : MeteorDream
# Time    : 2021/04/29 10:16:39
# language: Python
# Software: Visual Studio Code

import time
from typing import List


class Solution:
    # # dfs超时
    # def canCross(self, stones: List[int]) -> bool:
    #     n = len(stones)

    #     # 当前位置, 数组内坐标和上一步跳跃长度
    #     def dfs(start, s, jump):
    #         if s == n - 1:
    #             return True
    #         end = start + jump
    #         for i in range(s + 1, n):
    #             if stones[i] == end - 1 and dfs(end - 1, i, jump - 1):
    #                 return True
    #             elif stones[i] == end and dfs(end, i, jump):
    #                 return True
    #             elif stones[i] == end + 1 and dfs(end + 1, i, jump + 1):
    #                 return True
    #             elif stones[i] > end + 1:
    #                 break
    #         return False

    #     if not stones[1] == 1:
    #         return False
    #     return dfs(1, 1, 1)

    # dfs优化
    # 优化1: 改用hashmap记录
    # 优化2: 检测是否超出最大跳跃能力
    # def canCross(self, stones: List[int]) -> bool:
    #     n = len(stones)
    #     d = dict()
    #     target = stones[-1]

    #     # hashmap记录stone，并检查是否超出最大跳跃距离
    #     for i in range(1, n):
    #         if stones[i] - stones[i - 1] > i:
    #             return False
    #         d[stones[i]] = i

    #     # start - 当前位置, jump - 上一步跳跃长度
    #     def dfs(start, jump):
    #         if start == target:
    #             return True
    #         elif start > target:
    #             return False
    #         end = start + jump
    #         # jump不能为0否则会无限递归
    #         if jump > 1 and end - 1 in d and dfs(end - 1, jump - 1):
    #             return True
    #         elif end in d and dfs(end, jump):
    #             return True
    #         elif end + 1 in d and dfs(end + 1, jump + 1):
    #             return True
    #         return False

    #     return dfs(1, 1)

    # 记忆化dfs hashmap版
    # 执行用时：76 ms, 在所有 Python3 提交中击败了97.60%的用户
    # 内存消耗：18.7 MB, 在所有 Python3 提交中击败了35.95%的用户
    # def canCross(self, stones: List[int]) -> bool:
    #     n = len(stones)
    #     d = dict()
    #     mp = dict()

    #     # hashmap记录stone，并检查是否超出最大跳跃距离
    #     for i in range(1, n):
    #         if stones[i] - stones[i - 1] > i:
    #             return False
    #         d[stones[i]] = i

    #     # start - stone下标位置, jump - 上一步跳跃长度
    #     def dfs(start, jump):
    #         k = start * 10000 + jump
    #         if k in mp:
    #             return mp[k]
    #         if start == n - 1:
    #             return True
    #         end = stones[start] + jump
    #         # jump不能为0否则会无限递归
    #         if jump > 1 and end - 1 in d:
    #             cur = dfs(d[end - 1], jump - 1)
    #             mp[k] = cur if not k in mp else cur or mp[k]
    #             if cur:
    #                 return True
    #         if end in d:
    #             cur = dfs(d[end], jump)
    #             mp[k] = cur if not k in mp else cur or mp[k]
    #             if cur:
    #                 return True
    #         if end + 1 in d:
    #             cur = dfs(d[end + 1], jump + 1)
    #             mp[k] = cur if not k in mp else cur or mp[k]
    #             if cur:
    #                 return True

    #         mp[k] = False
    #         return False

    #     return dfs(1, 1)

    # 记忆化dfs
    # 执行用时：1552 ms, 在所有 Python3 提交中击败了30.99%的用户
    # 内存消耗：101.2 MB, 在所有 Python3 提交中击败了5.12%的用户
    def canCross(self, stones: List[int]) -> bool:
        n = len(stones)
        d = dict()
        mp = [[0 for i in range(n)] for i in range(n)]

        # hashmap记录stone，并检查是否超出最大跳跃距离
        for i in range(1, n):
            if stones[i] - stones[i - 1] > i:
                return False
            d[stones[i]] = i

        # start - stone下标位置, jump - 上一步跳跃长度
        def dfs(start, jump):
            if mp[start][jump]:
                return mp[start][jump] == 1
            if start == n - 1:
                return True
            end = stones[start] + jump
            # jump不能为0否则会无限递归
            if jump > 1 and end - 1 in d:
                cur = dfs(d[end - 1], jump - 1)
                mp[start][jump] = 1 if cur else -1
                if cur:
                    return True
            if end in d:
                cur = dfs(d[end], jump)
                mp[start][jump] = 1 if cur else -1
                if cur:
                    return True
            if end + 1 in d:
                cur = dfs(d[end + 1], jump + 1)
                mp[start][jump] = 1 if cur else -1
                if cur:
                    return True

            mp[start][jump] = -1
            return False

        return dfs(1, 1)

    # 动态规划
    # def canCross(self, stones: List[int]) -> bool:
    #     n = len(stones)

    #     # 检查是否超出最大跳跃距离
    #     for i in range(1, n):
    #         if stones[i] - stones[i - 1] > i:
    #             return False

    #     dp = [[False for i in range(n)] for j in range(n)]
    #     dp[1][1] = True

    #     for i in range(2, n):
    #         for j in range(1, i):
    #             k = stones[i] - stones[j]
    #             if k <= j + 1:
    #                 dp[i][k] = dp[j][k - 1] or dp[j][k] or dp[j][k + 1]

    #     for i in range(1, n):
    #         if dp[n - 1][i]:
    #             return True
    #     return False

    # 动态规划(hashmap版)
    # 执行用时：2800 ms, 在所有 Python3 提交中击败了21.57%的用户
    # 内存消耗：44.5 MB, 在所有 Python3 提交中击败了11.54%的用户
    # def canCross(self, stones: List[int]) -> bool:
    #     n = len(stones)

    #     # 检查是否超出最大跳跃距离
    #     for i in range(1, n):
    #         if stones[i] - stones[i - 1] > i:
    #             return False

    #     dp = dict()
    #     dp[10001] = True

    #     for i in range(2, n):
    #         for j in range(1, i):
    #             k = stones[i] - stones[j]
    #             if k <= j + 1:
    #                 tmp = j * 10000 + k
    #                 dp[i * 10000 + k] = (dp[tmp - 1] if tmp - 1 in dp else False) or (
    #                     dp[tmp] if tmp in dp else False) or (dp[tmp + 1] if tmp + 1 in dp else False)

    #     tmp = 10000 * (n - 1)
    #     for i in range(1, n):
    #         if tmp + i in dp and dp[tmp + i]:
    #             return True
    #     return False


if __name__ == "__main__":
    start = time.perf_counter()

    s = Solution()

    stones = [0, 1, 3, 5, 6, 8, 12, 17]
    print(s.canCross(stones))

    stones = [0, 1, 3, 5]
    print(s.canCross(stones))

    stones = [0, 1, 2, 3, 4, 8, 9, 11]
    print(s.canCross(stones))

    stones = list(range(500)) + [750]  # dfs超时用例(其实是999但本地执行会超过最大递归深度)
    print(s.canCross(stones))

    end = time.perf_counter()
    print("Running Time: {:,.2f}μs".format((end - start) * 10 ** 6))

# 记忆化递归dfs: Running Time: 67,174.20μs
# 记忆化dfs hashmap版: Running Time: 43,998.30μs
# 动态规划：Running Time: 95,934.50μs
# 动态规划hashmap版: Running Time: 142,562.40μs
