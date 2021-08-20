---
title: Luogu
date: 2021-08-11 16:21:50
---

## 前言

本文为洛谷刷题记录, 对应题目网址为 <https://www.luogu.com.cn/problem/> 后面加上题目编号 如<https://www.luogu.com.cn/problem/P1000>

洛谷在线IDE: <https://www.luogu.com.cn/ide>

做题顺序题单来源: <https://studyingfather.com/archives/841>

使用三种编程语言，分别是 python, C++, Java, 虽然没有标签但三种语言都有各自的特点应该很好辨认:

- C++ 的带有头文件典型的如 `#include <bits/stdc++.h>`, 一般也有 `using namespace std;`
- Java 代码一般是 `public class Main` 类，以及 `import java.util.*;`
- 除了上述两种剩下的就是 python 代码了，和前面两种语言相比特点是没有分号和大括号
- 用什么语言做题看心情，不保证每题都有三语言解法

---

## 小技巧

### C++字符串流

但是对于大量数据只能一个数一个数转换，颇为繁琐

还有一种方法就是 stringstream (使用stringstream 需包含头文件 `<sstream>`）

```cpp
int a = 123, b = 456, c = 789;

stringstream ss;

ss << a << b << c;
```

以上几行把a b c三个变量读入字符串流中，这样就可以把a b c三个变量无缝衔接起来，但是需要注意的是，stringstream型不能直接输出，也不支持迭代器，需要利用stringstream类的成员函数str()才能把它当成普通字符串来用，例如

```cpp
string s = ss.str();
```

而把字符串转为数值的话也是用stringstream，例如上面的ss就可以转换为一个int型

```cpp
int i;

ss >> i;
```

以上都是C++的方法，c语言有sprintf和sscanf，对应stringstream字符串流的读和写，`<stdlib.h>`中还有数值与字符串相互转换的iota和atoi函数，感兴趣的可以自己去了解。用c语言的sprintf比C++的字符串流效率高，但是我还是想用C++的字符串，为啥？因为C++字符串的可拓展性和灵活性比较高嘛hhhh

### C++输入输出问题

关同步，不能 `cin, scanf` 和 `cout, printf` 混用了，但能加快 `cin, cout` 的速度, 注意也不要用 `endl` 而用 `"\n"` 代替

```cpp
#include <cstdio>
#include <iostream>
using namespace std;
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    std::cout.tie(0);
    // 解题代码
    memset(vis,0,sizeof(vis));//初始化数组
}
```

### 输入输出重定向

```cpp
#include <cstdio>
int main() {
    // 标准声明：FILE *freopen( const char *path, const char *mode, FILE *stream );
    freopen("P1000.in", "r", stdin);  // 输入流重定向
    freopen("P1000.out", "w", stdout);  // 输出流重定向
    return 0;
}
```

```java
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.PrintStream;
import java.util.Scanner;

public class Main {
    public static void main(String[] args) throws FileNotFoundException {
        // 标准输入流重定向
        System.setIn(new FileInputStream("P1000_1.in"));
        // 标准输出流重定向
        System.setOut(new PrintStream(new FileOutputStream("P1000_1.out")));
        Scanner sc = new Scanner(System.in);
        // 设置分隔符（可以使用正则匹配）
        sc.useDelimiter("\n");
        System.out.println(sc.nextLine());
        sc.close();
    }
}
```

### 快速幂和快速素数判断

- 最简单的方法是对 $2 ~ \sqrt{n}$ 进行取余测试
- 给出了数据范围可以直接打出素数表
- Rabin-Miller测试（底分别是$2,3,5,7,11,13,17$的7次测试最小反例是 $341550071728321$, 在该范围内可以认为 “伪素数” 就是 素数）（$2, 325, 9375, 28178, 450775, 9780504, 1795265022$这组数在 $2^{64}$内都没有反例）
- 再优化，快速幂，FFT等等都能上，不过数据量没大到需要这些优化的程度

Rabin-Miller测试

摘自[知乎](https://zhuanlan.zhihu.com/p/220203643)

```cpp
typedef long long ll;
ll qpow(ll a, ll n, ll p)    // 快速幂
{
    ll ans = 1;
    while (n) {
        if (n & 1)
            ans = (__int128)ans * a % p;    // 注意！中间结果可能溢出，需要使用__int128过渡
        a = (__int128)a * a % p;
        n >>= 1;
    }
    return ans;
}
bool is_prime(ll x) {
    if (x < 3)    // 特判1，2
        return x == 2;
    if (x % 2 == 0)    // 特判偶数
        return false;
    ll A[] = {2, 325, 9375, 28178, 450775, 9780504, 1795265022}, d = x - 1, r = 0;
    while (d % 2 == 0)    // 算出d, r
        d /= 2, ++r;
    // 或：r = __builtin_ctz(d), d >>= r;
    for (auto a : A) {
        ll v = qpow(a, d, x);    // a^d
        // 如果a^d≡0，说明是a是x的倍数；如果a^d≡1或-1，说明这串数接下来一定都是1，不用继续计算
        if (v <= 1 || v == x - 1)
            continue;
        for (int i = 0; i < r; ++i) {
            v = (__int128)v * v % x;         // 同样使用__int128过渡
            if (v == x - 1 && i != r - 1)    // 得到-1，说明接下来都是1，可以退出了
            {
                v = 1;
                break;
            }
            // 在中途而非开头得到1，却没有经过-1，说明存在其他数字y≠-1满足y^2≡1，则x一定不是奇素数
            if (v == 1)
                return false;
        }
        if (v != 1)    // 查看是不是以1结尾
            return false;
    }
    return true;
}
```

自己改写的(甚至可以说是抄的。。。)：

```cpp
long quickpow(int x, int n, int mod) {
    // x ^ n % mod 快速幂
    long ans = 1;
    while (n != 0) {
        if (n & 1 == 1)
            ans = ans * x % mod;
        x = x * x % mod;
        n >>= 1;
    }
    return ans;
}

bool isprime(int x) {
    if (x < 3) return x == 2;
    if (x % 2 == 0) return false;
    int s[] = {2, 3, 5, 7, 11, 13, 17};
    int d = x - 1, r = 0;
    while (d % 2 == 0) {
        d >>= 1;
        ++r;
    }
    for (int b : s) {
        long y = quickpow(b, d, x);
        if (y == 1 || y == 0 || y == x - 1) continue;
        for (int i = 0; i < r; ++i) {
            y = y * y % x;
            if (y == x - 1 && i != r - 1) {
                y = 1;
                break;
            }
            if (y == 1) return false;
        }
        if (y != 1) return false;
    }
    return true;
}
```

### 矩阵快速幂

```java
public class Main {
    public int[][] matrix_mul(int[][] A, int[][] B, int mod) {
        // 简单矩阵乘法
        int r = A.length, c = B[0].length, d = B.length;
        if (d != A[0].length) // 不合理的矩阵乘法
            return null;
        int[][] s = new int[r][c];
        for (int i = 0; i < r; ++i) {
            for (int k = 0; k < d; ++k) {
                long tmp = (long) A[i][k];
                for (int j = 0; j < c; ++j) {
                    s[i][j] = (int) ((tmp * B[k][j] + s[i][j]) % mod);
                }
            }
        }
        return s;
    }

    public int[][] quickpow(int[][] A, int n, int mod) {
        // 矩阵快速幂
        int r = A.length;
        // 初值为 单位矩阵
        int[][] s = new int[r][r];
        for (int i = 0; i < r; ++i)
            s[i][i] = 1;
        while (n != 0) {
            if ((n & 1) == 1)
                s = matrix_mul(s, A, mod);
            A = matrix_mul(A, A, mod);
            n >>= 1;
        }
        return s;
    }

    public int[][] matrix_mul(int[][] A, int[][] B) {
        // 简单矩阵乘法(不取模版本)
        int r = A.length, c = B[0].length, d = B.length;
        if (d != A[0].length) // 不合理的矩阵乘法
            return null;
        int[][] s = new int[r][c];
        for (int i = 0; i < r; ++i) {
            for (int k = 0; k < d; ++k) {
                for (int j = 0; j < c; ++j) {
                    s[i][j] += A[i][k] * B[k][j];
                }
            }
        }
        return s;
    }

    public int[][] quickpow(int[][] A, int n) {
        // 矩阵快速幂(不取模版本)
        int r = A.length;
        // 初值为 单位矩阵
        int[][] s = new int[r][r];
        for (int i = 0; i < r; ++i)
            s[i][i] = 1;
        while (n != 0) {
            if ((n & 1) == 1)
                s = matrix_mul(s, A);
            A = matrix_mul(A, A);
            n >>= 1;
        }
        return s;
    }
}
```

```python
from typing import List

def matrix_mul(x: List[List[int]], y: List[List[int]], mod: int = 0) -> List[List[int]]:
    """矩阵乘法"""
    n1, n2, m1, m2 = len(x), len(x[0]), len(y), len(y[0])
    if n2 != m1:  # 无法做矩阵乘法
        return False
    ans = []
    for i in range(n1):
        # row = [sum((x[i][k] * y[k][j] % mod) if mod else x[i][k] * y[k][j] for k in range(m1)) for j in range(m2)]
        row = []
        for j in range(m2):
            s = 0
            for k in range(m1):
                if mod:
                    s += x[i][k] * y[k][j] % mod
                else:
                    s += x[i][k] * y[k][j]
            row.append(s)
        ans.append(row)
    return ans


def quickpow(x: List[List[int]], n: int, mod: int = 0) -> List[List[int]]:
    """矩阵快速幂"""
    # 初值是与 x 同阶的单位矩阵
    s = len(x)
    ans = [[int(i == j) for j in range(s)] for i in range(s)]
    while n:
        if n & 1:
            ans = matrix_mul(ans, x, mod)
        x = matrix_mul(x, x, mod)
        n >>= 1
    return ans
```

---

## 试机题

完全没有难度的题目，抛开编程小学生都会的题目

---

### 基本输入输出

1. 两数之和

```cpp
#include <bits/stdc++.h>
using namespace std;
int main(){
    long long a, b;
    cin >> a >> b;
    cout << a + b << endl;
    return 0;
}
```

```C
#include <stdio.h>
int main(){
    long long a, b;
    scanf("%d %d", &a, &b);
    printf("%d", a + b);
    return 0;
}
```

```python
print(sum(map(int, input().split())))
```

```java
import java.util.*;
public class Main{
    public static void main(String[] args){
        Scanner in = new Scanner(System.in);
        long long a = in.nextInt();
        long long b = in.nextInt();
        System.out.println(a + b);
    }
}
```

### P1000 超级玛丽游戏

#### 题目描述

超级玛丽是一个非常经典的游戏。请你用字符画的形式输出超级玛丽中的一个场景。

```cpp
                ********
               ************
               ####....#.
             #..###.....##....
             ###.......######              ###            ###
                ...........               #...#          #...#
               ##*#######                 #.#.#          #.#.#
            ####*******######             #.#.#          #.#.#
           ...#***.****.*###....          #...#          #...#
           ....**********##.....           ###            ###
           ....****    *****....
             ####        ####
           ######        ######
##############################################################
#...#......#.##...#......#.##...#......#.##------------------#
###########################################------------------#
#..#....#....##..#....#....##..#....#....#####################
##########################################    #----------#
#.....#......##.....#......##.....#......#    #----------#
##########################################    #----------#
#.#..#....#..##.#..#....#..##.#..#....#..#    #----------#
##########################################    ############
```

#### 输入格式

无输入

#### 输出格式

无输出

#### 输入输出样例

无

#### 解答代码

```python
s = """                ********
               ************
               ####....#.
             #..###.....##....
             ###.......######              ###            ###
                ...........               #...#          #...#
               ##*#######                 #.#.#          #.#.#
            ####*******######             #.#.#          #.#.#
           ...#***.****.*###....          #...#          #...#
           ....**********##.....           ###            ###
           ....****    *****....
             ####        ####
           ######        ######
##############################################################
#...#......#.##...#......#.##...#......#.##------------------#
###########################################------------------#
#..#....#....##..#....#....##..#....#....#####################
##########################################    #----------#
#.....#......##.....#......##.....#......#    #----------#
##########################################    #----------#
#.#..#....#..##.#..#....#..##.#..#....#..#    #----------#
##########################################    ############"""
print(s)
```

---

### P1001 A+B Problem

#### 题目描述

输入两个整数 a, ba,b，输出它们的和（$|a|,|b| \leq 10^9$ ）。

注意

1. Pascal 使用 integer 会爆掉哦！
2. 有负数哦！
3. C/C++ 的 main 函数必须是 int 类型，而且 C 最后要 return 0。这不仅对洛谷其他题目有效，而且也是 NOIP/CSP/NOI 比赛的要求！

好吧，同志们，我们就从这一题开始，向着大牛的路进发。

#### 输入格式

两个以空格分开的整数。

#### 输出格式

一个整数。

#### 输入输出样例

输入：20 30

输出：50

#### 解题思路

幼儿园小朋友都会的问题，主要是学习下数据的输入和输出

#### 解答代码

```python
print(sum(map(int, input().split())))
```

```java
import java.util.*;

public class Main {
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        int a = in.nextInt(), b = in.nextInt();
        System.out.println(a + b);
    }
}
```

```cpp
#include <bits/stdc++.h>

int main() {
    int a, b;
    std::cin >> a >> b;
    std::cout << a + b << std::endl;
    return 0;
}
```

---

### P1008 [NOIP1998 普及组] 三连击

#### 题目描述

将 1,2,…,9 共 9 个数分成 3 组，分别组成 3 个三位数，且使这 3 个三位数构成 1:2:3 的比例，试求出所有满足条件的 3 个三位数。

#### 输入格式

无输入

#### 输出格式

若干行，每行 3 个数字。按照每行第 1 个数字升序排列。

#### 输入输出样例

输入: #1

无

输出: #1

```cpp
192 384 576
* * *
...

* * *
（剩余部分不予展示）
```

#### 解题思路

枚举第一个数，然后按照比例计算出第二个数和第三个数，然后检查这三个数是否满足 由1~9组成

可以大概估算下范围：第一个数最小是 123，最大是 987 / 3 或 999 / 3

#### 解答代码

```python
ans = []
number = "123456789"
for i in range(123, 333):
    s = str(i)
    if '0' in s:
        continue
    s = "".join([s, str(i * 2), str(i * 3)])
    for n in number:
        if n not in s:
            break
    else:
        ans.append([i, i * 2, i * 3])
for a, b, c in ans:
    print(a, b, c)
```

```cpp
#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    void threenumber(){
    // vis[i] 表示 i + 1 已经有了
        vector<int> vis(9, 0);
        for (int i = 123; i < 333; ++i) {
            int x = i, y = i * 2, z = i * 3;
            while (x != 0) {
                int s = x % 10;
                x /= 10;
                if (s == 0 || vis[s - 1] == 1) goto end;
                else vis[s - 1] = 1;
            }
            while (y != 0) {
                int s = y % 10;
                y /= 10;
                if (s == 0 || vis[s - 1] == 1) goto end;
                else vis[s - 1] = 1;
            }
            while (z != 0) {
                int s = z % 10;
                z /= 10;
                if (s == 0 || vis[s - 1] == 1) goto end;
                else vis[s - 1] = 1;
            }
            cout << i << " " << i * 2 << " " << i * 3 << endl;
            end:
            for (int j = 0; j < 9; ++j) vis[j] = 0;
        }
    }
};

int main() {
    Solution s;
    s.threenumber();
    return 0;
}
```

```java
import java.util.*;

public class Main {
    public static void main(String[] args) {
        loop1:for (int i = 123; i < 333; ++i) {
            int[] vis = new int[9];
            int a = i, b = i * 2, c = i * 3;
            while (a > 0) {
                int s = a % 10;
                a /= 10;
                if (s == 0 || vis[s - 1] == 1) continue loop1;
                else vis[s - 1] = 1;
            }
            while (b > 0) {
                int s = b % 10;
                b /= 10;
                if (s == 0 || vis[s - 1] == 1) continue loop1;
                else vis[s - 1] = 1;
            }
            while (c > 0) {
                int s = c % 10;
                c /= 10;
                if (s == 0 || vis[s - 1] == 1) continue loop1;
                else vis[s - 1] = 1;
            }
            System.out.println(Integer.toString(i) + " " + Integer.toString(i * 2) + " " + Integer.toString(i * 3));
        }
    }
}
```

---

## 入门级-语言基础题

### P1421 小玉买文具

#### 题目描述

班主任给小玉一个任务，到文具店里买尽量多的签字笔。已知一只签字笔的价格是 1 元 9 角，而班主任给小玉的钱是 a 元 b 角，小玉想知道，她最多能买多少只签字笔呢。

#### 输入格式

输入只有一行两个整数，分别表示 a 和 b。

#### 输出格式

输出一行一个整数，表示小玉最多能买多少只签字笔。

#### 输入输出样例

输入: #1

```cpp
10 3
```

输出: #1

```cpp
5
```

#### 说明/提示

数据规模与约定

对于全部的测试点，保证 $0 \leq a \leq 10^4, 0 \leq b \leq 9 $

#### 解题思路

和生活中的钱计算一样，将“角”转为“元”再即可

#### 解答代码

```python
a, b = map(int, input().split())
print(int((a + b / 10) / 1.9))
```

```cpp
#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    int BuyStationery(int a, int b) {
        double money = a + (double)b / 10;
        return (int)(money / 1.9);
    }
};

int main() {
    int a, b;
    Solution s;
    cin >> a >> b;
    cout << s.BuyStationery(a, b) << endl;
    return 0;
}
```

```java
import java.util.*;
public class Main {
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        int a = in.nextInt(), b = in.nextInt();
        double money = a + (double)b / 10;
        System.out.println((int)(money / 1.9));
    }
}
```

---

### P1909 [NOIP2016 普及组] 买铅笔

#### 题目描述

P老师需要去商店买n支铅笔作为小朋友们参加NOIP的礼物。她发现商店一共有 3种包装的铅笔，不同包装内的铅笔数量有可能不同，价格也有可能不同。为了公平起 见，P老师决定只买同一种包装的铅笔。

商店不允许将铅笔的包装拆开，因此P老师可能需要购买超过n支铅笔才够给小朋 友们发礼物。

现在P老师想知道，在商店每种包装的数量都足够的情况下，要买够至少n支铅笔最少需要花费多少钱。

#### 输入格式

第一行包含一个正整数n，表示需要的铅笔数量。

接下来三行，每行用2个正整数描述一种包装的铅笔：其中第1个整数表示这种 包装内铅笔的数量，第2个整数表示这种包装的价格。

保证所有的7个数都是不超过10000的正整数。

#### 输出格式

1个整数，表示P老师最少需要花费的钱。

#### 输入输出样例

输入: #1

```cpp
57
2 2
50 30
30 27
```

输出: #1

```cpp
54
```

输入: #2

```cpp
9998
128 233
128 2333
128 666
```

输出: #2

```cpp
18407
```

输入: #3

```cpp
9999
101 1111
1 9999
1111 9999
```

输出: #3

```cpp
89991
```

#### 解题思路

只能买同一个包装的，那就太简单了，枚举三种情况取最小值即可

置于每一种情况的计算，小学生的问题没必要解释了吧~

#### 解答代码

```cpp
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int BuyPencils(int n, vector<vector<int> > & pencils) {
        int ans = 0x7FFFFFFF;
        for (int i = 0; i < 3; ++i) {
            // 数量、价格
            int x = pencils[i][0], y = pencils[i][1];
            ans = min(ans, (n / x + (n % x > 0 ? 1 : 0)) * y);
        }
        return ans;
    }
};

int main() {
    int n;
    vector<vector<int> > pencils(3, vector<int>(2, 0));
    cin >> n;
    for (int i = 0; i < 3; ++i){
        cin >> pencils[i][0] >> pencils[i][1];
    }
    Solution s;
    cout << s.BuyPencils(n, pencils);
    return 0;
}
```

```java
import java.util.*;

public class Main {
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        int n = in.nextInt();
        int[][] pencils = new int[3][2];
        for (int[] p : pencils) {
            p[0] = in.nextInt();
            p[1] = in.nextInt();
        }
        System.out.println(new Main().BuyPencils(n, pencils));
        in.close();
    }

    public int BuyPencils(int n, int[][] pencils) {
        int ans = Integer.MAX_VALUE;
        for (int[] p : pencils) {
            int num = p[0], prices = p[1];
            ans = Math.min(ans, (prices * (n / num + (n % num == 0 ? 0 : 1))));
        }
        return ans;
    }
}
```

```python
n = int(input())
pencils = []
for _ in range(3):
    pencils.append(map(int, input().split()))
ans = min(b * (n // a + (1 if n % a else 0)) for a, b in pencils)
print(ans)
```

---

### P1089 [NOIP2004 提高组] 津津的储蓄计划

#### 题目描述

津津的零花钱一直都是自己管理。每个月的月初妈妈给津津300元钱，津津会预算这个月的花销，并且总能做到实际花销和预算的相同。

为了让津津学习如何储蓄，妈妈提出，津津可以随时把整百的钱存在她那里，到了年末她会加上20%还给津津。因此津津制定了一个储蓄计划：每个月的月初，在得到妈妈给的零花钱后，如果她预计到这个月的月末手中还会有多于100元或恰好100元，她就会把整百的钱存在妈妈那里，剩余的钱留在自己手中。

例如11月初津津手中还有83元，妈妈给了津津300元。津津预计11月的花销是180元，那么她就会在妈妈那里存200元，自己留下183元。到了11月月末，津津手中会剩下33元钱。

津津发现这个储蓄计划的主要风险是，存在妈妈那里的钱在年末之前不能取出。有可能在某个月的月初，津津手中的钱加上这个月妈妈给的钱，不够这个月的原定预算。如果出现这种情况，津津将不得不在这个月省吃俭用，压缩预算。

现在请你根据2004年1月到12月每个月津津的预算，判断会不会出现这种情况。如果不会，计算到2004年年末，妈妈将津津平常存的钱加上20％还给津津之后，津津手中会有多少钱。

#### 输入格式

12行数据，每行包含一个小于350的非负整数，分别表示11月到12月津津的预算。

#### 输出格式

一个整数。如果储蓄计划实施过程中出现某个月钱不够用的情况，输出-X，X表示出现这种情况的第一个月；否则输出到2004年年末津津手中会有多少钱。

注意，洛谷不需要进行文件输入输出，而是标准输入输出。

#### 输入输出样例

输入: #1

```cpp
290
230
280
200
300
170
340
50 
90 
80 
200
60 
```

输出: #1

```cpp
-7 
```

输入: #2

```cpp
290 
230 
280 
200 
300 
170 
330 
50 
90 
80 
200 
60 
```

输出: #2

```cpp
1580
```

#### 解题思路

题目中已经给出了明确的计算流程，对于这种题目，选择合适的数据结构模拟即可

这题并没有什么需要使用的数据结构，记下每个月剩下的钱即可

#### 解答代码

```cpp
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int Jinjinplan(vector<int>& nums) {
        int n = nums.size(); // 12
        int pre = 0, s = 0; // 上个月剩下的零钱, 存下的零钱
        for (int i = 0; i < n; ++i) {
            int cur = pre + 300 - nums[i]; // 本月除去预算剩下的
            if (cur < 0) return -(i + 1);
            pre = cur % 100;
            s += cur - pre;
        }
        return int(s * 1.2) + pre;
    }
};

int main() {
    vector<int> nums(12, 0);
    for (int i = 0; i < 12; ++i) {
        cin >> nums[i];
    }
    Solution s;
    cout << s.Jinjinplan(nums);
    return 0;
}
```

```java
import java.util.*;

public class Main {
    public static void main(String[] args) {
        int[] nums = new int[12];
        Scanner sc = new Scanner(System.in);
        for (int i = 0; i < 12; ++i) {
            nums[i] = sc.nextInt();
        }
        Main s = new Main();
        System.out.println(s.Jinjinplan(nums));
        sc.close();
    }

    public int Jinjinplan(int[] nums) {
        int n = nums.length; // 12
        int pre = 0, s = 0; // 上个月剩下的和存在妈妈那里的
        for (int i = 0; i < n; ++i) {
            int cur = 300 + pre - nums[i];
            if (cur < 0)
                return -(i + 1); // 不够花了
            pre = cur % 100;
            s += cur - pre;
        }
        return (int)((double)s * 1.2) + pre;
    }
}
```

```python
class Solution:
    def Jinjinplan(self, nums):
        pre, s = 0, 0
        for i, m in enumerate(nums):
            cur = 300 + pre - m
            if cur < 0: return -(i + 1)
            pre = cur % 100
            s += cur - pre
        return int(s * 1.2) + pre

nums = [int(input()) for _ in range(12)]
print(Solution().Jinjinplan(nums))
```

---

### P1085 [NOIP2004 普及组] 不高兴的津津

#### 题目描述

津津上初中了。妈妈认为津津应该更加用功学习，所以津津除了上学之外，还要参加妈妈为她报名的各科复习班。另外每周妈妈还会送她去学习朗诵、舞蹈和钢琴。但是津津如果一天上课超过八个小时就会不高兴，而且上得越久就会越不高兴。假设津津不会因为其它事不高兴，并且她的不高兴不会持续到第二天。请你帮忙检查一下津津下周的日程安排，看看下周她会不会不高兴；如果会的话，哪天最不高兴。

#### 输入格式

输入包括7行数据，分别表示周一到周日的日程安排。每行包括两个小于10的非负整数，用空格隔开，分别表示津津在学校上课的时间和妈妈安排她上课的时间。

#### 输出格式

一个数字。如果不会不高兴则输出0，如果会则输出最不高兴的是周几（用1, 2, 3, 4, 5, 6, 7分别表示周一，周二，周三，周四，周五，周六，周日）。如果有两天或两天以上不高兴的程度相当，则输出时间最靠前的一天。

#### 输入输出样例

输入: #1

```cpp
5 3
6 2
7 2
5 3
5 4
0 4
0 6
```

输出: #1

```cpp
3
```

#### 解题思路

抽象的说，就是在一个长度为 7 的数组中查找大于 8 且最大数的下标

#### 解答代码

```cpp
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int UnhappyJinjin(vector<int>& nums) {
        int data = 0, tim = -1;
        for (int i = 0; i < 7; ++i) {
            if (nums[i] > 8 && nums[i] > tim) {
                data = i + 1;
                tim = nums[i];
            }
        }
        return data;
    }
};

int main() {
    vector<int> nums(7, 0);
    for (int i = 0; i < 7; ++i) {
        int a, b;
        cin >> a >> b;
        nums[i] = a + b;
    }
    Solution s;
    cout << s.UnhappyJinjin(nums) << endl;
    return 0;
}
```

```java
import java.util.*;
public class Main {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int data = 0, tim = -1;
        for (int i = 0; i < 7; ++i) {
            int s = sc.nextInt() + sc.nextInt();
            if (s > 8 && s > tim) {
                data = i + 1;
                tim = s;
            }
        }
        System.out.println(data);
        sc.close();
    }
}
```

```python
nums = [sum(map(int, input().split())) for _ in range(7)]
ans = 0
m = -1
for i, j in enumerate(nums):
    if j > 8 and  j > m:
        ans = i + 1
        m = j
print(ans)
```

---

### P1035 [NOIP2002 普及组] 级数求和

#### 题目描述

已知：$S_n= 1+1/2+1/3+…+1/n$。显然对于任意一个整数 $k$，当 $n$ 足够大的时候，$S_n > k$。

现给出一个整数 $k$，要求计算出一个最小的 $n$，使得 $S_n > k$。

#### 输入格式

一个正整数 k。

#### 输出格式

一个正整数 n。

#### 输入输出样例

输入: #1

```cpp
1
```

输出: #1

```cpp
2
```

输入: #2

```cpp
15
```

输出: #2

```cpp
1835421
```

#### 数据范围

对于 $100\%$ 的数据，$1\le k \le 15$。

#### 解题思路

调和级数是发散的，模拟即可, 时间复杂度 $O(e^k)$

调和级数没有通项公式，但有近似公式 $S_n = ln(n) + 0.5772$, 可以直接解方程得到 $n$

$n > e^{k - 0.5772}$

#### 解答代码

方法一：模拟

```cpp
#include <iostream>

int main() {
    int k;
    std::cin >> k;
    int i = 0;
    double s = 0;
    while (s <= k) {
        s += 1.0 / (++i);
    }
    std::cout << i << std::endl;
    return 0;
}
```

```java
import java.util.*;

public class Main {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int k = sc.nextInt();
        double s = 0;
        int i;
        for (i = 0; !(s > k); ) {
            s += 1.0 / (double) (++i);
        }
        System.out.println(i);
        sc.close();
    }
}
```

```python
k = int(input())
s, i = 0, 0
while not s > k:
    i += 1
    s += 1 / i
print(i)
```

方法二：数学

```python
import math
print(int(math.exp(int(input()) - 0.5772156649) + 0.5))
```

---

### P1980 [NOIP2013 普及组] 计数问题

#### 题目描述

试计算在区间 $1$ 到 $n$ 的所有整数中，数字 $x$（$0\leq x\leq9$）共出现了多少次？例如，在 $1$ 到 $11$ 中，即在 $1,2,3,4,5,6,7,8,9,10,11$ 中，数字 $1$ 出现了 $4$ 次。

#### 输入格式

$2$ 个整数 $n,x$，之间用一个空格隔开。

#### 输出格式

$1$ 个整数，表示 $x$ 出现的次数。

#### 输入输出样例

输入: #1

```cpp
11 1
```

输出: #1

```cpp
4
```

#### 数据范围

对于 $100\%$ 的数据，$1\le n\le 10^6$，$0\le x \le 9$

#### 解题思路

1. 如题，计数即可，时间复杂度 $O(nlog_{10}n)$
2. 找规律，例如 `n = 128, x = 1` (62个)
   1. 个位为 1 的 13 种: 1, 11, 21, 32, ... , 121 (规律是不看个位数那就是 0 ~ 12)
   2. 十位为 1 的 20 种: 10 ~ 19, 110 ~ 119 (规律是不看个位和十位那就是 0 ~ 1, 只看个位就是 0 ~ 9)
   3. 百位为 1 的 29 种: 100 ~ 128
   4. 由此可得时间复杂度为 $O(log_{10}n)$ 的方法

#### 解答代码

方法一：模拟&计数

```cpp
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int CountProblem(int n, int x) {
        int cnt = 0;
        for (int i = 1; i <= n; ++i) {
            int s = i;
            while (s > 0) {
                if (s % 10 == x) ++cnt;
                s /= 10;
            }
        }
        return cnt;
    }
};

int main() {
    Solution s;
    int n, x;
    cin >> n >> x;
    cout << s.CountProblem(n, x) << endl;
    return 0;
}
```

```java
import java.util.*;
public class Main {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int n = sc.nextInt(), x = sc.nextInt();
        sc.close();
        Main s = new Main();
        System.out.println(s.CountProblem(n, x));
    }
    
    public int CountProblem(int n, int x) {
        int cnt = 0;
        for (int i = 1; i <= n; ++i) {
            for (int j = i; j > 0; j /= 10) {
                if (j % 10 == x) ++cnt;
            }
        }
        return cnt;
    }
}
```

```python
n, x = input().split()
cnt = 0
for i in range(1, int(n) + 1):
    cnt += str(i).count(x)
print(cnt)
```

方法二：找规律(参考了评论区的代码)

```java
import java.util.*;
public class Main {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int n = sc.nextInt(), x = sc.nextInt();
        sc.close();
        Main s = new Main();
        System.out.println(s.CountProblem(n, x));
    }
    
    public int CountProblem(int n, int k) {
        int cnt = 0;
        for (int base = 1; base <= n; base *= 10) {
            // x, y, z 分别表示第 i 位 前， 中， 后的数值，如12580第3位 - 12,5,80
            int x = n / base / 10, y = (n / base) % 10, z = n % base;
            if (k != 0) {
                if (y > k)
                    cnt += (x + 1) * base;
                else if (y == k)
                    cnt += x * base + z + 1;
                else
                    cnt += x * base;
            }
            else {
                if (y == 0)
                    cnt += (x - 1) * base + z + 1;
                else
                    cnt += x * base;
            }
        }
        return cnt;
    }
}
```

---

### P1014 [NOIP1999 普及组] Cantor 表

#### 题目描述

现代数学的著名证明之一是 Georg Cantor 证明了有理数是可枚举的。他是用下面这一张表来证明这一命题的：

$1/1$ ,   $1/2$ ,   $1/3$ ,   $1/4$,    $1/5$,   …

$2/1$,   $2/2$ ,   $2/3$,    $2/4$,    …

$3/1$ ,   $3/2$,    $3/3$,    …

$4/1$,    $4/2$,    …

$5/1$,   …

…

我们以 Z 字形给上表的每一项编号。第一项是 $1/1$，然后是 $1/2$，$2/1$，$3/1$，$2/2$，…

#### 输入格式

整数$N$（$1 \leq N \leq 10^7$）。

#### 输出格式

表中的第 $N$ 项。

#### 输入输出样例

输入: #1

```cpp
7
```

输出: #1

```cpp
1/4
```

#### 解题思路

题目写得不是太清楚，但通过例子可以看出其实是在对角线上进行 Z 形的遍历

仔细观察不难发现对角线上的分数分子分母之和相等，并且第 $i$ 行有 $i$ 个分数，由此可以套用求和公式直接定位 $N$ 所在行数和在行中的位置，由此可以得到 $O(1)$ 时间复杂度的解法(具体细节参看注释吧)

#### 解答代码

```cpp
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    string Cantor(int n) {
        // 根据等差数列求和公式 (1 + i) * i / 2 = n 反推 n 所在行号 i
        int i = (int)ceil(sqrt(2 * (double)n + 0.25) - 0.5);
        int s = n - (i - 1) * i / 2; // 计算行内的具体位置
        if (i % 2 == 0) {
            // 偶数行逆序
            s = i + 1 - s;
        }
        return to_string(i + 1 - s) + "/" + to_string(s);
    }
};

int main() {
    Solution s;
    int n;
    cin >> n;
    cout << s.Cantor(n) << endl;
    return 0;
}
```

```java
import java.util.*;
public class Main {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        Main s = new Main();
        int n = sc.nextInt();
        sc.close();
        System.out.println(s.Cantor(n));
    }

    public String Cantor(int n) {
        // 根据等差数列求和公式 (1 + i) * i / 2 = n 反推 n 所在行号 i
        int i = (int)Math.ceil(Math.sqrt(2 * (double)n +0.25) - 0.5);
        int s = n - (i - 1) * i / 2; // 计算行内的具体位置
        if (i % 2 == 0) {
            // 偶数行逆序
            s = i + 1 - s;
        }
        return Integer.toString(i + 1 - s) + "/" + Integer.toString(s);
    }
}
```

```python
import math
n = int(input())
# 根据等差数列求和公式 (1 + i) * i / 2 = n 反推 n 所在行号 i
i = math.ceil(math.sqrt(2 * n + 0.25) - 0.5)
s = n - (i - 1) * i // 2 # 计算行内的具体位置
if i % 2 == 0:
    s = i - s + 1
print("{}/{}".format(i + 1 - s, s))
```

---

### P1307 [NOIP2011 普及组] 数字反转

#### 题目描述

给定一个整数，请将该数各个位上数字反转得到一个新数。新数也应满足整数的常见形式，即除非给定的原数为零，否则反转后得到的新数的最高位数字不应为零（参见样例2）。

#### 输入格式

一个整数 $N$

#### 输出格式

一个整数，表示反转后的新数。

#### 输入输出样例

输入: #1

```cpp
123
```

输出: #1

```cpp
321
```

输入: #2

```cpp
-380
```

输出: #2

```cpp
-83
```

#### 数据范围

$-1,000,000,000≤N≤1,000,000,000 $。

#### 解题思路

1. 好像没什么技巧，就取余除10运算就行(要注意取值范围)
2. 也可以当成字符串翻转

#### 解答代码

三种语言的实现有点不同

```cpp
#include <iostream>

class Solution {
public:
    long Reverse(long n) {
        // 保险起见输入输出都用 long
        long res = 0;
        while (n != 0) {
            res = res * 10 + n % 10;
            n /= 10;
        }
        return res;
    }
};

int main() {
    Solution s;
    long n;
    std::cin >> n;
    std::cout << s.Reverse(n) << std::endl;
    return 0;
}
```

```java
import java.util.*;

public class Main {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        Main s = new Main();
        String st = sc.next();
        sc.close();
        System.out.println(s.Reverse(st));
    }

    public String Reverse(String _s) {
        // 特殊处理下0
        if (_s.equals("0"))
            return "0";
        // 如果数字很大，那就必须得在字符串上进行翻转操作了
        StringBuilder sb = new StringBuilder();
        char[] s = _s.toCharArray();
        int n = s.length, end = 0;
        if (s[0] == '-') {
            sb.append('-');
            end = 1;
        }
        boolean tag = false; // 用于处理末尾为 0 反转后 0 在最前面的问题
        for (int i = n - 1; i >= end; --i) {
            if (tag)
                sb.append(s[i]);
            else if (s[i] != '0') {
                sb.append(s[i]);
                tag = true;
            }
        }
        return sb.toString();
    }
}
```

```python
def Reverse(n: int) -> int:
    """转字符串反转后再转回数字"""
    if n >= 0:
        return int(str(n)[::-1])
    else:
        return -int(str(n)[-1:0:-1])

print(Reverse(int(input())))
```

---

## 入门级-数组基础

### P1046 [NOIP2005 普及组] 陶陶摘苹果

#### 题目描述

陶陶家的院子里有一棵苹果树，每到秋天树上就会结出 $10$ 个苹果。苹果成熟的时候，陶陶就会跑去摘苹果。陶陶有个 $30$ 厘米高的板凳，当她不能直接用手摘到苹果的时候，就会踩到板凳上再试试。

现在已知 $10$ 个苹果到地面的高度，以及陶陶把手伸直的时候能够达到的最大高度，请帮陶陶算一下她能够摘到的苹果的数目。假设她碰到苹果，苹果就会掉下来。

#### 输入格式

输入包括两行数据。第一行包含 $10$ 个 $100$ 到 $200$ 之间（包括 $100$ 和 $200$ ）的整数（以厘米为单位）分别表示 $10$ 个苹果到地面的高度，两个相邻的整数之间用一个空格隔开。第二行只包括一个 $100$ 到 $120$ 之间（包含 $100$ 和 $120$ ）的整数（以厘米为单位），表示陶陶把手伸直的时候能够达到的最大高度。

#### 输出格式

输出包括一行，这一行只包含一个整数，表示陶陶能够摘到的苹果的数目。

#### 输入输出样例

输入: #1

```cpp
100 200 150 140 129 134 167 198 200 111
110
```

输出: #1

```cpp
5
```

#### 说明&提示

无

#### 解题思路

计数即可

#### 解答代码

```cpp
#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    int PickApples(vector<int>& nums, int h) {
        // nums 记录苹果高度，h 记录陶陶身高
        int cnt = 0;
        h += 30;
        for (int apple: nums) {
            if (h >= apple) cnt++;
        }
        return cnt;
    }
};

int main() {
    Solution s;
    int h;
    vector<int> nums(10);
    for (int i = 0; i < 10; ++i) {
        cin >> nums[i];
    }
    cin >> h;
    cout << s.PickApples(nums, h) << endl;
    return 0;
}
```

```java
import java.util.*;
public class Main {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        Main s = new Main();
        int[] nums = new int[10];
        for (int i = 0; i < 10; ++i) {
            nums[i] = sc.nextInt();
        }
        int h = sc.nextInt();
        sc.close();
        System.out.println(s.PickApples(nums, h + 30));
    }

    public int PickApples(int[] nums, int h) {
        int cnt = 0;
        for (int apple: nums) {
            if (h >= apple) cnt++;
        }
        return cnt;
    }
}
```

```python
from typing import List
class Solution():
    def PickApples(self, nums: List[int], h: int) -> int:
        """陶陶摘苹果"""
        return sum(1 for apple in nums if h >= apple)

print(Solution().PickApples(map(int, input().split()), int(input()) + 30))
```

---

### P1047 [NOIP2005 普及组] 校门外的树

#### 题目描述

某校大门外长度为 $l$ 的马路上有一排树，每两棵相邻的树之间的间隔都是 $1$ 米。我们可以把马路看成一个数轴，马路的一端在数轴 $0$ 的位置，另一端在 $l$ 的位置；数轴上的每个整数点，即 $0,1,2,\dots,l$，都种有一棵树。

由于马路上有一些区域要用来建地铁。这些区域用它们在数轴上的起始点和终止点表示。已知任一区域的起始点和终止点的坐标都是整数，区域之间可能有重合的部分。现在要把这些区域中的树（包括区域端点处的两棵树）移走。你的任务是计算将这些树都移走后，马路上还有多少棵树。

#### 输入格式

第一行有两个整数，分别表示马路的长度 $l$ 和区域的数目 $m$。

接下来 $m$ 行，每行两个整数 $u, v$，表示一个区域的起始点和终止点的坐标。

#### 输出格式

输出一行一个整数，表示将这些树都移走后，马路上剩余的树木数量。

#### 输入输出样例

输入: #1

```cpp
500 3
150 300
100 200
470 471
```

输出: #1

```cpp
298
```

#### 说明&提示

数据范围

- 对于 $20\%$ 的数据，保证区域之间没有重合的部分。
- 对于 $100\%$ 的数据，保证 $1 \leq l \leq 10^4$，$1 \leq m \leq 100$，$0 \leq u \leq v \leq l$。

#### 解题思路

1. 逐个标记
2. 线段树(简单题没必要用这么复杂的做法。。。才不是不会呢)

#### 解答代码

```cpp
#include <cstdio>
#include <vector>
using namespace std;

class Solution {
public:
    int CountTree(int s, vector<vector<int>>& nums) {
        vector<int> vis(s + 1, 1);
        for (vector<int>& loc : nums) {
            int start = loc[0], end = loc[1];
            for (int i = start; i <= end; ++i) {
                vis[i] = 0;
            }
        }
        int cnt = 0;
        for (int i : vis) {
            cnt += i;
        }
        return cnt;
    }
};

int main() {
    Solution s;
    int l, n;
    scanf("%d%d", &l, &n);
    vector<vector<int>> nums(n, vector<int>(2));
    for (int i = 0; i < n; ++i) {
        int start, end;
        scanf("%d%d", &start, &end);
        nums[i][0] = start;
        nums[i][1] = end;
    }
    printf("%d", s.CountTree(l, nums));
    return 0;
}
```

```java
import java.util.*;

public class Main {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int l = sc.nextInt(), m = sc.nextInt();
        int[] tree = new int[l + 1];
        for (int i = 0; i < m; ++i) {
            int start = sc.nextInt(), end = sc.nextInt();
            for (int j = start; j <= end; ++j) {
                tree[j] = 1;
            }
        }
        sc.close();
        int cnt = 0;
        for (int i : tree)
            cnt += i;
        System.out.println(l + 1 - cnt);
    }
}
```

---

### P1427 小鱼的数字游戏

#### 题目描述

小鱼最近被要求参加一个数字游戏，要求它把看到的一串数字 $a_i$（长度不一定，以 $0$ 结束），记住了然后反着念出来（表示结束的数字 $0$ 就不要念出来了）。这对小鱼的那点记忆力来说实在是太难了，你也不想想小鱼的整个脑袋才多大，其中一部分还是好吃的肉！所以请你帮小鱼编程解决这个问题。

#### 输入格式

一行内输入一串整数，以 $0$ 结束，以空格间隔。

#### 输出格式

一行内倒着输出这一串整数，以空格间隔。

#### 输入输出样例

输入: #1

```cpp
3 65 23 5 34 1 30 0
```

输出: #1

```cpp
30 1 34 5 23 65 3
```

#### 说明&提示

对于 $100\%$ 的数据，保证 $0 \leq a_i \leq 2^{31} - 1$，数字个数不超过 $100$。

#### 解题思路

用数组存储最后逆序输出即可

#### 解答代码

```cpp
#include <cstdio>
int nums[107];
int main() {
    int i = -1, s;
    scanf("%d", &s);
    while (s != 0) {
        nums[++i] = s;
        scanf("%d", &s);
    }
    while (i >= 0) {
        printf("%d ", nums[i--]);
    }
    return 0;
}
```

```java
import java.util.*;

public class Main {
    static int[] nums = new int[107];

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int i = -1, s = sc.nextInt();
        while (s != 0) {
            nums[++i] = s;
            s = sc.nextInt();
        }
        while (i >= 0) {
            System.out.print(nums[i--] + " ");
        }
        sc.close();
    }
}
```

```python
print(" ".join(input().split()[-2::-1]))
```

---

### P2141 [NOIP2014 普及组] 珠心算测验

#### 题目描述

珠心算是一种通过在脑中模拟算盘变化来完成快速运算的一种计算技术。珠心算训练，既能够开发智力，又能够为日常生活带来很多便利，因而在很多学校得到普及。

某学校的珠心算老师采用一种快速考察珠心算加法能力的测验方法。他随机生成一个正整数集合，集合中的数各不相同，然后要求学生回答：其中有多少个数，恰好等于集合中另外两个（不同的）数之和？

最近老师出了一些测验题，请你帮忙求出答案。

(本题目为2014NOIP普及T1)

#### 输入格式

共两行，第一行包含一个整数$n$，表示测试题中给出的正整数个数。

第二行有$n$个正整数，每两个正整数之间用一个空格隔开，表示测试题中给出的正整数。

#### 输出格式

一个整数，表示测验题答案。

#### 输入输出样例

输入: #1

```cpp
4
1 2 3 4
```

输出: #1

```cpp
2
```

#### 说明&提示

【样例说明】

由$1+2=3,1+3=4$，故满足测试要求的答案为$2$。  

注意，加数和被加数必须是集合中的两个不同的数。

【数据说明】

对于$100\%$的数据，$3 ≤ n ≤ 100$，测验题给出的正整数大小不超过$10,000$。

#### 解题思路

求满足 $a + b = c$ 且 $a,b,c$ 均在所给集合中的 $c$ 的数量

枚举其中两个数即可得到第三个数，检查第三个数是否在集合中即可

也可以枚举 $c$ 然后双指针查找另外两个数(要求数组要先排序)，时间复杂度不变

时间复杂度：$O(n^2)$ 时间界在于枚举两个数，双指针法同理
空间复杂度：$O(n)$

#### 解答代码

方法一：枚举+集合

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, v;
    scanf("%d", &n);
    unordered_set<int> s;
    for (int i = 0; i < n; ++i) {
        scanf("%d", &v);
        s.emplace(v);
    }
    unordered_set<int> ans;
    for (auto i = s.begin(); i != s.end(); i++) {
        for (auto j = next(i); j != s.end(); j++) {
            if (s.find(*i + *j) != s.end())
                ans.emplace(*i + *j);
        }
    }
    printf("%d", ans.size());
    return 0;
}
```

方法二：双指针

```java
import java.util.*;

public class Main {
    static int[] nums = new int[107];

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int n = sc.nextInt();
        int[] nums = new int[n];
        for (int i = 0; i < n; ++i) {
            nums[i] = sc.nextInt();
        }
        sc.close();
        Arrays.sort(nums);
        int cnt = 0;
        // A + B = C
        for (int i = 0; i < n; ++i) {
            // 枚举C，双指针查找 A,B
            int C = nums[i];
            int left = 0, right = i - 1;
            while (left < right && nums[left] + nums[right] != C) {
                int s = nums[left] + nums[right];
                if (s < C)
                    left++;
                else if (s > C)
                    right--;
            }
            if (left < right && nums[left] + nums[right] == C)
                cnt++;
        }
        System.out.println(cnt);
    }
}
```

---

### P5594 【XR-4】模拟赛

#### 题目描述

X 校正在进行 CSP 前的校内集训。

一共有 $n$ 名 OIer 参与这次集训，教练为他们精心准备了 $m$ 套模拟赛题。

然而，每名 OIer 都有各自的时间安排，巧合的是，他们在接下来的 $k$ 天中都恰好有 $m$ 天有空打模拟赛。

为了方便管理，教练规定一个人必须按顺序打完 $m$ 套模拟赛题。

比如，小 X 在接下来的第 $2,3,5$ 天有空打模拟赛，那么他就必须在第 $2$ 天打第 $1$ 套模拟赛题，第 $3$ 天打第 $2$ 套模拟赛题，第 $5$ 天打第 $3$ 套模拟赛题。

教练需要为每一个人的每一次模拟赛做准备，为了减小工作量，如果在某一天有多个人打同一套模拟赛题，那么教练只需要在这一天准备一场使用这一套题的模拟赛即可。

你作为机房大佬，教练想请你帮他计算一下，他每天需要准备多少场模拟赛。

#### 输入格式

第一行三个整数 $n,m,k$。

接下来 $n$ 行，每行 $m$ 个整数，第 $i$ 行第 $j$ 列的整数 $a_{i,j}$ 表示第 $i$ 个人在接下来的 $k$ 天中第 $j$ 个有空的日子为第 $a_{i,j}$ 天。

#### 输出格式

一行 $k$ 个整数，第 $i$ 个整数表示接下来的第 $i$ 天教练需要准备的模拟赛场数。

#### 输入输出样例

输入: #1

```cpp
1 3 5
2 3 5
```

输出: #1

```cpp
0 1 1 0 1
```

输入: #2

```cpp
6 3 7
2 3 4
2 5 7
3 5 7
1 3 5
5 6 7
1 2 3
```

输出: #2

```cpp
1 2 3 1 3 1 1
```

输入: #3

```cpp
10 10 20
2 3 4 8 9 11 12 16 17 18
2 3 6 10 12 13 14 15 19 20
1 3 7 10 11 13 14 15 17 19
1 2 4 6 7 9 15 17 19 20
2 3 5 6 9 11 14 16 19 20
1 2 3 8 9 10 11 12 15 19
1 4 6 7 9 12 13 17 18 19
1 7 8 9 10 11 13 15 18 20
1 5 6 7 8 9 13 16 18 19
4 5 7 10 11 13 14 17 18 20
```

输出: #3

```cpp
1 2 2 3 2 2 4 3 3 3 3 4 2 1 3 1 2 2 2 1
```

#### 说明&提示

本题采用捆绑测试。

- Subtask 1（13 points）：$n = m = k = 1$。
- Subtask 2（24 points）：$n = 1$。
- Subtask 3（24 points）：$m = 1$。
- Subtask 4（39 points）：无特殊限制。

对于 $100\%$ 的数据，$1 \le n,m,k \le 10^3$，$m \le k$，$1 \le a_{i,1} \lt a_{i,2} \lt \cdots \lt a_{i,m} \le k$。

#### 解题思路

理顺题目就好，没什么难点

#### 解答代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int main() {
    int n, m, k, d;
    scanf("%d%d%d", &n, &m, &k);
    vector<vector<int>> s(k + 1, vector<int>(m, 0));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            scanf("%d", &d);
            s[d][j] = 1;
        }
    }
    for (int i = 1; i <= k; ++i){
        int cnt = 0;
        for (int v: s[i]) {
            cnt += v;
        }
        printf("%d ", cnt);
    }
    return 0;
}
```

```java
import java.util.*;

public class Main {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int n = sc.nextInt(), m = sc.nextInt(), k = sc.nextInt(), d;
        int[][] s = new int[k + 1][m];
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                d = sc.nextInt();
                s[d][j] = 1;
            }
        }
        sc.close();
        for (int i = 1; i <= k; ++i) {
            int cnt = 0;
            for (int v : s[i])
                cnt += v;
            System.out.printf("%d ", cnt);
        }
    }
}
```

---

## 入门级-字符串基础

### P5015 [NOIP2018 普及组] 标题统计

#### 题目描述

凯凯刚写了一篇美妙的作文，请问这篇作文的标题中有多少个字符？ 注意：标题中可能包含大、小写英文字母、数字字符、空格和换行符。统计标题字 符数时，空格和换行符不计算在内。

#### 输入格式

输入文件只有一行，一个字符串 $s$。

#### 输出格式

输出文件只有一行，包含一个整数，即作文标题的字符数（不含空格和换行符）。

#### 输入输出样例

输入: #1

```cpp
234 
```

输出: #1

```cpp
3
```

输入: #2

```cpp
Ca 45 
```

输出: #2

```cpp
4
```

#### 说明&提示

【输入输出样例 1 说明】

标题中共有 3 个字符，这 3 个字符都是数字字符。

【输入输出样例 2 说明】

标题中共有$ 5$ 个字符，包括 $1$ 个大写英文字母， $1$ 个小写英文字母和 $2$ 个数字字符， 还有 $1$ 个空格。由于空格不计入结果中，故标题的有效字符数为 $4$ 个。

【数据规模与约定】  

- 规定 $|s|$ 表示字符串 $s$ 的长度（即字符串中的字符和空格数）。
- 对于 $40\%$ 的数据，$1 ≤ |s| ≤ 5$，保证输入为数字字符及行末换行符。
- 对于 $80\%$ 的数据，$1 ≤ |s| ≤ 5$，输入只可能包含大、小写英文字母、数字字符及行末换行符。
- 对于 $100\%$ 的数据，$1 ≤ |s| ≤ 5$，输入可能包含大、小写英文字母、数字字符、空格和行末换行符。

#### 解题思路

基础字符串的输入

#### 解答代码

```cpp
#include <iostream>
#include <cstring>
using namespace std;

int main(){
    string s;
    int ans=0;
    while (cin >> s)
        ans += s.length();
    cout << ans << endl;
    return 0;
}
```

```cpp
#include <cstdio>
#include <cstring>
using namespace std;

int main() {
    char s[7];
    gets(s);
    int n = strlen(s);
    int ans = 0;
    for (int i = 0; i < n; i++) {
        if (s[i] >= 'A' && s[i] <= 'Z')
            ans++;
        else if (s[i] >= 'a' && s[i] <= 'z')
            ans++;
        else if (s[i] >= '0' && s[i] <= '9')
            ans++;
    }
    printf("%d", ans);
    return 0;
}
```

```java
import java.util.*;

public class Main {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        String _s = sc.nextLine();
        int ans = 0;
        for (char s : _s.toCharArray()) {
            if (s >= 'A' && s <= 'Z')
                ans++;
            else if (s >= '0' && s <= '9')
                ans++;
            else if (s >= 'a' && s <= 'z')
                ans++;
        }
        sc.close();
        System.out.println(ans);
    }
}
```

```python
print(sum(map(len, input().split())))
```

---

### P1055 [NOIP2008 普及组] ISBN 号码

#### 题目描述

每一本正式出版的图书都有一个ISBN号码与之对应，ISBN码包括$9$位数字、$1$位识别码和$3$位分隔符，其规定格式如`x-xxx-xxxxx-x`，其中符号`-`就是分隔符（键盘上的减号），最后一位是识别码，例如`0-670-82162-4`就是一个标准的ISBN码。ISBN码的首位数字表示书籍的出版语言，例如$0$代表英语；第一个分隔符`-`之后的三位数字代表出版社，例如$670$代表维京出版社；第二个分隔符后的五位数字代表该书在该出版社的编号；最后一位为识别码。

识别码的计算方法如下：

首位数字乘以$1$加上次位数字乘以$2$……以此类推，用所得的结果$ \bmod 11$，所得的余数即为识别码，如果余数为$10$，则识别码为大写字母$X$。例如ISBN号码`0-670-82162-4`中的识别码$4$是这样得到的：对`067082162`这$9$个数字，从左至右，分别乘以$1,2,...,9$再求和，即$0×1+6×2+……+2×9=158$，然后取$158 \bmod 11$的结果$4$作为识别码。

你的任务是编写程序判断输入的ISBN号码中识别码是否正确，如果正确，则仅输出`Right`；如果错误，则输出你认为是正确的ISBN号码。

#### 输入格式

一个字符序列，表示一本书的ISBN号码（保证输入符合ISBN号码的格式要求）。

#### 输出格式

一行，假如输入的ISBN号码的识别码正确，那么输出`Right`，否则，按照规定的格式，输出正确的ISBN号码（包括分隔符`-`）。

#### 输入输出样例

输入: #1

```cpp
0-670-82162-4
```

输出: #1

```cpp
Right
```

#### 说明&提示

无

#### 解题思路

按题目要求计算识别码即可

#### 解答代码

```cpp
#include <cstdio>
#include <iostream>
using namespace std;

int main() {
    char s[17];
    gets(s);
    int m = 0;
    for (int i = 0, j = 1; i < 12; ++i) {
        if (s[i] == '-') continue;
        m += (j++) * (s[i] - '0');
    }
    m %= 11;
    char tag;
    if (m == 10) tag = 'X';
    else tag = '0' + m;
    if (tag == s[12])
        printf("Right");
    else {
        for (int i = 0; i < 12; ++i) {
            printf("%c", s[i]);
        }
        printf("%c", tag);
    }
    return 0;
}
```

```java
import java.util.*;

public class Main {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        char[] st = sc.nextLine().toCharArray();
        int cnt = 0, j = 1;
        for (int i = 0; i < 12; ++i) {
            if (st[i] == '-')
                continue;
            cnt += (j++) * (st[i] - '0');
        }
        cnt %= 11;
        char s;
        if (cnt == 10)
            s = 'X';
        else
            s = (char) ('0' + cnt);
        if (st[12] == s)
            System.out.println("Right");
        else {
            st[12] = s;
            System.out.println(st);
        }
        sc.close();
    }
}
```

---

### P1308 [NOIP2011 普及组] 统计单词数

#### 题目描述

一般的文本编辑器都有查找单词的功能，该功能可以快速定位特定单词在文章中的位置，有的还能统计出特定单词在文章中出现的次数。

现在，请你编程实现这一功能，具体要求是：给定一个单词，请你输出它在给定的文章中出现的次数和第一次出现的位置。注意：匹配单词时，不区分大小写，但要求完全匹配，即给定单词必须与文章中的某一独立单词在不区分大小写的情况下完全相同（参见样例1 ），如果给定单词仅是文章中某一单词的一部分则不算匹配（参见样例2 ）。

#### 输入格式

共$2$行。

第$1$行为一个字符串，其中只含字母，表示给定单词；

第$2$行为一个字符串，其中只可能包含字母和空格，表示给定的文章。

#### 输出格式

一行，如果在文章中找到给定单词则输出两个整数，两个整数之间用一个空格隔开，分别是单词在文章中出现的次数和第一次出现的位置（即在文章中第一次出现时，单词首字母在文章中的位置，位置从$0$ 开始）；如果单词在文章中没有出现，则直接输出一个整数$-1$。

#### 输入输出样例

输入: #1

```cpp
To
to be or not to be is a question
```

输出: #1

```cpp
2 0

```

输入: #2

```cpp
to
Did the Ottoman Empire lose its power at that time
```

输出: #2

```cpp
-1
```

#### 说明&提示

数据范围

$1≤$ 单词长度 $≤10$。

$1≤$ 文章长度 $≤1,000,000$。

#### 解题思路

很简单的字符串全匹配

#### 解答代码

```java
import java.util.*;

public class Main {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        String _s1 = sc.nextLine(), _s2 = sc.nextLine();
        sc.close();
        char[] s1 = _s1.toCharArray(), s2 = _s2.toCharArray();
        int n1 = s1.length, n2 = s2.length;
        // 将字符转换为小写字符
        for (int i = 0; i < n1; ++i) {
            s1[i] |= 32;
        }
        for (int i = 0; i < n2; ++i) {
            s2[i] |= 32;
        }
        // 全匹配
        int ind = -1, s = 0;
        loop: for (int i = 0; i < n2; ++i) {
            // 单词前一个和后一个字符应该是空格
            if ((i == 0 || s2[i - 1] == ' ') && (i + n1 - 1 == n2 || (i + n1 < n2 && s2[i + n1] == ' '))) {
                // System.out.println(i + "开始匹配：");
                for (int j = 0; j < n1; ++j) {
                    if (s1[j] != s2[i + j])
                        continue loop;
                }
                // System.out.println("匹配成功");
                if (ind == -1)
                    ind = i;
                ++s;
            }
        }
        if (s == 0)
            System.out.println(-1);
        else System.out.println(Integer.toString(s) + " " + ind);
    }
}
```

仅20分解法，错误原因：要求返回第一次出现的位置，位置是按字符计数而不是按单词计数

```python
def CountWords(word: str, paper: str) -> None:
    ind, s = -1, 0
    for i, w in enumerate(paper.split()):
        if word == w:
            s += 1
            if ind == -1:
                ind = i
    if ind == -1:
        print(-1)
    else:
        print(s, ind, sep = " ")
    return None

print(CountWords())
```

---

### P2010 [NOIP2016 普及组] 回文日期

#### 题目描述

在日常生活中，通过年、月、日这三个要素可以表示出一个唯一确定的日期。

牛牛习惯用$8$位数字表示一个日期，其中，前$4$位代表年份，接下来$2$位代表月 份，最后$2$位代表日期。显然：一个日期只有一种表示方法，而两个不同的日期的表 示方法不会相同。

牛牛认为，一个日期是回文的，当且仅当表示这个日期的8位数字是回文的。现 在，牛牛想知道：在他指定的两个日期之间包含这两个日期本身），有多少个真实存 在的日期是回文的。

一个$8$位数字是回文的，当且仅当对于所有的$i ( 1  \le i \le  8)$从左向右数的第i个 数字和第$9-i$个数字（即从右向左数的第$i$个数字）是相同的。

例如：

•对于2016年11月19日，用$8$位数字$20161119$表示，它不是回文的。

•对于2010年1月2日，用$8$位数字$20100102$表示，它是回文的。

•对于2010年10月2日，用$8$位数字$20101002$表示，它不是回文的。

每一年中都有$12$个月份：

其中，$1,3,5,7,8,10,12$月每个月有$31$天；$4,6,9,11$月每个月有$30$天；而对于$2$月，闰年时有$29$天，平年时有$28$天。

一个年份是闰年当且仅当它满足下列两种情况其中的一种：

1.这个年份是$4$的整数倍，但不是$100$的整数倍；

2.这个年份是$400$的整数倍。

例如：

•以下几个年份都是闰年：$2000,2012,2016$。

•以下几个年份是平年：$1900,2011,2014$。

#### 输入格式

两行，每行包括一个$8$位数字。

第一行表示牛牛指定的起始日期。

第二行表示牛牛指定的终止日期。

保证$ date\_i $和都是真实存在的日期，且年份部分一定为$4$位数字，且首位数字不为$0$。

保证$ date 1 $ —定不晚于$ date 2 $。

#### 输出格式

一个整数，表示在$date1$和$date2$之间，有多少个日期是回文的。

#### 输入输出样例

输入: #1

```cpp
20110101
20111231
```

输出: #1

```cpp
1
```

输入: #2

```cpp
20000101
20101231
```

输出: #2

```cpp
2
```

#### 说明&提示

【样例说明】

对于样例1，符合条件的日期是$20111102$。

对于样例2，符合条件的日期是$20011002$和$20100102$。

【子任务】

对于$60\%$的数据，满足$date1 = date2$。

#### 解题思路

一个日期是由 4 位的年份 + 2 位月份 + 2 位日期，由前 4 位与后 4 位成镜像关系，可知一个年份最多有一个 “回文日期”，所以可以枚举所有起始到最后年份的 “回文日期”，再检查 “回文日期” 是否合理

#### 解答代码

```java
import java.util.*;

public class Main {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        Main s = new Main();
        int st = sc.nextInt(), ed = sc.nextInt();
        sc.close();
        System.out.println(s.PalindromeDate(st, ed));
    }

    static Set<Integer> month_with_31;
    static {
        month_with_31 = new HashSet<>();
        month_with_31.add(1);
        month_with_31.add(3);
        month_with_31.add(5);
        month_with_31.add(7);
        month_with_31.add(8);
        month_with_31.add(10);
        month_with_31.add(12);
    }

    public int PalindromeDate(int start, int end) {
        // 返回 起止日期中合法的回文日期 的数量
        int cnt = 0;
        // 起止年份
        int y1 = start / 10000, y2 = end / 10000;
        for (int i = y1; i <= y2; ++i) {
            // 枚举年份对应的 “回文日期”
            int year = i, month = 0, day = 0;
            for (int j = 0; j < 2; ++j) {
                month = month * 10 + year % 10;
                year /= 10;
            }
            for (int j = 0; j < 2; ++j) {
                day = day * 10 + year % 10;
                year /= 10;
            }
            year = i;
            int date = year * 10000 + month * 100 + day;
            if (date < start || date > end)
                continue;
            // 检查 “回文日期” 是否为真实存在的日期
            if (month > 12 || day > 31 || month == 0 || day == 0)
                continue;
            if (!month_with_31.contains(month) && day > 30)
                continue;
            if (month == 2) {
                if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) {
                    // 闰年
                    if (day > 29)
                        continue;
                } else { // 平年
                    if (day > 28)
                        continue;
                }
            }
            cnt++;
        }
        return cnt;
    }
}
```

```python
m_31 = {1, 3, 5, 7, 8, 10, 12}

def PalindromeDate(start: str, end: str) -> int:
    """枚举年份对应的回文日期，校验是否合理"""
    cnt = 0
    st, ed = int(start), int(end)
    y1, y2 = int(start[:4]), int(end[:4])
    # 枚举年份对应回文日期
    for i in range(y1, y2 + 1):
        date = str(i)
        date += date[::-1]
        d = int(date)
        if not st <= d <= ed:
            continue
        # 检查 “回文日期” 是否为真实存在的日期
        year, month, day = map(int, [date[:4], date[4:6], date[6:]])
        if not 0 < month <= 12 or not 0 < day <= 31:
            continue
        if month not in m_31 and day > 30:
            continue
        if month == 2:
            if (year % 4 == 0 and year % 100) or year % 400 == 0:
                if day > 29:
                    continue
            else:
                if day > 28:
                    continue
        cnt += 1
    return cnt

print(PalindromeDate(input(), input()))
```

---

### P1012 [NOIP1998 提高组] 拼数

#### 题目描述

设有 $n$ 个正整数 $a_1 \dots a_n$，将它们联接成一排，相邻数字首尾相接，组成一个最大的整数。

#### 输入格式

第一行有一个整数，表示数字个数 $n$。

第二行有 $n$ 个整数，表示给出的 $n$ 个整数 $a_i$。

#### 输出格式

一个正整数，表示最大的整数

#### 输入输出样例

输入: #1

```cpp
3
13 312 343
```

输出: #1

```cpp
34331213
```

输入: #2

```cpp
4
7 13 4 246
```

输出: #2

```cpp
7424613
```

#### 说明&提示

对于全部的测试点，保证 $1 \leq n \leq 20$，$1 \leq a_i \leq 10^9$。

#### 解题思路

把数字拼接起来最大，那么高位数字越大越好，~~可以将数字先排序，但规则是：先按第一个数字的大小排，如果第一个数字一样大，那么就对比第二个数字，以此类推，然后拼接所得即最大的数字~~ <-- 典型错误

```cpp
6
321 32 407 135 13 217
Right answer: 407 32 321 217 135 13
Wrong answer: 407 321 32 217 135 13
```

正确的排序规则为：$A+B<B+A$ ，其中 + 是字符串拼接操作而比较是基于数值操作的（也可以是字典序因为拼接后等长）

#### 解答代码

```cpp
#include <algorithm>
#include <iostream>
#include <cstring>
#include <vector>
using namespace std;

class comp {
public:
    bool operator()(const string& x, const string& y) {
        return x + y > y + x;
    }
};

int main() {
    int n;
    cin >> n;
    vector<string> s(n);
    for (int i = 0; i < n; ++i) {
        cin >> s[i];
    }
    comp c;
    sort(s.begin(), s.end(), c);
    string ans = "";
    for (string str : s)
        ans += str;
    cout << ans;
    return 0;
}
```

典型错误(纯字典序)：

```python
input()
print("".join(sorted(input().split(), reverse = True)))
```

正确的比较规则：

```python
from functools import cmp_to_key
input()
print("".join(sorted(input().split(), key = cmp_to_key(lambda x, y: 1 if x + y < y + x else -1))))
```

---

### P5587 打字练习

#### 题目描述

R 君在练习打字。

有这样一个打字练习网站，给定一个范文和输入框，会根据你的输入计算准确率和打字速度。可以输入的字符有小写字母、空格和 `.`（英文句号），输入字符后，光标也会跟着移动。

输入的文本有多行，R 君可以通过换行键来换行，换行后光标移动到下一行的开头。

R 君也可以按退格键（为了方便，退格键用 `&lt;` 表示），以删除上一个打的字符，并将光标回移一格。特殊的，如果此时光标已经在一行的开头，则不能继续退格（即忽略此时输入的退格键）。

网站的比较方式遵循以下两个原则：

- 逐行比较，即对于范文和输入的每一行依次比较，不同行之间不会产生影响，多余的行会被忽略。
- 逐位比较，即对于两行的每一个字符依次比较，当且仅当字符相同时才会被算作一次正确，否则会被算作错误。计算答案时，只统计相同的字符个数。

需要注意的是，回车键不会被计入正确的字符个数。

R 君看到网站上显示他花了 $T$ 秒完成了这次的打字游戏，请你计算出他的 KPM（Keys per minutes，每分钟输入的字符个数），答案四舍五入保留整数部分。

#### 输入格式

R 君会依次告诉你网站的范文，他的输入和花费的时间。

其中范文和输入将会这样读入：给定若干行字符串，以单独的一行 `EOF` 结束，其中 `EOF` 不算入输入的文本。

最后一行一个整数 $T$，表示他打字花费了 $T$ 秒。

可以参考样例输入输出文件和样例解释辅助理解。

#### 输出格式

一行一个整数，表示 KPM。

#### 输入输出样例

输入: #1

```cpp
hello world.
aaabbbb
x
EOF
heelo world.
aaacbbbb
y<x
EOF
60
```

输出: #1

```cpp
18
```

#### 说明&提示

样例解释

第一行的正确字符数为 11。  
第二行的正确字符数为 6，错误的字符 `c` 仍会占据一个位置。  
第三行的正确字符数为 1，R 君使用退格键删除了被打错的字符 `y`

数据范围

对于 $20\%$ 的数据，不存在换行键。  
对于 $40\%$ 的数据，不存在退格键。  
对于 $100\%$ 的数据，$T \leq 10^3$，保证每个文本段的总字符数（包括换行）不超过 $10^5$ 个且总行数不超过 $10^4$。

#### 解题思路

模拟即可，退格键的处理方法是将用栈处理，遇到退格键就出栈（如果栈非空）否则入栈，最后栈中的就是不带退格键的文本了

C++中直接用string模拟栈，因为STL中的stack是不支持顺序遍历的，也可以用动态数组或者静态数组模拟，这样方便后序的比较操作，然后 getline() 函数按理说是不读入换行符的，但洛谷在线IDE里面却会带换行符，不知道为什么

有两个坑：

1. 范文也有退格键（这个只能过50）
2. 空行不会被忽略，这里我被题目误导了，题目“多余的行会被忽略”是说 R 君多输入的行或范文比 R 君输入多的行都无视掉，不是说忽略掉文中的空行，debug了两个小时qaq（这个会得90卡在测试用例3）

#### 解答代码

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    vector<string> input;
    string st;
    int cnt = 0, tim;
    // 读取范文保存下来
    while (true) {
        getline(cin, st);
        if (st == "EOF") break;
        string s = "";
        for (char c : st) {
            if (c == '<') {
                if (!s.empty())
                    s.pop_back();
            }
            else
                s.push_back(c);
        }
        if (!s.empty())
            input.emplace_back(s);
    }
    int n = input.size(), j = 0;
    while (true) {
        getline(cin, st);
        if (st == "EOF") break;
        if (j >= n) continue;
        //输入文本放入栈中，处理退格
        string s = "";
        for (char c : st) {
            if (c == '<') {
                if (!s.empty())
                    s.pop_back();
            }
            else
                s.push_back(c);
        }
        int len = min(s.size(), input[j].size());
        // 逐字符对比范文
        for (int k = 0; k < len; ++k) {
            if (s[k] == input[j][k]) cnt++;
        }
        ++j;
    }
    cin >> tim;
    cout << int(cnt * 60.0 / tim + 0.5);
    return 0;
}
```

```java
import java.util.*;

public class Main {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        List<Deque<Character>> s1 = new ArrayList<>();
        List<Deque<Character>> s2 = new ArrayList<>();
        String EOF = "EOF";
        while (true) {
            String s = sc.nextLine();
            if (s.equals(EOF))
                break;
            // 处理退格符
            Deque<Character> word = new ArrayDeque<>();
            for (char c : s.toCharArray()) {
                if (c == '<') {
                    if (!word.isEmpty())
                        word.pollLast();
                } else
                    word.add(c);
            }
            s1.add(word);
        }
        while (true) {
            String s = sc.nextLine();
            if (s.equals(EOF))
                break;
            // 处理退格符
            Deque<Character> word = new ArrayDeque<>();
            for (char c : s.toCharArray()) {
                if (c == '<') {
                    if (!word.isEmpty())
                        word.pollLast();
                } else
                    word.add(c);
            }
            s2.add(word);
        }
        int T = sc.nextInt();
        sc.close();
        System.out.println(new Main().TypingCheck(s1, s2, T));
    }

    public int TypingCheck(List<Deque<Character>> s1, List<Deque<Character>> s2, int time) {
        int n1 = s1.size(), n2 = s2.size();
        int cnt = 0, i = 0;
        for (Deque<Character> word1 : s1) {
            if (i == n2)
                break;
            Deque<Character> word2 = s2.get(i++);
            int n = Math.min(word1.size(), word2.size());
            for (int j = 0; j < n; ++j) {
                if (word1.pollFirst() == word2.pollFirst())
                    cnt++;
            }
        }
        return (int) ((double) cnt * 60 / time + 0.5);
    }
}
```

---

## 入门级-递归

这里不得不推崇一下 Python 的装饰器 cache(3.9以上版本才有的，3.2以上的用 lru_cache)，记忆化递归神器！

---

### P1028 [NOIP2001 普及组] 数的计算

#### 题目描述

我们要求找出具有下列性质数的个数(包含输入的正整数 $n$)。

先输入一个正整数 $n$($n \le 1000$),然后对此正整数按照如下方法进行处理：

1. 不作任何处理；

2. 在它的左边加上一个正整数,但该正整数不能超过原数的一半；

3. 加上数后,继续按此规则进行处理,直到不能再加正整数为止。

#### 输入格式

$1$ 个正整数 $n$($n \le 1000$)

#### 输出格式

$1$ 个整数，表示具有该性质数的个数。

#### 输入输出样例

输入: #1

```cpp
6
```

输出: #1

```cpp
6
```

#### 说明&提示

满足条件的数为

6，16，26，126，36，136

#### 解题思路

题目的说明有点模糊，从示例和解释中可以看到，所谓“原数”是指最初的数字或者说新加上的数字

可以记忆化递归、动态规划、打表

#### 解答代码

动态规划

```cpp
#include <cstdio>
#include <vector>
using namespace std;

int NumberCount(int n);

int main() {
    int s;
    scanf("%d", &s);
    printf("%d", NumberCount(s));
    return 0;
}

int NumberCount(int n) {
    if (n <= 1) return 1;
    int ed = (n >> 1) + 1;
    // dp[i] 表示 小于等于 i 的数字之和
    vector<int> dp(ed);
    dp[1] = 1;
    for (int i = 2; i < ed; ++i) {
        // dp[i] = 第 i 个数字的种类数 + 前 i - 1 个数字的种类和
        // dp[i] = dp[i >> 1] + 1   +  dp[i - 1]
        dp[i] = dp[i / 2] + dp[i - 1] + 1;
    }
    // 第 n 个数字的种类数为 dp[n >> 1] + 1
    return dp[ed - 1] + 1;
}
```

半打表半递推: 打表体现在使用静态变量来记录并静态计算，重复实例化类并不会多次计算，而只需从静态变量中取值即可（不太能确定OJ的机制，所以这个机制不一定能起效）

```java
import java.util.*;

public class Main {
    static int[] dp = new int[1007];
    static {
        dp[1] = 1;
        for (int i = 2; i < 1007; ++i) {
            dp[i] = dp[i >> 1] + 1 + dp[i - 1];
        }
    };

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int n = sc.nextInt();
        sc.close();
        System.out.println(new Main().NumberCount(n));
    }

    public int NumberCount(int n) {
        return dp[n >> 1] + 1;
    }
}
```

记忆化递归

```python
from functools import lru_cache
@lru_cache(None)
def NumberCount(n: int) -> int:
    if n == 1:
        return 1
    ans = 1  # n 本身也是符合规则的
    for i in range(1, n // 2 + 1):
        ans += NumberCount(i)
    return ans

print(NumberCount(int(input())))
```

---

### P1036 [NOIP2002 普及组] 选数

#### 题目描述

已知 $n$ 个整数 $x_1,x_2,\cdots,x_n$，以及 $1$ 个整数 $k$（$k\lt n$）。从 $n$ 个整数中任选 $k$ 个整数相加，可分别得到一系列的和。例如当 $n=4$，$k=3$，$4$ 个整数分别为 $3,7,12,19$ 时，可得全部的组合与它们的和为：

$3+7+12=22$

$3+7+19=29$

$7+12+19=38$

$3+12+19=34$

现在，要求你计算出和为素数共有多少种。

例如上例，只有一种的和为素数：$3+7+19=29$。

#### 输入格式

第一行两个空格隔开的整数 $n,k$（$1 \le n \le 20$，$k\lt n$）。

第二行 $n$ 个整数，分别为 $x_1,x_2,\cdots,x_n$（$1 \le x_i \le 5\times 10^6$）。

#### 输出格式

输出一个整数，表示种类数。

#### 输入输出样例

输入: #1

```cpp
4 3
3 7 12 19
```

输出: #1

```cpp
1
```

#### 说明&提示

无

#### 解题思路

递归思路很简单，对一个数有两种选择：可选可不选

一个剪枝思路：剩下的可选数的数量必须大于 K，否则无法选到足够多的数

另外，校验一个数是否是质数, 小技巧里面有提到

#### 解答代码

递归 + 剪枝 + 米·拉素数测试 + 快速幂

```cpp
#include <bits/stdc++.h> 
using namespace std;

long quickpow(int x, int y, int mod);
bool isprime(int x);
int Select(vector<int>& nums, int k);

int main() {
    int n, k, x;
    scanf("%d%d", &n, &k);
    vector<int> s(n);
    for (int i = 0; i < n; ++i) {
        scanf("%d", &x);
        s[i] = x;
    }
    printf("%d", Select(s, k));
    return 0;
}

int Select(vector<int>& nums, int k) {
    int n = nums.size();
    function<int(int, int, int)> dfs = [&](int i, int j, int s) -> int {
        if (j == 0) return isprime(s);
        if (i + j > n) return 0;    // 剪枝操作
        return dfs(i + 1, j, s) + dfs(i + 1, j - 1, s + nums[i]);
    };
    return dfs(0, k, 0);
}

long quickpow(int x, int y, int mod) {
    // x ^ y % mod 快速幂
    long ans = 1;
    while (y != 0) {
        if (y & 1 == 1)
            ans = ans * x % mod;
        x = x * x % mod;
        y >>= 1;
    }
    return ans;
}

bool isprime(int x) {
    if (x < 3) return x == 2;
    if (x % 2 == 0) return false;
    int s[] = {2, 3, 5, 7, 11, 13, 17};
    int d = x - 1, r = 0;
    while (d % 2 == 0) {
        d >>= 1;
        ++r;
    }
    for (int b : s) {
        long y = quickpow(b, d, x);
        if (y == 1 || y == 0 || y == x - 1) continue;
        for (int i = 0; i < r; ++i) {
            y = y * y % x;
            if (y == x - 1 && i != r - 1) {
                y = 1;
                break;
            }
            if (y == 1) return false;
        }
        if (y != 1) return false;
    }
    return true;
}
```

```java
import java.util.*;

class Main {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int n = sc.nextInt(), k = sc.nextInt();
        int[] nums = new int[n];
        for (int i = 0; i < n; ++i) {
            nums[i] = sc.nextInt();
        }
        sc.close();
        System.out.println(new Main().Select(nums, k));
    }

    private int[] nums;
    private int n;

    int Select(int[] nums, int k) {
        this.nums = nums;
        this.n = nums.length;
        return dfs(0, k, 0);
    }

    int dfs(int i, int k, int s) {
        if (k == 0)
            return isprime(s) ? 1 : 0;
        if (i + k > n)
            return 0;
        return dfs(i + 1, k, s) + dfs(i + 1, k - 1, s + nums[i]);
    }

    boolean isprime(int x) {
        // 朴素检查 判断 x 是否是素数
        if (x < 3)
            return x == 2;
        if (x % 2 == 0)
            return false;
        int n = (int) Math.sqrt(x) + 1;
        for (int i = 3; i < n; i += 2) {
            if (x % i == 0)
                return false;
        }
        return true;
    }
}
```

---

### P1464 Function

#### 题目描述

对于一个递归函数$w(a,b,c)$

- 如果$a \le 0$ or $b \le 0$ or $c \le 0$就返回值$1$.
- 如果$a\gt 20$ or $b\gt 20$ or $c\gt 20$就返回$w(20,20,20)$
- 如果$a\lt b$并且$b\lt c$ 就返回$w(a,b,c-1)+w(a,b-1,c-1)-w(a,b-1,c)$
- 其它的情况就返回$w(a-1,b,c)+w(a-1,b-1,c)+w(a-1,b,c-1)-w(a-1,b-1,c-1)$

这是个简单的递归函数，但实现起来可能会有些问题。当$a,b,c$均为15时，调用的次数将非常的多。你要想个办法才行.

> absi2011 : 比如 $w(30,-1,0)$既满足条件1又满足条件2  
> 这种时候我们就按最上面的条件来算  
> 所以答案为1

#### 输入格式

会有若干行。

并以$-1,-1,-1$结束。

保证输入的数在$[-9223372036854775808,9223372036854775807]$之间，并且是整数。

#### 输出格式

输出若干行，每一行格式：

`w(a, b, c) = ans`

注意空格。

#### 输入输出样例

输入: #1

```cpp
1 1 1
2 2 2
-1 -1 -1
```

输出: #1

```cpp
w(1, 1, 1) = 2
w(2, 2, 2) = 4
```

#### 说明&提示

记忆化搜索

#### 解题思路

提示已经说明了记忆化搜索，套上cache即可

#### 解答代码

```cpp
#include <cstdio>
#include <string>
#include <unordered_map>
using namespace std;

typedef long long ll;
unordered_map<string, ll> cache;

ll w(ll a, ll b, ll c) {
    string key = to_string(a) + "_" + to_string(b) + "_" + to_string(c);
    if (cache.find(key) != cache.end()) return cache[key];

    ll ans;
    if (a <= 0 || b <= 0 || c <= 0)
        ans = 1;
    else if (a > 20 || b > 20 || c > 20)
        ans = w(20, 20, 20);
    else if (a < b && b < c)
        ans = w(a, b, c - 1) + w(a, b - 1, c - 1) - w(a, b - 1, c);
    else
        ans = w(a - 1, b, c) + w(a - 1, b - 1, c) + w(a - 1, b, c - 1) - w(a - 1, b - 1, c - 1);
    cache[key] = ans;
    return ans;
}

int main() {
    ll a, b, c;
    scanf("%lld%lld%lld", &a, &b, &c);
    while (a != -1 || b != -1 || c != -1) {
        printf("w(%lld, %lld, %lld) = %lld\n", a, b, c, w(a, b, c));
        scanf("%lld%lld%lld", &a, &b, &c);
    }
    return 0;
}
```

```java
import java.util.*;

class Main {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        long a = sc.nextLong(), b = sc.nextLong(), c = sc.nextLong();
        Main s = new Main();
        while (a != -1 || b != -1 || c != -1) {
            System.out.printf("w(%d, %d, %d) = %d\n", a, b, c, s.w(a, b, c));
            a = sc.nextLong();
            b = sc.nextLong();
            c = sc.nextLong();
        }
        sc.close();
    }

    public Map<String, Long> cache = new HashMap<>();

    public long w(long a, long b, long c) {
        String s = Long.toString(a) + "-" + Long.toString(b) + "-" + Long.toString(c);
        if (cache.containsKey(s))
            return cache.get(s);
        long ans;
        if (a <= 0 || b <= 0 || c <= 0)
            ans = 1;
        else if (a > 20 || b > 20 || c > 20)
            ans = w(20, 20, 20);
        else if (a < b && b < c)
            ans = w(a, b, c - 1) + w(a, b - 1, c - 1) - w(a, b - 1, c);
        else
            ans = w(a - 1, b, c) + w(a - 1, b - 1, c) + w(a - 1, b, c - 1) - w(a - 1, b - 1, c - 1);
        cache.put(s, ans);
        return ans;
    }
}
```

```python
from functools import lru_cache

@lru_cache(None)
def w(a, b, c):
    if a <= 0 or b <= 0 or c <= 0:
        return 1
    if a > 20 or b > 20 or c > 20:
        return w(20, 20, 20)
    if a < b and b < c:
        return w(a, b, c - 1) + w(a, b - 1, c - 1) - w(a, b - 1, c)
    return w(a - 1, b, c) + w(a - 1, b - 1, c) + w(a - 1, b, c - 1) - w(a - 1, b - 1, c - 1)
    
while 1:
    a, b, c = map(int, input().split())
    if a == -1 and b == -1 and c == -1:
        break
    print("w({}, {}, {}) = {}".format(a, b, c, w(a, b, c)))
```

---

### P5534 【XR-3】等差数列

#### 题目描述

小 X 给了你一个等差数列的前两项以及项数，请你求出这个等差数列各项之和。

等差数列：对于一个 $n$ 项数列 $a$，如果满足对于任意 $i \in [1,n)$，有 $a_{i+1} - a_i = d$，其中 $d$ 为定值，则称这个数列为一个等差数列。

#### 输入格式

一行 $3$ 个整数 $a_1, a_2, n$，表示等差数列的第 $1,2$ 项以及项数。

#### 输出格式

一行一个整数，表示答案。

#### 输入输出样例

输入: #1

```cpp
1 2 3
```

输出: #1

```cpp
6
```

输入: #2

```cpp
-5 -10 5
```

输出: #2

```cpp
-75
```

#### 说明&提示

【样例 $1$ 说明】

这个等差数列为 `1 2 3`，其各项之和为 $6$。

数据范围：

- $|a_1|,|a_2| \le 10^6$。
- $3 \le n \le 10^6$。

#### 解题思路

等差数列求和？套公式就好啦

$$
s=\sum^n_{i = 1}a_i=\frac{(a_1+a_n) \times n}{2}=\frac{(2a_1+(n-1)\times d) \times n}{2}
$$

再估算下数据范围：由 $a_1, a_2$能推出公差 $d$ 可以达到 $2 \times 10^6$, 由此答案可能达到 $10^{12}$, 要使用 `long`

#### 解答代码

```cpp
#include <cstdio>
using namespace std;
typedef long long ll;
int main() {
    ll a1, a2, n;
    scanf("%lld%lld%lld", &a1, &a2, &n);
    printf("%lld", ((2 * a1 + (n - 1) * (a2 - a1)) * n) / 2);
    return 0;
}
```

```java
import java.util.*;

class Main {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        long a1 = sc.nextLong(), a2 = sc.nextLong(), n = sc.nextLong();
        sc.close();
        System.out.println(((2 * a1 + (n - 1) * (a2 - a1)) * n) / 2);
    }
}
```

```python
a1, a2, n = map(int, input().split())
d = a2 - a1
print(((2 * a1 + (n - 1) * d) * n) // 2)
```

---

### P1192 台阶问题

#### 题目描述

有$N$级的台阶，你一开始在底部，每次可以向上迈最多$K$级台阶（最少$1$级），问到达第$N$级台阶有多少种不同方式。

#### 输入格式

两个正整数N，K。

#### 输出格式

一个正整数，为不同方式数，由于答案可能很大，你需要输出$ans \bmod 100003$后的结果。

#### 输入输出样例

输入: #1

```cpp
5 2
```

输出: #1

```cpp
8
```

#### 说明&提示

对于$20\%$的数据,有$N ≤ 10, K ≤ 3$;

对于$40\%$的数据，有$N ≤ 1000$;

对于$100\%$的数据，有$N ≤ 100000,K ≤ 100$。

#### 解题思路

经典动态规划了，或者记忆化搜索

状态转移方程：$dp[i]=\sum^{k}_{j = 1}dp[i - j]$

或者更进一步矩阵快速幂

$$
\begin{bmatrix}
dp[n] \\
dp[n - 1] \\
\dots \\
dp[n - k + 2] \\
dp[n - k + 1]
\end{bmatrix} = \begin{bmatrix}
1 & 1 & \dots & 1 & 1 \\
1 & 0 & \dots & 0 & 0 \\
0 & 1 & \dots & 0 & 0 \\
\dots & \dots & \dots & \dots & \dots \\
0 & 0 & \dots & 1 & 0 \\
\end{bmatrix} \begin{bmatrix}
dp[n - 1] \\
dp[n - 2] \\
\dots \\
dp[n - k + 1] \\
dp[n - k]
\end{bmatrix}
$$

#### 解答代码

动态规划 + 滚动数组

```cpp
#include <cstdio>
#include <vector>
using namespace std;

int mod = 100003;

int main() {
    int n, k;
    scanf("%d%d", &n, &k);
    if (k == 1) {
        printf("1");
        return 0;
    }
    // dp[i] 表示到达 i 位置的方案数
    vector<int> dp(k, 0);
    dp[0] = 1;
    dp[1] = 1;
    // s 表示 dp 数组的和
    int s = 2;
    for (int i = 2; i < k; ++i) {
        dp[i] = s;
        s = (s + dp[i]) % mod;
    }
    // 转移方程为 dp[i] = \sum^{k}_{j=1}dp[i - j]
    for (int i = k; i < n; ++i) {
        int tmp = dp[i % k];
        dp[i % k] = s;
        s = (s + mod - tmp + s) % mod;
    }
    if (n < k) s = dp[n];
    printf("%d", s);
    return 0;
}
```

矩阵快速幂

```java
import java.util.*;

public class Main {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int n = sc.nextInt(), k = sc.nextInt();
        sc.close();
        System.out.println(new Main().Step(n, k, 100003));
    }

    int Step(int n, int k, int mod) {
        if (n <= 1 || k == 1)
            return 1;
        if (n <= k)
            return qpow(n - 1, mod);
        int[][] b = new int[k][1];
        int[][] e = new int[k][k];
        b[k - 1][0] = 1;
        b[k - 2][0] = 1;
        for (int i = k - 3; i >= 0; --i) {
            b[i][0] = (b[i + 1][0] * 2) % mod;
        }
        Arrays.fill(e[0], 1);
        for (int i = 1; i < k; ++i) {
            e[i][i - 1] = 1;
        }
        int[][] ans = matrix_mul(quickpow(e, n - k + 1, mod), b, mod);
        return ans[0][0];
    }

    int qpow(int n, int mod) {
        long x = 2;
        long ans = 1;
        while (n != 0) {
            if ((n & 1) == 1)
                ans = (ans * x) % mod;
            x = (x * x) % mod;
            n >>= 1;
        }
        return (int)ans;

    }

    public int[][] matrix_mul(int[][] A, int[][] B, int mod) {
        int r = A.length, c = B[0].length, d = B.length;
        if (d != A[0].length) // 不合理的矩阵乘法
            return null;
        int[][] s = new int[r][c];
        for (int i = 0; i < r; ++i) {
            for (int k = 0; k < d; ++k) {
                long tmp = (long) A[i][k];
                for (int j = 0; j < c; ++j) {
                    s[i][j] = (int) ((tmp * B[k][j] + s[i][j]) % mod);
                }
            }
        }
        return s;
    }

    public int[][] quickpow(int[][] A, int n, int mod) {
        int r = A.length;
        int[][] s = new int[r][r];
        for (int i = 0; i < r; ++i)
            s[i][i] = 1;
        while (n != 0) {
            if ((n & 1) == 1)
                s = matrix_mul(s, A, mod);
            A = matrix_mul(A, A, mod);
            n >>= 1;
        }
        return s;
    }
}
```

~~python 使用 记忆化搜索最方便~~, 超过最大递归深度了 >_<  下面代码看看就好

```python
from functools import lru_cache
mod = 100003

@lru_cache(None)
def dfs(n: int, k: int) -> int:
    """返回到达第 n 阶台阶的方案数"""
    if n < 0: return 0
    if n == 0 or n == 1:
        return 1
    return sum(dfs(n - i, k) for i in range(1, k + 1)) % mod

n, k = map(int, input().split())
print(dfs(n, k))
```

---

### P1025 [NOIP2001 提高组] 数的划分

#### 题目描述

将整数 $n$ 分成 $k$ 份，且每份不能为空，任意两个方案不相同（不考虑顺序）。

例如：$n=7$，$k=3$，下面三种分法被认为是相同的。

$1,1,5$;
$1,5,1$;
$5,1,1$.

问有多少种不同的分法。

#### 输入格式

$n,k$ （$6&lt;n \le 200$，$2  \le k  \le  6$）

#### 输出格式

$1$ 个整数，即不同的分法。

#### 输入输出样例

输入: #1

```cpp
7 3
```

输出: #1

```cpp
4
```

#### 说明&提示

四种分法为：  
$1,1,5$;  
$1,2,4$;  
$1,3,3$;  
$2,2,3$.

#### 解题思路

难点在于去重，可以限制数值必须按升序排列即可

好吧，DFS 解法确实不难，但 DP 难度不小

由 dfs 得到的 dp 解法：

1. $dp[i][j]$ 表示将数 $i$ 划分成 $j$ 个数的方案数
2. 状态转移方程：$dp[i][j] = \sum_{y = 1}^{i - 1} dp[i - y][j - 1]$
3. 怎么防止重复呢？DFS解法中设置了第三个参数 `limit` 限制了划分的数是单调非减的，同理，将三重循环 $i, j, y$ 中的划分拿到最外层 $y, i, j$，即可限制划分是单调非减的，即在计算大小为 $y$ 的划分时，$dp$ 数组中的划分方案划分大小都是不超过 $y$ 的，由此可以保证划分的单调非减性

时间复杂度: $O(n^2k)$

看了评论区才做出的dp解法：换个角度，题目可以看做 $n$ 个小球，放到 $k$ 个盒子里面的方案数，要求盒子不能为空，小球和盒子没区别，设当前问题为 $F(n, k)$，那么子问题就是：

1. 至少有一个盒子里面放一个球，拿出那个盒子，把一个球放到盒子里面: $F(n - 1, k - 1)$
2. 所以盒子都有至少两个球，每个盒子里面都放一个球，$F(n - k, k)$
3. 推出状态转移方程：$F(n, k) = F(n - 1, k - 1) + F(n - k, k)$

时间复杂度: $O(nk)$

#### 解答代码

动态规划方法二

```cpp
#include <cstdio>
#include <vector>
using namespace std;

int NumberPartition(int n, int k) {
    // dp[i][j] 表示数 i 划分为 k 份
    vector<vector<int>> dp(n + 1, vector<int>(k + 1));
    for (int i = 1; i <= n; ++i) dp[i][1] = 1;
    for (int i = 2; i <= n; ++i) {
        for (int j = 2; j <= k; ++j) {
            dp[i][j] = (i > j ? dp[i - j][j] : 0) + dp[i - 1][j - 1];
        }
    }
    return dp[n][k];
}

int main() {
    int n, k;
    scanf("%d%d", &n, &k);
    printf("%d", NumberPartition(n, k));
    return 0;
}
```

动态规划方法一

```java
import java.util.*;

public class Main {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int n = sc.nextInt(), k = sc.nextInt();
        sc.close();
        System.out.println(new Main().NumberPartition(n, k));
    }

    public int NumberPartition(int n, int k) {
        // dp[i][j] 表示将数 i 划分为 j 份
        int[][] dp = new int[n + 1][k + 1];
        dp[0][0] = 1;
        // i 划分为 x + y 
        // dp[i][j] = \sum_{y = 1}^{i} dp[y][j - 1]
        // 限制 划分只能由小到大，方法是调整循环顺序
        for (int y = 1; y <= n; ++y) {
            for (int i = y; i <= n; ++i) {
                for (int j = 1; j <= k; ++j) {
                    dp[i][j] += dp[i - y][j - 1];
                }
            }
        }
        return dp[n][k];
    }
}
```

这题数据量不大，应该不会递归栈溢出了吧~  
成功通过 ^_^

```python
from functools import lru_cache

@lru_cache(None)
def dfs(n: int, k: int, limit: int) -> int:
    """将整数 n 划分为 k 份 且每份要大于等于 limit"""
    if k == 1:
        return 1 if n >= limit else 0
    if limit * k > n:
        return 0
    return sum(dfs(n - i, k - 1, i) for i in range(limit, n))

n, k = map(int, input().split())
print(dfs(n, k, 1))
```

---

end

---

## 有必要二刷的题目

- P1047 [NOIP2005 普及组] 校门外的树 - 线段树解法
- P1012 [NOIP1998 提高组] 拼数 - 简单排序
- P1025 [NOIP2001 提高组] 数的划分 - 动态规划
