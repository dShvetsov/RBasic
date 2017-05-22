#include <iostream>
#include <string>

#include "SA.h"
#include "exec.h"

int main()
{
    Parser p;
    Executer e;
    while (true){
    try{
        p.analyze();
        std::cout << p.prog << std::endl;
        e.execute(p.prog);
        TTV.clear();
        p.prog.clear();
    }
    catch(const char *s) {std::cout << s << std::endl;}
    }
    return 0;
}

