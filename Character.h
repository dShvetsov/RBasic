#ifndef Character__h
#define Character__h

#include "R_type.h"

class Character_t:public R_type{
    std::vector<std::string *> v;
    void clear()
    {
        if (!isfake()){
            for (unsigned int i = 0; i < v.size(); i++)
            {
                if (v[i] != NULL)
                    delete v[i];
            }
        }
        v.clear();
        v.push_back(NULL);
        R_type::size = 0;
    }
public:
    Character_t(std::string &s):R_type(Character){
        v.push_back(NULL);
        std::string *ps = new std::string(s);
        v.push_back(ps);
        R_type::size = 1;
    }
    Character_t():R_type(Character){v.push_back(NULL); R_type::size = 0;}
    void add(){
        v.push_back(NULL);
        R_type::size++;
    }
    void add(std::string &s)
    {
        std::string *ps  = new std::string(s);
        v.push_back(ps);
        R_type::size++;
    }
    void addaddr(std::string *s)
    {
        v.push_back(s);
        R_type::size++;
    }
    void write()
    {
        for (unsigned int i = 1; i < v.size(); i++)
        {
            if (v[i] != NULL)
                std::cout << *v[i] << ' ';
            else
                std::cout << "NULL ";
        }
    }
    int Beq(R_type *);
    int Eq(R_type *);
    int Neq(R_type *);
    int Bigger(R_type *);
    int Less(R_type *);
    int Leq(R_type *);
    int at(const std::set<unsigned int> &);
    int in(R_type *);
    std::string* kernel_at_char(int i){return v[i];}
    R_type * ToNum(){throw "Cannot assign character to numeric";}
    R_type * ToLog(){throw "Cannot assign character to logical";}
    R_type * ToChar(){return this;}
};

#endif
