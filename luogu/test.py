# -*- coding: utf-8 -*-
# File    : test.py
# Author  : MeteorDream
# Time    : 2021/12/07 14:37:36
# language: Python
# Software: Visual Studio Code

from typing import List, Any
from functools import cache, lru_cache
from collections import deque, defaultdict, Counter
import itertools

class Solution:
    dir = ((0, 1), (0, -1), (1, 0), (-1, 0))
    def colorBorder(self, grid: List[List[int]], row: int, col: int, color: int) -> List[List[int]]:
        n, m = len(grid), len(grid[0])
        d = deque([(row, col), ])
        vis = set()
        b = grid[row][col]
        while d:
            x, y = d.popleft()
            vis.add(x * m + y)
            for dx, dy in self.dir:
                tx, ty = x + dx, y + dy
                if 0 <= tx < n and 0 <= ty < m:
                    if grid[tx][ty] != b and grid[tx][ty] != -1:
                        grid[x][y] = -1
                    elif grid[tx][ty] == b and tx * m + ty not in vis:
                        d.append((tx, ty))
            if x == 0 or x == n - 1 or y == 0 or y == m - 1:
                grid[x][y] = -1
        for i, a in enumerate(grid):
            for j, b in enumerate(a):
                if b == -1:
                    grid[i][j] = color
        return grid

class Solution:
    def validTicTacToe(self, board: List[str]) -> bool:
        board = [' ' for _ in range(9)]
        s = set()

        def trans():
            ans = 0
            for a in board:
                if a == ' ':
                    ans += 0
                elif a == 'X':
                    ans += 1
                elif a == 'O':
                    ans += 2
            return ans

        s.add(trans())

        def check():
            # 检查行
            for i in range(3):
                if board[i * 3] != ' ' and board[i * 3] == board[i * 3 + 1] == board[i * 3 + 2]:
                    return True
                if board[i] != ' ' and board[i] == board[3 + i] == board[6 + i]:
                    return True
            if board[0] != ' ' and board[0] == board[4] == board[8]:
                return True
            if board[2] != ' ' and board[2] == board[4] == board[6]:
                return True
            return False

        def dfs(player):
            for i in range(9):
                if board[i] == ' ':
                    if player % 2 == 0:
                        board[i] = 'X'
                    else:
                        board[i] = 'O'
                    s.add(trans())
                    if not check():
                        dfs(player + 1)
                    board[i] = ' '
        
        dfs(0)
        print(s, len(s), file=open("out.out", 'w'))

    def validTicTacToess(self, board: List[str]) -> bool:
        return sum(3 ** (8 - i) * (0 if j == ' ' else 1 if j == 'X' else 2) for i, j in enumerate("".join(board))) in self.s

class Solution:
    def maxIncreaseKeepingSkyline(self, grid: List[List[int]]) -> int:
        row, col = [max(g) for g in grid], [max(grid[i][j] for i in range(len(grid))) for j in range(len(grid[0]))]
        return sum(min(row[i], col[j]) - grid[i][j] for i in range(len(grid)) for j in range(len(grid[0])))

# 472. 连接词(https://leetcode-cn.com/problems/concatenated-words/)
class Solution:
    def findAllConcatenatedWordsInADict(self, words: List[str]) -> List[str]:
        trie = [None for _ in range(27)] # 下标 26 标志是否是结尾
        a = ord('a')

        def dfs(word, idx):
            """Check begin from the word idx-th is exited?"""
            if idx == len(word):
                return True
            root = trie
            for i in range(idx, len(word)):
                if root[26] and dfs(word, i):
                    return True
                w = ord(word[i]) - a
                if not root[w]:
                    return False
                root = root[w]
            return root[26] is True
        
        def insert(word):
            """Insert the word into trie"""
            root = trie
            for w in word:
                w = ord(w) - a
                if not root[w]:
                    root[w] = [None for _ in range(27)]
                root = root[w]
            root[26] = True
        
        words.sort(key=len)
        ans = list()
        for word in words:
            if dfs(word, 0):
                ans.append(word)
            else:
                insert(word)
        return ans

# 127. 单词接龙(https://leetcode-cn.com/problems/word-ladder/)
class Solution:
    z = "qwertyuiopasdfghjklzxcvbnm"
    def ladderLength(self, beginWord: str, endWord: str, wordList: List[str]) -> int:
        # 建图：将相差一个字母的词连接起来
        s = set(wordList)
        s.add(beginWord)
        if endWord not in s: return 0
        n = len(wordList)
        g = defaultdict(set)
        for word in s:
            w = list(word)
            for i, j in enumerate(w):
                for k in self.z:
                    if not k == j:
                        w[i] = k
                        nw = "".join(w)
                        if nw in s:
                            g[word].add(nw)
                            g[nw].add(word)
                w[i] = j
        # bfs
        dq = set([beginWord, ])
        vis = set([beginWord, ])
        step = 1
        while dq:
            nxt = set()
            for cur in dq:
                vis.add(cur)
                if endWord in g[cur]:
                    return step + 1
                for c in g[cur]:
                    if c not in vis:
                        nxt.add(c)
            dq = nxt
            step += 1
        return 0

class Solution:
    def primePalindrome(self, n: int) -> int:
        print([i for i in range(1, int(1e8)) if self.check(i)], file=open("luogu.out", 'w'))

    def check(self, n):
        if not n == int(str(n)[::-1]):
            return False
        for i in range(2, n):
            if n % i == 0:
                return False
            elif i * i > n:
                break
        return True

import random
class SkipNode:
    def __init__(self, val=0x7FFFFFFF, level=32):
        self.val = val
        self.level = [None for _ in range(level)]

class Skiplist:

    MAXL = 32
    S, P = 0xFFFF, 4
    PS = P // S

    def __init__(self):
        self.size = 0
        self.level = 0
        self.head = SkipNode()
        self.tail = SkipNode(level=0)
        for i, _ in enumerate(self.head.level):
            self.head.level[i] = self.tail

    def find(self, val) -> SkipNode:
        p = self.head
        for i in range(self.level - 1, -1):
            while p.level[i] is not None and p.level[i].val < val:
                p = p.level[i]
        p = p.level[0]
        return p

    def search(self, target: int) -> bool:
        p = self.find(target)
        return p.val == target

    def add(self, num: int) -> None:
        update = [None for _ in range(Skiplist.MAXL)]
        p = self.head
        for i in range(self.level - 1, -1, -1):
            while p.level[i] is not None and p.level[i].val < num:
                p = p.level[i]
            update[i] = p
        lv = Skiplist.randomLevel()
        if lv > self.level:
            self.level += 1
            lv = self.level
            update[lv - 1] = self.head
        newNode = SkipNode(num, lv)
        for i in range(lv - 1, -1, -1):
            p = update[i]
            newNode.level[i] = p.level[i]
            p.level[i] = newNode
        self.size += 1
        
    def erase(self, num: int) -> bool:
        update = [None for _ in range(Skiplist.MAXL)]
        p = self.head
        for i in range(self.level - 1, -1, -1):
            while p.level[i] is not None and p.level[i].val < num:
                p = p.level[i]
            update[i] = p
        p = p.level[0]
        if p.val != num: return False
        for i in range(self.level):
            if update.level[i] != p:
                break
            update[i].level[i] = p.level[i]
        while self.level > 0 and self.head.level[self.level - 1] == self.tail:
            self.level -= 1
        self.size -= 1

    def __len__(self):
        return self.size
    
    @staticmethod
    def randomLevel():
        level = 1
        while level < Skiplist.MAXL and (random.randint(0, Skiplist.S) < Skiplist.PS):
            level += 1
        return level

s = Solution()
s.primePalindrome(1)
 