#ifndef LA__cpp
#define LA__cpp

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <ctype.h>
#include <string>
#include <vector>
#include <iterator>

#include "variable_table.h"
#include "R_type.h"

enum vtable{MAIN_TABLE, TEMP_TABLE, OTHER};

enum type_of_lex
{
    LEX_NULL,
    LEX_IN,
    LEX_AND, LEX_OR, LEX_NOT, LEX_BIGGER, LEX_LES, LEX_BEQ, LEX_LEQ, LEX_EQ, LEX_NEQ,
    LEX_PLUS, LEX_MINUS, LEX_MUL, LEX_DIV,
    LEX_INTERVAL,
    LEX_BROP, LEX_BRCL, LEX_SQBROP, LEX_SQBRCL,
    LEX_ID, LEX_END, LEX_SEMIEND,
    LEX_CONST,
    LEX_COMMA,
    LEX_LEN, LEX_C, LEX_MODE, LEX_MATRIX,
    LEX_UNMIN, LEX_UNPL,
    LEX_FIGOP, LEX_FIGCL,
    LEX_IS, LEX_REPEART, LEX_IF, LEX_BREAK,
    POLIZ_LABEL, POLIZ_GO, POLIZ_FGO
};


class addr
{
    vtable t;
    int offset;
public:
    addr(int offsetn, vtable tn)
        :t(tn), offset(offsetn)
    { }

    addr(const addr& o)
        : t(o.t), offset(o.offset)
    { }

    vtable get_table() {return t;};

    int get_offset() {return offset;}

    addr& operator= (const addr &v)
    {
        t = v.t;
        offset = v.offset;
        return *this;
    }
};

class Lex
{
    type_of_lex t_lex;
    addr v_lex;
public:
    Lex ( type_of_lex t, int v, vtable tab )
        : v_lex(v, tab)
    {
        t_lex = t;
    }

    Lex( type_of_lex t = LEX_NULL)
        : v_lex(0, OTHER)
    {
        t_lex = t;
    }

    Lex ( type_of_lex t, int v)
        : v_lex(v, OTHER)
    {
        t_lex = t;
    }

    Lex (const Lex &o)
        : v_lex(o.v_lex)
    {
        t_lex = o.t_lex;
    }


    Lex& operator=(const Lex &q)
    {
        v_lex = q.v_lex;
        t_lex = q.t_lex;
        return *this;
    }

    type_of_lex get_type () { return t_lex; }
    addr get_value () { return v_lex; }

    friend std::ostream& operator << ( std::ostream &s, Lex l );
};



class Scanner
{
    enum state { H, IDENT, NUMB, ALE, DELIM, QUOTES, SLEEP};
    static const std::string TW[];
    static const type_of_lex words[];
    static const std::string TD[];
    static const type_of_lex dlms[];
    std::string current_string;
    std::string::iterator position;
    int expnum;
    state CS;
    //int fp;
    char c;
    std::string buf;

    bool exp(){return expnum == 0;}

    void clear_string()
    {
        current_string.clear();
        position = current_string.end();
    }

    void add ()
    {
        buf += c;
    }

    void add (char cc)
    {
        buf += cc;
    }

    int look ( const std::string &buf,const std::string *list );

    void gc (bool p = false);

public:
    Lex get_lex (bool p = false);

    void not_end_exp() {expnum++;}

    void end_exp();

    Scanner ( const char * program = NULL )
    {
        CS = H;
        clear_string();
        buf.clear();
        expnum = 0;
        gc();
    }
};

#endif
