/*     -*- coding: utf-8 -*-     */
/* File    : 946_validate_stack_sequences.cpp */
/* Author  : MeteorDream         */
/* Time    : 2021/06/14 16:42:53 */
/* language: C/C++               */
/* Software: Visual Studio Code  */

#include "LeetCode.h"

#ifdef __946__

/* 
[946. 验证栈序列](https://leetcode-cn.com/problems/validate-stack-sequences/)

难度: 中等

*/

/* // 模拟
class Solution {
public:
    bool validateStackSequences(vector<int>& pushed, vector<int>& popped) {
        int n = pushed.size();
        // 设置一个栈模拟出栈入栈行为
        stack<int> s;
        // 逐个检查能否得到popped出栈序列
        for (int i = 0, j = 0; j < n;) {
            // 若栈顶元素不是当前popped序列所处理的那个，那就从pushed序列取元素入栈
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
}; */

/* // 模拟 + 空间压缩 */
class Solution {
public:
    // 注意到我们设置用于模拟的栈大小不会超出pushed的大小，且pushed和popped的元素都只需遍历一次就行，那么我们可以在pushed上原地进行模拟，其余思路不变
    bool validateStackSequences(vector<int>& pushed, vector<int>& popped) {
        int n = pushed.size();
        // pushed 已经遍历过的位置设置一个模拟栈的栈顶指针
        int s = 0;
        // 逐个检查能否得到popped出栈序列
        for (int i = 0, j = 0; j < n;) {
            // 若栈顶元素不是当前popped序列所处理的那个，那就从pushed序列取元素入栈
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

int Submit() {
    Solution s;

    /* 输入 */
    cout << "输入:" << endl;

    /* 输出 */
    cout << "输出:" << endl;

    return 0;
}

#endif