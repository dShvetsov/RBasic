#include "LA.h"

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <ctype.h>
#include <string>
#include <vector>
#include <iterator>

#include "variable_table.cpp"
#include "R_type.cpp"

std::ostream& operator << ( std::ostream &s, Lex l )
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


int Scanner::look(const std::string &buf,const std::string *list)
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

void Scanner::gc(bool p = false)
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
void Scanner::end_exp(){
    expnum--;
    if (expnum < 0) throw "strange error";
}

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
