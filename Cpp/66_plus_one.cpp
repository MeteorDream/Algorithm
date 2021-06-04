/*     -*- coding: utf-8 -*-     */
/* File    : 66_加一.cpp */
/* Author  : MeteorDream         */
/* Time    : 2021/05/03 15:57:51 */
/* language: C/C++               */
/* Software: Visual Studio Code  */

#include <bits/stdc++.h>
#include "LeetCode.h"
using namespace std;

#ifdef __066__

/* 
66. 加一

难度: 简单

给定一个由 **整数** 组成的 **非空** 数组所表示的非负整数，在该数的基础上加一。

最高位数字存放在数组的首位， 数组中每个元素只存储**单个**数字。

你可以假设除了整数 0 之外，这个整数不会以零开头。

 

示例 1：

>> 输入：digits = [1,2,3]
>> 输出：[1,2,4]
>> 解释：输入数组表示数字 123。

示例 2：

>> 输入：digits = [4,3,2,1]
>> 输出：[4,3,2,2]
>> 解释：输入数组表示数字 4321。

示例 3：

>> 输入：digits = [0]
>> 输出：[1]
 

提示：

- 1 <= digits.length <= 100
- 0 <= digits[i] <= 9

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/plus-one
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

class Solution
{
public:
    /* 
    * 执行用时：0 ms, 在所有 C++ 提交中击败了100.00%的用户
    * 内存消耗：8.6 MB, 在所有 C++ 提交中击败了37.24%的用户
    */
    vector<int> plusOne(vector<int> &digits)
    {
        int plus = 1;
        for (auto i = digits.rbegin(); i != digits.rend(); i++)
        {
            *i = *i + plus;
            if (*i > 9)
            {
                *i -= 10;
                plus = 1;
            }
            else
            {
                plus = 0;
                break;
            }
        }
        if (plus == 1)
            digits.insert(digits.begin(), 1);
        return digits;
    }
};

int Submit()
{
    Solution s;

    /* 输入 */
    cout << "输入:" << endl;
    // vector<int> nums{1, 2, 3};
    vector<int> nums{9, 9, 9};
    for (auto i = nums.begin(); i != nums.end(); i++)
        cout << *i << ends;
    cout << endl;

    /* 输出 */
    cout << "输出:" << endl;
    s.plusOne(nums);
    for (auto i = nums.begin(); i != nums.end(); i++)
        cout << *i << ends;
    cout << endl;
    return 0;
}

#endif