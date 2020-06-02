# -*- coding: utf-8 -*-
# LeetCode Question
# @Time    : 2020/2/5 15:21
# @Author  : MeteorDream
# @File    : First.py
# @Software: PyCharm

"""
LeetCode Question:
1 两数之和
给定一个整数数组 nums 和一个目标值 target，请你在该数组中找出和为目标值的那 两个 整数，并返回他们的数组下标。

你可以假设每种输入只会对应一个答案。但是，你不能重复利用这个数组中同样的元素。

示例:

给定 nums = [2, 7, 11, 15], target = 9

因为 nums[0] + nums[1] = 2 + 7 = 9
所以返回 [0, 1]

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/two-sum
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
"""

import time

"""
思路：
1、第一种思路很容易就能想到，我们可以穷举所以可能的a, b，若存在满足条件的数组，那么我们返回对应的下标即可，设nums中有n个元素，那么a就有n种取值，相对应的b就有n-1种取值(b不能与a取同样的值)，所以这种方法对应的时间复杂度就是O(n * (n-1)) = O(n2)，空间复杂度为O(1)。
2、我们将条件进行变形：b = target - a ，一旦我们确定一个元素a，那么满足条件的b的值其实已经确定了，我们可以在数组中查找是否存在满足条件b即可确定答案了。由于a有n种可能，而在数组中查找b一般需要遍历整个数组，所以较第一种方法其实并没有什么实际区别。
3、前面的思路都属于暴力解法的范畴，那么我们如何改进呢？有一个点我们可以注意到，给定的数组并不是有序的，思考一下如果给定的数组是有序(假设是递增有序)的，那么能否有更简单的解法呢？答案是肯定的。例如，我们先取第一个数为a，即最小的数，那么我们可以先取数组中最大的数即最后一个数作为b，为什么呢？因为如果此时a + b < target，由于b已经是最大的数了，那么a与数组中任意的数之和不可能超过a + b，同样不可能等于目标值target了，此时我们就可以免去一轮扫描而直接排除掉a，同样的道理，若a + b > target，由于a已经是最小的值，所以数组中同样不存在满足条件的其他的a值，所以我们就可以直接排除掉b，以此类推。按照这种双指针的思路我们只需要一次遍历就可以完成查找了，即时间复杂度为O(n)，再加上排序消耗的时间开销，根据使用方法不同最优解为O(nlog2n)，故总的时间复杂度为O(n) + O(nlog2n) = O(nlog2n)。
4、排序需要的开销并不小，有没有可能更近一步将时间降低到O(n)呢？即一次或常数次遍历即可完成查找呢？首先遍历数组依次取每一个数作为a这个步骤是不可省略的，在上一个方法中我们使用数组排序的方法使得对b的查找时间降到了O(1)，但增加了排序的开销，有没有可能在未排序的数组中也能用O(1)的时间找到b呢？答案是Hash表，Hash表通过Hash函数将关键字映射到地址，我们只需对根据b = Target - a式计算结果使用Hash函数计算即可在O(1)时间中得到答案。在python中的dict(字典)数据类型就是一种Hash表，所以我们直接使用dict制作一个"反数组"的Hash表，即dict[Value] = i (数组是nums[i] = Value)。然后遍历对数组中的每一个值a计算对应b值并在Hash表中进行查找，运行时间复杂度为O(n)，空间复杂度为O(n) - Hash表的开销。在第二种方法中我们在Hash表还没创建时就开始了查找，这是因为在数组中符合条件的数值是成对出现的，对结果[a, b]，在查找a的时候Hash表中没有答案，但遍历达到b的时候就能在Hash表中的a，因此可以将第一种方法改进使得对原数组一次遍历就能找到答案，使得执行效率有所提高。
图文解析：https://mp.weixin.qq.com/s?__biz=MzIyNDQ4MjU1NQ==&mid=2247483876&idx=1&sn=bccce2ccf384b75da04ff677166ae021&chksm=e80f0470df788d669955c7d338553c0afbface4624641ece14b3283d6265b2ca7709e87b4dbf&token=225027562&lang=zh_CN#rd
"""


# Result Code
class Solution:
    def twoSum_1(self, nums, target):
        '''
        暴力解法(思路2)
        执行用时 :1036 ms, 在所有 Python3 提交中击败了29.99%的用户
        内存消耗 :14.1 MB, 在所有 Python3 提交中击败了77.95%的用户
        Running Time: 47.50μs
        '''
        n = -1
        for i in nums:
            n += 1
            if target - i in nums:
                for j in range(len(nums)):
                    if nums[j] == target - i and n != j:
                        break
                if j == len(nums) - 1 and nums[j] != target - i:
                    continue
                return [n, j]
        return []

    def twoSum_2(self, nums, target):
        '''
        hash表查找(思路4)
        执行用时 :1344 ms, 在所有 Python3 提交中击败了29.99%的用户
        内存消耗 :14.8 MB, 在所有 Python3 提交中击败了77.95%的用户
        Running Time: 47.90μs
        '''
        # 创建一个空的Hash表，并初始化，将值作为索引而数值下标作为值
        index = dict()
        for i, n in enumerate(nums):
            index[n] = i

        # 根据Hash表进行遍历查找
        for i, n in enumerate(nums):
            if target - n in index:
                if not index[target - n] == i:
	    # 此处判断主要是防止重复值导致的错误
	    # 如[1, 2, 3], Target = 4时输出[1, 1]
                    return [i, index[target - n]]
        return []

    def twoSum_3(self, nums, target):
        '''
        边创建Hash表边进行查找(对上一种解法的优化)
        执行用时 :52 ms, 在所有 Python3 提交中击败了91.83%的用户
        内存消耗 :14.2 MB, 在所有 Python3 提交中击败了70.08%的用户
        Running Time: 57.20μs
        '''
        # 创建一个空的Hash表
        index = dict()

        # 边创建Hash表边进行查找
        for i, n in enumerate(nums):
            if target - n in index and not index[target - n] == i:
                return [i, index[target - n]]
            index[n] = i
        return []

    def twoSum_4(self, nums, target):
        """
        双指针解法(思路3)
        执行用时 :76 ms, 在所有 Python3 提交中击败了49.81%的用户
        内存消耗 :14.6 MB, 在所有 Python3 提交中击败了13.41%的用户
        Running Time: 46.80μs
        """
        # 对nums数组进行排序，但因为需要返回对应下标，所以排序不能破坏原数组，
        # 将排序后的数组保存在临时数组
        temp = sorted(nums)

        # 遍历数组，移动首尾指针查找符合要求的数组（p-首指针，q-尾指针）
        # 题目说明了必定有解，否则可以根据p < q的条件判断是否越界，若不满该条件说明无解
        p, q = 0, len(temp) - 1
        while True:
            sum = temp[p] + temp[q]
            if sum < target:
                p += 1
            elif sum > target:
                q -= 1
            else: # sum == target 找到符合要求的值，结束查找
                break
        
        # 在原数组中查找结果对应的两个值的下标
        a, b = 0, 0
        for i in range(len(nums)):
            if nums[i] == temp[p] and a == 0:
                # 注意这里增加一个a == 0 的判断条件是防止temp[i] == temp[j]的情况导致的错误
                a = i
            elif nums[i] == temp[q]:
                b = i
        return [a, b]


if __name__ == "__main__":
    start = time.perf_counter()

    nums = [3, 2, 4]
    target = 6
    f = Solution()
    print(f.twoSum_4(nums, target))
    # [1, 2]

    nums = [2, 7, 11, 15]
    target = 9
    print(f.twoSum_4(nums, target))
    # [0, 1]

    end = time.perf_counter()
    print("Running Time: {:,.2f}μs".format((end - start) * 10 ** 6))
