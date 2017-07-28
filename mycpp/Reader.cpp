#include "Reader.hpp"
#include "Types.hpp"
#include <regex>
const std::regex malReg("[\\s,]*(~@|[\\[\\]{}()'`~^@]|\"(?:\\\\.|[^\\\\\"])*\"|;.*|[^\\s\\[\\]{}('\"`,;)]+)");
const std::regex digitReg("^-?\\d*\\.?\\d+");

std::string Reader::next(){
    auto token = this->tokens[this->index];
    this->index++;
    return token;
}

std::string Reader::peek(){
    return this->tokens[this->index];
}

bool Reader::empty(){
    return this->tokens.size()==(uint)this->index;
}

Reader tokenizer(const char* line){
    std::string sline(line);
    std::smatch sm;
    std::vector<std::string> tokens;
    auto lbegin = std::sregex_iterator(sline.begin(),sline.end(),malReg);
    auto lend = std::sregex_iterator();
    for(;lbegin!=lend;lbegin++){
        std::smatch sm=*lbegin;
        if(sm.size()>0){
            tokens.push_back(sm[1].str());
        }
    }
    return Reader(std::move(tokens));
}

MalItemPtr readList(Reader& reader, bool vector = false);
MalItemPtr readMap(Reader& reader);

MalItemPtr readAtom(std::string token){
    std::smatch sm;
    if(std::regex_match(token,sm,digitReg)){
        double digit = std::stod(token);
        return std::make_shared<MalNumber>(digit);
    }else if(token[0]=='\"'){
        return std::make_shared<MalString>(token);
    }else{
        return std::make_shared<MalSymbol>(token);
    }
}

MalItemPtr readForm(Reader& reader){
    if(reader.empty()){
        return std::make_shared<MalSymbol>("");
    }
    auto token = reader.next();
    if(token == "("){
        auto list = readList(reader);
        return list;
    }else if(token == "["){
        auto list = readList(reader, true);
        return list;
    }else if(token == "{"){
        auto map = readMap(reader);
        return map;
    }else if(token == "}"){
        throw MalParseException("hash map pair not match");
    }else{
        return readAtom(token);
    }
}

MalItemPtr readList(Reader& reader, bool vector){
    auto token = reader.peek();
    auto list = std::make_shared<MalList>(vector);
    auto rightEnd = vector?"]":")";
    while(token!=rightEnd){
        list->m_items.push_back(readForm(reader));
        if(reader.empty()){
            throw MalRightParenException(rightEnd);
        }
        token = reader.peek();
    }
    reader.next(); //skip right paren
    return list;
}

MalItemPtr readMap(Reader& reader){
    auto token = reader.peek();
    auto map = std::make_shared<MalMap>();
    while(token!="}"){
        std::string name = reader.next();
        map->m_map[name] = readForm(reader);
        if(reader.empty()){
            throw MalRightParenException("}");
        }
        token = reader.peek();
    }
    reader.next();
    return map;
}

void checkQuote(const char* line){
    std::string lineStr(line);
    bool quote = false;
    bool backSlash = false;
    for(uint i=0;i<lineStr.size();i++){
        switch(lineStr[i]){
            case '\"':
            quote = backSlash?quote:!quote;
            break;
            case '\\':
            backSlash = !backSlash;
            break;
            default:
            backSlash = false;
            break;
        }
    }
    if(quote){
        throw MalRightParenException("\"");
    }
}

MalItemPtr readStr(const char* line){
    try{
        checkQuote(line);
        //std::cout<<"checkQuote finish"<<std::endl;
        Reader reader = tokenizer(line);
        //std::cout<<"tokenized"<<std::endl;
        MalItemPtr item = readForm(reader);
        //std::cout<<"item read finish"<<std::endl;
        return item;
    }catch(MalRightParenException &e){
        std::cout<<e.what()<<std::endl;
        return nullptr;
    }catch(MalParseException &e){
        std::cout<<e.what()<<std::endl;
        return nullptr;
    }
}
