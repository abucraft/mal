#include <vector>
#include <map>
#include <string>
#include <iostream>
#include <stdexcept>
#include "MAL.hpp"
#ifndef INCLUDE_TYPES_HPP
#define INCLUDE_TYPES_HPP

#define TYPEOF(type, elm) (std::dynamic_pointer_cast<type>(elm)!=nullptr)

class MalItem : public std::enable_shared_from_this<MalItem>{
    public:
    virtual MalItemPtr eval(MalEnvPtr env){return shared_from_this();}
    virtual std::string toString() const = 0;
    virtual ~MalItem(){}
    friend std::ostream& operator<<(std::ostream&os,const MalItemPtr malItem);
};

class MalList : public MalItem{
    bool m_isVector;
    public:
    MalList(bool v):m_isVector(v){}
    MalList():m_isVector(false){}
    MalItemPtr eval(MalEnvPtr) override;
    std::vector<MalItemPtr> m_items;
    bool isVector(){return m_isVector;}
    std::string toString() const override;
    ~MalList(){}
};

class MalMap : public MalItem{
    public:
    MalMap(){}
    std::map<std::string, MalItemPtr> m_map;
    MalItemPtr eval(MalEnvPtr) override;
    std::string toString() const override;
    ~MalMap(){}
};

class MalNumber: public MalItem{
    double m_value;
    public:
    MalNumber(double n):m_value(n){}
    double value(){return m_value;}
    std::string toString() const override;
    ~MalNumber(){}
};

class MalString: public MalItem{
    std::string m_str;
    public:
    MalString(std::string s):m_str(s){}
    std::string value(){return m_str;}
    std::string toString() const override;
    ~MalString(){}
};

class MalSymbol: public MalItem{
    std::string m_symbol;
    public:
    MalSymbol(std::string str):m_symbol(str){}
    MalItemPtr eval(MalEnvPtr) override;
    std::string toString() const override;
    ~MalSymbol(){}
};

class MalCallable: public MalItem{
    public:
    std::string toString() const override{return "callable function";}
    virtual MalItemPtr apply(MalEnvPtr env, MalItemPtrIter argsBegin, MalItemPtrIter argsEnd){return nullptr;}
};

class MalBuiltIn: public MalCallable{
    public:
    typedef MalItemPtr (*ApplyFunc)(MalEnvPtr,MalItemPtrIter,MalItemPtrIter);
    MalItemPtr apply(MalEnvPtr env,MalItemPtrIter argsBegin,MalItemPtrIter argsEnd) override{return m_func(env,argsBegin,argsEnd);}
    MalBuiltIn(std::string name, ApplyFunc func):m_name(name),m_func(func){}
    std::string toString() const override{return "built in function '"+m_name+"'";}
    private:
    std::string m_name;
    ApplyFunc m_func;
};


class MalRightParenException: public std::exception{
    public:
    std::string target;
    MalRightParenException(std::string s):target(s){}
    std::string what(){ return "expected '"+target+"', got EOF"; }
};

class MalParseException: public std::exception{
    public:
    std::string description;
    MalParseException(std::string s):description(s){}
    std::string what(){ return description;}
};

class MalRuntimeException: public std::exception{
    public:
    std::string description;
    MalRuntimeException(std::string s): description(s){}
    std::string what(){ return description;}
};
#endif 