/*     -*- coding: utf-8 -*-     */
/* File    : 725_split_linked_list_in_parts.cpp */
/* Author  : MeteorDream         */
/* Time    : 2021/05/10 18:33:40 */
/* language: C/C++               */
/* Software: Visual Studio Code  */

#include "LeetCode.h"

#ifdef __725__

/* 
725. 分隔链表

难度: 中等

给定一个头结点为 $root$ 的链表, 编写一个函数以将链表分隔为 $k$ 个连续的部分。

每部分的长度应该尽可能的相等: 任意两部分的长度差距不能超过 1，也就是说可能有些部分为 null。

这k个部分应该按照在链表中出现的顺序进行输出，并且排在前面的部分的长度应该大于或等于后面的长度。

返回一个符合上述规则的链表的列表。

举例： 1->2->3->4, k = 5 // 5 结果 [ [1], [2], [3], [4], null ]

示例 1：

> 输入: 
> root = [1, 2, 3], k = 5
> 输出: [[1],[2],[3],[],[]]
> 解释:
> 输入输出各部分都应该是链表，而不是数组。
> 例如, 输入的结点 root 的 val= 1, root.next.val = 2, \\\\root.next.next.val = 3, 且 root.next.next.next = null。
> 第一个输出 output[0] 是 output[0].val = 1, output[0].next = null。
> 最后一个元素 output[4] 为 null, 它代表了最后一个部分为空链表。

示例 2：

> 输入: 
> root = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10], k = 3
> 输出: [[1, 2, 3, 4], [5, 6, 7], [8, 9, 10]]
> 解释:
> 输入被分成了几个连续的部分，并且每部分的长度相差不超过1.前面部分的长度大于等于后面部分的长度。
 

提示:

- $root$ 的长度范围： $[0, 1000]$.
- 输入的每个节点的大小范围：[0, 999].
- $k$ 的取值范围： $[1, 50]$.

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/split-linked-list-in-parts
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

// class Solution {
// public:
//     vector<ListNode*> splitListToParts(ListNode* root, int k) {
//         vector<ListNode*> ans(k, nullptr);
//         ans[0] = root;
//         /* 初始化指针数组，按顺序指向前k个结点 */
//         for (int i = 1; i < k; ++i)
//             if (ans[i - 1] != nullptr)
//                 ans[i] = ans[i - 1]->next;
//         /* 移动指针，数组下标为 i 的指针每次前进 i + 1 */
//         while (ans[k - 1] != nullptr) {
//             for (int i = 0; i < k - 1; ++i) {
//                 ans[k - 1] = ans[k - 1]->next;
//                 if (ans[k - 1] == nullptr) break;
//                 for (int j = i; j < k - 1; ++j)
//                     if (ans[j] != nullptr)
//                         ans[j] = ans[j]->next;
//                     else {
//                         break;
//                     }
//             }
//             if (ans[k - 1] != nullptr) ans[k - 1] = ans[k - 1]->next;
//         }
//         /* 此时链表已经由 k - 1 个指针划分为 k 段，数组中的指针均指向各段最后一个结点 */
//         /* 将链表分割成 k 段，并将数组指针设为各段的头结点, 即上一段最后一个结点的next指针指向的结点 */
//         for (int i = k - 1; i > 0; --i)
//             if (ans[i - 1] != nullptr) {
//                 ans[i] = ans[i - 1]->next;
//                 ans[i - 1]->next = nullptr;
//             }
//         /* 第一段的头结点为 root */
//         ans[0] = root;
//         return ans;
//     }
// };

class Solution {
public:
    vector<ListNode*> splitListToParts(ListNode* root, int k) {
        int size = 0, dif = 0;
        ListNode *p = root, *q;
        vector<ListNode*> ans(k, nullptr);
        for (; p != nullptr; p = p->next) ++size;
        dif = size / k;
        size %= k;
        p = root;
        for (int i = 0; i < k; ++i) {
            ans[i] = p;
            for (int j = 0; j < dif + (i + 1 < size ? 1 : 0) - 1; ++j) {
                if (p != nullptr) p = p->next;
            }
            if (p == nullptr) {
                break;
            }
            else {
                q = p;
                p = p->next;
                q->next = nullptr;
            }
        }
        return ans;
    }
};

int Submit() {
    Solution s;

    /* 输入 */
    cout << "输入:" << endl;
    vector<int> nums{1, 2, 3, 4, 5, 6, 7};
    List L(nums);
    s.splitListToParts(L.head->next, 3);

    return 0;
}

#endif