# -*- coding: utf-8 -*-
# File    : 65_有效数字.py
# Author  : MeteorDream
# Time    : 2021/05/30 20:06:34
# language: Python
# Software: Visual Studio Code

import time
from typing import List

# [65. 有效数字](https://leetcode-cn.com/problems/valid-number/)


# class Solution:
#     # 正则表达式匹配
#     def isNumber(self, s: str) -> bool:
#         if re.match(r"^([+-]?(\d+(\.\d*)?|(\.\d+)))([eE][+-]?\d+)?$", s):
#             return True
#         return False

# DFA(有限状态自动机)
# 有效数字组成： (整数 | 小数) (e 指数整数)
# 整数 = 符号 + 数字
# 小数 = 符号 + 数字 + 小数点 + 数字 (小数点细分为前面有数字的小数点和前面没数字的小数点)
#
# 0起始状态：符号、整数数字、前面无数字的小数点
# 1符号：整数数字、前面无数字的小数点
# 2整数数字：整数数字、前面有数字的小数点、e/E、终止态
# 3前面无数字的小数点：小数数字
# 4前面有数字的小数点：小数数字、e/E、终止态
# 5小数数字：小数数字、e/E、终止态
# 6 e/E：指数符号、指数数字
# 7指数符号：指数数字
# 8指数数字：指数数字、终止态
# 9终止态：-1错误态
class DFA:
    def __init__(self) -> None:
        self.state = 0
        self.end = [2, 4, 5, 8]

    def get_char(self, s: str) -> bool:
        num = ord(s) - ord('0')
        if s in "+-":
            if self.state == 0:
                self.state = 1  # 符号
            elif self.state == 6:
                self.state = 7  # 指数符号
            else:
                return False  # 错误态
        elif 0 <= num <= 9:
            if self.state < 3:
                self.state = 2  # 整数数字
            elif self.state < 6:
                self.state = 5  # 小数数字
            elif self.state < 9:
                self.state = 8  # 指数数字
            else:
                return False  # 错误态
        elif s in "eE":
            if self.state == 2 or self.state == 4 or self.state == 5:
                self.state = 6
            else:
                return False
        elif s == '.':
            if self.state < 2:
                self.state = 3  # 前面无数字的小数点
            elif self.state == 2:
                self.state = 4  # 前面无数字的小数点
            else:
                return False
        else:
            return False
        return True


class Solution:
    def isNumber(self, s: str) -> bool:
        dfa = DFA()
        for ss in s:
            if not dfa.get_char(ss):
                return False
        return dfa.state in dfa.end


if __name__ == "__main__":
    start = time.perf_counter()

    end = time.perf_counter()
    print("Running Time: {:,.2f}μs".format((end - start) * 10 ** 6))
