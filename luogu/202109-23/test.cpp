#include <bits/stdc++.h>
using namespace std;

using VI = vector<int>;
using VII = vector<VI>;

// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode()
        : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x)
        : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right)
        : val(x), left(left), right(right) {}
};

class Solution {
public:
    int s, d;
    string getDirections(TreeNode* root, int startValue, int destValue) {
        s = startValue;
        d = destValue;
        string left = "", right = "";
    }

    char dfs(TreeNode* root, string& left, string& right) {
        // 找到 s return 's', 找到 d return 'd'，路径直接返回结果，否则无视
        if (root != nullptr) {
        }
    }
};

/* 
给你一个大小为 m x n 的整数矩阵 grid ，表示一个网格。另给你三个整数 row、col 和 color 。网格中的每个值表示该位置处的网格块的颜色。

当两个网格块的颜色相同，而且在四个方向中任意一个方向上相邻时，它们属于同一 连通分量 。

连通分量的边界 是指连通分量中的所有与不在分量中的网格块相邻（四个方向上）的所有网格块，或者在网格的边界上（第一行/列或最后一行/列）的所有网格块。

请你使用指定颜色 color 为所有包含网格块 grid[row][col] 的 连通分量的边界 进行着色，并返回最终的网格 grid 。
*/

class Solution {
public:
    vector<vector<int>> colorBorder(vector<vector<int>>& grid, int row, int col, int color) {
        deque<vector<int>> d;
        return grid;
    }
};

int main() {
    VII graph;
    graph.push_back(VI{2, 5});
    graph.push_back(VI{3});
    graph.push_back(VI{0, 4, 5});
    graph.push_back(VI{1, 4, 5});
    graph.push_back(VI{2, 3});
    graph.push_back(VI{0, 2, 3});
    Solution s;
}