/* 
* coding: utf-16 -*- 
* File    : LeetCode_374.java
* Author  : MeteorDream
* Time    : 2021/06/14 15:36:15
* language: Java
* Software: Visual Studio Code
* */

/* [374. 猜数字大小](https://leetcode-cn.com/problems/guess-number-higher-or-lower/) */

/** 
 * Forward declaration of guess API.
 * @param  num   your guess
 * @return 	     -1 if num is lower than the guess number
 *			      1 if num is higher than the guess number
 *               otherwise return 0
 * int guess(int num);
 */

public class LeetCode_374 extends GuessGame {
    public static void main(String[] args) {
        LeetCode_374 s = new LeetCode_374();

        System.out.println(s + "Finish!");
    }

    // 简单基础二分
    public int guessNumber(int n) {
        int left = 1, right = n;
        while (left < right) {
            int mid = left + (right - left) / 2;
            int ans = guess(mid);
            if (ans == 0)
                return mid;
            else if (ans == -1)
                right = mid - 1;
            else
                left = mid + 1;
        }
        return left;
    }

}

class GuessGame {
    // 为了语法检查不报错随便写的API
    public int guess(int num) {
        return 0;
    }
}