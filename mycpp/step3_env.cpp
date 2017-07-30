#include <readline/readline.h>
#include <readline/history.h>
#include <string>
#include <stdio.h>
#include "Reader.hpp"
#include "Environment.hpp"
#include "Types.hpp"
#include "Printer.hpp"
int main(){
    MalEnvPtr env = std::make_shared<MalEnv>();
    envStack.push_back(env);
    env->set("+",std::make_shared<MalBuiltIn>("+",builtin_add));
    env->set("-",std::make_shared<MalBuiltIn>("-",builtin_sub));
    env->set("*",std::make_shared<MalBuiltIn>("*",builtin_mul));
    env->set("/",std::make_shared<MalBuiltIn>("/",builtin_div));
    env->set("def!",std::make_shared<MalBuiltIn>("def!",builtin_def));
    env->set("let*",std::make_shared<MalBuiltIn>("let*",builtin_let));
    const std::string prompt = "user> ";
    while(1){
        char *line = readline(prompt.c_str());
        add_history(line);
        MalItemPtr lItem = readStr(line);
        if(lItem!=nullptr){
            try{
                //std::cout<<lItem<<std::endl;
                MalItemPtr result = lItem->eval(env);
                std::cout<<result<< std::endl;
            }catch(MalRuntimeException &e){
                std::cout<<e.what()<<std::endl;
            }
        }
    }
}