# -*- coding: utf-8 -*-
# File    : 105_从前序与中序遍历序列构造二叉树.py
# Author  : MeteorDream
# Time    : 2021/05/28 11:36:40
# language: Python
# Software: Visual Studio Code

import time
import math
import sys
import os
from typing import List

from functools import cache  # 装饰器，用于缓存递归函数中间值
from TreeNodeAndLinkNode import *  # 二叉树结点和链表结点

# [105. 从前序与中序遍历序列构造二叉树](https://leetcode-cn.com/problems/construct-binary-tree-from-preorder-and-inorder-traversal/)

# 递归方法
# class Solution:
#     def __init__(self):
#         self.ind = dict()

#     def buildTree(self, preorder: List[int], inorder: List[int]) -> TreeNode:
#         n = len(preorder)
#         for i in range(n):
#             self.ind[inorder[i]] = i
#         return self.build(preorder, 0, n - 1, inorder, 0, n - 1)

#     # 根据 preorder [i,j] 范围内 和 inorder [x,y] 范围内 的元素建树
#     def build(self, preorder, i, j, inorder, x, y):
#         # 若 i > j 则树空
#         if i > j:
#             return None
#         # 若 i == j 则该树只有一个根结点
#         elif i == j:
#             return TreeNode(preorder[i])
#         # 前序 preorder 的第一个值是根结点的值
#         val = preorder[i]
#         root = TreeNode(val)
#         # 在中序 inorder 查找根结点所在值
#         z = self.ind[val]
#         # 递归创建左子树和右子树
#         root.left = self.build(preorder, i + 1, i + z - x, inorder, x, z - 1)
#         root.right = self.build(preorder, i + z - x + 1, j, inorder, z + 1, y)
#         return root

# 迭代方法
class Solution:
    def buildTree(self, preorder: List[int], inorder: List[int]) -> TreeNode:
        n = len(preorder)
        if n == 0:
            return None
        root = TreeNode(preorder[0])
        st = [root]
        i = 0
        for j in range(1, n):
            tmp = st[-1]
            if tmp.val == inorder[i]:
                while st and st[-1].val == inorder[i]:
                    tmp = st.pop()
                    i += 1
                tmp.right = TreeNode(preorder[j])
                st.append(tmp.right)
            else:
                tmp.left = TreeNode(preorder[j])
                st.append(tmp.left)
        return root


if __name__ == "__main__":
    start = time.perf_counter()

    end = time.perf_counter()
    print("Running Time: {:,.2f}μs".format((end - start) * 10 ** 6))
