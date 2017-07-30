#include "Environment.hpp"
#include "Types.hpp"

std::vector<MalEnvPtr> envStack;

MalItemPtr MalEnv::get(std::string name){
    if(m_map.find(name)==m_map.end()){
        if(m_parent!=nullptr){
            return m_parent->get(name);
        }else{
            return nullptr;
        }
    }else{
        return m_map[name];
    }
}

void MalEnv::set(std::string name,MalItemPtr value){
    m_map[name]=value;
}