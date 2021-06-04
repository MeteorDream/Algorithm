# -*- coding: utf-8 -*-
# File    : 66_plus_one.py
# Author  : MeteorDream
# Time    : 2021/05/03 17:22:22
# language: Python
# Software: Visual Studio Code

import time
from typing import List

"""
[66. 加一](https://leetcode-cn.com/problems/plus-one)

难度: 简单

给定一个由 **整数** 组成的 **非空** 数组所表示的非负整数，在该数的基础上加一。

最高位数字存放在数组的首位， 数组中每个元素只存储**单个**数字。

你可以假设除了整数 0 之外，这个整数不会以零开头。

$\quad$

示例 1：

>> 输入：digits = [1,2,3]
>> 输出：[1,2,4]
>> 解释：输入数组表示数字 123。

示例 2：

>> 输入：digits = [4,3,2,1]
>> 输出：[4,3,2,2]
>> 解释：输入数组表示数字 4321。

示例 3：

>> 输入：digits = [0]
>> 输出：[1]

提示：

- 1 <= digits.length <= 100
- 0 <= digits[i] <= 9
"""


class Solution:
    def plusOne(self, digits: List[int]) -> List[int]:
        n = len(digits) - 1
        t = 1  # 进位标志
        for i in range(n, -1, -1):
            digits[i] += t
            if digits[i] > 9:
                digits[i] -= 10
                t = 1
            else:
                return digits
        # 特殊处理 9, 99, 999 等情况
        if t == 1:
            return [1] + digits


if __name__ == "__main__":
    start = time.perf_counter()

    s = Solution()

    digits = [1, 2, 3]
    print("输入:", digits)
    print("理论输出:", [1, 2, 4])
    print("实际输出:", s.plusOne(digits), '\n')

    digits = [9, 9, 9]
    print("输入:", digits)
    print("理论输出:", [1, 0, 0, 0])
    print("实际输出:", s.plusOne(digits), '\n')

    end = time.perf_counter()
    print("Running Time: {:,.2f}μs".format((end - start) * 10 ** 6))
