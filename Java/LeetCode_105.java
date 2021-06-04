/* 
* coding: utf-16 -*- 
* File    : LeetCode_105.java
* Author  : MeteorDream
* Time    : 2021/05/28 01:40:37
* language: Java
* Software: Visual Studio Code
* */

/* [105. 从前序与中序遍历序列构造二叉树](https://leetcode-cn.com/problems/construct-binary-tree-from-preorder-and-inorder-traversal/) */

import java.util.*;

public class LeetCode_105 {
    public static void main(String[] args) {
        LeetCode_105 s = new LeetCode_105();

        System.out.println(s + "Finish!");
    }

    // /* 优化递归 */
    // public TreeNode buildTree(int[] preorder, int[] inorder) {
    //     int n = preorder.length;
    //     HashMap<Integer, Integer> ind = new HashMap<>(n * 2);
    //     for (int i = 0; i < n; ++i)
    //         ind.put(inorder[i], i);
    //     return build(preorder, 0, n - 1, inorder, 0, n - 1, ind);
    // }

    // /* 根据 preorder [i,j] 范围内 和 inorder [x,y] 范围内 的元素建树 */
    // public TreeNode build(int[] preorder, int i, int j, int[] inorder, int x, int y, HashMap<Integer, Integer> ind) {
    //     /* 若 i > j 则树空 */
    //     if (i > j)
    //         return null;
    //     /* 若 i == j 则该树只有一个根结点 */
    //     else if (i == j)
    //         return new TreeNode(preorder[i]);
    //     /* 前序 preorder 的第一个值是根结点的值 */
    //     int val = preorder[i];
    //     TreeNode root = new TreeNode(val);
    //     /* 在中序 inorder 查找根结点所在值 */
    //     int z = ind.get(val);
    //     /* 递归创建左子树和右子树 */
    //     root.left = build(preorder, i + 1, i + z - x, inorder, x, z - 1, ind);
    //     root.right = build(preorder, i + z - x + 1, j, inorder, z + 1, y, ind);
    //     return root;
    // }

    /* // 迭代解法 */
    public TreeNode buildTree(int[] preorder, int[] inorder) {
        int n = preorder.length;
        if (n == 0)
            return null;
        TreeNode root = new TreeNode(preorder[0]);
        Stack<TreeNode> st = new Stack<>();
        st.push(root);
        int i = 0;
        for (int j = 1; j < n; ++j) {
            TreeNode tmp = st.peek();
            if (tmp.val == inorder[i]) {
                while (!st.empty() && st.peek().val == inorder[i]) {
                    tmp = st.pop();
                    ++i;
                }
                tmp.right = new TreeNode(preorder[j]);
                st.push(tmp.right);
            } else {
                tmp.left = new TreeNode(preorder[j]);
                st.push(tmp.left);
            }
        }
        return root;
    }
}