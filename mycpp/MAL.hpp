#include <memory>
#include <vector>
#ifndef INCLUDE_MAL_HPP
#define INCLUDE_MAL_HPP
#define ASSERT(expr,description) \
        if(!(expr)){ \
            throw MalRuntimeException(description); \
        }
class MalEnv;
typedef std::shared_ptr<MalEnv> MalEnvPtr;
class MalItem;
typedef std::shared_ptr<MalItem> MalItemPtr;

typedef std::vector<MalItemPtr>::iterator MalItemPtrIter;

class MalRuntimeException;

MalItemPtr builtin_add(MalEnvPtr env, MalItemPtrIter argsBegin, MalItemPtrIter argsEnd);
MalItemPtr builtin_sub(MalEnvPtr env, MalItemPtrIter argsBegin, MalItemPtrIter argsEnd);
MalItemPtr builtin_mul(MalEnvPtr env, MalItemPtrIter argsBegin, MalItemPtrIter argsEnd);
MalItemPtr builtin_div(MalEnvPtr env, MalItemPtrIter argsBegin, MalItemPtrIter argsEnd);

#endif