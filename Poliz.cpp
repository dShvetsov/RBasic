#ifndef Poliz__cpp
#define Poliz__cpp
/*
#include "LA.cpp"
#include "R_type.cpp"
#include "SA.cpp"
#include "variable_table.cpp"
*/
class Poliz
{
    std::vector<Lex> p;
    int free;
public:
    void clear() {p.clear(); free = 0;}
    Poliz():free(0){}
    void put_lex(Lex l){p.push_back(l); ++free;}
    void put_lex(Lex l, int place) {
        try{
            p.at(place) = l;
        }
        catch (...) {throw "POLIZ: access in not existing element";}
    };
    void blank(){ p.push_back(Lex(LEX_NULL)); free++;}
    int get_free(){return free; }
    Lex& operator[] (int index)
    {
        if (index > free)
            throw "Poliz: indefinite element of array";
        else
            return p[index];
    }
    friend std::ostream & operator << (std::ostream& os, Poliz &prog)
    {
        for (std::vector<Lex>::iterator i = prog.p.begin(); i != prog.p.end(); i++)
        {
            os << *i;
        }
        return os;
    }
};



#endif
