/*     -*- coding: utf-8 -*-     */
/* File    : 213_house_robber_II.cpp */
/* Author  : MeteorDream         */
/* Time    : 2021/05/07 10:49:09 */
/* language: C/C++               */
/* Software: Visual Studio Code  */

#include "LeetCode.h"

#ifdef __213__

/* 
213. 打家劫舍 II

难度: 中等

你是一个专业的小偷，计划偷窃沿街的房屋，每间房内都藏有一定的现金。这个地方所有的房屋都 **围成一圈** ，这意味着第一个房屋和最后一个房屋是紧挨着的。同时，相邻的房屋装有相互连通的防盗系统，**如果两间相邻的房屋在同一晚上被小偷闯入，系统会自动报警** 。

给定一个代表每个房屋存放金额的非负整数数组，计算你 **在不触动警报装置的情况下** ，今晚能够偷窃到的最高金额。

$\quad$

示例 1：

> 输入：nums = [2,3,2]
> 输出：3
> 解释：你不能先偷窃 1 号房屋（金额 = 2），然后偷窃 3 号房屋（金额 = 2）, 因为他们是相邻的。

示例 2：

> 输入：nums = [1,2,3,1]
> 输出：4
> 解释：你可以先偷窃 1 号房屋（金额 = 1），然后偷窃 3 号房屋（金额 = 3）。
> $\qquad$ 偷窃到的最高金额 = 1 + 3 = 4 。

示例 3：

> 输入：nums = [0]
> 输出：0
 

提示：

- 1 <= nums.length <= 100
- 0 <= nums[i] <= 1000

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/house-robber-ii
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

*/

// class Solution {
// public:
//     /* 记忆化dfs */
//     /* 两个数组分别记录偷与不偷第i个房屋的情况下第i个房屋及之后能偷窃到的最大值 */
//     /* 初始值设置为-1，表示不偷 */
//     int st[107];
//     int rob(vector<int>& nums) {
//         int n = nums.size();
//         /* x, y, z 分别表示前i - 2， i - 1, i个房屋所能偷到的最大值 */
//         int x = nums[0], y = max(nums[0], n > 1 ? nums[1] : 0), z;
//         /* 初始化缓存数组 */
//         for (int i = 0; i < nums.size() + 2; st[i++] = -1) {}
//         /* 动态规划+滚动数组 */
//         for (int i = 2; i < n - 1; ++i) {
//             z = max(x + nums[i], y);
//             x = y;
//             y = z;
//         }
//         return max(dfs(nums, 1, false), y);
//     }

//     /* 返回第i个房屋及之后能偷窃到的最大值，issteal标志第i - 1个房屋是否偷窃 */
//     int dfs(vector<int>& nums, int i, bool issteal) {
//         /* i越界，没房屋可供偷窃，只能空手而归了>_< */
//         if (i >= nums.size()) return 0;
//         /* 前一个偷过了，那这个就不能偷了！去下一家看看~ */
//         else if (issteal) {
//             if (st[i + 2] == -1) st[i + 2] = dfs(nums, i + 1, false);
//             return st[i + 2];
//         }
//         /* 前一个没偷过，那么这个可偷可不偷，两者取大的那个 */
//         else {
//             if (st[i + 1] == -1) st[i + 1] = dfs(nums, i + 1, true);
//             if (st[i + 2] == -1) st[i + 2] = dfs(nums, i + 1, false);
//             return max(st[i + 1] + nums[i], st[i + 2]);
//         }
//     }
// };

class Solution {
public:
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

int Submit() {
    Solution s;

    /* 输入 */
    vector<int> nums{2, 3, 2};    //4
    cout << "输入:" << endl;
    for (auto i = nums.begin(); i != nums.end(); i++) cout << *i << ends;
    cout << endl;

    /* 输出 */
    cout << "输出:" << endl;
    cout << s.rob(nums) << "  (4)" << endl
         << endl;

    /* 输入 */
    nums.clear();
    nums.insert(nums.begin(), {1, 2, 3, 1});    // 4
    cout << "输入:" << endl;
    for (auto i = nums.begin(); i != nums.end(); i++) cout << *i << ends;
    cout << endl;

    /* 输出 */
    cout << "输出:" << endl;
    cout << s.rob(nums) << "  (4)" << endl
         << endl;

    /* 输入 */
    nums.clear();
    nums.insert(nums.begin(), {1, 2});    // 2
    cout << "输入:" << endl;
    for (auto i = nums.begin(); i != nums.end(); i++) cout << *i << ends;
    cout << endl;

    /* 输出 */
    cout << "输出:" << endl;
    cout << s.rob(nums) << "  (2)" << endl
         << endl;

    return 0;
}

#endif
