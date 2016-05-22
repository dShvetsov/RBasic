#ifndef runner__cpp
#define runner_cpp

#include <iostream>
#include <sstream>
#include <vector>
#include <stack>
#include <iterator>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <ctype.h>
#include <typeinfo>
#include <set>
#include <list>

#include "R_typeh.cpp"
#include "variable_table.cpp"
#include "R_type.cpp"
#include "LA.cpp"
#include "Numeric.cpp"
#include "Logical.cpp"
#include "Character.cpp"
#include "Poliz.cpp"
#include "SA.cpp"
#include "func.cpp"
#include "exec.cpp"

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

#endif
