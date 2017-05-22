#ifndef Poliz__cpp
#define Poliz__cpp

#include <vector>
#include <iostream>

#include "LA.h"
#include "R_type.h"
#include "SA.h"
#include "variable_table.h"

class Poliz
{
    std::vector<Lex> p;
    int free;
public:
    void clear();
    Poliz():free(0){}
    void put_lex(Lex l);
    void put_lex(Lex l, int place);
    void blank();
    int get_free();
    Lex& operator[] (int index);
    friend std::ostream & operator << (std::ostream& os, Poliz &prog);
};


#endif
