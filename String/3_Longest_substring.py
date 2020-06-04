# -*- coding: utf-8 -*-
# LeetCode Question
# @Time    : 2020/2/12 23:08
# @Author  : MeteorDream
# @File    : 3_Longest_substring.py
# @Software: PyCharm

"""
LeetCode Question:
3 无重复字符的最长子串
给定一个字符串，请你找出其中不含有重复字符的 最长子串 的长度。

示例 1:
输入: "abcabcbb"
输出: 3
解释: 因为无重复字符的最长子串是 "abc"，所以其长度为 3。

示例 2:
输入: "bbbbb"
输出: 1
解释: 因为无重复字符的最长子串是 "b"，所以其长度为 1。

示例 3:
输入: "pwwkew"
输出: 3
解释: 因为无重复字符的最长子串是 "wke"，所以其长度为 3。

     请注意，你的答案必须是 子串 的长度，"pwke" 是一个子序列，不是子串。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/longest-substring-without-repeating-characters
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

"""

"""
思路：
1、遍历字符串的所有子串，逐个检查是否满足互异的要求，对满足要求的子串记录长度，最后遍历结束以后我们返回最大值即所求的答案。
2、在暴力解法中，出现了许多不必要的操作，例如示例1的"abcabcbb"，对前四个字符"abca"中已经出现了重复字符"a"，那么对应以"abca"开头的其他子串都是不符合要求的，为了查找不重复的子串，我们必须抛弃掉其中一个"a"，因为第一个"a"的各个连续长度的字符串已经查找过了，所以我们选择去掉第一个字符"a"，继续检查"bca"开头的子串，在接下来的子串"bcab"中，又出现了"b"，同理，我们放弃第一个"b"继续寻找更长的子串。在上面的描述中可以看到如果从头开始查找，一旦遇到重复的字符，我们可以利用这个重复信息排除掉包含重复的所有字符，这就导出了一种只需要一次遍历就能得到结果的方法。
微信图文：https://mp.weixin.qq.com/s?__biz=MzIyNDQ4MjU1NQ==&mid=2247483910&idx=1&sn=42653e5be0de1b38999cfca70ae8de5f&chksm=e80f0792df788e84cf062ce63974caa66fa1d4d038a436967ee27739c9f5a423577df15a7607&token=1894225558&lang=zh_CN#rd
"""


# Result Code

class Solution:
    def lengthOfLongestSubstring_1(self, s: str) -> int:
        """
        暴力解法
        超出时间限制
        """
        # 记录满足要求的最大子串的长度
        long = 0

        # 遍历所有子串并逐个检查
        for i in range(len(s)):
            for j in range(i + 1, len(s) + 1):
                if self.Check(s[i: j]):
                    # 若该子串是无重复子串，判断长度是否大于记录值，是则更新
                    if j - i > long:
                        long = j - i
        return long

    def Check(self, s: str) -> bool:
        # 检查字符串是否含有重复字符
        Set = []
        # 逐个取字符串中字符，如果序列中没有，则将该字符放入序列中
        for i in s:
            if i in Set:
                # 如果出现序列中已经存在的字符，说明有重复
                return False
            Set.append(i)
        return True

    def lengthOfLongestSubstring_2(self, s: str) -> int:
        """
        滑动窗口
        执行用时:56ms,在所有Python3提交中击败了94.03%的用户
        内存消耗:13.2MB,在所有Python3提交中击败了51.63%的用户
        """
        # 设定一个字典集(HashMap)记录字符对应下标
        Set = dict()

        # loc记录滑动窗口左边界， long记录当前最长无重复子串长度
        loc = 0
        long = 0

        # 使用滑动窗口进行一轮查找
        for i in range(len(s)):
            while s[i] in Set:
                # 发现重复字符，滑动窗口左边界向右移动
                del Set[s[loc]]
                loc += 1
            Set[s[i]] = i
            long = i - loc + 1 if i - loc + 1 > long else long

        return long

    def lengthOfLongestSubstring(self, s: str) -> int:
        """
        # 对字典集的操作进行优化，只增不删以提高执行速度(空间换时间)
        执行用时 :48 ms, 在所有 Python3 提交中击败了99.02%的用户
        内存消耗 :13.3 MB, 在所有 Python3 提交中击败了50.41%的用户
        """
        # 设定一个字典集(HashMap)记录字符对应下标
        Set = dict()

        # loc记录滑动窗口左边界， long记录当前最长无重复子串长度
        loc = 0
        long = 0

        # 使用滑动窗口进行一轮查找
        for i in range(len(s)):
            if s[i] in Set and Set[s[i]] >= loc:
                # 发现重复字符，滑动窗口左边界向右移动
                loc = Set[s[i]] + 1
            Set[s[i]] = i
            long = i - loc + 1 if i - loc + 1 > long else long
        return long


if __name__ == "__main__":
    # input
    Sol = Solution()
    s = ""
    print(s, Sol.lengthOfLongestSubstring(s))
    s = "c"
    print(s, Sol.lengthOfLongestSubstring(s))
    s = "abcabcbb"
    print(s, Sol.lengthOfLongestSubstring(s))
    s = "bbbbb"
    print(s, Sol.lengthOfLongestSubstring(s))
    s = "pwwkew"
    print(s, Sol.lengthOfLongestSubstring(s))
    s = "blnbizztdxqsxzdeavbjsqvvzpfuzdtdojeyidrlchfzhkfjfgtayqvxgcthfpkvypuiunvzvaaengpumkulbrkhtgoa"
    print(s, Sol.lengthOfLongestSubstring(s))
