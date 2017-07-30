#include "Types.hpp"
#include "Environment.hpp"

MalItemPtr builtin_add(MalEnvPtr env, MalItemPtrIter argsBegin, MalItemPtrIter argsEnd){
    ASSERT(std::distance(argsBegin,argsEnd) == 2,"args number of '+' is not 2");
    auto arg1 = *argsBegin;
    argsBegin++;
    auto arg2 = *argsBegin;
    arg1 = arg1->eval(env);
    arg2 = arg2->eval(env);
    ASSERT(TYPEOF(MalNumber,arg1),"first arg is not a number");
    ASSERT(TYPEOF(MalNumber,arg2),"second arg is not a number");
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
    ASSERT(TYPEOF(MalNumber,arg1),"first arg is not a number");
    ASSERT(TYPEOF(MalNumber,arg2),"second arg is not a number");
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
    ASSERT(TYPEOF(MalNumber,arg1),"first arg is not a number");
    ASSERT(TYPEOF(MalNumber,arg2),"second arg is not a number");
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
    ASSERT(TYPEOF(MalNumber,arg1),"first arg is not a number");
    ASSERT(TYPEOF(MalNumber,arg2),"second arg is not a number");
    double value1 = std::dynamic_pointer_cast<MalNumber>(arg1)->value();
    double value2 = std::dynamic_pointer_cast<MalNumber>(arg2)->value();
    return std::make_shared<MalNumber>(value1/value2);
}

MalItemPtr builtin_def(MalEnvPtr env, MalItemPtrIter argsBegin, MalItemPtrIter argsEnd){
    ASSERT(std::distance(argsBegin,argsEnd) == 2,"args number of 'def!' is not 2");
    auto arg1 = *argsBegin;
    argsBegin++;
    auto arg2 = *argsBegin;
    arg2 = arg2->eval(env);
    ASSERT(TYPEOF(MalSymbol, arg1),"first arg is not a symbol");
    env->set(arg1->toString(), arg2);
    return arg2;
}

MalItemPtr builtin_let(MalEnvPtr env, MalItemPtrIter argsBegin, MalItemPtrIter argsEnd){
    ASSERT(std::distance(argsBegin,argsEnd) == 2,"args number of 'let*' is not 2");
    auto arg1 = *argsBegin;
    argsBegin++;
    auto arg2 = *argsBegin;
    ASSERT(TYPEOF(MalList, arg1), "first arg is not a list");
    auto list = std::dynamic_pointer_cast<MalList>(arg1); 
    auto itemIter = list->m_items.begin();
    auto newEnv = std::make_shared<MalEnv>(env);
    envStack.push_back(newEnv);
    while(itemIter!=list->m_items.end()){
        auto symbol = *itemIter;
        ASSERT(TYPEOF(MalSymbol, symbol), symbol->toString() + " is not a symbol");
        itemIter++;
        ASSERT(itemIter!=list->m_items.end(),"let* "+symbol->toString()+" not defined");
        auto value = (*itemIter)->eval(newEnv);
        itemIter++;
        newEnv->set(symbol->toString(), value);
    }
    auto result = arg2->eval(newEnv);
    return result;
}