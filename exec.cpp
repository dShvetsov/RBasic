#ifndef exec__cpp
#define exec__cpp
/*
#include <stack>
#include <iostream>
*/

class Executer
{
    Lex pc_el;
public:
    void execute(Poliz &prog);
};

void Executer::execute (Poliz &prog)
{
    std::stack<addr> args;
    std::list<R_type *> cargs;
    addr v1(0, OTHER), v2(0, OTHER);
    addr last(0, OTHER);
    Lex LastLex;
    R_type *vR1, *vR2;
    int index = 0, size = prog.get_free();
    bool *bp;
    while (index < size)
    {
        pc_el = prog [ index ];
        switch( pc_el.get_type())
        {
            case LEX_CONST:
            case LEX_ID:
            case POLIZ_LABEL:
                args.push(pc_el.get_value());
                break;
            case LEX_NOT:
                v1 = args.top();
                args.pop();
                vR1 = v1.get_table() == MAIN_TABLE ? TID[v1.get_offset()] : TTV[v1.get_offset()];
                args.push(addr(vR1->Not(), TEMP_TABLE));
                break;
            case LEX_OR:
                v2 = args.top();
                args.pop();
                v1 = args.top();
                args.pop();
                vR1 = v1.get_table() == MAIN_TABLE ? TID[v1.get_offset()] : TTV[v1.get_offset()];
                vR2 = v2.get_table() == MAIN_TABLE ? TID[v2.get_offset()] : TTV[v2.get_offset()];
                args.push(addr(vR1->Or(vR2), TEMP_TABLE));
                break;
            case LEX_AND:
                v2 = args.top();
                args.pop();
                v1 = args.top();
                args.pop();
                vR1 = v1.get_table() == MAIN_TABLE ? TID[v1.get_offset()] : TTV[v1.get_offset()];
                vR2 = v2.get_table() == MAIN_TABLE ? TID[v2.get_offset()] : TTV[v2.get_offset()];
                args.push(addr(vR1->And(vR2), TEMP_TABLE));
                break;
            case LEX_PLUS:
                v2 = args.top();
                args.pop();
                v1 = args.top();
                args.pop();
                vR1 = v1.get_table() == MAIN_TABLE ? TID[v1.get_offset()] : TTV[v1.get_offset()];
                vR2 = v2.get_table() == MAIN_TABLE ? TID[v2.get_offset()] : TTV[v2.get_offset()];
                args.push(addr(vR1->Plus(vR2), TEMP_TABLE));
                break;
            case LEX_MINUS:
                v2 = args.top();
                args.pop();
                v1 = args.top();
                args.pop();
                vR1 = v1.get_table() == MAIN_TABLE ? TID[v1.get_offset()] : TTV[v1.get_offset()];
                vR2 = v2.get_table() == MAIN_TABLE ? TID[v2.get_offset()] : TTV[v2.get_offset()];
                args.push(addr(vR1->Minus(vR2), TEMP_TABLE));
                break;
            case LEX_MUL:
                v2 = args.top();
                args.pop();
                v1 = args.top();
                args.pop();
                vR1 = v1.get_table() == MAIN_TABLE ? TID[v1.get_offset()] : TTV[v1.get_offset()];
                vR2 = v2.get_table() == MAIN_TABLE ? TID[v2.get_offset()] : TTV[v2.get_offset()];
                args.push(addr(vR1->Mul(vR2), TEMP_TABLE));
                break;
            case LEX_DIV:
                v2 = args.top();
                args.pop();
                v1 = args.top();
                args.pop();
                vR1 = v1.get_table() == MAIN_TABLE ? TID[v1.get_offset()] : TTV[v1.get_offset()];
                vR2 = v2.get_table() == MAIN_TABLE ? TID[v2.get_offset()] : TTV[v2.get_offset()];
                args.push(addr(vR1->Div(vR2), TEMP_TABLE));
                break;
            case LEX_EQ:
                v2 = args.top();
                args.pop();
                v1 = args.top();
                args.pop();
                vR1 = v1.get_table() == MAIN_TABLE ? TID[v1.get_offset()] : TTV[v1.get_offset()];
                vR2 = v2.get_table() == MAIN_TABLE ? TID[v2.get_offset()] : TTV[v2.get_offset()];
                args.push(addr(Eq(vR1, vR2), TEMP_TABLE));
                break;
            case LEX_NEQ:
                v2 = args.top();
                args.pop();
                v1 = args.top();
                args.pop();
                vR1 = v1.get_table() == MAIN_TABLE ? TID[v1.get_offset()] : TTV[v1.get_offset()];
                vR2 = v2.get_table() == MAIN_TABLE ? TID[v2.get_offset()] : TTV[v2.get_offset()];
                args.push(addr(Neq(vR1, vR2), TEMP_TABLE));
                break;
            case LEX_BIGGER:
                v2 = args.top();
                args.pop();
                v1 = args.top();
                args.pop();
                vR1 = v1.get_table() == MAIN_TABLE ? TID[v1.get_offset()] : TTV[v1.get_offset()];
                vR2 = v2.get_table() == MAIN_TABLE ? TID[v2.get_offset()] : TTV[v2.get_offset()];
                args.push(addr(Bigger(vR1, vR2), TEMP_TABLE));
                break;
            case LEX_BEQ:
                v2 = args.top();
                args.pop();
                v1 = args.top();
                args.pop();
                vR1 = v1.get_table() == MAIN_TABLE ? TID[v1.get_offset()] : TTV[v1.get_offset()];
                vR2 = v2.get_table() == MAIN_TABLE ? TID[v2.get_offset()] : TTV[v2.get_offset()];
                args.push(addr(Beq(vR1, vR2), TEMP_TABLE));
                break;
            case LEX_LES:
                v2 = args.top();
                args.pop();
                v1 = args.top();
                args.pop();
                vR1 = v1.get_table() == MAIN_TABLE ? TID[v1.get_offset()] : TTV[v1.get_offset()];
                vR2 = v2.get_table() == MAIN_TABLE ? TID[v2.get_offset()] : TTV[v2.get_offset()];
                args.push(addr(Less(vR1, vR2), TEMP_TABLE));
                break;
            case LEX_LEQ:
                v2 = args.top();
                args.pop();
                v1 = args.top();
                args.pop();
                vR1 = v1.get_table() == MAIN_TABLE ? TID[v1.get_offset()] : TTV[v1.get_offset()];
                vR2 = v2.get_table() == MAIN_TABLE ? TID[v2.get_offset()] : TTV[v2.get_offset()];
                args.push(addr(Leq(vR1, vR2), TEMP_TABLE));
                break;
            case LEX_INTERVAL:
                v2 = args.top();
                args.pop();
                v1 = args.top();
                args.pop();
                vR1 = v1.get_table() == MAIN_TABLE ? TID[v1.get_offset()] : TTV[v1.get_offset()];
                vR2 = v2.get_table() == MAIN_TABLE ? TID[v2.get_offset()] : TTV[v2.get_offset()];
                args.push(addr(vR1->interval(vR2), TEMP_TABLE));
                break;
            case LEX_SQBRCL:
                v2 = args.top();
                args.pop();
                v1 = args.top();
                args.pop();                vR1 = v1.get_table() == MAIN_TABLE ? TID[v1.get_offset()] : TTV[v1.get_offset()];
                vR2 = v2.get_table() == MAIN_TABLE ? TID[v2.get_offset()] : TTV[v2.get_offset()];

                args.push(addr(vR1->at(vR2->get_tuple()), TEMP_TABLE));
                break;
            case LEX_UNMIN:
                v1 = args.top();
                args.pop();
                vR1 = v1.get_table() == MAIN_TABLE ? TID[v1.get_offset()] : TTV[v1.get_offset()];
                args.push(addr(vR1->Unmin(), TEMP_TABLE));
                break;
            /*case LEX_UNPL:
                v1 = args.pop();
                vR1 = v1.get_table() == MAIN_TABLE ? TID[v1.get_offset()] : TTV[v1.get_offset()];
                args.push(addr(vR1->Unplus(), TEMP_TABLE));
                break; */
            case POLIZ_GO:
                v1 = args.top();
                args.pop();
                index = v1.get_offset() - 1;
                break;
            case POLIZ_FGO:
                v1 = args.top();
                args.pop();
                v2 = args.top();
                args.pop();
                vR2 = v2.get_table() == MAIN_TABLE ? TID[v2.get_offset()] : TTV[v2.get_offset()];
                bp = (vR2->ToLog())-> kernel_at_log(1);
                if (bp == NULL || *bp == false)
                {
                    index = v1.get_offset() - 1;
                }
            case LEX_BROP:
                args.push(addr(0, OTHER));
                break;
            case LEX_MODE:
                v1 = args.top();
                args.pop();
                while (v1.get_table() != OTHER)
                {
                    vR1 = v1.get_table() == MAIN_TABLE ? TID[v1.get_offset()] : TTV[v1.get_offset()];
                    cargs.push_front(vR1);
                    v1 = args.top();
                    args.pop();
                }
                args.push(addr(Mode(cargs), TEMP_TABLE));
                break;
            case LEX_LEN:
                v1 = args.top();
                args.pop();
                while (v1.get_table() != OTHER)
                {
                    vR1 = v1.get_table() == MAIN_TABLE ? TID[v1.get_offset()] : TTV[v1.get_offset()];
                    cargs.push_front(vR1);
                    v1 = args.top();
                    args.pop();
                }
                args.push(addr(lenght(cargs), TEMP_TABLE));
                break;
            case LEX_C:
                v1 = args.top();
                args.pop();
                while (v1.get_table() != OTHER)
                {
                    vR1 = v1.get_table() == MAIN_TABLE ? TID[v1.get_offset()] : TTV[v1.get_offset()];
                    cargs.push_front(vR1);
                    v1 = args.top();
                    args.pop();
                }
                args.push(addr(conc(cargs), TEMP_TABLE));
                cargs.clear();
                break;
            case LEX_IN:
                v2 = args.top();
                args.pop();
                v1 = args.top();
                args.pop();
                vR1 = v1.get_table() == MAIN_TABLE ? TID[v1.get_offset()] : TTV[v1.get_offset()];
                vR2 = v2.get_table() == MAIN_TABLE ? TID[v2.get_offset()] : TTV[v2.get_offset()];
                if (vR1->in(vR2) == -1)
                {
                    vR1 = change_type(vR1, vR2->get_type());
                    if (v1.get_table() == MAIN_TABLE)
                    {
                        TID.change(v1.get_offset(), vR1);
                    }
                    else
                    {
                        TTV.change(v1.get_offset(), vR1);
                    }
                    vR1->in(vR2);
                }
                args.push(v2);
                break;
            case LEX_FIGCL:
                if (!args.empty())
                {
                    if (LastLex.get_type() != LEX_END)
                    {
                        if (LastLex.get_type() != LEX_IN && LastLex.get_type() != POLIZ_GO && LastLex.get_type()!= POLIZ_FGO)
                        {
                            v1 = args.top();
                            last = v1;
                            vR1 = v1.get_table() == MAIN_TABLE ? TID[v1.get_offset()] : TTV[v1.get_offset()];
                            vR1 -> write();
                            std::cout << std::endl;
                            args.pop();
                        }
                        else
                        {
                            last = args.top();
                            args.pop();
                        }
                    }
                }
                else
                {
                    last = addr(TTV.put(Nulltype), TEMP_TABLE);
                }
                args.push(last);

                break;
            case LEX_FIGOP:
                args.push(addr(0, OTHER));
                break;
            case LEX_END:
                if (!args.empty())
                {
                    if (index != 0 && LastLex.get_type() != LEX_IN && LastLex.get_type() != POLIZ_GO && LastLex.get_type()!= POLIZ_FGO)
                    {
                        v1 = args.top();
                        last = v1;
                        vR1 = v1.get_table() == MAIN_TABLE ? TID[v1.get_offset()] : TTV[v1.get_offset()];
                        vR1 -> write();
                        std::cout << std::endl;
                    }
                    else
                    {
                        last = args.top();
                    }
                    args.pop();
                }
                else
                {
                    last = addr(TTV.put(Nulltype), TEMP_TABLE);
                }
                break;
            default: throw "default error";
        }
        index++;
        LastLex = pc_el;
    }
    /*while (!args.empty())
    {
        v1 = args.top();
        args.pop();
        vR1 = v1.get_table() == MAIN_TABLE ? TID[v1.get_offset()] : TTV[v1.get_offset()];
        vR1 -> write();
        std::cout  << std::endl;
    } */
}

#endif
