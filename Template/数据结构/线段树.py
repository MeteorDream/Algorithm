# -*- coding: utf-8 -*-
# File    : 线段树.py
# Author  : MeteorDream
# Time    : 2022/06/06 10:44:52
# language: Python
# Software: Visual Studio Code

## 线段树模板（动态开点）
# 未通过测试，可能会有 bug

class TreeNode:
    def __init__(self, val=0, tag=0, left=None, right=None) -> None:
        """ 结点值，懒惰标记，左右孩子结点 """
        self.val = val
        self.tag = tag
        self.left = left
        self.right = right
    
class SegmentTree:
    """ 线段树 - 动态开点 (以区间和为模板，其余计算需要修改) """
    def __init__(self, left, right) -> None:
        self.root = TreeNode()
        self.left = left
        self.right = right
    
    def push_up(self, node: TreeNode):
        """ 向上合并 """
        node.val = node.left.val + node.right.val
    
    def update_tag(self, node, left, right, k):
        """ 更新懒惰标记 """
        node.tag += k
        node.val += k * (right - left + 1)
    
    def push_down(self, node, left, right):
        """ 下传懒惰标记 """
        mid = (left + right) >> 1
        self.update_tag(node.left, left, mid, node.tag)
        self.update_tag(node.right, mid + 1, right, node.tag)
        node.tag = 0
    
    def _update(self, node, cur_left, cur_right, left, right, c):
        """ 更新区间 [left, right], 当前区间 [cur_left, cur_right], 修改变化量 """
        if left <= cur_left and right >= cur_right:
            node.val += c * (cur_right - cur_left + 1)
            node.tag += c
        else:
            # 动态开点
            if not node.left:
                node.left = TreeNode()
            if not node.right:
                node.right = TreeNode()
            # 递归更新
            mid = (cur_left + cur_right) >> 1
            if node.tag != 0:
                self.push_down(node, cur_left, cur_right)
            if left <= mid:
                self._update(node.left, cur_left, mid, left, right, c)
            if mid < right:
                self._update(node.right, mid + 1, cur_right, left, right, c)
            self.push_up(node)
    
    def update(self, left, right, c):
        """ 更新区间 [left, right] 内的值，变化量 c """
        self._update(self.root, self.left, self.right, left, right, c)
    
    def _query(self, node, cur_left, cur_right, left, right):
        """ 区间查询 [left, right] 是查询区间，当前区间 [cur_left, cur_right] """
        if left <= cur_left and right >= cur_right:
            return node.val
        mid = (cur_left + cur_right) >> 1
        ans = 0
        self.push_down(node, cur_left, cur_right)
        if left <= mid:
            ans += self._query(node.left, cur_left, mid, left, right)
        if right > mid:
            ans += self._query(node.right, mid + 1, cur_right, left, right)
        return ans
    
    def query(self, left, right):
        """ 查询区间 [left, right] """
        return self._query(self.root, self.left, self.right, left, right)