#include "Environment.hpp"
#include "Types.hpp"

MalItemPtr MalEnv::get(std::string name){
    ASSERT(m_map.find(name)!=m_map.end(),name+" not found");
    return m_map[name];
}

void MalEnv::set(std::string name,MalItemPtr value){
    m_map[name]=value;
}