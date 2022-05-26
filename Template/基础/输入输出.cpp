#include <cstdio>
#include <iostream>
using namespace std;

int main() {
    // 标准声明：FILE *freopen( const char *path, const char *mode, FILE *stream );
    freopen("luogu.in", "r", stdin);      // 输入流重定向
    freopen("luogu.out", "w", stdout);    // 输出流重定向

    // 关同步
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    std::cout.tie(0);
    // 解题代码
    int vis[1];
    memset(vis, 0, sizeof(vis));    //初始化数组
}