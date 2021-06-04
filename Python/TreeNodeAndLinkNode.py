# -*- coding: utf-8 -*-
# File    : TreeNodeAndListNode.py
# Author  : MeteorDream
# Time    : 2021/05/27 18:55:11
# language: Python
# Software: Visual Studio Code

class TreeNode:
    def __init__(self, x, left=None, right=None):
        self.val = x
        self.left = left
        self.right = left


class ListNode:
    def __init__(self, x, next=None):
        self.val = x
        self.next = next
