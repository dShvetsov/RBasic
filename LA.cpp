#ifndef LA__cpp
#define LA__cpp
/*
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <ctype.h>
#include <string>
#include <vector>
#include <iterator>
#include "variable_table.cpp"
#include "R_type.cpp"
*/
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
    addr(int offsetn, vtable tn):t(tn), offset(offsetn){}
    vtable get_table(){return t;};
    int get_offset(){return offset;}
    addr & operator = (const addr &v)
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
    Lex ( type_of_lex t, int v, vtable tab ):v_lex(v, tab)
    {
        t_lex = t;
    }
    Lex( type_of_lex t = LEX_NULL):v_lex(0, OTHER)
    {
        t_lex = t;
    }
    Lex ( type_of_lex t, int v): v_lex(v, OTHER)
    {
        t_lex = t;
    }
    Lex& operator =(const Lex &q)
    {
        t_lex = q.t_lex;
        v_lex = q.v_lex;
        return *this;
    }
    type_of_lex get_type () { return t_lex; }
    addr get_value () { return v_lex; }

      friend std::ostream& operator << ( std::ostream &s, Lex l )
    {
        switch(l.t_lex)
        {
        case LEX_NULL: s << "NULL "; break;
        case LEX_IN: s << "<- " ; break;
        case  LEX_AND : s << "& " ; break;
        case  LEX_OR : s <<"| "; break;
        case  LEX_NOT : s <<"!"; break;
        case LEX_BIGGER : s <<" > "; break;
        case LEX_LES : s <<"< "; break;
        case LEX_BEQ : s <<"<= "; break;
        case LEX_LEQ : s <<">= "; break;
        case LEX_EQ : s <<"== "; break;
        case LEX_NEQ : s <<"!= "; break;
        case LEX_PLUS : s <<"+ "; break;
        case LEX_MINUS : s <<"- "; break;
        case LEX_MUL : s <<"* "; break;
        case LEX_DIV : s <<"/ "; break;
        case LEX_INTERVAL : s <<": "; break;
        case LEX_BROP : s <<"( "; break;
        case LEX_BRCL : s <<") "; break;
        case LEX_SQBROP : s <<"[ "; break;
        case LEX_SQBRCL : s <<"] "; break;
        case LEX_ID : s <<"ID "; break;
        case LEX_END : s <<"; "; break;
        case LEX_SEMIEND : s <<"slash n "; break;
        case LEX_FIGOP : s << "{ "; break;
        case LEX_FIGCL : s << "} "; break;
        case POLIZ_LABEL : s << l.v_lex.get_offset() << " "; break;
        case POLIZ_FGO : s << "!F "; break;
        case POLIZ_GO : s << "! "; break;
        case LEX_CONST : s << "C "; break;
        case LEX_UNMIN : s << "~ "; break;
        case LEX_UNPL : s << "@ "; break;
        case LEX_MODE : s << "mode "; break;
        default : s << " WOOOOW " ; break;
        }
    return s;
    }
};



class Scanner
{
    enum state { H, IDENT, NUMB, ALE, DELIM, QUOTES, SLEEP};
    static const std::string TW[];
    static type_of_lex words[];
    static const std::string TD[];
    static type_of_lex dlms[];
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

    int look ( const std::string &buf,const std::string *list )
    {
        int i = 1;
        while ( !(list[i].empty()) )
        {
            if ( !buf.compare(list[i]) )
                return i;
            ++i;
        }
        return 0;
    }
    void gc (bool p = false)
    {
        if (position == current_string.end())
        {
            if (!p)
                std::cout << "> ";
            else
                std::cout << "+ ";
            if (std::getline(std::cin, current_string));
            if (std::cin.eof()) exit(0);
            current_string += '\n';
            position = current_string.begin();
        }
        c = *(position++);
    }
public:
    Lex get_lex (bool p = false);
    void not_end_exp(){expnum++;}
    void end_exp(){
        expnum--;
        if (expnum < 0) throw "strange error";
        }
    Scanner ( const char * program = NULL )
    {
        CS = H;
        clear_string();
        buf.clear();
        expnum = 0;
        gc();
    }
};

const std::string Scanner::TW[] =
{
    "",
    "TRUE", "FALSE",
    "NULL", "repeart", "if", "break",
    "c", "length", "mode", "matrix"
    ,""
};
const std::string Scanner:: TD[] =
{
    "",
    "<-",
    "&", "|", "!",
    ">", "<", ">=", "<=", "==", "!=",
    "+", "-", "*", "/",
    ":",
    "(", ")", "[", "]",
    ";", "\n", "," , "=", "{", "}", ""
};

type_of_lex Scanner::words[] =
{
    LEX_NULL,
    LEX_CONST, LEX_CONST,
    LEX_CONST, LEX_REPEART, LEX_IF, LEX_BREAK,
    LEX_C, LEX_LEN, LEX_MODE, LEX_MATRIX,
    LEX_NULL
};

type_of_lex Scanner::dlms[] =
{
    LEX_NULL,
    LEX_IN,
    LEX_AND, LEX_OR, LEX_NOT,
    LEX_BIGGER, LEX_LES, LEX_BEQ, LEX_LEQ, LEX_EQ, LEX_NEQ,
    LEX_PLUS, LEX_MINUS, LEX_MUL, LEX_DIV,
    LEX_INTERVAL,
    LEX_BROP, LEX_BRCL, LEX_SQBROP, LEX_SQBRCL, LEX_END, LEX_SEMIEND,
    LEX_COMMA, LEX_IS, LEX_FIGOP, LEX_FIGCL,
    LEX_NULL
};

Lex Scanner::get_lex (bool p)
{
    int j;
    bool firstpoint = true;
    if ( CS == SLEEP ) gc(p);
    CS = H;
    do
        {
        switch ( CS )
        {
            case H:
                if ( c == '\n' && exp())
                {
                    CS = SLEEP;
                    return Lex(LEX_SEMIEND);
                }
                else if ( isspace(c) )
                    gc (p);
                else if ( isalpha(c) || c == '.' )
                {
                    buf.clear ();
                    add ();
                    gc (p);
                    CS = IDENT;
                }
                else if ( isdigit(c) )
                {
                    buf.clear();
                    add();
                    gc (p);
                    CS = NUMB;
                }
                else if ( c== '#' )
                {
                    clear_string();
                    CS = SLEEP;
                    return Lex(LEX_SEMIEND);
                }
                else if ( c== '=' || c== '<' || c== '>' || c=='!')
                {
                    buf.clear ();
                    add ();
                    gc (p);
                    CS = ALE;
                }
                else if ( c == ';')
                {
                    gc(p);
                    return Lex(LEX_END);
                }
                else if ( c == '\"')
                {
                    buf.clear();
                    gc(p);
                    CS = QUOTES;
                }
                else if (c == ',')
                {
                    gc(p);
                    return Lex(LEX_COMMA);
                }
                else
                {
                    CS = DELIM;
                }
                break;
            case IDENT:
                if ( isalpha(c) || isdigit(c) || c == '.' )
                {
                    add ();
                    gc (p);
                }
                else if ( (j = look (buf, TW)) != 0 )
                    {
                        if (words[j] == LEX_CONST)
                        {
                            if (!buf.compare("NULL"))
                                 j = TTV.put(Nulltype);
                            else
                                j = TTV.put(Logical, buf);
                            return Lex(LEX_CONST, j, TEMP_TABLE);
                        }
                        else
                            return Lex (words[j]);
                    }
                else
                {
                    j = TID.put(buf);
                    return Lex (LEX_ID, j, MAIN_TABLE);
                }
                break;
            case NUMB:
                if ( isdigit(c) )
                {
                    add();
                    gc(p);
                }else if (c == '.' && firstpoint)
                {
                    add();
                    gc(p);
                    firstpoint = false;
                }
                else
                {
                    j = TTV.put(Numeric, buf);
                    return Lex ( LEX_CONST, j, TEMP_TABLE );
                }
                break;
            case ALE:
                if ( c == '=' || c == '-' )
                {
                    int tmp = look(buf, TD);
                    add ();
                    gc (p);
                    if ((j = look ( buf, TD )) != 0)
                    {
                        return Lex( dlms[j]);
                    }
                    else
                        return Lex ( dlms[tmp]);
                }
                else
                {
                    j = look (buf, TD);
                    return Lex ( dlms[j]);
                }
                break;
            case DELIM:
                buf.clear();
                add ();
                if ( (j = look(buf, TD)) != 0 )
                {
                    gc (p);
                    return Lex ( dlms[j]);
                }
                else
                    throw c;
                break;
             case QUOTES:
                if (c == '\"')
                {
                    gc(p);
                    j = TTV.put(Character, buf);
                    return Lex(LEX_CONST, j, TEMP_TABLE);
                }
                else if (c == '\\')
                {
                    gc(p);
                    if (c == 'n') add('\n');
                    else if (c == 't') add('\t');
                    else {add('\\'); add();}
                    gc(p);
                }
                else
                {
                    add();
                    gc(p);
                }
                break;
            case SLEEP: throw "it's impossible";
        } // end switch
    }
    while ( true );
}


#endif
