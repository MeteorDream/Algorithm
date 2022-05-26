from typing import List
import itertools
class Solution:
    sss = ["Gold Medal","Silver Medal","Bronze Medal"]
    def findRelativeRanks(self, score: List[int]) -> List[str]:
        ans = [None for _ in score]
        it = itertools.chain(self.sss, map(str, range(4, int(1e5))))
        {j: i for i, j in sorted(enumerate(score), key=lambda x: x[1], reverse=True)}
        for i, (j, _) in zip(itertools.chain(self.sss, map(str, range(4, int(1e5)))), sorted(enumerate(score), key=lambda x: x[1], reverse=True)):
            ans[j] = i
        return ans

from collections import Counter, defaultdict
class Solution:
    def validArrangement(self, pairs: List[List[int]]) -> List[List[int]]:
        # 存储图
        edges = defaultdict(list)
        # 存储入度和出度
        indeg, outdeg = Counter(), Counter()
        for x, y in pairs:
            edges[x].append(y)
            indeg[y] += 1
            outdeg[x] += 1
        
        # 寻找起始节点
        start = pairs[0][0]
        for x in outdeg:
            # 如果有节点出度比入度恰好多 1，那么只有它才能是起始节点
            if outdeg[x] == indeg[x] + 1:
                start = x
                break
        
        ans = list()
        
        # 深度优先搜索（Hierholzer 算法）求解欧拉通路
        def dfs(u: int) -> None:
            while edges[u]:
                v = edges[u].pop()
                dfs(v)
                ans.append([u, v])
        
        dfs(start)
        return ans[::-1]


if __name__ == '__main__':
    s = Solution()
    s.validArrangement([[8,5],[8,7],[0,8],[0,5],[7,0],[5,0],[0,7],[8,0],[7,8]])