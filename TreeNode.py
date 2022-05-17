# -*- coding: utf-8 -*-
# File    : TreeNode.py
# Author  : MeteorDream
# Time    : 2021/05/27 18:55:11
# language: Python
# Software: Visual Studio Code

from typing import List


class TreeNode:
    def __init__(self, x, left=None, right=None):
        self.val = x
        self.left = left
        self.right = left


class Tree(object):
    def __init__(self, nums=None):
        self.root = None
        self.height = 0
        self.filecount = 1
        if nums:
            self.SetTree(nums)
        self.PrintPoint = self.root

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

    def nextnode(self) -> int:
        # 扁平化二叉搜索树迭代器，中序输出树节点
        while self.PrintPoint:
            # 存在左子树，则左子树的最右节点存放指向该节点的线索(指针)
            if self.PrintPoint.left:
                mostright = self.PrintPoint.left
                # 查找左子树最右节点
                while mostright.right and not mostright.right == self.PrintPoint:
                    mostright = mostright.right
                # 若查找结果不为空(回到根节点)，说明左子树最右节点已经存放了线索并且左子树已经遍历过，抹去该线索
                if mostright.right:
                    mostright.right = None
                # 若结果为空，存入线索，根节点左移(root = root->left)，重复查找
                else:
                    mostright.right = self.PrintPoint
                    self.PrintPoint = self.PrintPoint.left
                    continue
            # 根节点不存在左子树或左子树已经遍历过，输出该节点，再将根节点右移(root = root->right)
            ans = self.PrintPoint.val
            self.PrintPoint = self.PrintPoint.right
            return ans

    def PrintMidTree(self):
        # 利用线索在O(1)空间中序遍历二叉树(不改动树本身)
        print("中序遍历: ", end="")
        self.PrintPoint = self.root
        while self.PrintPoint:
            print(self.nextnode(), end=" ")
        print()

    def PrintPreTree(self):
        # 递归前序遍历二叉树
        def PreVisit(root: TreeNode):
            if root:
                print(root.val, end=" ")
                PreVisit(root.left)
                PreVisit(root.right)

        print("前序遍历: ", end="")
        PreVisit(self.root)
        print()

    def PrintPostTree(self):
        # 递归后序遍历二叉树
        def PostVisit(root: TreeNode):
            if root:
                PostVisit(root.left)
                PostVisit(root.right)
                print(root.val, end=" ")

        print("后序遍历: ", end="")
        PostVisit(self.root)
        print()

    def PrintLevelTree(self):
        # 层序遍历二叉树
        Queue = list()
        print("层序遍历: ", end="")
        if self.root:
            Queue.append(self.root)
        while Queue:
            cur = Queue.pop(0)
            print(cur.val, end=" ")
            if cur.left:
                Queue.append(cur.left)
            if cur.right:
                Queue.append(cur.right)
        print()
