---
title: LeetCode 162 寻找峰值
date: 2021-06-16 11:23:11
categories:
- [LeetCode]
tags: [LeetCode,二分查找]
---

## 题目

[162. 寻找峰值]([题目链接](https://leetcode-cn.com/problems/find-peak-element/))

难度: 中等

<!--more-->

峰值元素是指其值大于左右相邻值的元素。

给你一个输入数组 `nums`，找到峰值元素并返回其索引。数组可能包含多个峰值，在这种情况下，返回 **任何一个峰值** 所在位置即可。

你可以假设 `nums[-1] = nums[n] = -∞` 。

$\quad$

示例 1：

> **输入：**nums = [1,2,3,1]
> **输出：**2
> **解释：**3 是峰值元素，你的函数应该返回其索引 2。

示例 2：

> **输入：**nums = [1,2,1,3,5,6,4]
> **输出：**1 或 5
> **解释：**你的函数可以返回索引 1，其峰值元素为 2；
> $\quad \qquad$ 或者返回索引 5， 其峰值元素为 6。

$\quad$

提示：

- $1 <= nums.length <= 1000$
- $-2^{31} <= nums[i] <= 2^{31} - 1$
- 对于所有有效的 `i` 都有 $nums[i] != nums[i + 1]$

**进阶：**你可以实现时间复杂度为 $O(logN)$ 的解决方案吗？

---

## 解析

这题其实是 [852. 山脉数组的峰顶索引](https://leetcode-cn.com/problems/peak-index-in-a-mountain-array/)的进阶版，主要有两点不同之处

1. 是不再是山脉数组，简而言之山脉数组就是可以划分为先单调递增再单调递减的两段。而本题的数组却不是规律的只有两段的数组，但本题却还是能按照山脉数组的方法进行二分处理，后面会详细证明
2. 是数组左右两端被认为是 $- \infty$，这挺有意思的，可以由两种理解方式
   - 数组首尾可以认为是单调递增和单调递减的
   - 若第二个元素小于第一个元素，那么第一个元素就可以认为是峰值，尾元素同理
   - 这也正好对应了边界条件处理的两种方法，基于语言特性，后面的代码示例中，python使用了第一种方法处理(python中索引-1表示list中最后一个元素，所以只需在末尾添加一个负无穷即可兼顾首尾两侧的边界情况)而C++和java使用了第二种方法处理(而数组若要在首元素位置插入元素需要整体后移一位，相较而言还是单独处理边界较好)

---

## 方法一、顺序搜索

最简单的方法自然是遍历数组顺序搜索，逐一判断每个位置是否是峰值，加上本题数据量很小，数组长度最大仅为 $1e4$ ，如果不管进阶的要求的话 $O(n)$ 与 $O(logn)$ 的效率其实相差不大

```python
# Code language: Python
class Solution:
    def findPeakElement(self, nums: List[int]) -> int:
        # 简单顺序搜索
        nums.append(-float("inf"))
        for i in range(len(nums)):
            if nums[i - 1] < nums[i] > nums[i + 1]:
                return i
```

```java
/* Code language: Java */
class Solution {
    public int findPeakElement(int[] nums) {
        int n = nums.length;
        if (n == 1 || nums[0] > nums[1])
            return 0;
        for (int i = 1; i < n - 1; ++i)
            if (nums[i] > nums[i - 1] && nums[i] > nums[i + 1])
                return i;
        return n - 1;
    }
}
```

```cpp
/* Code language: C++ */
class Solution {
public:
    int findPeakElement(vector<int>& nums) {
        int n = nums.size();
        if (n <= 1 || nums[0] > nums[1])
            return 0;
        for (int i = 1; i < n - 1; ++i)
            if (nums[i] > nums[i + 1] && nums[i] > nums[i - 1])
                return i;
        return n - 1;
    }
};
```

- 时间复杂度: $O(n)$
- 空间复杂度: $O(1)$

---

## 方法二、二分搜索

进阶要求时间复杂度 $O(logn)$，可以考虑使用二分搜索，我们假设你已经学会了[山脉数组的二分方式](https://leetcode-cn.com/problems/peak-index-in-a-mountain-array/solution/852-shan-mai-shu-zu-de-feng-ding-suo-shu-f91g/)。

但问题来了：这题的数组并不是有序的，甚至也不是山脉数组的局部有序，要如何使用二分求解呢？

注意到，题目有两个小小的隐藏提示

1. 数组两端认为是负无穷，而数组的值是确定的整型数，必然不会是正无穷，这说明数组中必定能找到一个峰值
   - 证明很简单：左右两端都是负无穷，而数组中的数都大于负无穷，那么左端到数组是单调递增的，数组到右端是单调递减的，所以峰值必然存在
2. 若峰值不止一个，我们随意找到一个就行，由此我们想到，因为数组中相邻两个数必然不同，我们可以将数组划分为若干个“山脉数组”，只有找到其中一个“山脉数组”的峰值即可，我们证明这种想法的可行性
   - 换而言之，这种方法不会在有解的情况下查找不到解，先回顾“山脉数组”的二分解法：
     - 若中点递增，说明极值点在右方
     - 若中点递减，说明极值点在左方
   - 考虑本题数组
     - 若中点递增，则中点与右端点都小于中点的下一个数，与1中证明同理，可以得出右半段必然存在峰值
     - 若中点递减，则左端点与中点都小于中点的前一个数，与1中证明同理，可以得出左半段必然存在峰值

总的来说，我们可以认为，数组中有且只有一个极大值，那么这题就转换为了[山脉数组的二分方式](https://leetcode-cn.com/problems/peak-index-in-a-mountain-array/solution/852-shan-mai-shu-zu-de-feng-ding-suo-shu-f91g/)，只需再加上边界的处理，就能得到本题的二分解法。

```python
# Code language: Python
class Solution:
    def findPeakElement(self, nums: List[int]) -> int:
        # 二分查找
        nums.append(-float("inf"))
        lo, hi = 0, len(nums) - 1
        while lo < hi:
            mid = (lo + hi) // 2
            if nums[mid] < nums[mid + 1]:
                lo = mid + 1
            else:
                hi = mid
        return lo
```

```java
/* Code language: Java */
class Solution {
    public int findPeakElement(int[] nums) {
        int n = nums.length;
        if (n == 1 || nums[0] > nums[1])
            return 0;
        if (nums[n - 1] > nums[n - 2])
            return n - 1;
        int left = 1, right = n - 2;
        while (left < right) {
            int mid = left + (right - left) / 2;
            if (nums[mid] > nums[mid + 1])
                right = mid;
            else
                left = mid + 1;
        }
        return left;
    }
}
```

```cpp
/* Code language: C++ */
class Solution {
public:
    int findPeakElement(vector<int>& nums) {
        int n = nums.size();
        if (n <= 1 || nums[0] > nums[1])
            return 0;
        if (nums[n - 1] > nums[n - 2])
            return n - 1;
        int lo = 1, hi = n - 1;
        while (lo < hi) {
            int mid = lo + (hi - lo >> 1);
            if (nums[mid] > nums[mid + 1])
                hi = mid;
            else
                lo = mid + 1;
        }
        return lo;
    }
};
```

- 时间复杂度: $O(logn)$
- 空间复杂度: $O(1)$
