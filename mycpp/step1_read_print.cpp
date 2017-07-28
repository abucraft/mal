#include <readline/readline.h>
#include <readline/history.h>
#include <string>
#include <stdio.h>
#include "Reader.hpp"
#include "Types.hpp"
#include "Printer.hpp"
int main(){
    const std::string prompt = "user> ";
    while(1){
        char *line = readline(prompt.c_str());
        add_history(line);
        MalItemPtr lItem = readStr(line);
        if(lItem!=nullptr){
            std::cout<<lItem<< std::endl;
        }
    }
}