// 快排模板
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

// 比较函数
template <typename T>
inline bool comp(T a, T b) {
    // a 在 b 前面返回 true，否则返回 false
    return a < b;
}

// 对 [start, end] 范围内的函数进行快速排序
template <typename T = int>
void quicksort(T nums[], int start, int end) {
    if (start >= end)
        return;
    else if (start + 1 == end) {
        if (!comp(nums[start], nums[end]))
            swap(nums[start], nums[end]);
    }
    else {
        int idx = rand() % (end - start + 1) + start;
        swap(nums[start], nums[idx]);
        int left = start, right = end;
        while (left < right) {
            while (left < right && !comp(nums[right], nums[start])) right--;
            while (left < right && !comp(nums[start], nums[left])) left++;
            if (left < right)
                swap(nums[left], nums[right]);
            else
                break;
        }
        swap(nums[start], nums[left]);
        quicksort<T>(nums, start, left - 1);
        quicksort<T>(nums, left + 1, end);
    }
}

int n, t;
int nums[100007];

int main() {
    // freopen("luogu.in", "r", stdin);      // 输入流重定向
    // freopen("luogu.out", "w", stdout);    // 输出流重定向

    srand((unsigned)time(0));

    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        scanf("%d", &t);
        nums[i] = t;
    }
    quicksort(nums, 0, n - 1);
    for (int i = 0; i < n; ++i) {
        printf("%d ", nums[i]);
    }

    return 0;
}