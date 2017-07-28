#include <readline/readline.h>
#include <readline/history.h>
#include <string>
#include <stdio.h>
using namespace std;
int main(){
    const string prompt = "user> ";
    while(1){
        char *line = readline(prompt.c_str());
        add_history(line);
        printf("%s\n",line);
    }
}