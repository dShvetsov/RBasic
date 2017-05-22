#include "variable_table.h"

#include <sstream>

#include "R_type.h"
#include "LA.h"

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
