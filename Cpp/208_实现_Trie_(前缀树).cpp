#include <iostream>
#include <vector>
#include <string>
#include <math.h>
// #include <bits/stdc++.h>

using namespace std;

struct DicNode{
public:
    int tag = 0;
    struct DicNode *next[26];
    int end = 0;
};

class Trie {
public:
    struct DicNode Head;
    /** Initialize your data structure here. */
    Trie() {
        /* 好像没什么需要初始化的…… */
    }
    
    /** Inserts a word into the trie. */
    void insert(string word) {
        struct DicNode *p = &Head;
        int d;
        /* 遍历单词每一位，先根据tag判断是否存在对应的结点，再执行插入 */
        for (char s: word){
            d = s - 'a';
            if (p->tag & (1 << d))
                p = p->next[d];
            /* 没有对应结点哦，需要先开数组再设标记，最后执行插入 */
            else{
                p->next[d] = new struct DicNode;
                p->tag |= (1 << d);
                p = p->next[d];
            }
        }
        /* 单词结尾在end里标记 */
        p->end |= (1 << d);
    }
    
    /** Returns if the word is in the trie. */
    bool search(string word) {
        /* 基本思路和插入差不多，改插入操作为判断操作 */
        struct DicNode *p = &Head;
        int d;
        for (char s: word){
            d = s - 'a';
            if (p->tag & (1 << d))
                p = p->next[d];
            else
                return false;
        }
        return p->end & (1 << d);
    }
    
    /** Returns if there is any word in the trie that starts with the given prefix. */
    bool startsWith(string prefix) {
        /* 和search几乎一样，不过不需要检查end标记啦 */
        struct DicNode *p = &Head;
        int d;
        for (char s: prefix){
            d = s - 'a';
            if (p->tag & (1 << d))
                p = p->next[d];
            else
                return false;
        }
        return true;
    }
};

/**
 * Your Trie object will be instantiated and called as such:
 * Trie* obj = new Trie();
 * obj->insert(word);
 * bool param_2 = obj->search(word);
 * bool param_3 = obj->startsWith(prefix);
 */

int _208_Trie(){

    Trie* obj = new Trie();
    obj->insert("apple");
    bool param_2 = obj->search("app");
    bool param_3 = obj->startsWith("app");

    cout << param_2 << " , " << param_3 << endl;

    return 0;
}