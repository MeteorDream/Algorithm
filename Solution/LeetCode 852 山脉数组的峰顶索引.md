---
title: LeetCode 852 山脉数组的峰顶索引
date: 2021-06-15 14:32:28
categories:
- [LeetCode]
tags: [LeetCode,二分查找]
---

## 题目

[852. 山脉数组的峰顶索引]([题目链接](https://leetcode-cn.com/problems/peak-index-in-a-mountain-array/))

难度: 简单

<!--more-->

符合下列属性的数组 arr 称为 **山脉数组** ：

- `arr.length >= 3`
- 存在 `i`（`0 < i < arr.length - 1`）使得：
  - `arr[0] < arr[1] < ... arr[i-1] < arr[i]`
  - `arr[i] > arr[i+1] > ... > arr[arr.length - 1]`
给你由整数组成的山脉数组 `arr` ，返回任何满足 `arr[0] < arr[1] < ... arr[i - 1] < arr[i] > arr[i + 1] > ... > arr[arr.length - 1]` 的下标 i 。

示例 1：

> **输入：**arr = [0,1,0]
> **输出：**1

示例 2：

> **输入：**arr = [0,2,1,0]
> **输出：**1

示例 3：

> **输入：**arr = [0,10,5,2]
> **输出：**1

示例 4：

> **输入：**arr = [3,4,5,1]
> **输出：**2

示例 5：

> **输入：**arr = [24,69,100,99,79,78,67,36,26,19]
> **输出：**2

**提示：**

- $3 <= arr.length <= 10^4$
- $0 <= arr[i] <= 10^6$
- 题目数据保证 arr 是一个山脉数组

**进阶：**

很容易想到时间复杂度 `O(n)` 的解决方案，你可以设计一个 `O(log(n))` 的解决方案吗？

## 解析

题目已经保证所给数组是山脉数组，即前一段单调递增，后一段单调递减，所以我们需要查找的就是数组中最大的那个值，也可以说是极值点

## 方法一、顺序查找

最简单的办法就是我们一个一个数的由前向后查找，当发现从某一个数开始数值变小了，那就是我们要查找的值了

```python
# Code language: Python
class Solution:
    def peakIndexInMountainArray(self, arr: List[int]) -> int:
        # 顺序查找最大值
        for i in range(1, len(arr) - 1):
            if arr[i] > arr[i + 1]:
                return i
```

```java
/* Code language: Java */
class Solution {
    public int peakIndexInMountainArray(int[] arr) {
        int n = arr.length - 1;
        for (int i = 1; i < n; ++i) {
            if (arr[i] > arr[i + 1])
                return i;
        }
        return n;
    }
}
```

```cpp
/* Code language: C++ */
class Solution {
public:
    int peakIndexInMountainArray(vector<int>& arr) {
        int n = arr.size() - 1;
        for (int i = 1; i < n; ++i) {
            if (arr[i] > arr[i + 1])
                return i;
        }
        return n;
    }
};
```

- 时间复杂度: $O(n)$
- 空间复杂度: $O(1)$

---

## 方法二、二分查找

题目进阶要求 $O(logn)$ 的时间复杂度，又联系到数组是局部有序的，很容易就能想到要使用二分查找。  
因为待查找的是极大值点，所以我们可以根据mid中点的情况来判断极大值的情况

- 若中点值比右方值大，说明极值点在中点左侧(包括中点)
- 若中点值比右方小，说明极值点在中点右侧(不包括中点)

概括的说就是，查找第一个 **arr的值比下一个位置的arr的值大** 的下标,也就是类似lower_bound() 和 bisect_left()

```python
# Code language: Python
class Solution:
    def peakIndexInMountainArray(self, arr: List[int]) -> int:
        # 二分查找最大值
        left, right = 0, len(arr) - 1
        while left < right:
            mid = (left + right) // 2
            if arr[mid] > arr[mid + 1]:
                right = mid
            else:
                left = mid + 1
        return left
```

```java
/* Code language: Java */
class Solution {
    public int peakIndexInMountainArray(int[] arr) {
        int left = 1, right = arr.length - 1;
        while (left < right) {
            int mid = left + (right - left) / 2;
            if (arr[mid] > arr[mid + 1])
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
    int peakIndexInMountainArray(vector<int>& arr) {
        int left = 1, right = arr.size() - 1;
        while (left < right) {
            int mid = left + (right - left) / 2;
            if (arr[mid] > arr[mid + 1])
                right = mid;
            else
                left = mid + 1;
        }
        return left;
    }
};
```

- 时间复杂度: $O(logn)$
- 空间复杂度: $O(1)$

---

## 方法三、三分查找

对于查找极值点，也可以采用三分的方法，即用两个点将区间三等分，通过比较两个三等分点可以排除掉左区间或右区间

- 若左等分点大于右等分点，有两种情况：极大值点在左区间或中区间，所以可以排除右区间
- 若左等分点小于右等分点，有两种情况：极大值点在中区间或右区间，所以可以排除左区间

```python
# Code language: Python
class Solution:
    def peakIndexInMountainArray(self, arr: List[int]) -> int:
        # 三分查找最大值
        left, right = 0, len(arr) - 1
        while left < right:
            m = (right - left) // 3
            m1 = left + m
            m2 = right - m
            if arr[m1] > arr[m2]:
                right = m2 - 1
            else:
                left = m1 + 1
        return left
```

```java
/* Code language: Java */
class Solution {
    public int peakIndexInMountainArray(int[] arr) {
        int left = 1, right = arr.length - 1;
        while (left < right) {
            int m = (right - left) / 3;
            int m1 = left + m, m2 = right - m;
            if (arr[m1] > arr[m2])
                right = m2 - 1;
            else
                left = m1 + 1;
        }
        return left;
    }
}
```

```cpp
/* Code language: C++ */
class Solution {
public:
    int peakIndexInMountainArray(vector<int>& arr) {
        int left = 1, right = arr.size() - 1;
        while (left < right) {
            int m = (right - left) / 3;
            int m1 = left + m, m2 = right - m;
            if (arr[m1] > arr[m2])
                right = m2 - 1;
            else
                left = m1 + 1;
        }
        return left;
    }
};
```

- 时间复杂度: $O(log_3n)$
- 空间复杂度: $O(1)$

---

看起来三分查找每次只能排除 $\dfrac{1}{3}$ 还不如二分查找每次排除 $\dfrac{1}{2}$  
这是因为我们并没有充分利用三分的两个三等分点单调方面的性质，我们考虑如下三种情况：

- 极大值点在左区间，那么两个三等分点都是单调递减的
- 极大值点在右区间，那么两个三等分点都是单调递增的
- 极大值点在中间区间，那么第一个三等分点是单调递增的，第二个三等分点是单调递减的

由此，我们可以得到每次三分都能排除掉 $\dfrac{2}{3}$ 的做法

```python
# Code language: Python
class Solution:
    def peakIndexInMountainArray(self, arr: List[int]) -> int:
        # 三分查找最大值
        left, right = 1, len(arr) - 2
        while left < right:
            m = (right - left) // 3
            m1 = left + m
            m2 = right - m
            if arr[m1] > arr[m1 + 1]:
                right = m1
            elif arr[m2] < arr[m2 + 1]:
                left = m2 + 1
            else:
                left = m1 + 1
                right = m2
        return left
```

```java
/* Code language: Java */
class Solution {
    public int peakIndexInMountainArray(int[] arr) {
        int left = 1, right = arr.length - 2;
        while (left < right) {
            int m = (right - left) / 3;
            int m1 = left + m, m2 = right - m;
            if (arr[m1] > arr[m1 + 1])
                right = m1;
            else if (arr[m2] < arr[m2 + 1])
                left = m2 + 1;
            else {
                left = m1 + 1;
                right = m2;
            }
        }
        return left;
    }
}
```

```cpp
/* Code language: C++ */
class Solution {
public:
    int peakIndexInMountainArray(vector<int>& arr) {
        int left = 1, right = arr.size() - 2;
        while (left < right) {
            int m = (right - left) / 3;
            int m1 = left + m, m2 = right - m;
            if (arr[m1] > arr[m1 + 1])
                right = m1;
            else if (arr[m2] < arr[m2 + 1])
                left = m2 + 1;
            else {
                left = m1 + 1;
                right = m2;
            }
        }
        return left;
    }
};
```

- 时间复杂度: $O(log_3n)$
- 空间复杂度: $O(1)$

---

### 关于时间复杂度计算

有提问为什么每次排除 $\dfrac{1}{3}$ 区间还是 $O(log_3n)$ 的时间复杂度，下面给出数学证明

先看看二分：

二分每次排除 $\dfrac{1}{2}$ 区间, 假设经过 m 次排除，只剩下一个值，即最终答案，那么有：

$$
(\dfrac{1}{2})^m \times n = 1
$$

两边取对数

$$
-m+log_2n = 0
$$

即得：

$$
m = log_2n
$$

---

对于三分有同样的证明方法：

三分每次排除 $\dfrac{1}{3}$ 区间, 假设经过 m 次排除，只剩下一个值，即最终答案，那么有：

$$
(\dfrac{2}{3})^m \times n = 1
$$

同理，两边取对数
$$
\quad m + log_{\dfrac{2}{3}}(n) = 0
$$

利用换底公式处理

$$
m + \dfrac{log_3(n)}{log_3(2) - log_3(3)} = 0
$$

恒等变形

$$
m = (\dfrac{1}{1-log_3(2)})log_3(n)
$$

结果是：

$$
m \approx 2.7095 log_3(n) \\
m = O(log_3n)
$$

所以总的来说三分的方法也是对数级别的复杂度，也就是说三分的复杂度也可以写成 $O(logn)$ (通过换底公式可以得到)，因此二分到三分的优化是常数级别的优化
