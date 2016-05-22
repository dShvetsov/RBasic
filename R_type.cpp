#ifndef R_type__cpp
#define R_type__cpp

#define EPS 0.000000001
/*
#include <iostream>
#include <cstdio>
#include <vector>
#include <iterator>
#include <cstdlib>
#include <typeinfo>
#include "LA.cpp"
#include "variable_table.cpp"
*/

int at(std::set<int> &a) {
    return TTV.put(Nulltype, true);
}

R_type *R_type::ToLog()
{
    int ind = TTV.put(Logical);
    for (int i = 0; i < size; i ++)
    {
        TTV[ind]->add();
    }
    return TTV[ind];
}

R_type *R_type::ToNum()
{
    int ind = TTV.put(Numeric);
    for (int i = 0; i < size; i ++)
    {
        TTV[ind]->add();
    }
    return TTV[ind];
}

R_type *R_type::ToChar()
{
    int ind = TTV.put(Character);
    for (int i = 0; i < size; i ++)
    {
        TTV[ind]->add();
    }
    return TTV[ind];
}

int Eq(R_type *a, R_type *b)
{
    if (a->get_type() == Character || b->get_type() == Character)
        return (a->ToChar())->Eq(b);
    return (a->ToNum())->Eq(b);
}

int Neq(R_type *a, R_type *b)
{
    if (a->get_type() == Character || b->get_type() == Character)
        return (a->ToChar())->Neq(b);
    return (a->ToNum())->Neq(b);
}

int Bigger(R_type *a, R_type *b)
{
    if (a->get_type() == Character || b->get_type() == Character)
        return (a->ToChar())->Bigger(b);
    return (a->ToNum())->Bigger(b);
}

int Beq(R_type *a, R_type *b)
{
    if (a->get_type() == Character || b->get_type() == Character)
        return (a->ToChar())->Beq(b);
    return (a->ToNum())->Beq(b);
}

int Less(R_type *a, R_type *b)
{
    if (a->get_type() == Character || b->get_type() == Character)
        return (a->ToChar())->Less(b);
    return (a->ToNum())->Less(b);
}

int Leq(R_type *a, R_type *b)
{
    if (a->get_type() == Character ||  b ->get_type() == Character)
        return (a->ToChar())->Leq(b);
    return (a->ToNum())->Leq(b);
}





#endif
