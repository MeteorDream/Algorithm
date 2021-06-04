/*     -*- coding: utf-8 -*-     */
/* File    : 337_house_robber_III.cpp */
/* Author  : MeteorDream         */
/* Time    : 2021/05/07 21:25:23 */
/* language: C/C++               */
/* Software: Visual Studio Code  */

#include "LeetCode.h"

#ifdef __337__

/* 
337. 打家劫舍 III

难度: 中等

在上次打劫完一条街道之后和一圈房屋后，小偷又发现了一个新的可行窃的地区。这个地区只有一个入口，我们称之为“根”。 除了“根”之外，每栋房子有且只有一个“父“房子与之相连。一番侦察之后，聪明的小偷意识到“这个地方的所有房屋的排列类似于一棵二叉树”。 如果两个直接相连的房子在同一天晚上被打劫，房屋将自动报警。

计算在不触动警报的情况下，小偷一晚能够盗取的最高金额。

示例 1:

> https://assets.leetcode.com/uploads/2021/03/10/rob1-tree.jpg
> 
> **输入:** [3,2,3,null,3,null,1]
> 
> **输出:** 7 
> **解释:** 小偷一晚能够盗取的最高金额 = 3 + 3 + 1 = 7.

示例 2:

> https://assets.leetcode.com/uploads/2021/03/10/rob2-tree.jpg
> 
> **输入:** [3,4,5,1,3,null,1]
> 
> **输出:** 9
> **解释:** 小偷一晚能够盗取的最高金额 = 4 + 5 = 9.

提示：

- 树中结点的数量在 $[1, 10^4]$ 范围内
- $0 <= Node.val <= 10^4$

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/house-robber-iii
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

class Solution {
public:
    int rob(TreeNode* root) {
        return dfs(root, false);
    }

    /* 计算当前这棵树能偷取的最大值, is_rob表示父节点是否偷窃了 */
    int dfs(TreeNode* root, bool is_rob) {
        if (root == nullptr)
            return 0;
        else if (is_rob)
            return dfs(root->left, false) + dfs(root->right, false);
        else
            return max(dfs(root->left, false) + dfs(root->right, false), dfs(root->left, true) + dfs(root->right, true) + root->val);
    }
};

int Submit() {
    Solution s;

    /* 输入 */
    vector<int> nums{3, 2, 3, -1, 3, -1, 1};
    Tree T(nums);
    // cout << "输入:" << endl;
    cout << endl;

    /* 输出 */
    cout << "输出:" << endl;
    cout << s.rob(T.root) << "(7)" << endl;

    nums.clear();
    nums.insert(nums.begin(), {3, 4, 5, 1, 3, -1, 1});

    /* 输出 */
    T.CreateTree(nums);
    cout << "输出:" << endl;
    cout << s.rob(T.root) << "(9)" << endl;

    return 0;
}

#endif