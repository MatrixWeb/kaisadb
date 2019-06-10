#include "arena.h"

namespace kaisadb {

static const int kBlockSize = 4096;

Arena::Arena():alloc_ptr_(nullptr),alloc_size_remaining_(0),memory_usage_(0){

}
Arena::~Arena() {
    for(size_t i=0;i<blocks_.size();i++){
        delete[] blocks_[i];
    }
}
inline char* Arena::Allocate(size_t bytes)
{
    assert(bytes>0);
    if(bytes<alloc_size_remaining_){
        char* result=alloc_ptr_;
        alloc_ptr_+=bytes;
        alloc_size_remaining_-=bytes;
        return result;
    }
    return AllockFallBack(bytes);
}

char* Arena::AllockFallBack(size_t bytes){
    if(bytes > kBlockSize/4){
        char* result=AllocateNewBlock(bytes);
        return result;
    }
    alloc_ptr_ = AllocateNewBlock(kBlockSize);
    alloc_size_remaining_ = kBlockSize;
    char* result= alloc_ptr_;
    alloc_ptr_+=bytes;
    alloc_size_remaining_-=bytes;
    return result;
}

char* Arena::AllocateNewBlock(size_t block_bytes){
    char* result=new char[block_bytes];
    blocks_.push_back(result);
    memory_usage_.fetch_add(block_bytes+sizeof(char*),std::memory_order_relaxed);
    return result;
}
} //namespace kaisadb