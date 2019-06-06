#include<cstddef>
#include<cstdint>
#include<atomic>
#include<vector>
#ifndef STORAGE_KAISADB_AREA_H_


#define STORAGE_KAISADB_AREA_H_
namespace kaisadb {

class Area
{
private:
    /* data */
public:
    Area(/* args */);
    Area(const Area&) = delete;
    char* Allocate(size_t bytes);
    char* AllocateAligned(size_t bytes);
    ~Area();
private:
    char* AllockFallBack(size_t bytes);
    char* AllocateNewBlock(size_t block_bytes);
    //Allocation state
    char* alloc_ptr_;
    size_t alloc_size_remaining_;

    std::vector<char*> blocks_;
    std::atomic<size_t> memory_usage_;
};

Area::Area(/* args */)
{
}

Area::~Area()
{
}


}  //namespace kaisadb
#endif