#ifndef variable_table__cpp
#define variable_table__cpp
/*
#include "R_type.cpp"
#include "LA.cpp"
#include <sstream>
*/

class tabl_ident  // Таблица идентификаторов
{
    std::vector<R_type *> variable;
    std::vector<std::string> name;
    int top;
public:
    tabl_ident ()
    {
        top = 0;
    }
    void change(int ind, R_type *a)
    {
        variable[ind] = a;
    }
    R_type *operator[] ( int k )
    {
        return variable[k];
    }
    int put ( const std::string &buf );
    ~tabl_ident()
    {
        for (std::vector<R_type *>::iterator i = variable.begin(); i != variable.end(); i++){
            if (*i != NULL){
                delete *i;
            }
        }
    }
};

int tabl_ident::put ( const std::string &buf )
{
    for (int j = 0; j < top; ++j )
        if ( !buf.compare(name[j]) )
            return j;
    name.push_back(buf);
    R_type *h = new R_type;
    variable.push_back(h); // загоняем в стэк нулл => смотрим на декларацию как если не нулл
    return top++;
}

tabl_ident TID; // Создаем таблицу идентификаторв


class tabl_temp
{
    std::vector<R_type *> tabl;
    int top;
public:
    tabl_temp():top(0){};
    int put(kind_of_type l, std::string& value);
    int put(kind_of_type t, bool fake = false);
    void change(int ind, R_type *a)
    {
        tabl[ind] = a;
    }
    R_type * operator [](int i) {return tabl[i];}
    void clear()
    {
        for (std::vector<R_type *>::iterator i = tabl.begin(); i != tabl.end(); i++){
            if (*i != NULL){
                delete *i;
            }
        }
        tabl.clear();
        top = 0;
    }
    ~tabl_temp()
    {
        for (std::vector<R_type *>::iterator i = tabl.begin(); i != tabl.end(); i++){
            if (*i != NULL){
                delete *i;
            }
        }
    }
};

int tabl_temp::put(kind_of_type t, std::string& value)
{
    R_type *new_var;
    std::istringstream iss(value);
    switch(t)
    {
    case Nulltype:
        new_var = new R_type;
    case Numeric:
        double x;
        iss >> x;
        new_var = new Numeric_t(x);
        break;
    case Character:
        new_var = new Character_t(value);
        break;
    case Logical:
        new_var = new Logical_t(!value.compare("TRUE"));
        break;
    }
    tabl.push_back(new_var);
    return top++;
}

int tabl_temp::put(kind_of_type t, bool fake)
{
    R_type *new_var;
    switch(t)
    {
    case Nulltype: new_var = new R_type; break;
    case Numeric: new_var = new Numeric_t; break;
    case Logical: new_var = new Logical_t; break;
    case Character: new_var = new Character_t; break;
    }
    tabl.push_back(new_var);
    if (fake) new_var->fake_on();
    return top++;
}

tabl_temp TTV; // создаем таблицу временных переменных

#endif
