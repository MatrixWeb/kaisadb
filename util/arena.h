#include<cstddef>
#include<cstdint>
#include<atomic>
#include<vector>
#include<cassert>
#ifndef STORAGE_KAISADB_AREA_H_


#define STORAGE_KAISADB_AREA_H_
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




}  //namespace kaisadb
#endif