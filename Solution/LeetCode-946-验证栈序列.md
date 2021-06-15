---
title: LeetCode 946.验证栈序列
date: 2021-06-14 17:10:58
categories:
- [LeetCode]
tags: [LeetCode,栈]
---

## 题目

[946. 验证栈序列](https://leetcode-cn.com/problems/validate-stack-sequences/)

难度: 中等

给定 `pushed` 和 `popped` 两个序列，每个序列中的 **值都不重复**，只有当它们可能是在最初空栈上进行的推入 push 和弹出 pop 操作序列的结果时，返回 `true`；否则，返回 `false` 。

$\quad$

示例 1：

> **输入：**pushed = [1,2,3,4,5], popped = [4,5,3,2,1]
> **输出：**true
> **解释：**我们可以按以下顺序执行：
> push(1), push(2), push(3), push(4), pop() -> 4,
> push(5), pop() -> 5, pop() -> 3, pop() -> 2, pop() -> 1

示例 2：

> **输入：**pushed = [1,2,3,4,5], popped = [4,3,5,1,2]
> **输出：**false
> **解释：**1 不能在 2 之前弹出。
> $\quad$

提示：

- `0 <= pushed.length == popped.length <= 1000`
- `0 <= pushed[i], popped[i] < 1000`
- `pushed` 是 `popped` 的排列。

## 解析

这是道模拟题，我们先想想手动考察出栈、入栈序列是否合理要怎么做。这是栈的基本操作了，如果不会做建议先学习下数据结构关于栈方面的内容。

这需要一个设置一个栈来实现出栈入栈的操作，举个🌰

入栈序列`[1,2,3,4,5]`  
出栈序列`[3,5,4,2,1]`

我们考察出栈序列：

- 想要将3出栈，那么3以及3之前的值都需要入栈，此时栈中序列为`[1,2,3]`，可以将3出栈
- 想要将5出栈，那么5以及5之前的值都需要入栈，此时栈中序列为`[1,2,4,5]`，可以将5出栈
- 可以看出，栈`[1,2,4]`的出栈顺序恰好就是`[4,2,1]`满足所给出栈序列，所以这个出栈顺序是合理的

若我们将出栈序列改为`[3,5,4,1,2]`, 就会发现 1 不可能在 2 之前出栈，所以这个序列就是不合理的

## 方法一：模拟

模拟的思路很简单很清晰，我们完全可以将上述思路转化为代码实现

```python
# Code language: Python
class Solution:
    # 模拟
    def validateStackSequences(self, pushed: List[int], popped: List[int]) -> bool:
        n = len(pushed)
        i, j = 0, 0
        st = []  # 设置一个栈模拟出栈入栈行为
        # 逐个检查能否得到popped出栈序列
        while j < n:
            # 若栈顶元素不是当前popped序列所处理的那个或栈空，那就从pushed序列取元素入栈
            while i < n and (not st or st[-1] != popped[j]):
                st.append(pushed[i])
                i += 1
            # 如果出栈序列用完了都得不到出栈序列元素，说明pushed的入栈顺序不可能得到popped的出栈顺序
            if not i < n and st[-1] != popped[j]:
                return False
            while st and j < n and st[-1] == popped[j]:
                st.pop()
                j += 1
        return True
```

```cpp
/* Code language: C++ */
/* // 模拟 */
class Solution {
public:
    bool validateStackSequences(vector<int>& pushed, vector<int>& popped) {
        int n = pushed.size();
        // 设置一个栈模拟出栈入栈行为
        stack<int> s;
        // 逐个检查能否得到popped出栈序列
        for (int i = 0, j = 0; j < n;) {
            // 若栈顶元素不是当前popped序列所处理的那个或栈空，那就从pushed序列取元素入栈
            while (i < n && (s.empty() || s.top() != popped[j]))
                s.emplace(pushed[i++]);
            // 如果出栈序列用完了都得不到出栈序列元素，说明pushed的入栈顺序不可能得到popped的出栈顺序
            if (i == n && s.top() != popped[j])
                return false;
            while (j < n && !s.empty() && s.top() == popped[j]) {
                s.pop();
                ++j;
            }
        }
        return true;
    }
};
```

```java
/* Code language: Java */
class Solution {
    /* // 模拟 */
    public boolean validateStackSequences(int[] pushed, int[] popped) {
        int n = pushed.length;
        // 设置一个栈模拟出栈入栈行为
        Stack<Integer> s = new Stack<>();
        // 逐个检查能否得到popped出栈序列
        for (int i = 0, j = 0; j < n;) {
            // 若栈顶元素不是当前popped序列所处理的那个或栈空，那就从pushed序列取元素入栈
            while (i < n && (s.empty() || s.peek() != popped[j]))
                s.push(pushed[i++]);
            // 如果出栈序列用完了都得不到出栈序列元素，说明pushed的入栈顺序不可能得到popped的出栈顺序
            if (i == n && s.peek() != popped[j])
                return false;
            while (!s.empty() && s.peek() == popped[j]) {
                s.pop();
                ++j;
            }
        }
        return true;
    }
}
```

- 时间复杂度: $O(n)$, `pushed`和`popped`都只需遍历一次
- 空间复杂度: $O(n)$, 最坏情况下所有元素都先入栈，再逐一出栈

## 方法二：空间优化+模拟

注意到 `pushed` 和 `popped` 都只需遍历一次，而模拟栈中的元素都是 `pushed` 中由前向后取得的，所以我们可以将 `pushed` 中已经遍历过的部分当成模拟栈，以实现空间优化，其余部分还是模拟的思路。当然，缺点是 `pushed` 数组中的数值被覆盖了。

```python
# Code language: Python
class Solution:
    # 模拟 + 空间优化
    # 注意到我们设置用于模拟的栈大小不会超出pushed的大小，且pushed和popped的元素都只需遍历一次就行，那么我们可以在pushed上原地进行模拟，其余思路不变
    def validateStackSequences(self, pushed: List[int], popped: List[int]) -> bool:
        n = len(pushed)
        i, j = 0, 0
        # pushed 已经遍历过的位置设置一个模拟栈的栈顶指针
        s = 0
        # 逐个检查能否得到popped出栈序列
        while j < n:
            # 若栈顶元素不是当前popped序列所处理的那个或栈空，那就从pushed序列取元素入栈
            while i < n and (s == 0 or pushed[s - 1] != popped[j]):
                pushed[s] = pushed[i]
                s += 1
                i += 1
            # 如果出栈序列用完了都得不到出栈序列元素，说明pushed的入栈顺序不可能得到popped的出栈顺序
            if not i < n and pushed[s - 1] != popped[j]:
                return False
            while s > 0 and j < n and pushed[s - 1] == popped[j]:
                s -= 1
                j += 1
        return True
```

```cpp
/* Code language: C++ */
/* // 模拟 + 空间优化 */
class Solution {
public:
    // 注意到我们设置用于模拟的栈大小不会超出pushed的大小，且pushed和popped的元素都只需遍历一次就行，那么我们可以在pushed上原地进行模拟，其余思路不变
    bool validateStackSequences(vector<int>& pushed, vector<int>& popped) {
        int n = pushed.size();
        // pushed 已经遍历过的位置设置一个模拟栈的栈顶指针
        int s = 0;
        // 逐个检查能否得到popped出栈序列
        for (int i = 0, j = 0; j < n;) {
            // 若栈顶元素不是当前popped序列所处理的那个或栈空，那就从pushed序列取元素入栈
            while (i < n && (s == 0 || pushed[s - 1] != popped[j]))
                pushed[s++] = pushed[i++];
            // 如果出栈序列用完了都得不到出栈序列元素，说明pushed的入栈顺序不可能得到popped的出栈顺序
            if (i == n && pushed[s - 1] != popped[j])
                return false;
            while (j < n && s > 0 && pushed[s - 1] == popped[j]) {
                s -= 1;
                ++j;
            }
        }
        return true;
    }
};
```

```java
/* Code language: Java */
class Solution {
    /* // 模拟 + 空间压缩 */
    // 注意到我们设置用于模拟的栈大小不会超出pushed的大小，且pushed和popped的元素都只需遍历一次就行，那么我们可以在pushed上原地进行模拟，其余思路不变
    public boolean validateStackSequences(int[] pushed, int[] popped) {
        int n = pushed.length;
        // pushed 已经遍历过的位置设置一个模拟栈的栈顶指针
        int s = 0;
        // 逐个检查能否得到popped出栈序列
        for (int i = 0, j = 0; j < n;) {
            // 若栈顶元素不是当前popped序列所处理的那个或栈空，那就从pushed序列取元素入栈
            while (i < n && (s == 0 || pushed[s - 1] != popped[j]))
                pushed[s++] = pushed[i++];
            // 如果出栈序列用完了都得不到出栈序列元素，说明pushed的入栈顺序不可能得到popped的出栈顺序
            if (i == n && pushed[s - 1] != popped[j])
                return false;
            while (s > 0 && pushed[s - 1] == popped[j]) {
                --s;
                ++j;
            }
        }
        return true;
    }
}
```

- 时间复杂度: $O(n)$, `pushed`和`popped`都只需遍历一次
- 空间复杂度: $O(1)$
