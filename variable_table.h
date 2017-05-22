#ifndef variable_table__h
#define variable_table__h

#include <sstream>

#include "R_type.h"
#include "LA.h"

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

extern tabl_ident TID;


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

extern tabl_temp TTV;

#endif
