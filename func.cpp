#include "func.h"

#include <string>

#include "variable_table.h"
#include "R_type.h"
#include "Numeric.h"
#include "Logical.h"
#include "Character.h"

int conc(std::list<R_type *> a)
{
    if (a.empty())
    {
        return TTV.put(Nulltype);
    }
    kind_of_type t;
    t = (a.front())->get_type();
    int ind = TTV.put(t);
    bool *b;
    double *d;
    std::string *s;
    for (std::list<R_type *>::iterator i = a.begin(); i != a.end(); i++)
    {
        for (int j = 1; j <= (*i)->Rsize(); j++)
        {
            switch(t)
            {
            case Nulltype:
                TTV[ind]->add();
                break;
            case Logical:
                b = (*i)->kernel_at_log(j);
                if (b != NULL)
                    TTV[ind]->add(*b);
                else
                    TTV[ind]->add();
                break;
            case Numeric:
                d = (*i)->kernel_at_num(j);
                if (d != NULL)
                    TTV[ind]->add(*d);
                else
                    TTV[ind]->add();
                break;
            case Character:
                s =(*i)->kernel_at_char(j);
                if (s != NULL)
                    TTV[ind]->add(*s);
                else
                    TTV[ind]->add();
                break;
            }
        }
    }
    return ind;
}

int Mode(std::list<R_type *> a)
{
    if (a.empty())
    {
        throw "Function Mode must have >1 arguments";
    }
    std::string sNull("NULL");
    std::string sLog("Logical");
    std::string sNum("Numeric");
    std::   string sChar("Character");
    int ind = TTV.put(Character);
    for (std::list<R_type *>::iterator i = a.begin(); i != a.end(); i++)
    {
        kind_of_type t = (*i)->get_type();
        switch(t)
        {
        case Nulltype:
            TTV[ind]->add(sNull);
            break;
        case Logical:
            TTV[ind]->add(sLog);
            break;
        case Numeric:
            TTV[ind]->add(sNum);
            break;
        case Character:
            TTV[ind]->add(sChar);
            break;
        }
    }
    return ind;
}

int lenght(std::list<R_type *> a)
{
    if (a.empty())
    {
        throw "Function Length must have > 1 args";
    }
    int ind = TTV.put(Numeric);
    for (std::list<R_type *>::iterator i = a.begin(); i != a.end(); i++)
    {
        TTV[ind]->add(double((*i)->Rsize()));
    }
    return ind;
}
