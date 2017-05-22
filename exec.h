#ifndef exec__h
#define exec__h

#include "LA.h"
#include "Poliz.h"

class Executer
{
    Lex pc_el;
public:
    void execute(Poliz &prog);
};

#endif
