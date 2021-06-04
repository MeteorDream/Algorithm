/*     -*- coding: utf-8 -*-     */
/* File    : 146_lru_cache.cpp */
/* Author  : MeteorDream         */
/* Time    : 2021/06/02 16:56:13 */
/* language: C/C++               */
/* Software: Visual Studio Code  */

#include "LeetCode.h"

#ifdef __146__

/* 
146. LRU 缓存机制

难度: 中等

*/
class LinkNode {
public:
    LinkNode *prev, *next;
    int key, val;
    LinkNode(int key, int val, LinkNode* prev, LinkNode* next)
        : key(key), val(val), prev(prev), next(next) {}
    LinkNode(int key, int val) {
        LinkNode(key, val, nullptr, nullptr);
    }
    LinkNode() {
        LinkNode(0, 0, nullptr, nullptr);
    }

    void PopNode() {
        // 从链表中取出当前结点
        if (prev != nullptr)
            prev->next = next;
        if (next != nullptr)
            next->prev = prev;
        this->next = nullptr;
        this->prev = nullptr;
    }

    LinkNode* AddNode(int key, int val) {
        // 在 当前结点 后面插入一个新结点
        LinkNode* q = next;
        next = new LinkNode(key, val, this, q);
        q->prev = next;
        return next;
    }

    LinkNode* AddNode(LinkNode* node) {
        // 在 当前结点 后面插入一个已有结点
        LinkNode* q = next;
        next = node;
        q->prev = node;
        node->next = q;
        node->prev = this;
        return node;
    }
};

class LRUCache {
public:
    LRUCache(int capacity) {
        this->capacity = capacity;
        p.reserve(capacity * 2);
        head = new LinkNode();
        head->prev = head;
        head->next = head;
        size = 0;
    }

    int get(int key) {
        if (p.find(key) != p.end()) {
            LinkNode* cur = p[key];
            cur->PopNode();
            head->AddNode(cur);
            return cur->val;
        }
        else
            return -1;
    }

    void put(int key, int value) {
        if (p.find(key) != p.end()) {
            p[key]->val = value;
            get(key);
        }
        else {
            if (size == capacity) {
                LinkNode* q = head->prev;
                head->prev = q->prev;
                head->prev->next = head;
                p.erase(q->key);
                delete q;
                --size;
            }
            p[key] = head->AddNode(key, value);
            ++size;
        }
    }

private:
    // 容量和实际存放的数据数量
    int capacity, size;
    // 双向循环链表的头指针
    LinkNode* head;
    unordered_map<int, LinkNode*> p;
};

int Submit() {
    LRUCache lRUCache(2);
    lRUCache.put(1, 1);    // 缓存是 {1=1}
    lRUCache.put(2, 2);    // 缓存是 {1=1, 2=2}
    lRUCache.get(1);       // 返回 1
    lRUCache.put(3, 3);    // 该操作会使得关键字 2 作废，缓存是 {1=1, 3=3}
    lRUCache.get(2);       // 返回 -1 (未找到)
    lRUCache.put(4, 4);    // 该操作会使得关键字 1 作废，缓存是 {4=4, 3=3}
    lRUCache.get(1);       // 返回 -1 (未找到)
    lRUCache.get(3);       // 返回 3
    lRUCache.get(4);       // 返回 4

    return 0;
}

#endif