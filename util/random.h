#ifndef STORAGE_KAISADB_UTIL_RANDOM_H_
#define STORAGE_KAISADB_UTIL_RANDOM_H_

#include<stdint.h>

namespace kaisadb {

class Random{

private:
    uint32_t seed_;

public:
    explicit Random(uint32_t s): seed_(s & 0x7ffffffffu){
        if(seed_ ==0 || seed_ == 2147483647L){
            seed_=1
        }
    }
}

} //namespace kaisadb

#endif