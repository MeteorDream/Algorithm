# -*- coding: utf-8 -*-
# File    : 554_砖墙.py
# Author  : MeteorDream
# Time    : 2021/05/02 15:38:15
# language: Python
# Software: Visual Studio Code

import time
from typing import List
import heapq

"""
$\qquad$题解里面都是哈希表的解法，这里提供一个优先队列的解法，时间复杂度高于哈希表的解法但空间复杂度低于哈希表解法

## 基础解题思路

$\qquad$先看懂题目，首先题目给出一个数组，数组元素是砖墙每行的砖块长度，这里可以明确一点，每行的砖块数量是不确定的，但砖墙的宽度是一个统一的值。所以简单思路就是对砖墙的每列遍历数组查找是否为砖块与砖块直接的缝隙，进而找到穿过砖块最少的位置。
$\qquad$我们可以维护n个指针来确定每行的查找位置，但每列都要查找对于如`wall = [[1，1,99999], [99999，2], [1,99999,1]]`这种数据来说就很不合适了，因为砖墙宽度为100001但实际上我们遍历的100001次wall中超过$99\%$的位置都是没有缝隙的，对这些位置的遍历查找是低效无用的，于是我们自然而然的想到我们并不需要查找所有的位置，而是只需要查找有缝隙的位置就可以了。这样的查找要求我们每次都要在n个指针中找到最靠近左边的，所以很自然就会想到使用优先队列来保存n个指针。

## 优先队列求解步骤

1. 首先初始化优先队列，将每行至少有两个砖块的的起始位置保存到优先队列，同时需要记录下对应的行、列
2. 从优先队列中查找最小值，即最左边的位置，这对优先队列而言很容易
3. 在这最左边的位置查找缝隙数量，方法是从优先队列中将指针出队，直到优先队列中没有该位置的指针，当然出队的指针在使用后需要移动到对应行下一块砖的右边，再重新入队，当然，若是到了砖墙右边界就无需再次入队了
4. 重复执行2,3两步查找所有存在缝隙的位置，直到优先队列为空结束查找

## python代码

还有一些细节没说清楚，具体的看看代码吧~

```python []
class Solution:
    def leastBricks(self, wall: List[List[int]]) -> int:
        n = len(wall)

        # heap内存放的格式为(前缀和、行、列)
        heap = list()
        ans = n

        for i in range(n):
            if len(wall[i]) > 1:
                heapq.heappush(heap, [wall[i][0], i, 1])

        while heap:
            # 最左边的位置
            count = 0
            cur = heap[0][0]
            while heap and heap[0][0] == cur:
                count += 1
                tmp = heapq.heappop(heap)
                if tmp[2] + 1 < len(wall[tmp[1]]):
                    tmp[0] += wall[tmp[1]][tmp[2]]
                    tmp[2] += 1
                    heapq.heappush(heap, tmp)
            if n - count < ans:
                ans = n - count

        return ans
```

## 复杂度分析

$\qquad$时间复杂度$O(nmlog(nm))$, 在优先队列中，wall中每个元素都入队出队一次，平均时间是O(nmlog(nm))

$\qquad$空间复杂度O(n)，优先队列中存放n个指针

## 后记

$\qquad$更近一步的，我们不同步计算每行的缝隙，而是使用哈希表直接统计缝隙位置，就能在$O(nm)$时间内完成计算，当然哈希表的空间是$O(nm)$是比使用优先队列要大一些的。优秀题解很多，这里就不赘述了。

```python []
class Solution:
    def leastBricks(self, wall: List[List[int]]) -> int:
        n = len(wall)
        d = dict()

        for i in wall:
            s, count = len(i), 0
            for j in range(s - 1):
                count += i[j]
                if count in d:
                    d[count] += 1
                else:
                    d[count] = 1

        ans = n
        for i in d.keys():
            if n - d[i] < ans:
                ans = n - d[i]
        return ans
```
"""


class Solution:
    # def leastBricks(self, wall: List[List[int]]) -> int:
    #     n = len(wall)

    #     # heap内存放的格式为(前缀和、行、列)
    #     heap = list()
    #     ans = n

    #     for i in range(n):
    #         if len(wall[i]) > 1:
    #             heapq.heappush(heap, [wall[i][0], i, 1])

    #     while heap:
    #         # 最左边的位置
    #         count = 0
    #         cur = heap[0][0]
    #         while heap and heap[0][0] == cur:
    #             count += 1
    #             tmp = heapq.heappop(heap)
    #             if tmp[2] + 1 < len(wall[tmp[1]]):
    #                 tmp[0] += wall[tmp[1]][tmp[2]]
    #                 tmp[2] += 1
    #                 heapq.heappush(heap, tmp)
    #         if n - count < ans:
    #             ans = n - count

    #     return ans

    def leastBricks(self, wall: List[List[int]]) -> int:
        n = len(wall)
        d = dict()

        for i in wall:
            s, count = len(i), 0
            for j in range(s - 1):
                count += i[j]
                if count in d:
                    d[count] += 1
                else:
                    d[count] = 1

        ans = n
        for i in d.keys():
            if n - d[i] < ans:
                ans = n - d[i]
        return ans


if __name__ == "__main__":
    start = time.perf_counter()

    s = Solution()
    wall = [[1, 2, 2, 1], [3, 1, 2], [1, 3, 2],
            [2, 4], [3, 1, 2], [1, 3, 1, 1]]
    print(s.leastBricks(wall))
    # 2

    wall = [[1], [1], [1]]
    print(s.leastBricks(wall))
    # 3

    print(divmod(-1, 10))

    end = time.perf_counter()
    print("Running Time: {:,.2f}μs".format((end - start) * 10 ** 6))
