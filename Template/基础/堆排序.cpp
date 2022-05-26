#include <cstdio>
#include <cstdlib>
#include <ctime>
using namespace std;

// 交换 a, b 的值
template <typename T>
void swap(T& a, T& b) {
    T c = a;
    a = b;
    b = c;
}

template <typename T>
inline bool comp(T a, T b) {
    // a 在 b 前面返回 true，否则返回 false
    return a < b;
}

// 大顶堆操作：下滤
template <typename T>
inline void percdown(T nums[], int target, int n) {
    int a = target * 2 + 1, b = a + 1, x;
    while (true) {
        x = target;
        if (a < n && comp(nums[x], nums[a])) x = a;
        if (b < n && comp(nums[x], nums[b])) x = b;
        if (x != target)
            swap<T>(nums[x], nums[target]);
        else
            break;
        target = x, a = x * 2 + 1, b = a + 1;
    }
}

// 大顶堆操作：上滤
template <typename T>
inline void percup(T nums[], int target) {
    int f = target - 1 >> 1;
    while (target > 0 && comp(nums[f], nums[target])) {
        swap<T>(nums[f], nums[target]);
        target = f;
        f = target - 1 >> 1;
    }
}

// 对 [0, n) 范围内的数建堆（自底向上构建大顶堆）
template <typename T>
inline void buildheap(T nums[], int n) {
    for (int i = n / 2; i >= 0; --i) {
        percdown<T>(nums, i, n);
    }
}

// 堆排序：对 [0, n) 范围内的数排序
template <typename T>
void heapsort(T nums[], int n) {
    buildheap<T>(nums, n);
    for (int i = n - 1; i > 0; --i) {
        swap(nums[0], nums[i]);
        percdown<T>(nums, 0, i);
    }
}

// -------------------- 测试部分 ---------------------

// 格式化输出数组
void ArrayPrint(int nums[], int n) {
    for (int i = 0; i < n; ++i) {
        printf("%2d ", nums[i]);
    }
    putchar('\n');
}

// 检查数组是否递增有序
bool check_sort(int nums[], int n) {
    for (int i = 1; i < n; ++i) {
        if (nums[i] < nums[i - 1]) return false;
    }
    return true;
}

// 排序检查函数(随机生成长度为1000的数组进行排序并重复1000次)
bool SortTest() {
    freopen("luogu.out", "w", stdout);    // 输出流重定向
    int nums[1007];
    srand((unsigned int)time(NULL));
    for (int i = 0; i < 1000; ++i) {
        for (int j = 0; j < 1000; ++j) {
            nums[i] = rand() % 10000;
            printf("%4d ", nums[i]);
        }
        putchar('\n');

        // 排序函数在这里~~~~~~~~
        heapsort<int>(nums, 1000);
        // quicksort<int>(nums, 0, 999);

        if (!check_sort(nums, 1000)) return false;
        printf("检查通过\n");
    }
    return true;
}

int main() {
    if (SortTest())
        printf("\n排序函数没有问题\n");
    else
        printf("\n排序函数有错误\n");
    return 0;
}