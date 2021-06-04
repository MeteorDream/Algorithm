# -*- coding: utf-8 -*-
# File    : 8_字符串转换整数(atoi).py
# Author  : MeteorDream
# Time    : 2021/05/31 21:50:31
# language: Python
# Software: Visual Studio Code

import time
from typing import List

# [8. 字符串转换整数 (atoi)](https://leetcode-cn.com/problems/string-to-integer-atoi/)

# 正则匹配方法
# class Solution:
#     def myAtoi(self, str: str) -> int:
#         return max(min(int(*re.findall('^[\+\-]?\d+', str.lstrip())), 2 ** 31 - 1), -2 ** 31)


# 模拟
# class Solution:
#     def myAtoi(self, str: str) -> int:
#         n = len(str)
#         ans, zf = 0, 1
#         s = 0
#         while s < n and str[s] == ' ':
#             s += 1
#         if s < n and str[s] in "+-":
#             if str[s] == '-':
#                 zf = -1
#             s += 1
#         while s < n:
#             if ord('0') <= ord(str[s]) <= ord('9'):
#                 ans = ans * 10 + zf * (ord(str[s]) - ord('0'))
#             else:
#                 break
#             s += 1
#         if ans > 2147483647:
#             return 2147483647
#         elif ans < -2147483648:
#             return -2147483648
#         else:
#             return ans

# DFA
class DFA:
    def __init__(self) -> None:
        self.ans = 0
        self.cur = "start"
        self.sign = 1
        self.trans = {
            "start": {"space", "sign", "number"},
            "space": {"space", "sign", "number"},
            "sign": {"number"},
            "number": {"number"}
        }

    def get_char(self, s: str) -> bool:
        num = ord(s) - ord('0')
        if s == ' ':
            next = "space"
        elif s in "+-":
            next = "sign"
        elif 0 <= num <= 9:
            next = "number"
        else:
            return False
        if next not in self.trans[self.cur]:
            return False
        self.cur = next
        if s == '-':
            self.sign = -1
        elif 0 <= num <= 9:
            self.ans = self.ans * 10 + self.sign * num
            if self.ans > 2147483647:
                self.ans = 2147483647
                return False
            elif self.ans < -2147483648:
                self.ans = -2147483648
                return False
        return True


class Solution:
    def myAtoi(self, str: str) -> int:
        dfa = DFA()
        for s in str:
            if not dfa.get_char(s):
                return dfa.ans
        return dfa.ans


if __name__ == "__main__":
    start = time.perf_counter()

    s = Solution()
    s.myAtoi("  42a")

    end = time.perf_counter()
    print("Running Time: {:,.2f}μs".format((end - start) * 10 ** 6))
