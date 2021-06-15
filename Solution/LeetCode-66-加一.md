---
title: LeetCode 66. 加一
date: 2021-05-03 16:59:08
categories:
- [LeetCode]
tags: [LeetCode,数组]
---

## 题目

[66. 加一](https://leetcode-cn.com/problems/plus-one)

难度: 简单

给定一个由 **整数** 组成的 **非空** 数组所表示的非负整数，在该数的基础上加一。

最高位数字存放在数组的首位， 数组中每个元素只存储**单个**数字。

你可以假设除了整数 0 之外，这个整数不会以零开头。

$\quad$

示例 1：

> **输入：** digits = [1,2,3]
> **输出：** [1,2,4]
> **解释：** 输入数组表示数字 123。

示例 2：

> **输入：** digits = [4,3,2,1]
> **输出：** [4,3,2,2]
> **解释：** 输入数组表示数字 4321。

示例 3：

> **输入：** digits = [0]
> **输出：** [1]

提示：

- 1 <= digits.length <= 100
- 0 <= digits[i] <= 9

***

## 解析

这是一题简单难度的题目，题目也不复杂。

解释一下就是: 使用了一个数组来存储一个数字，在数组中的元素就是数字的每一位的值，例如[1,2,3]就是123。这应该很好理解。

我们要做的事情就是将这个用数组表示的数字加一。不难想到，我们只要模拟简单加法就可以了。需要注意的仅仅是进位问题(尤其是加一后数组长度加一的情况), 例如测试值为 $9, 29, 999$ 。

算法步骤如下:

1. 指针指向数组最后一位，将其值加一
2. 判断是否要进位，如果需要进位，指针前移一位，重复执行1，2，如无需进位则执行3
3. 最后根据最后一次执行是否进位判断是否需要增加一位(这里是处理类似 $999 + 1 = 1000$ 的情况)

## 代码

```cpp
/* Code language: C/C++ */
class Solution
{
public:
    vector<int> plusOne(vector<int> &digits)
    {
        int plus = 1;
        for (auto i = digits.rbegin(); i != digits.rend(); i++) {
            *i = *i + plus;
            if (*i > 9) {
                *i -= 10;
                plus = 1;
            }
            else {
                plus = 0;
                break;
            }
        }
        if (plus == 1)
            digits.insert(digits.begin(), 1);
        return digits;
    }
};
```

```python
# Code language: Python
class Solution:
    def plusOne(self, digits: List[int]) -> List[int]:
        n = len(digits) - 1
        t = 1  # 进位标志
        for i in range(n, -1, -1):
            digits[i] += t
            if digits[i] > 9:
                digits[i] -= 10
                t = 1
            else:
                return digits
        # 特殊处理 9, 99, 999 等情况
        if t == 1:
            return [1] + digits
```
