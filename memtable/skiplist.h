#ifndef STORAGE_KAISADB_DB_SKIPLIST_H_
#define STORAGE_KAISADB_DB_SKIPLIST_H_ 

#include <iostream>
#include <cstdio>
#include "util/arena.h"
#include "util/random.h"


template <typename Key , class Comparator>
class SkipList {

private:
    struct Node;

public:
    explicit SkipList(Comparator cmp, Arena* arena);
    SkipList(const SkipList&) = delete;
    SkipList& operator=(const SkipList&) = delete;
private:
    enum { kMaxHeight = 12 };
    Node* NewNode(const Key& key, int height);
    int RandomHeight();

    bool KeyIsAfterNode(const Key& key, Node* n)const;
    Node* FindGreaterOrEqual(const Key& key , Node** prev)const;
    inline int GetMaxHeight()const {
        return max_height_.load(std::memory_order_relaxed);
    }

    Comparator const compare_;
    std::atomic<int> max_height_;
    Arena* const arena_;
    Node* const head_;
    Random rnd_;
};

template <typename Key , class Comparator>
struct SkipList<Key,Comparator>::Node
{
    explicit Node(const Key& k):key(k){}
    /* data */
    Key const key;
    Node* Next(int n){
        return next_[n].load(std::memory_order_acquire);
    }
    void SetNext(int n, Node* x){
        next_[n].store(x,std::memory_order_release);
    }
    Node* NoBarrier_Next(int n){
        return next_[n].load(std::memory_order_relaxed);
    }
    void NoBarrier_SetNext(int n,Node* x){
        next[n].store(x,std::memory_order_relaxed);
    }
private:
    std::atomic<Node*> next_[1];
};


template <typename Key , class Comparator>
SkipList<Key, Comparator>::Node* SkipList<Key, Comparator>::NewNode(const Key& key, int height)
{
    char* const node_memory = arena_->AllocateAligned(sizeof(Node)+sizeof(std::atomic<Node*>)*(height-1));
    return new (node_memory) Node(key);
}


template <typename Key, class Comparator>
int SkipList<Key, Comparator>::RandomHeight(){
    static const unsigned int kBranching = 4;
    int height=1;
    while(height<max_height_ && ((rnd_.Next()%kBranching)==0){
        height++;
    }
    return height;
}

template <typename Key , class Comparator>
SkipList<Key, Comparator>::SkipList(Comparator cmp , Arena* arena)
    :compare_(cmp),
    arena_(arena),
    head_(NewNode(0,kMaxHeight)),
    max_height_=1,
    rnd_(0xdeadbeef){
        for(int i=0;i<kMaxHeight;I++){
            head_.SetNext(i,nullptr);
        }
}

template <typename Key , class Comparator>
bool SkipList<Key,Comparator>::KeyIsAfterNode(const Key& key, Node* n) const {
    return (n!=nullptr) && (compare_(n->key , key)<0);
}

template <typename Key , class Comparator>
typename SkipList<Key,Comparator>::Node*
SkipList<Key,Comparator>::FindGreaterOrEqual(const Key& key , Node** prev)const {
    Node* x = head_;
    int level =  GetMaxHeight() - 1;
    while(true){
        Node* next = x->Next(level);
        if(KeyIsAfterNode(key,next)){
            x=next;
        }else{
            if(prev!=nullptr)prev[level]=x;
            if(level==0){
                return x;
            }else{
                level--;
            }
        }
    }
}


#endif