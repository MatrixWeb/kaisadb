#ifndef STORAGE_KAISADB_AREA_H_
#define STORAGE_KAISADB_AREA_H_

#include<cstddef>
#include<cstdint>
#include<atomic>
#include<vector>
#include<cassert>
namespace kaisadb {

class Arena
{
private:
    /* data */
public:
    Arena(/* args */);
    Arena(const Arena&) = delete;
    Arena& operator=(const Arena&) = delete;
    char* Allocate(size_t bytes);
    char* AllocateAligned(size_t bytes);
    ~Arena();
private:
    char* AllockFallBack(size_t bytes);
    char* AllocateNewBlock(size_t block_bytes);
    //Allocation state
    char* alloc_ptr_;
    size_t alloc_size_remaining_;

    std::vector<char*> blocks_;
    std::atomic<size_t> memory_usage_;
};
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



}  //namespace kaisadb
#endif