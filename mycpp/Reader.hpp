#include <vector>
#include <string>
#include "Types.hpp"
class Reader{
    std::vector<std::string> tokens;
    int index;
    public:
    Reader(std::vector<std::string>&& tk):tokens(tk),index(0){}
    Reader(Reader&& reader):tokens(reader.tokens),index(reader.index){}
    std::string next();
    std::string peek();
    bool empty();
};

MalItemPtr readStr(const char* line);