/* 
* coding: utf-16 -*- 
* File    : LeetCode_297.java
* Author  : MeteorDream
* Time    : 2021/06/14 22:07:03
* language: Java
* Software: Visual Studio Code
* */

/**
 *[297. 二叉树的序列化与反序列化](https://leetcode-cn.com/problems/serialize-and-deserialize-binary-tree/)
 * 难度: 困难
 * 题解：https://leetcode-cn.com/problems/serialize-and-deserialize-binary-tree/solution/er-cha-shu-de-xu-lie-hua-yu-fan-xu-lie-h-b684/
 * */

import java.util.*;

public class LeetCode_297 {
    public static void main(String[] args) {
        LeetCode_297 s = new LeetCode_297();

        Codec c = new Codec();

        // [12, 3, 555, 5, null, null, 520]
        TreeNode T = new TreeNode(12, new TreeNode(3, new TreeNode(5), null),
                new TreeNode(555, null, new TreeNode(520)));
        c.deserialize(c.serialize(T));

        // [18, 0, -1]
        T = new TreeNode(18, new TreeNode(0), new TreeNode(-1));
        c.deserialize(c.serialize(T));

        // []
        System.out.println(c.serialize(null));
        c.deserialize(c.serialize(null));

        System.out.println(s + "Finish!");
    }
}

/**
 * toString():
 *  
public String toString() {
    Iterator<E> it = iterator();
    if (! it.hasNext())
        return "[]";

    StringBuilder sb = new StringBuilder();
    sb.append('[');
    for (;;) {
        E e = it.next();
        sb.append(e == this ? "(this Collection)" : e);
        if (! it.hasNext())
            return sb.append(']').toString();
        sb.append(',').append(' ');
    }
} */

class Codec {

    // Encodes a tree to a single string.
    public String serialize(TreeNode root) {
        if (root == null)
            return "[]";

        Queue<TreeNode> s = new LinkedList<>();
        StringBuilder sb = new StringBuilder();
        int cnt = 1; // 表示队列中非空结点的数量

        sb.append('[');
        s.add(root);

        while (true) {
            TreeNode cur = s.poll();
            if (cur == null)
                sb.append("null");
            else {
                --cnt;
                sb.append(cur.val);
                s.add(cur.left);
                s.add(cur.right);
                if (cur.left != null)
                    ++cnt;
                if (cur.right != null)
                    ++cnt;
            }
            if (cnt == 0 || s.isEmpty())
                return sb.append(']').toString();
            sb.append(',');
        }
    }

    // Decodes your encoded data to tree.
    public TreeNode deserialize(String data) {
        if (data.length() <= 2)
            return null;
        String[] nums = data.substring(1, data.length() - 1).split(",");

        int n = nums.length, p = 0;
        if (n == 0)
            return null;
        Queue<TreeNode> q = new ArrayDeque<>();
        TreeNode root = new TreeNode(Integer.valueOf(nums[p++]));
        q.add(root);
        while (p < n) {
            TreeNode cur = q.poll();
            if (!nums[p++].equals("null")) {
                cur.left = new TreeNode(Integer.valueOf(nums[p - 1]));
                q.add(cur.left);
            }
            if (p < n && !nums[p++].equals("null")) {
                cur.right = new TreeNode(Integer.valueOf(nums[p - 1]));
                q.add(cur.right);
            }
        }
        return root;
    }
}

// Your Codec object will be instantiated and called as such:
// Codec ser = new Codec();
// Codec deser = new Codec();
// TreeNode ans = deser.deserialize(ser.serialize(root));