#include "util/testharness.h"
#include<vector>
#include<stdlib.h>
#include<string>
#include<string.h>
namespace kaisadb {

namespace test {

namespace {
struct Test {
    const char* base;
    const char* name;
    void (*func)();
};
std::vector<Test>* tests;
}// namespace

bool RegisterTest(const char* base , const char* name , void(*func)()){
    if(tests == nullptr){
        tests = new std::vector<Test>;
    }
    Test t;
    t.base = base;
    t.name = name;
    t.func = func;
    tests->push_back(t);
    return true;


}

int RunAllTests(){
    const char* matcher = getenv("KAISADB_TESTS");
    int num = 0;
    if(tests!=nullptr){
        for(size_t i = 0;i<tests->size();i++){
            const Test& t= (*tests)[i];
            if(matcher!=nullptr){
                std::string name = t.base;
                name.push_back('.');
                name.append(t.name);
                if(strstr(name.c_str(),matcher)==nullptr){
                    continue;
                }
            }
            fprintf(stderr , "==== Test %s.%s\n",t.base,t.name);
            (*t.func)();
            num++;
        }
    }
    fprintf(stderr , "==== PASSED %d tests\n",num);
    return 0;
}





} // namespace test

} // namespace kaisadb