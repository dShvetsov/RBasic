#ifndef SA__cpp
#define SA__cpp
/*
#include <iostream>
#include "LA.cpp"
#include <stack>
#include "Poliz.cpp"
#include <vector>

*/
class Parser
{
    Lex curr_lex;
    std::stack<int> repeart_points;
    std::vector<Lex> lexems;
    int position;
    int lexems_size;
    type_of_lex c_type;
    Scanner scan;
    void gvl(bool p = false)
    {
        Lex tmp;
        tmp = scan.get_lex(p);
        lexems.push_back(tmp);
        lexems_size++;
        while (tmp.get_type() != LEX_SEMIEND && tmp.get_type() != LEX_END)
        {
            tmp = scan.get_lex(p);
            lexems.push_back(tmp);
            lexems_size++;
        }
    }

    int in_count()
    {
        int tmp = position - 1; // Тут может быть без -1
        int sq = 0, ans = 0;
        type_of_lex l;
        l = lexems[tmp].get_type();
        while ( l != LEX_END && l != LEX_SEMIEND && l != LEX_FIGOP  && l != LEX_SQBRCL && l != LEX_BRCL)
        {
            if (l == LEX_IN) ans++;
            if (l == LEX_SQBROP)
            {
                sq++;
                while (sq != 0)
                {
                    if (tmp == lexems_size)
                        gvl(true);
                    tmp++;
                    l = lexems[tmp].get_type();
                    if (l == LEX_SQBROP) sq++;
                    if (l == LEX_SQBRCL) sq--;
                }
            }else
            if (l == LEX_BROP)
            {
                sq++;
                while( sq != 0)
                {
                    if ( tmp == lexems_size )
                        gvl(true);
                    tmp++;
                    l = lexems[tmp].get_type();
                    if (l == LEX_BROP) sq++;
                    if (l == LEX_BRCL) sq--;
                }
            }else
            if (l == LEX_FIGOP)
            {
                sq++;
                while ( sq!= 0 )
                {
                    if ( tmp == lexems_size )
                        gvl(true);
                    tmp++;
                    l = lexems[tmp].get_type();
                    if ( l == LEX_FIGOP ) sq++;
                    if (l == LEX_FIGCL) sq--;
                }

            }
            l = lexems[++tmp].get_type();
        }
        return ans;
    }

    void vl_clear() { lexems.clear(); lexems_size =  position = 0; }
    Lex gl(bool p =false){
        if (position == lexems_size){
            gvl(p);
        }
        curr_lex = lexems[position++];
        c_type = curr_lex.get_type();
        return curr_lex;
    }
    void Expr();
    void Start();
    void Exph();
    void Expp();
    void Exp1();
    void Exp2();
    void Exp3();
    void Exp4();
    void Exp5();
    void Exp6();
    void Exp7();
    void ArgList();
    void ArgListElem();
    void Variable();
    void Program();
    void S1();
    void get_valid_lex();
public:
    Poliz prog;
    Parser(const char *program = NULL):scan(program){lexems_size = position = 0;}
    void analyze();
};

void Parser::get_valid_lex()
{
    gl(true);
    while (c_type == LEX_SEMIEND)
    {
        gl(true);
    }
}

void Parser::analyze()
{
    vl_clear();
    gl();
    try{
        Program();
    }
    catch(const char *a) {std::cout << a << std::endl; return;}
    //std::cout << "OK" << std::endl;
}

void Parser::Program()
{
    Start();
    prog.put_lex(Lex(LEX_END));
}
/*
    while ( c_type == LEX_END || c_type == LEX_SEMIEND )
    {
        gl();
        Expr();
    }
} */

void Parser::Start()
{
    if (c_type == LEX_REPEART)
    {
        get_valid_lex();
        int pl0, pl1, pl2;  // pl0 ! pl1 ! pl2 ___{break}____ go! end
        pl0 = prog.get_free();// from pl0 to pl2
        prog.blank(); //from break to pl1
        prog.put_lex(Lex(POLIZ_GO)); // from pl1 to end
        pl1 = prog.get_free();   // from go to pl2
        repeart_points.push(pl1);
        prog.blank();
        prog.put_lex(Lex(POLIZ_GO));
        pl2 = prog.get_free();
        prog.put_lex(Lex(POLIZ_LABEL, pl2), pl0);
        Expr();
        prog.put_lex(Lex(POLIZ_LABEL, pl2));
        prog.put_lex(Lex(POLIZ_GO));
        prog.put_lex(Lex(POLIZ_LABEL, prog.get_free()), pl1);
        repeart_points.pop();
        //Expr();
    }else if (c_type == LEX_IF)
    {
        int p1;
        get_valid_lex();
        if (c_type != LEX_BROP) throw "Expected ( before if";
        get_valid_lex();
        Expr();
        if (c_type != LEX_BRCL) throw "Expected ) after expression";
        get_valid_lex();
        p1 = prog.get_free();
        prog.blank();
        prog.put_lex(Lex(POLIZ_FGO));
        Expr();
        prog.put_lex(Lex(POLIZ_LABEL, prog.get_free()), p1);
    }else Expr();
}

void Parser::S1(){
    while (c_type == LEX_END || c_type == LEX_SEMIEND)
    {
        prog.put_lex(Lex(LEX_END));
        get_valid_lex(); // Тут может быть и gl()
        Expr();
    }
}

void Parser::Expr()
{
    if (c_type == LEX_BREAK)
    {
        if (repeart_points.empty()) throw "Break without repeart";
        prog.put_lex(Lex(POLIZ_LABEL, repeart_points.top()));
        prog.put_lex(Lex(POLIZ_GO));
        gl();
        return;
    }
    int n = in_count();
    for (int i = 0; i < n; i++)
    {
        Variable();
        if (c_type != LEX_IN) throw "Expected <-";
        get_valid_lex();
    }
    Exp1();
    for (int i = 0; i < n; i++)
    {
        prog.put_lex(Lex(LEX_IN));
    }
}


void Parser::Exp1()
{
    Expp();
    while (c_type == LEX_OR)
    {
        get_valid_lex();
        Expp();
        prog.put_lex(Lex(LEX_OR));
    }
}

void Parser::Expp()
{
    Exp2();
    while (c_type == LEX_AND)
    {
        get_valid_lex();
        Exp2();
        prog.put_lex(Lex(LEX_AND));
    }
}

void Parser::Exp2()
{
    if (c_type == LEX_NOT)
    {
        get_valid_lex();
        Exp3();
        prog.put_lex(Lex(LEX_NOT));
    }
    Exp3();
}

void Parser::Exp3()
{
    Exp4();
    if ( c_type == LEX_LES || c_type == LEX_BIGGER || c_type == LEX_LEQ || c_type == LEX_BEQ ||
        c_type == LEX_EQ || c_type == LEX_NEQ)
    {
        Lex tmp = curr_lex;
        get_valid_lex();
        Exp4();
        prog.put_lex(tmp);
    }
}

void Parser::Exp4()
{
    Exp5();
    while (c_type == LEX_PLUS || c_type == LEX_MINUS)
    {
        Lex tmp = curr_lex;
        get_valid_lex();
        Exp5();
        prog.put_lex(tmp);
    }
}

void Parser::Exp5()
{
    Exp6();
    while (c_type == LEX_MUL || c_type == LEX_DIV)
    {
        Lex tmp = curr_lex;
        get_valid_lex();
        Exp6();
        prog.put_lex(tmp);
    }
}
void Parser::Exp6()
{
    Exph();
    if (c_type == LEX_INTERVAL)
    {
        get_valid_lex();
        Exph();
        prog.put_lex(Lex(LEX_INTERVAL));
    }
}

void Parser::Exph()
{
    if (c_type == LEX_MINUS)
    {
        get_valid_lex();
        Exp7();
        prog.put_lex(Lex(LEX_UNMIN));
    }else
    if (c_type == LEX_PLUS)
    {
        get_valid_lex();
        Exp7();
        prog.put_lex(Lex(LEX_UNPL));
    }else Exp7();
}

void Parser::Exp7()
{
    if (c_type == LEX_BROP)
    {
        get_valid_lex();
        Expr();
        if (c_type != LEX_BRCL) throw "Syntax Error: breakets not found";
        gl();
    }
    else if (c_type == LEX_C || c_type == LEX_LEN || c_type == LEX_MATRIX || c_type == LEX_MODE)
    {
        Lex tmp = curr_lex;
        get_valid_lex();
        if (c_type != LEX_BROP) throw "Syntax Error: Function without breakets";
        get_valid_lex();
        ArgList();
        prog.put_lex(tmp);
    }
    else if (c_type == LEX_ID)
    {
        Variable();
    }else if (c_type == LEX_CONST)
    {
        prog.put_lex(curr_lex);
        gl();
        return;
    } else if (c_type == LEX_FIGOP)
    {
        //prog.put_lex(curr_lex);
        get_valid_lex();
        Start();
        while (c_type == LEX_END || c_type == LEX_SEMIEND)
        {
            prog.put_lex(Lex(LEX_END));
            get_valid_lex();
            Start();
        }
        if (c_type != LEX_FIGCL) throw "Expected figure close breakets";
        //prog.put_lex(curr_lex);
        gl();
    }
}

void Parser:: Variable()
{
    if (c_type != LEX_ID) throw "Error expectef identificator";
    prog.put_lex(curr_lex);
    gl();
    if (c_type == LEX_SQBROP)
    {
        get_valid_lex();
        Expr();
        if (c_type != LEX_SQBRCL) throw "Syntax Error";
        prog.put_lex(curr_lex);
        gl();
    }

}

void Parser::ArgList()
{
    prog.put_lex(Lex(LEX_BROP));
    if (c_type == LEX_BRCL) {gl(); return;}
    ArgListElem();
    while (c_type == LEX_COMMA)
    {
        get_valid_lex();
        ArgListElem();
    }
    if (c_type != LEX_BRCL) throw "Expected close breackets";
    gl();
}

void Parser::ArgListElem()
{
    Expr();
/*    if (c_type == LEX_IS)
    {
        gl();
        Expr();
    } */
}

#endif
