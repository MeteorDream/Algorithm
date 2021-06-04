# -*- coding: utf-8 -*-
# File    : 87_scramble-string.py
# Author  : MeteorDream
# Time    : 2021/04/16 18:12:06
# language: Python
# Software: Visual Studio Code

import time
from typing import List
import random

# 使用下面描述的算法可以扰乱字符串 s 得到字符串 t ：
# 如果字符串的长度为 1 ，算法停止
# 如果字符串的长度 > 1 ，执行下述步骤：
# 在一个随机下标处将字符串分割成两个非空的子字符串。即，如果已知字符串 s ，则可以将其分成两个子字符串 x 和 y ，且满足 s = x + y 。
# 随机 决定是要「交换两个子字符串」还是要「保持这两个子字符串的顺序不变」。即，在执行这一步骤之后，s 可能是 s = x + y 或者 s = y + x 。
# 在 x 和 y 这两个子字符串上继续从步骤 1 开始递归执行此算法。
# 给你两个 长度相等 的字符串 s1 和 s2，判断 s2 是否是 s1 的扰乱字符串。如果是，返回 true ；否则，返回 false 。


class Solution:
    def Scramble(self, s: str) -> str:
        n = len(s)
        if n <= 1:
            return s
        ind = random.randint(0, n)
        if random.randint(0, 1):
            return self.Scramble(s[ind:]) + self.Scramble(s[:ind])
        else:
            return self.Scramble(s[:ind]) + self.Scramble(s[ind:])


if __name__ == "__main__":
    start = time.perf_counter()

    s = Solution()

    print(s.Scramble("abcdefghij"))

    end = time.perf_counter()
    print("Running Time: {:,.2f}μs".format((end - start) * 10 ** 6))
