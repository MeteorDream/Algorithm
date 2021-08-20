/* 
* coding: utf-16 -*- 
* File    : LeetCode_946.java
* Author  : MeteorDream
* Time    : 2021/06/14 16:27:09
* language: Java
* Software: Visual Studio Code
* */

/* [946. 验证栈序列](https://leetcode-cn.com/problems/validate-stack-sequences/)
 * 难度: 中等
 * */

import java.util.*;

public class LeetCode_946 {
    public static void main(String[] args) {
        LeetCode_946 s = new LeetCode_946();

        System.out.println(s + "Finish!");
    }

    /* // 模拟
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
    } */

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