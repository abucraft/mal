#include "Types.hpp"

MalItemPtr builtin_add(MalEnvPtr env, MalItemPtrIter argsBegin, MalItemPtrIter argsEnd){
    ASSERT(std::distance(argsBegin,argsEnd) == 2,"args number of '+' is not 2");
    auto arg1 = *argsBegin;
    argsBegin++;
    auto arg2 = *argsBegin;
    arg1 = arg1->eval(env);
    arg2 = arg2->eval(env);
    ASSERT(TYPEOF(MalNumber,arg1),"first arg is not number");
    ASSERT(TYPEOF(MalNumber,arg2),"second arg is not number");
    double value1 = std::dynamic_pointer_cast<MalNumber>(arg1)->value();
    double value2 = std::dynamic_pointer_cast<MalNumber>(arg2)->value();
    return std::make_shared<MalNumber>(value1+value2);
}
MalItemPtr builtin_sub(MalEnvPtr env, MalItemPtrIter argsBegin, MalItemPtrIter argsEnd){
    ASSERT(std::distance(argsBegin,argsEnd) == 2,"args number of '-' is not 2");
    auto arg1 = *argsBegin;
    argsBegin++;
    auto arg2 = *argsBegin;
    arg1 = arg1->eval(env);
    arg2 = arg2->eval(env);
    ASSERT(TYPEOF(MalNumber,arg1),"first arg is not number");
    ASSERT(TYPEOF(MalNumber,arg2),"second arg is not number");
    double value1 = std::dynamic_pointer_cast<MalNumber>(arg1)->value();
    double value2 = std::dynamic_pointer_cast<MalNumber>(arg2)->value();
    return std::make_shared<MalNumber>(value1-value2);
}

MalItemPtr builtin_mul(MalEnvPtr env, MalItemPtrIter argsBegin, MalItemPtrIter argsEnd){
    ASSERT(std::distance(argsBegin,argsEnd) == 2,"args number of '*' is not 2");
    auto arg1 = *argsBegin;
    argsBegin++;
    auto arg2 = *argsBegin;
    arg1 = arg1->eval(env);
    arg2 = arg2->eval(env);
    ASSERT(TYPEOF(MalNumber,arg1),"first arg is not number");
    ASSERT(TYPEOF(MalNumber,arg2),"second arg is not number");
    double value1 = std::dynamic_pointer_cast<MalNumber>(arg1)->value();
    double value2 = std::dynamic_pointer_cast<MalNumber>(arg2)->value();
    return std::make_shared<MalNumber>(value1*value2);
}

MalItemPtr builtin_div(MalEnvPtr env, MalItemPtrIter argsBegin, MalItemPtrIter argsEnd){
    ASSERT(std::distance(argsBegin,argsEnd) == 2,"args number of '/' is not 2");
    auto arg1 = *argsBegin;
    argsBegin++;
    auto arg2 = *argsBegin;
    arg1 = arg1->eval(env);
    arg2 = arg2->eval(env);
    ASSERT(TYPEOF(MalNumber,arg1),"first arg is not number");
    ASSERT(TYPEOF(MalNumber,arg2),"second arg is not number");
    double value1 = std::dynamic_pointer_cast<MalNumber>(arg1)->value();
    double value2 = std::dynamic_pointer_cast<MalNumber>(arg2)->value();
    return std::make_shared<MalNumber>(value1/value2);
}