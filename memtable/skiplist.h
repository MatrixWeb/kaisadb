#include <iostream>
#include <cstdio>

template <typename Key , class Comparator>
class SkipList {

    private:
        struct Node;

    Comparator const comparator;
    std::atomic<int> max_height_;
    Node* const head_;

}

template <typename Key , class Comparator>
struct SkipList<Key,Comparator>::Node
{
    /* data */
    Key const key;
    private:
        std::atomic<Node*> next_[1];
};
