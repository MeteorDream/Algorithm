# -*- coding: utf-8 -*-
# File    : 897. 递增顺序搜索树.py
# Author  : MeteorDream
# Time    : 2021/04/25 12:41:59
# language: Python
# Software: Visual Studio Code

import time, math, sys, os
from typing import List

class TreeNode(object):
    def __init__(self, val = 0, left = None, right = None):
        self.val = val
        self.left = left
        self.right = right

class Tree(object):
    def __init__(self, nums=None):
        self.root = None
        self.height = 0
        self.filecount = 1
        if nums:
            self.SetTree(nums)
        self.cur = self.root
    
    def SetTree(self, nums: List[int]):
        # 使用层序遍历的部分插入结点
        if not nums:
            return
        Queue = list()
        self.root = TreeNode(nums.pop(0))
        Queue.append(self.root)
        while nums:
            n = Queue.pop(0)
            nd = nums.pop(0)
            if nd:
                n.left = TreeNode(nd)
                Queue.append(n.left)
            if nums:
                nd = nums.pop(0)
                if nd:
                    n.right = TreeNode(nd)
                    Queue.append(n.right)
        # 计算二叉树高度并记录
        self.height = self.FindHeight(self.root)
    
    def FindHeight(self, root: TreeNode):
        # 递归计算二叉树高度
        if root:
            return max(self.FindHeight(root.left), self.FindHeight(root.right)) + 1
        else:
            return 0

class Solution:
    # def increasingBST(self, root: TreeNode) -> TreeNode:
    #     s = list()
    #     while root:
    #         s.append(root)
    #         root = root.left
    #     newroot = TreeNode()
    #     last = newroot
    #     while s:
    #         cur = s.pop()
    #         last.left = None
    #         last.right = cur
    #         last = cur
    #         if cur.right:
    #             cur = cur.right
    #             while cur:
    #                 s.append(cur)
    #                 cur = cur.left
    #     return newroot.right

    def increasingBST(self, root: TreeNode) -> TreeNode:
        # 利用线索在O(1)空间中序遍历二叉树
        self.cur = root
        dummy = TreeNode(0)
        Treeptr = dummy
        while self.cur:
            Treeptr.left = None
            Treeptr.right = self.nextnode()
            self.cur = self.cur.right
            Treeptr = Treeptr.right
        Treeptr.left = None
        Treeptr.right = None
        return dummy.right


    def nextnode(self) -> int:
        # 扁平化二叉搜索树迭代器，中序输出树节点
        while self.cur:
            # 存在左子树，则左子树的最右节点存放指向该节点的线索(指针)
            if self.cur.left:
                mostright = self.cur.left
                # 查找左子树最右节点
                while mostright.right and not mostright.right == self.cur:
                    mostright = mostright.right
                # 若查找结果不为空(回到根节点)，说明左子树最右节点已经存放了线索并且左子树已经遍历过，抹去该线索
                if mostright.right:
                    mostright.right = None
                # 若结果为空，存入线索，根节点左移(root = root->left)，重复查找
                else:
                    mostright.right = self.cur
                    self.cur = self.cur.left
                    continue
            # 根节点不存在左子树或左子树已经遍历过，输出该节点，再将根节点右移(root = root->right)
            return self.cur


if __name__ == "__main__":
    start = time.perf_counter()

    s = Solution()
    T = Tree([2,1,4,None,None,3])
    ans = s.increasingBST(T.root)

    end = time.perf_counter()
    print("Running Time: {:,.2f}μs".format((end - start) * 10 ** 6))
