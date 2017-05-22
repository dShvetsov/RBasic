#include "Character.h"

#include "variable_table.h"

int Character_t::Eq(R_type *el)
{
    Character_t *a = dynamic_cast<Character_t *>(el->ToChar());
    int ind = TTV.put(Logical);
    int mod1 = v.size(), mod2 =  a->v.size();
    for (int i = 0; i < max(v.size(), a->v.size()) - 1; i++)
    {
        if (v[i % mod1 + 1] != NULL && a->v[i % mod2 + 1] != NULL)
        {
            TTV[ind]->add(!(*v[i % mod1 + 1]).compare(*(a->v[i % mod2 + 1])));
        }
        else{TTV[ind]->add();}
    }
    return ind;
}

int Character_t::Neq(R_type *el)
{
    Character_t *a = dynamic_cast<Character_t *>(el->ToChar());
    int ind = TTV.put(Logical);
    int mod1 = v.size(), mod2 =  a->v.size();
    for (int i = 0; i < max(v.size(), a->v.size()) - 1; i++)
    {
        if (v[i % mod1 + 1] != NULL && a->v[i % mod2 + 1] != NULL)
        {
            TTV[ind]->add( (*v[i % mod1 + 1]).compare(*(a->v[i % mod2 + 1])) == 0);
        }
        else{TTV[ind]->add();}
    }
    return ind;
}

int Character_t::Bigger(R_type *el)
{
    Character_t *a = dynamic_cast<Character_t *>(el->ToChar());
    int ind = TTV.put(Logical);
    int mod1 = v.size(), mod2 =  a->v.size();
    for (int i = 0; i < max(v.size(), a->v.size()) - 1; i++)
    {
        if (v[i % mod1 + 1] != NULL && a->v[i % mod2 + 1] != NULL)
        {
            TTV[ind]->add((*v[i % mod1 + 1]).compare(*(a->v[i % mod2 + 1])) > 0);
        }
        else{TTV[ind]->add();}
    }
    return ind;
}

int Character_t::Less(R_type *el)
{
    Character_t *a = dynamic_cast<Character_t *>(el->ToChar());
    int ind = TTV.put(Logical);
    int mod1 = v.size(), mod2 =  a->v.size();
    for (int i = 0; i < max(v.size(), a->v.size()) - 1; i++)
    {
        if (v[i % mod1 + 1] != NULL && a->v[i % mod2 + 1] != NULL)
        {
            TTV[ind]->add((*v[i % mod1 + 1]).compare(*(a->v[i % mod2 + 1])) < 0);
        }
        else{TTV[ind]->add();}
    }
    return ind;
}

int Character_t::Leq(R_type *el)
{
    Character_t *a = dynamic_cast<Character_t *>(el->ToChar());
    int ind = TTV.put(Logical);
    int mod1 = v.size(), mod2 =  a->v.size();
    for (int i = 0; i < max(v.size(), a->v.size()) - 1; i++)
    {
        if (v[i % mod1 + 1] != NULL && a->v[i % mod2 + 1] != NULL)
        {
            TTV[ind]->add((*v[i% mod1 + 1]).compare(*(a->v[i % mod2 + 1])) <= 0);
        }
        else{TTV[ind]->add();}
    }
    return ind;
}

int Character_t::Beq(R_type *el)
{
    Character_t *a = dynamic_cast<Character_t *>(el->ToChar());
    int ind = TTV.put(Logical);
    int mod1 = v.size(), mod2 =  a->v.size();
    for (int i = 0; i < max(v.size(), a->v.size()) - 1; i++)
    {
        if (v[i % mod1 + 1] != NULL && a->v[i % mod2 + 1] != NULL)
        {
            TTV[ind]->add((*v[i % mod1 + 1]).compare(*(a->v[i % mod2 + 1])) >= 0);
        }
        else{TTV[ind]->add();}
    }
    return ind;
}

int Character_t::at(const std::set<unsigned int> &tuple)
{
    int ind = TTV.put(Character, true);
    for (std::set<unsigned int>::iterator i = tuple.begin(); i != tuple.end(); i++)
    {
        if (*i < 0 || *i >= v.size()) throw "Out of range";
        TTV[ind]->addaddr(v[*i]);
    }
    return ind;
}

int Character_t::in(R_type * el)
{
    if (R_type::isfake())
    {
        if (el->get_type() != Character) throw "Cannot assigment numeric not numeric";
        Character_t * a = dynamic_cast<Character_t *> (el);
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
        if (el->get_type() == Character)
        {
            Character_t *a =dynamic_cast<Character_t *>(el);
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
    return 1;
}
