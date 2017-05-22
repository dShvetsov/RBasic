#include "Logical.h"

#include "variable_table.h"

int Logical_t::Not()
{
    int ind = TTV.put(Numeric);
    for (unsigned int i = 1; i < v.size(); i++)
    {
        if (v[i] != NULL)
            TTV[ind]->add(!(*v[i]));
        else
            TTV[ind]->add();
    }
    return ind;
}

int Logical_t::And(R_type *el)
{
    Logical_t *two = dynamic_cast<Logical_t *>(el->ToLog());
    int ind = TTV.put(Logical);
    bool a, b, isnull;
    int mod1 = v.size(), mod2 =  two->v.size();
    for (int i = 0; i < max(v.size(), two->v.size()) - 1; i++)
    {
        isnull = false;
        a = b = true;
        if (v[i % mod1 + 1] != NULL)
            a = *v[i % mod1 + 1];
        else
            isnull = true;
        if ( two->v[i % mod2 + 1] != NULL)
            b = *two->v[i % mod2 + 1];
        else
            isnull = true;
        if (isnull)
        {
            if (a == false || b == false)
                TTV[ind]->add(false);
            else
                TTV[ind]->add();
        }
        else
        {
            TTV[ind]->add(a && b);
        }
    }
    return ind;
}

int Logical_t::Or(R_type *el)
{
    Logical_t *two = dynamic_cast<Logical_t *>(el->ToLog());
    int ind = TTV.put(Logical);
    bool a, b, isnull;
    int mod1 = v.size(), mod2 =  two->v.size();
    for (int i = 0; i < max(v.size(), two->v.size()) - 1; i++)
    {
        isnull = false;
        a = b = false;
        if (v[i % mod1 +1] != NULL)
            a = *v[i % mod1 + 1];
        else
            isnull = true;
        if ( two->v[i % mod2 + 1] != NULL)
            b = *two->v[i % mod2 + 1];
        else
            isnull = true;
        if (isnull)
        {
            if (a == true || b == true)
                TTV[ind]->add(true);
            else
                TTV[ind]->add();
        }
        else
        {
            TTV[ind]->add(a || b);
        }
    }
    return ind;
}

std::set<unsigned int> Logical_t::get_tuple()
{
    std::set<unsigned int> a;
    for (unsigned int i = 1; i < v.size(); i++)
    {
        if (v[i] != NULL && *v[i])
        {
            a.insert(i);
        }
    }
    return a;
}

int Logical_t:: at(const std::set<unsigned int> &tuple)
{
    int ind = TTV.put(Logical, true);
    for (std::set<unsigned int>::iterator i = tuple.begin(); i != tuple.end(); i++)
    {
        if (*i < 0 || *i >= v.size()) throw "Out of range";
        TTV[ind]->addaddr(v[*i]);
    }
    return ind;
}

int Logical_t:: in(R_type *el)
{
    if (R_type::isfake())
    {
        if (el->get_type() != Logical) throw "Cannot assigment numeric not numeric";
        Logical_t *a = dynamic_cast<Logical_t *>(el);
        int mod = a->v.size() - 1;
        for (unsigned int i = 1; i < v.size(); i++)
        {
            if ( a->v[(i % mod) + 1] != NULL)
                (*v[i]) = *(a->v[(i % mod) + 1]);
            else
                (v[i]) = NULL;
        }
        return 1;
    }
    else
    {
        clear();
        if (el->get_type() == Logical)
        {
            Logical_t *a = dynamic_cast<Logical_t *>(el);
            for (unsigned int i = 1; i < a->v.size(); i++)
            {
                if (a->v[i] != NULL)
                {
                    add(*(a->v[i]));
                }
                else
                {
                    add();
                }
            }
        }
        else
        {
            return -1;
        }
    }
    return -1;
}

R_type *Logical_t::ToNum()
{
    int ind = TTV.put(Character);
    for (unsigned int i = 1; i < v.size(); i++)
    {
        if (v[i] != NULL)
        {
            TTV[ind] -> add( double( *v[i]));
        }
        else
        {
            TTV[ind] -> add();
        }
    }
    return TTV[ind];
}

R_type *Logical_t::ToChar()
{
    int ind = TTV.put(Character);
    for (unsigned int i = 1; i < v.size(); i++)
    {
        if (v[i] != NULL)
        {
            if ( (*v[i]))
                TTV[ind] -> add("true");
            else
                TTV[ind] -> add("false");
        }
        else
        {
            TTV[ind] -> add();
        }
    }
    return TTV[ind];
}
