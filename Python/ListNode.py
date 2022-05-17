# -*- coding: utf-8 -*-
# File    : ListNode.py
# Author  : MeteorDream
# Time    : 2021/06/04 17:16:30
# language: Python
# Software: Visual Studio Code

from typing import Iterable

class ListNode:
    """ You can create LinkList like ListNode.CreateList(range(10), False) """
    def __init__(self, x=0, next=None):
        self.val = x
        self.next = next

    def __str__(self):
        if self.next is not None:
            return f"{self.val} -> {str(self.next)}"
        return str(self.val)

    def __format__(self, __format_spec: str) -> str:
        return self.val.__format__(__format_spec)

    def __repr__(self):
        return self.__str__()

    @staticmethod
    def CreateList(nums: Iterable, head: bool=True):
        """ Create LinkList according to nums with head node """
        dummy = ListNode()
        pre = dummy
        for v in nums:
            pre.next = ListNode(v)
            pre = pre.next
        return dummy if head else dummy.next

if __name__ == '__main__':
    root = ListNode.CreateList(range(10), False)
    print(root)
