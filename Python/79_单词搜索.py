# -*- coding: utf-8 -*-
# File    : 79_单词搜索.py
# Author  : MeteorDream
# Time    : 2021/05/28 17:29:25
# language: Python
# Software: Visual Studio Code

import time
import math
import sys
import os
from typing import List

from functools import cache  # 装饰器，用于缓存递归函数中间值
from TreeNodeAndLinkNode import *  # 二叉树结点和链表结点

# [79. 单词搜索](https://leetcode-cn.com/problems/word-search/)


class Solution:
    def exist(self, board: List[List[str]], word: str) -> bool:
        n, m, s = len(board), len(board[0]), len(word)

        def dfs(i, j, k):
            # word 查询完了说明查找到了!
            if k == s:
                return True
            # 越界返回 false
            elif i < 0 or i >= n or j < 0 or j >= m:
                return False
            # 不匹配返回 false
            elif board[i][j] != word[k]:
                return False
            else:
                # 匹配，则先做标记，然后递归查询，最后恢复现场
                tmp = board[i][j]
                board[i][j] = '#'
                if dfs(i + 1, j, k + 1) or dfs(i - 1, j, k + 1) or dfs(i, j + 1, k + 1) or dfs(i, j - 1, k + 1):
                    board[i][j] = tmp
                    return True
                else:
                    board[i][j] = tmp
                    return False

        # 前处理
        d = dict()
        for b in board:
            for c in b:
                if c in d:
                    d[c] += 1
                else:
                    d[c] = 1
        for c in word:
            if c in d:
                d[c] -= 1
                if d[c] < 0:
                    return False
            else:
                return False

        for b in range(n):
            for c in range(m):
                if dfs(b, c, 0):
                    return True
        return False


if __name__ == "__main__":
    start = time.perf_counter()

    end = time.perf_counter()
    print("Running Time: {:,.2f}μs".format((end - start) * 10 ** 6))
