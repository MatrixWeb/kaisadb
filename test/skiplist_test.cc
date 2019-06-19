#include "memtable/skiplist.h"
#include "util/testharness.h"
#include "util/random.h"
#include "util/arena.h"
namespace kaisadb{

typedef uint64_t Key;

struct Comparator
{
    /* data */
    int operator()(const Key& a , const Key& b)const{
        if(a<b){
            return -1;
        }else if(a>b){
            return 1;
        }else{
            return 0;
        }
    }
};

class SkipTest {};

TEST(SkipTest, Empty) {
    Arena arena;
    Comparator cmp;
    SkipList<Key, Comparator> list(cmp, &arena);
    ASSERT_TRUE(!list.Contains(12));
    SkipList<Key, Comparator>::Iterator iter(&list);
    ASSERT_TRUE(!iter.Valid());
    iter.SeekToFirst();
    ASSERT_TRUE(!iter.Valid());
    iter.Seek(100);
    ASSERT_TRUE(!iter.Valid());
    iter.SeekToLast();
    ASSERT_TRUE(!iter.Valid());
    


}

}

int main(int argc, char** argv){
    return ::kaisadb::test::RunAllTests();
}