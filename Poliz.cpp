#include "Poliz.h"

#include <vector>
#include <iostream>

void Poliz::clear() {p.clear(); free = 0;}

void Poliz::put_lex(Lex l){p.push_back(l); ++free;}

void Poliz::put_lex(Lex l, int place) {
    try{
        p.at(place) = l;
    }
    catch (...) {
        throw "POLIZ: access in not existing element";
    }
}

void Poliz::blank()
{ p.push_back(Lex(LEX_NULL)); free++;}

int Poliz::get_free()
{return free; }

Lex& Poliz::operator[] (int index)
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

