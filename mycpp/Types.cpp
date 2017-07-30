#include "Types.hpp"
#include "Environment.hpp"
#include <sstream>
#include <iterator>

std::ostream& operator<<(std::ostream& out,const MalItemPtr malItem){
    out << malItem->toString();
    return out;
}

std::string MalList::toString() const{
    std::ostringstream oss;
    char leftParen,rightParen;
    if(m_isVector){
        leftParen='[';
        rightParen=']';
    }else{
        leftParen='(';
        rightParen=')';
    }
    oss<<leftParen;
    if(!m_items.empty()){
        std::copy(m_items.begin(), m_items.end()-1,std::ostream_iterator<MalItemPtr>(oss, " "));
        oss<<m_items.back();
    }
    oss<<rightParen;
    return oss.str();
}

std::string MalMap::toString() const{
    std::ostringstream oss;
    oss<<'{';
    if(!m_map.empty()){
        std::string common = "";
        for(auto i=m_map.begin();i!=m_map.end();i++){
            oss<<i->first;
            oss<<' ';
            oss<<i->second;
            oss<<common;
            common=",";
        }
    }
    oss<<'}';
    return oss.str();
}

std::string MalNumber::toString() const{
    std::ostringstream oss;
    oss<<m_value;
    return oss.str();
}

std::string MalString::toString() const{
    return m_str;
}

std::string MalSymbol::toString() const{
    return m_symbol;
}

MalItemPtr MalList::eval(MalEnvPtr env){
    if(!m_isVector){
        if(m_items.size()==0){
            return shared_from_this();
        }
        //std::cout<<m_items.size();
        MalItemPtrIter iter = m_items.begin();
        std::string name = (*iter)->toString();
        MalItemPtr op = (*iter)->eval(env);
        ASSERT(TYPEOF(MalCallable, op), name+" is not callable");
        MalItemPtrIter argsBegin = ++iter;
        MalItemPtrIter argsEnd = m_items.end();
        return std::dynamic_pointer_cast<MalCallable>(op)->apply(env, argsBegin, argsEnd);
    } else {
        auto nVec=std::make_shared<MalList>(true);
        for(auto i: m_items){
            nVec->m_items.push_back(i->eval(env));
        }
        return nVec;
    }
}

MalItemPtr MalMap::eval(MalEnvPtr env){
    auto nMap = std::make_shared<MalMap>();
    for(auto i =m_map.begin();i!=m_map.end();i++){
        nMap->m_map[i->first]=i->second->eval(env);
    }
    return nMap;
}

MalItemPtr MalSymbol::eval(MalEnvPtr env){
    auto value = env->get(toString());
    //std::cout<<"get "<<toString()<<std::endl;
    ASSERT(value!=nullptr,"'"+toString()+"' not found");
    return value;
}