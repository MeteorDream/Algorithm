#include <cstdio>
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
    return a < b;
}

// 归并: [left, mid - 1], [mid, right)已经有序，将两者合并成一段有序的
template <typename T>
void merge(T nums[], T tmp[], int left, int mid, int right) {
    int i = left, j = mid, k = left;
    while (i < mid && j < right) {
        if (comp(nums[i], nums[j]))
            tmp[k++] = nums[i++];
        else
            tmp[k++] = nums[j++];
    }
    while (i < mid) tmp[k++] = nums[i++];
    while (j < right) tmp[k++] = nums[j++];
    for (k = left; k < right; ++k) nums[k] = tmp[k];
}

// 归并排序主程序：对 [start, end) 范围内的元素进行排序(需要等大的临时空间)
template <typename T>
void mergesort(T nums[], T tmp[], int start, int end) {
    if (start < end - 1) {
        int mid = start + (end - start >> 1);
        mergesort<T>(nums, tmp, start, mid);
        mergesort<T>(nums, tmp, mid, end);
        merge<T>(nums, tmp, start, mid, end);
    }
}