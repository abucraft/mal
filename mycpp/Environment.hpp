#include "MAL.hpp"
#include <map>
#include <string>
#ifndef INCLUDE_ENVIRONMENT_HPP
#define INCLUDE_ENVIRONMENT_HPP

class MalEnv :public std::enable_shared_from_this<MalEnv>{
    std::map<std::string, MalItemPtr> m_map;
    public:
    MalItemPtr get(std::string name);
    void set(std::string name, MalItemPtr value);
    ~MalEnv(){}
};

#endif