# -*- coding: utf-8 -*-
# File    : 953.py
# Author  : MeteorDream
# Time    : 2022/05/17 16:41:46
# language: Python
# Software: Visual Studio Code

import time
from typing import List

# [953. 验证外星语词典](https://leetcode.cn/problems/verifying-an-alien-dictionary/)
# 难度: 简单

# 题解：[【验证外星语词典】简单模拟](https://leetcode.cn/problems/verifying-an-alien-dictionary/solution/yan-zheng-wai-xing-yu-ci-dian-by-meteord-xewi/)

class Solution:
    def isAlienSorted(self, words: List[str], order: str) -> bool:
        ord_map = {j: i for i, j in enumerate(order)}
        pre = ""
        for word in words:
            # 比较 pre 和 word
            for i, j in zip(pre, word):
                if i != j:
                    if ord_map[i] > ord_map[j]:
                        return False
                    else:
                        break
            else:
                if len(pre) > len(word):
                    return False
            pre = word
        return True

    TESTCASE = [(["hello","leetcode"], "hlabcdefgijkmnopqrstuvwxyz"),
                (["word","world","row"], "worldabcefghijkmnpqstuvxyz"),
                (["apple","app"], "abcdefghijklmnopqrstuvwxyz")]
    TESTANS = [True, False, False]

if __name__ == "__main__":
    start = time.perf_counter()

    s = Solution()
    for i, o in zip(s.TESTCASE, s.TESTANS):
        assert s.isAlienSorted(*i) == o

    end = time.perf_counter()
    print("Running Time: {:,.2f}μs".format((end - start) * 10 ** 6))
