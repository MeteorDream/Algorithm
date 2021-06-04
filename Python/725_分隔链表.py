# -*- coding: utf-8 -*-
# File    : 725_分隔链表.py
# Author  : MeteorDream
# Time    : 2021/05/10 20:02:01
# language: Python
# Software: Visual Studio Code

import time
from typing import List
from ListNode import *


class Solution:
    def splitListToParts(self, root: ListNode, k: int) -> List[ListNode]:
        ans = [None for i in range(k)]
        ans[0] = root
        # 初始化指针数组，按顺序指向前k个结点
        for i in range(1, k):
            if ans[i - 1]:
                ans[i] = ans[i - 1].next
        # 移动指针，数组下标为 i 的指针每次前进 i + 1
        while ans[k - 1]:
            for i in range(k-1):
                ans[k - 1] = ans[k - 1].next
                if not ans[k - 1]:
                    break
                for j in range(i, k - 1):
                    ans[j] = ans[j].next
            if ans[k - 1]:
                ans[k - 1] = ans[k - 1].next
        # 此时链表已经由 k - 1 个指针划分为 k 段，数组中的指针均指向各段最后一个结点
        # 将链表分割成 k 段，并将数组指针设为各段的头结点, 即上一段最后一个结点的next指针指向的结点
        for i in range(k - 1, 0, -1):
            if ans[i - 1]:
                ans[i] = ans[i - 1].next
                ans[i - 1].next = None
        # 第一段的头结点为 root
        ans[0] = root
        return ans


if __name__ == "__main__":
    start = time.perf_counter()

    end = time.perf_counter()
    print("Running Time: {:,.2f}μs".format((end - start) * 10 ** 6))
