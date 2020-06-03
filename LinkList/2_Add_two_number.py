# -*- coding: utf-8 -*-
# LeetCode Question
# @Time    : 2020/2/5 16:52
# @Author  : MeteorDream
# @File    : 2_Add_two_number.py
# @Software: PyCharm

"""
LeetCode Question:
2 两数相加
给出两个 非空 的链表用来表示两个非负的整数。其中，它们各自的位数是按照 逆序 的方式存储的，并且它们的每个节点只能存储 一位 数字。

如果，我们将这两个数相加起来，则会返回一个新的链表来表示它们的和。

您可以假设除了数字 0 之外，这两个数都不会以 0 开头。

示例：

输入：(2 -> 4 -> 3) + (5 -> 6 -> 4)
输出：7 -> 0 -> 8
原因：342 + 465 = 807

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/add-two-numbers
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
"""

import time

"""
思路：
1、由题目信息可以看到由于数字在链表中逆序存储并且是非负整数，那么两串链表表示的数字实际上已经按位对齐了，我们要做的就是将他们按位相加即可。

注意点：
1、进位的处理需要注意，不要遗漏；
2、进位在两个链表处理完以后还需要检测，针对的是如99 + 1 = 100等类似的情况；
3、注意不要丢失掉单链表的头指针，否则整个链表都将丢失。

优化小技巧：就是在较短的链表中补0，使得可以将所有内容放到一个循环里面，当然我们并不是单独计算链表长度再在短链表加上零结点，这么做太过多余了，我们只需要在链表结束以后，再对链表取值的时候给0就可以了

图文教程：https://mp.weixin.qq.com/s?__biz=MzIyNDQ4MjU1NQ==&mid=2247483887&idx=1&sn=e78ccc7ce1c3fe8d18e614ba76c1640f&chksm=e80f047bdf788d6d112def459810718c5c333455124dea3788705aafe53bae18989aa816c2de&token=1396876161&lang=zh_CN#rd
"""

# Result Code
# Definition for singly-linked list.
class ListNode:
    def __init__(self, x):
        self.val = x
        self.next = None

def CreatList(num):
    # 根据数组创建带头结点的单链表，返回头结点
    head = ListNode(None)
    p = head
    for n in num:
        p.next = ListNode(n)
        p = p.next
    return head

def TravelList(head):
    # 遍历输出单链表
    if not head:
        print("List is empty!")
        return None
    p = head
    print(head.val if head.val else "head", end="")
    while p.next:
        p = p.next
        print(" -> ", p.val, end="")
    print()

class Solution:
    def addTwoNumbers(self, l1, l2):
        """
        用竖式计算的方法按位相加，注意进位
        :param l1: ListNode
        :param l2: ListNode
        :return: ListNode
        执行用时 :64 ms, 在所有 Python3 提交中击败了94.61%的用户
        内存消耗 :13.3 MB, 在所有 Python3 提交中击败了55.65%的用户
        Running Time: 141.30μs
        """

        # 创建一个新的链表存放结果
        l3 = None   # 初始链表为空，头指针为None
        p, q = l1, l2
        t = 0  # 进位标识

        # 两个数按位相加
        while p and q:
            # 每位和等于两数对应位及进位(如果有)之和
            k = p.val + q.val + t

            # 检查本次计算是否需要进位
            # 如果需要进位则将进位标识设+1，并且和减10
            t = 0
            while k >= 10:
                k -= 10
                t += 1

            # 将结果存放到新建的结点并插入到新链表l3前面,更新l3头指针
            # 两加数向后推一位
            node = ListNode(k)
            node.next = l3
            l3 = node
            p = p.next
            q = q.next

        # p没处理完则继续用上述方法处理
        while p:
            k = p.val + t
            t = 0
            while k >= 10:
                k -= 10
                t += 1
            node = ListNode(k)
            node.next = l3
            l3 = node
            p = p.next

        # q没处理完则继续用上述方法处理
        while q:
            k = q.val + t
            t = 0
            while k >= 10:
                k -= 10
                t += 1
            node = ListNode(k)
            node.next = l3
            l3 = node
            q = q.next

        # 两链表都处理完了检查进位标识
        # 若进位标识不为0说明还要再补一位，例如99 + 1 = 100
        if t > 0:
            k = ListNode(t)
            k.next = l3
            l3 = k

        # 由于我们得到的结果链表数字是正序的，所以将链表逆序
        temp = l3
        l3 = None
        while temp:
            k = temp
            temp = temp.next
            k.next = l3
            l3 = k

        return l3

    def addTwoNumbers_2(self, l1, l2):
        """
        对上面的代码进行一些优化和改进
        :param l1: ListNode
        :param l2: ListNode
        :return: ListNode
        执行用时 :72 ms, 在所有 Python3 提交中击败了76.51%的用户
        内存消耗 :13 MB, 在所有 Python3 提交中击败了55.88%的用户
        Running Time: 204.20μs
        """

        # 创建一个带头结点的新的链表存放结果,l3是头指针
        l3 = ListNode(0)
        t = 0  # 进位标识
        p, q, r = l1, l2, l3  # r作为尾指针

        # 两个数按位相加
        while p or q or t:
            # 每位和等于两数对应位及进位(如果有)之和
            # 如果没有那么对应位用0替代
            k = (p.val if p else 0) + (q.val if q else 0) + t

            # 检查本次计算是否需要进位
            # 如果需要进位则将进位标识设+1，并且和减10
            t = 0
            while k >= 10:
                k -= 10
                t += 1

            # 在l3末尾创建一个存放本次结果的新节点，然后尾指针后移
            # 两加数的指针向后推一位，若已到链表末端则置0
            r.next = ListNode(k)
            r = r.next
            p, q = p.next if p else 0, q.next if q else 0

        return l3.next


if __name__ == "__main__":
    start = time.perf_counter()

    x = CreatList([2, 4, 3]).next
    TravelList(x)
    y = CreatList([5, 6, 4]).next
    TravelList(y)
    TravelList(Solution().addTwoNumbers_2(x, y))

    x = CreatList([9, 9, 9]).next
    TravelList(x)
    y = CreatList([1]).next
    TravelList(y)
    TravelList(Solution().addTwoNumbers_2(x, y))

    x = ListNode(5)
    TravelList(x)
    y = ListNode(5)
    TravelList(y)
    TravelList(Solution().addTwoNumbers_2(x, y))

    end = time.perf_counter()
    print("Running Time: {:,.2f}μs".format((end - start) * 10 ** 6))