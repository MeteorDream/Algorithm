/*     -*- coding: utf-8 -*-     */
/* File    : main.cpp            */
/* Author  : MeteorDream         */
/* Time    : 2021/04/27 23:46:37 */
/* language: C/C++               */
/* Software: Visual Studio Code  */

#include "main.h"

using namespace std;

int main() {
    /* 计时变量 */
    clock_t st, et;

    /* 程序开始运算 */
    st = clock();

    func();

    /* 程序运行结束 */
    et = clock();
    printf("Running time: %d ms\n", (et - st));
    return 0;
}

void func() {
    /* CppExample */
    // example();

    /* 周赛测试程序 */
    // Contest();

    /* LeetCode 做题用 */
    Submit();

    /* 自动创建题目文件 */
    // CreateFile(BuildFileName(525, "contiguous-array"));
}

string BuildFileName(int num, string s) {
    string filename = to_string(num) + "_";
    for (char ss : s)
        if (ss == '-')
            filename += '_';
        else if (ss == ' ')
            continue;
        else
            filename += ss;
    filename += ".cpp";
    return filename;
}

void CreateFile(string FileName) {
    ofstream f;
    // 如果没有文件，生成空文件, 如果有文件，在文件尾追加
    f.open(FileName, ios::app);
    f.close();
}