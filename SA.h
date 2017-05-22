#ifndef SA__cpp
#define SA_cpp



#include "LA.hpp"
#include "Poliz.hpp"

class Parser
{
    Lex curr_lex;
    std::stack<int> repeart_points;
    std::vector<Lex> lexems;
    int position;
    int lexems_size;
    type_of_lex c_type;
    Scanner scan;
    void gvl(bool p = false);
    int in_count();

    void vl_clear()
    { lexems.clear(); lexems_size =  position = 0; }

    Lex gl(bool p = false);
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

    Parser(const char *program = NULL)
        :scan(program)
    {lexems_size = position = 0;}

    void analyze();
};

#endif
