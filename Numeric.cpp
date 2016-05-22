
int Numeric_t::Plus(R_type *a)
{
    Numeric_t *two = dynamic_cast<Numeric_t *> (a->ToNum());
    int ind = TTV.put(Numeric);
    int mod1 =v.size() - 1, mod2 =  two->v.size() - 1;
    for (int i = 0; i < max(v.size(), two->v.size()) - 1 ; i++)
    {
        if (v[i % mod1 + 1] != NULL && two->v[i % mod2 + 1] != NULL)
            TTV[ind]->add( *v[i % mod1 + 1] + *(two->v[i % mod2 + 1]));
        else
            TTV[ind]->add();
    }
    return ind;
}


int Numeric_t::Minus(R_type *a)
{
    Numeric_t *two = dynamic_cast<Numeric_t *>(a->ToNum());
    int ind = TTV.put(Numeric);
    int mod1 =v.size() - 1, mod2 =  two->v.size() - 1;
    for (int i = 0; i < max(v.size(), two->v.size()) - 1; i++)
    {
        if (v[i % mod1 + 1] != NULL && two -> v[i % mod2 + 1] != NULL)
            TTV[ind]->add( *v[i % mod1 + 1] - *(two -> v[i % mod2 + 1]));
        else
            TTV[ind]->add();
    }
    return ind;
}

int Numeric_t::Mul(R_type *a)
{
    Numeric_t *two = dynamic_cast<Numeric_t *> (a->ToNum());
    int ind = TTV.put(Numeric);
    int mod1 =v.size() - 1, mod2 =  two->v.size() - 1;
    for (int i = 0; i < max(v.size(), two->v.size()) - 1; i++)
    {
        if (v[i % mod1 + 1] != NULL && two -> v[i % mod2 + 1] != NULL)
            TTV[ind]->add( *v[i % mod1 + 1] * *(two->v[i % mod2 + 1]));
        else
            TTV[ind]->add();
    }
    return ind;
}


int Numeric_t::Div(R_type *a)
{
    Numeric_t *two = dynamic_cast<Numeric_t *> (a->ToNum());
    int ind = TTV.put(Numeric);
    int mod1 =v.size() - 1, mod2 =  two->v.size() - 1;
    for (int i = 0; i < max(v.size(), two->v.size()) -1; i++)
    {
        if (v[i % mod1 + 1] != NULL && two->v[i % mod2 + 1] != NULL)
            TTV[ind]->add( *v[i % mod1 + 1] / *(two->v[i % mod2 + 1]));
        else
            TTV[ind]->add();
    }
    return ind;
}

R_type* Numeric_t::ToChar()
{
    int ind = TTV.put(Character);
    std::ostringstream oss;
    std::string s;
    for (unsigned int i = 1; i < v.size(); i++)
    {
        if ( v[i] != NULL)
        {
            oss <<  (*v[i]);
            s = oss.str();
            TTV[ind]->add(s);
        }
        else
        {
            TTV[ind]->add();
        }
    }
    return TTV[ind];
}


R_type * Numeric_t::ToLog()
{
    int ind = TTV.put(Logical);
    for (unsigned int i = 1; i < v.size(); i++)
    {
        if ( v[i] != NULL)
        {
            TTV[ind]->add( (*v[i]) > EPS );
        }
        else
        {
            TTV[ind]->add();
        }
    }
    return TTV[ind];
}


int Numeric_t::Eq(R_type *a)
{
    Numeric_t * two = dynamic_cast<Numeric_t *> (a->ToNum());
    int ind = TTV.put(Logical);
    int mod1 =v.size() - 1, mod2 =  two->v.size() - 1;
    for (int i = 0; i < max(v.size(), two->v.size()) -1; i++)
    {
        if (v[i % mod2 + 1] != NULL && two -> v[i % mod1 + 1] != NULL)
        {
            TTV[ind]->add( abs(*v[i % mod1 + 1] - *(two->v[i % mod2 + 1])) < EPS);
        }
        else{TTV[ind]->add();}
    }
    return ind;
}



int Numeric_t::Neq(R_type *a)
{
    Numeric_t *two = dynamic_cast<Numeric_t *> (a->ToNum());
    int ind = TTV.put(Logical);
    int mod1 =v.size() - 1, mod2 =  two->v.size() - 1;
    for (int i = 0 ; i < max(v.size(), two->v.size()) -1; i++)
    {
        if (v[i % mod1 + 1] != NULL && two->v[i % mod2 + 1] != NULL)
        {
            TTV[ind]->add( abs(*v[i % mod1 + 1] - *(two->v[i % mod2 + 1])) > EPS);
        }
        else
        {
            TTV[ind]->add();
        }
    }
    return ind;
}


int Numeric_t::Bigger(R_type *a)
{
    Numeric_t *two = dynamic_cast<Numeric_t *> (a->ToNum());
    int ind = TTV.put(Logical);
    int mod1 =v.size() - 1, mod2 =  two->v.size() - 1;
    for (int i = 0 ; i < max(v.size(), two->v.size()) -1; i++)
    {
        if (v[i % mod1 + 1] != NULL && two->v[i % mod2 + 1] != NULL)
        {
            TTV[ind]->add( *v[i % mod1 + 1] > *(two -> v[i % mod2 + 1]));
        }
        else
        {
            TTV[ind]->add();
        }
    }
    return ind;
}

int Numeric_t::Less(R_type *a)
{
    Numeric_t *two = dynamic_cast<Numeric_t *> (a->ToNum());
    int ind = TTV.put(Logical);
    int mod1 =v.size() - 1, mod2 =  two->v.size() - 1;
    for (int i = 0; i < max(v.size(), two->v.size()) - 1; i++)
    {
        if (v[i % mod1 + 1] != NULL && two->v[i % mod2 + 1] != NULL)
        {
            TTV[ind]->add( *v[i % mod1 + 1] < *(two -> v[i % mod2 + 1]));
        }
        else
        {
            TTV[ind]->add();
        }
    }
    return ind;
}


int Numeric_t::Beq(R_type *a)
{
    Numeric_t *two = dynamic_cast<Numeric_t *> (a->ToNum());
    int ind = TTV.put(Logical);
    int mod1 =v.size() - 1, mod2 =  two->v.size() - 1;
    for (int i = 0; i < max(v.size(), two->v.size()) - 1; i++)
    {
        if (v[i % mod1 + 1] != NULL && two->v[i % mod2 + 1] != NULL)
        {
            TTV[ind]->add( *v[i % mod1 + 1] > *(two->v[i % mod2 + 1]) || abs(*v[i % mod1 + 1] - *(two->v[i % mod2 + 1])) < EPS);
        }
        else
        {
            TTV[ind]->add();
        }
    }
    return ind;
}


int Numeric_t::Leq(R_type *a)
{
    Numeric_t *two = dynamic_cast<Numeric_t *> (a->ToNum());
    int ind = TTV.put(Logical);
    int mod1 =v.size() - 1, mod2 =  two->v.size() - 1;
    for (int i =  0; i < max(v.size(), two->v.size()) -1; i++)
    {
        if (v[i % mod1 + 1] != NULL && two->v[i % mod2 + 1] != NULL)
        {
            TTV[ind]->add( *v[i % mod1 + 1] < *(two->v[i % mod2 + 1]) || abs(*v[i % mod1 + 1] - *(two->v[i % mod2 + 1])) < EPS);
        }
        else
        {
            TTV[ind]->add();
        }
    }
    return ind;
}

int Numeric_t::Unmin()
{
    int ind = TTV.put(Numeric);
    for (unsigned int i = 1; i < v.size(); i++)
    {
        if (v[i] != NULL)
        {
            TTV[ind]->add(*v[i]);
        }
        else
        {
            TTV[ind]->add();
        }
    }
    return ind;
}

int Numeric_t::interval(R_type *two)
{
    Numeric_t *a = dynamic_cast<Numeric_t *> (two->ToNum());
    double q = *kernel_at_num(1), b = *(a->kernel_at_num(1));
    int from = (int)q, to = (int)b + 1;
    int ind = TTV.put(Numeric);
    if (from < to)
    {
        for (int i = from; i != to; i ++)
        {
            TTV[ind]->add(double(i));
        }
    }
    else
    {
        for (int i = from; i != to; i --)
        {
            TTV[ind]->add(double(i));
        }
    }
    return ind;
}
int Numeric_t::at(const std::set<unsigned int> &tuple)
{
    int ind = TTV.put(Numeric, true);
    for (std::set<unsigned int>::iterator i = tuple.begin(); i != tuple.end(); i++)
    {
        if (*i <= 0 || *i >= v.size()) throw "Out of range";
        TTV[ind]->addaddr(v[*i]);
    }
    return ind;
}


std::set<unsigned int> Numeric_t::get_tuple()
{
    std::set<unsigned int> s;
    for (unsigned int i = 1; i < v.size(); i++)
    {
        if (v[i] != NULL && *v[i] > 0)
            s.insert((unsigned int)((*v[i])));
    }
    return s;
}

int Numeric_t::in(R_type *an)
{
    if (R_type::isfake())
    {
        if (an->get_type() != Numeric) throw "Cannot assigment numeric not numeric";
        Numeric_t *a = dynamic_cast<Numeric_t *>(an);
        int mod = a->v.size() - 1;
        for (unsigned int i = 1; i < v.size(); i++)
        {
            if ( a->v[(i % mod) + 1] != NULL)
            {
                (*v[i]) = *(a->v[(i % mod) + 1]);
            }
            else
                (v[i]) = NULL;
        }
        return 1;
    }
    else
    {
        clear();
        if (an->get_type() == Numeric)
        {
            Numeric_t *a = dynamic_cast<Numeric_t *> (an);
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
