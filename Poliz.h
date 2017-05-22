#ifndef Poliz__cpp
#define Poliz__cpp

#include <vector>
#include <iostream>

#include "LA.cpp"
#include "R_type.cpp"
#include "SA.cpp"
#include "variable_table.cpp"

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
