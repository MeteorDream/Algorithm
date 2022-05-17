---
title: LeetCode 213 打家劫舍II
date: 2021-05-07 11:15:48
categories:
- [LeetCode]
tags: [LeetCode,动态规划,深度优先搜索]
---

## 题目

[213. 打家劫舍 II](https://leetcode-cn.com/problems/house-robber-ii)

难度: 中等

<!--more-->

你是一个专业的小偷，计划偷窃沿街的房屋，每间房内都藏有一定的现金。这个地方所有的房屋都 **围成一圈** ，这意味着第一个房屋和最后一个房屋是紧挨着的。同时，相邻的房屋装有相互连通的防盗系统，**如果两间相邻的房屋在同一晚上被小偷闯入，系统会自动报警** 。

给定一个代表每个房屋存放金额的非负整数数组，计算你 **在不触动警报装置的情况下** ，今晚能够偷窃到的最高金额。

$\quad$

示例 1：

> **输入：** nums = [2,3,2]
> **输出：** 3
> **解释：** 你不能先偷窃 1 号房屋（金额 = 2），然后偷窃 3 号房屋（金额 = 2）, 因为他们是相邻的。

示例 2：

> **输入：** nums = [1,2,3,1]
> **输出：** 4
> **解释：** 你可以先偷窃 1 号房屋（金额 = 1），然后偷窃 3 号房屋（金额 = 3）。  
> $\qquad$ 偷窃到的最高金额 = 1 + 3 = 4 。

示例 3：

> **输入：** nums = [0]
> **输出：** 0

提示：

- 1 <= nums.length <= 100
- 0 <= nums[i] <= 1000

## 解析

这题是 「[198. 打家劫舍](https://leetcode-cn.com/problems/house-robber)」 (后面称打家劫舍I)的进阶版，所以先做出 「打家劫舍I」 就能很快解出这题，关于 「打家劫舍I」 的讲解可以查看这篇文章 「[LeetCode 198 打家劫舍](https://meteordream.github.io/LeetCode/2021-05/06111613.html)」

对比一下两题，很容易发现和 「打家劫舍I」 相比本题多出一个限制条件，房屋成环形，换而言之，就是没法同时偷第一间房屋和最后一间房屋了。

这个限制条件其实限制并不大，我们依照题意，将第一间和最后一间单独拎出来讨论：

1. 不偷第一间房屋，那么后续情况就回到了 「打家劫舍I」 的情况，从第二间房屋开始就能使用记忆化dfs或动态规划的思路求解
2. 不偷最后一间房屋，同样问题回到了 「打家劫舍I」 的情况，从第一间开始使用记忆化dfs或动态规划的思路求解但不计算最后一间
3. 那么有没有可能第一间和最后一间房屋都不偷是最大的情况呢？当然是有可能的，假设不偷第一间和最后一间房屋所能偷得的金额是 $M$, 那么不难看出其实情况1和情况2的计算结果也都会是 $M$, 所以实际上在前两种情况已经包含了两间房屋都不偷的可能，也就无需单独讨论了
4. 最后，我们将情况1和情况2比较，能偷取金额大的就是我们需要的结果了

几个小细节：

- 动态规划：计算前 $n-1$ 间房屋是比较容易的，只需返回 $n-1$ 的结果即可，而忽略第一间房屋则可以将dp[0]初值设为0即能按照 「打家劫舍I」 的方法计算出忽略第一间房屋情况的结果了
- 记忆化dfs：记忆化dfs其实是由后往前的，所以忽略第一间房屋是容易计算的，只需调用 `dfs(nums, 1, false)` 即可，对于不偷最后一间房屋，同样的办法，我们可以将最后一间房屋的缓存单独设为0即可得到我们想要的结果
- 对 「打家劫舍I」 的解答中的记忆化dfs进行了一点点的化简，即将 $nst[i] = st[i + 1]$ 代入消去nst数组，使得空间复杂度的常数降低了

$\quad$

- 时间复杂度: $O(n)$, 每次动态规划或记忆化dfs都需要遍历数组一次
- 空间复杂度: $O(n)$, 若仅使用滚动数组+动态规划则空间复杂度为 $O(1)$

## 代码

```cpp
/* Code language: C/C++ */
class Solution {
public:
    /* 两次动态规划 */
    int rob(vector<int>& nums) {
        int n = nums.size();
        if (n == 1) return nums[0];
        return max(my_rob(nums, 1, n), my_rob(nums, 0, n - 1));
    }

    /* 动态规划 + 滚动数组 */
    /* x, y, z 分别表示前i - 2， i - 1, i个房屋所能偷到的最大值 */
    int my_rob(vector<int>& nums, int begin, int end) {
        int n = end - begin;
        int x = nums[begin], y = max(nums[begin], n > 1 ? nums[begin + 1] : 0), z;
        for (int i = begin + 2; i < end; ++i) {
            z = max(x + nums[i], y);
            x = y;
            y = z;
        }
        return y;
    }
};
```

```python
# Code language: Python
class Solution:
    # 两次动态规划
    def rob(self, nums: List[int]) -> int:
        n = len(nums)
        # x, y 分别表示前i - 1， i个房屋所能偷到的最大值
        x, y = nums[0], max(nums[0], nums[1] if n > 1 else 0)
        for i in range(2, n - 1):
            x, y = y, max(x + nums[i], y)
        ans = y
        # x, y 分别表示前i - 1， i个房屋所能偷到的最大值
        x, y = 0, max(0, nums[1] if n > 1 else 0)
        for i in range(2, n):
            x, y = y, max(x + nums[i], y)

        return max(ans, y)
```

```cpp
/* Code language: C/C++ */
class Solution {
public:
    /* 记忆化dfs + 动态规划 */
    /* 两个数组分别记录偷与不偷第i个房屋的情况下第i个房屋及之后能偷窃到的最大值 */
    /* 初始值设置为-1，表示不偷 */
    int st[107];
    int rob(vector<int>& nums) {
        /* x, y, z 分别表示前i - 2， i - 1, i个房屋所能偷到的最大值 */
        int n = nums.size();
        int x = nums[0], y = max(nums[0], n > 1 ? nums[1] : 0), z;

        /* 初始化缓存数组 */
        for (int i = 0; i < nums.size() + 2; st[i++] = -1) {}

        /* 动态规划+滚动数组 计算 前n-1间房屋最大值 */
        for (int i = 2; i < n - 1; ++i) {
            z = max(x + nums[i], y);
            x = y;
            y = z;
        }

        /* 不偷第一间的情况由记忆化dfs计算的 */
        return max(dfs(nums, 1, false), y);
    }

    /* 返回第i个房屋及之后能偷窃到的最大值，issteal标志第i - 1个房屋是否偷窃 */
    int dfs(vector<int>& nums, int i, bool issteal) {
        /* i越界，没房屋可供偷窃，只能空手而归了>_< */
        if (i >= nums.size()) return 0;
        /* 前一个偷过了，那这个就不能偷了！去下一家看看~ */
        else if (issteal) {
            if (st[i + 2] == -1) st[i + 2] = dfs(nums, i + 1, false);
            return st[i + 2];
        }
        /* 前一个没偷过，那么这个可偷可不偷，两者取大的那个 */
        else {
            if (st[i + 1] == -1) st[i + 1] = dfs(nums, i + 1, true);
            if (st[i + 2] == -1) st[i + 2] = dfs(nums, i + 1, false);
            return max(st[i + 1] + nums[i], st[i + 2]);
        }
    }
};
```

```python
# Code language: Python
class Solution:
    # 动态规划+记忆化dfs
    def rob(self, nums: List[int]) -> int:
        n = len(nums)
        # x, y 分别表示前i - 1， i个房屋所能偷到的最大值
        x, y = nums[0], max(nums[0], nums[1] if n > 1 else 0)
        for i in range(2, n - 1):
            x, y = y, max(x + nums[i], y)

        # 返回第i个房屋及之后能偷窃到的最大值，issteal标志第i - 1个房屋是否偷窃
        @lru_cache(None)
        def dfs(i, issteal):
            # i越界，没房屋可供偷窃，只能空手而归了>_<
            if i >= n:
                return 0
            # 前一个偷过了，那这个就不能偷了！去下一家看看~
            elif issteal:
                return dfs(i + 1, False)
            # 前一个没偷过，那么这个可偷可不偷，两者取大的那个
            else:
                return max(dfs(i + 1, True) + nums[i], dfs(i + 1, False))

        return max(dfs(1, False), y)
```
