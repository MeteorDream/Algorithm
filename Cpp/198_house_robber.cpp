/*     -*- coding: utf-8 -*-     */
/* File    : 198_house_robber.cpp */
/* Author  : MeteorDream         */
/* Time    : 2021/05/05 19:20:16 */
/* language: C/C++               */
/* Software: Visual Studio Code  */

#include "LeetCode.h"

#ifdef __198__

/* 
198. 打家劫舍

难度: 中等

你是一个专业的小偷，计划偷窃沿街的房屋。每间房内都藏有一定的现金，影响你偷窃的唯一制约因素就是相邻的房屋装有相互连通的防盗系统，**如果两间相邻的房屋在同一晚上被小偷闯入，系统会自动报警**。

给定一个代表每个房屋存放金额的非负整数数组，计算你 **不触动警报装置的情况下** ，一夜之内能够偷窃到的最高金额。

$\quad$

示例 1：

> 输入：[1,2,3,1]
> 输出：4
> 解释：偷窃 1 号房屋 (金额 = 1) ，然后偷窃 3 号房屋 (金额 = 3)。
>      偷窃到的最高金额 = 1 + 3 = 4 。

示例 2：

> 输入：[2,7,9,3,1]
> 输出：12
> 解释：偷窃 1 号房屋 (金额 = 2), 偷窃 3 号房屋 (金额 = 9)，接着偷窃 5 号房屋 (金额 = 1)。
>      偷窃到的最高金额 = 2 + 9 + 1 = 12 。

提示：

- 1 <= nums.length <= 100
- 0 <= nums[i] <= 400

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/house-robber
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

// class Solution {
// public:
//     /* dfs 时间复杂度 $O(f(n))$  TLE */
//     int rob(vector<int>& nums) {
//         return dfs(nums, 0, false);
//     }

//     /* 返回第i个房屋及之后能偷窃到的最大值，issteal标志第i - 1个房屋是否偷窃 */
//     int dfs(vector<int>& nums, int i, bool issteal) {
//         /* i越界，没房屋可供偷窃，只能空手而归了>_< */
//         if (i >= nums.size()) return 0;
//         /* 前一个偷过了，那这个就不能偷了！去下一家看看~ */
//         else if (issteal)
//             return dfs(nums, i + 1, false);
//         /* 前一个没偷过，那么这个可偷可不偷，两者取大的那个 */
//         else
//             return max(dfs(nums, i + 1, true) + nums[i], dfs(nums, i + 1, false));
//     }
// };

class Solution {
public:
    /* 记忆化dfs */
    /* 两个数组分别记录偷与不偷第i个房屋的情况下第i个房屋及之后能偷窃到的最大值 */
    /* 初始值设置为-1，表示不偷 */
    int st[109], nst[109];
    int rob(vector<int>& nums) {
        /* 初始化缓存数组 */
        for (int i = 0; i < nums.size(); ++i) {
            st[i]  = -1;
            nst[i] = -1;
        }
        return dfs(nums, 0, false);
    }

    /* 返回第i个房屋及之后能偷窃到的最大值，issteal标志第i - 1个房屋是否偷窃 */
    int dfs(vector<int>& nums, int i, bool issteal) {
        /* i越界，没房屋可供偷窃，只能空手而归了>_< */
        if (i >= nums.size()) return 0;
        /* 前一个偷过了，那这个就不能偷了！去下一家看看~ */
        else if (issteal) {
            if (nst[i + 1] == -1) nst[i + 1] = dfs(nums, i + 1, false);
            return nst[i + 1];
        }
        /* 前一个没偷过，那么这个可偷可不偷，两者取大的那个 */
        else {
            if (st[i + 1] == -1) st[i + 1] = dfs(nums, i + 1, true);
            if (nst[i + 1] == -1) nst[i + 1] = dfs(nums, i + 1, false);
            return max(st[i + 1] + nums[i], nst[i + 1]);
        }
    }
};

// class Solution {
// public:
//     /* 动态规划 */
//     /* dp[i] 表示前i个房屋所能偷到的最大值 */
//     /* dp[i] 分为偷与不偷 */
//     int dp[109];
//     int rob(vector<int>& nums) {
//         int n = nums.size();
//         dp[0] = nums[0];
//         dp[1] = max(nums[0], n > 1 ? nums[1] : 0);
//         for (int i = 2; i < n; ++i)
//             dp[i] = max(dp[i - 1], dp[i - 2] + nums[i]);
//         return dp[n - 1];
//     }
// };

// class Solution {
// public:
//     /* 动态规划 + 滚动数组 */
//     /* x, y, z 分别表示前i - 2， i - 1, i个房屋所能偷到的最大值 */
//     int rob(vector<int>& nums) {
//         int n = nums.size();
//         int x = nums[0], y = max(nums[0], n > 1 ? nums[1] : 0), z;
//         for (int i = 2; i < n; ++i) {
//             z = max(x + nums[i], y);
//             x = y;
//             y = z;
//         }
//         return y;
//     }
// };

int Submit() {
    Solution s;

    /* 输入 */
    vector<int> nums{1, 2, 3, 1};    //4
    cout << "输入:" << endl;
    for (auto i = nums.begin(); i != nums.end(); i++) cout << *i << ends;
    cout << endl;

    /* 输出 */
    cout << "输出:" << endl;
    cout << s.rob(nums) << endl;

    /* 输入 */
    nums.clear();
    nums.insert(nums.begin(), {2, 7, 9, 3, 1});    // 12
    cout << "输入:" << endl;
    for (auto i = nums.begin(); i != nums.end(); i++) cout << *i << ends;
    cout << endl;

    /* 输出 */
    cout << "输出:" << endl;
    cout << s.rob(nums) << endl;

    return 0;
}

#endif