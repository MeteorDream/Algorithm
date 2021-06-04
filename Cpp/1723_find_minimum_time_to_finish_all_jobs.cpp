/*     -*- coding: utf-8 -*-     */
/* File    : 1723_find_minimum_time_to_finish_all_jobs.cpp */
/* Author  : MeteorDream         */
/* Time    : 2021/05/08 13:06:24 */
/* language: C/C++               */
/* Software: Visual Studio Code  */

#include "LeetCode.h"

#ifdef __1723__

/* 
1723

难度: 困难

给你一个整数数组 $jobs$ ，其中 $jobs[i]$ 是完成第 $i$ 项工作要花费的时间。

请你将这些工作分配给 $k$ 位工人。所有工作都应该分配给工人，且每项工作只能分配给一位工人。工人的 **工作时间** 是完成分配给他们的所有工作花费时间的总和。请你设计一套最佳的工作分配方案，使工人的 **最大工作时间** 得以 **最小化** 。

返回分配方案中尽可能 **最小** 的 **最大工作时间** 。

 

示例 1：

> 输入：jobs = [3,2,3], k = 3
> 输出：3
> 解释：给每位工人分配一项工作，最大工作时间是 3 。

示例 2：

> 输入：jobs = [1,2,4,7,8], k = 2
> 输出：11
> 解释：按下述方式分配工作：
> 1 号工人：1、2、8（工作时间 = 1 + 2 + 8 = 11）
> 2 号工人：4、7（工作时间 = 4 + 7 = 11）
> 最大工作时间是 11 。
 

提示：

- $1 <= k <= jobs.length <= 12$
- $1 <= jobs[i] <= 10^7$

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/find-minimum-time-to-finish-all-jobs
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

*/

// class Solution {
// public:
//     /* dfs - TLE */
//     int works[12];
//     int mtime = 10000007;
//     int minimumTimeRequired(vector<int>& jobs, int k) {
//         mtime = 10000007;
//         if (k >= jobs.size()) return vmax(jobs);
//         for (int i = 0; i < 12; works[i++] = 0) {}
//         dfs(jobs, 0, k);
//         return mtime;
//     }

//     void dfs(vector<int>& jobs, int i, int k) {
//         if (i >= jobs.size()) {
//             int m = works[0];
//             for (auto e : works)
//                 if (e > m) m = e;
//             if (m < mtime) mtime = m;
//         }
//         else {
//             for (int j = 0; j < k; ++j) {
//                 works[j] += jobs[i];
//                 dfs(jobs, i + 1, k);
//                 works[j] -= jobs[i];
//             }
//         }
//     }

//     int vmax(vector<int>& nums) {
//         int m = nums[0];
//         for (auto e : nums) {
//             if (e > m) m = e;
//         }
//         return m;
//     }
// };

class Solution {
public:
    /* dfs + 剪枝 */
    int works[12];
    int mtime = 10000007;
    int minimumTimeRequired(vector<int>& jobs, int k) {
        mtime = 10000007;
        if (k >= jobs.size()) return vmax(jobs);
        for (int i = 0; i < 12; works[i++] = 0) {}
        dfs(jobs, 0, k);
        return mtime;
    }

    void dfs(vector<int>& jobs, int i, int k) {
        if (i >= jobs.size()) {
            int m = works[0];
            for (auto e : works)
                if (e > m) m = e;
            if (m < mtime) mtime = m;
        }
        else {
            for (int j = 0; j < k; ++j) {
                works[j] += jobs[i];
                dfs(jobs, i + 1, k);
                works[j] -= jobs[i];
            }
        }
    }

    int vmax(vector<int>& nums) {
        int m = nums[0];
        for (auto e : nums) {
            if (e > m) m = e;
        }
        return m;
    }
};

int Submit() {
    Solution s;
    vector<int> nums{1, 2, 4, 7, 8};
    cout << s.minimumTimeRequired(nums, 2) << endl;
    nums.clear();
    nums.insert(nums.begin(), {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12});
    cout << s.minimumTimeRequired(nums, 10) << endl;
    return 0;
}

#endif