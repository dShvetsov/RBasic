#ifndef Numeric__h
#define Numeric__h

#include "R_type.h"

class Numeric_t:public R_type
{
    std::vector<double *> v;
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
    }
public:
    ~Numeric_t() {clear();}
    Numeric_t():R_type(Numeric){
        v.push_back(NULL);
        R_type::size = 0;
    };
    void add(double x)
    {
        double *tmp = new double (x);
        v.push_back(tmp);
        R_type::size ++;
    }
    void add() {
        v.push_back(NULL);
        R_type::size++;
    }
    void addaddr(double *x){
        v.push_back(x);
    }
    Numeric_t(double x):R_type(Numeric)
    {
        v.push_back(NULL);
        double *px = new double(x);
        v.push_back(px);
        R_type::size = 1;
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

    int Plus(R_type *);
    int Minus(R_type *);
    int Mul(R_type *);
    int Div(R_type *);
    int Eq(R_type *);
    int Neq(R_type *);
    int Bigger(R_type *);
    int Beq(R_type *);
    int Less(R_type *);
    int Leq(R_type *);
    int Unmin();
    R_type *ToChar();
    R_type *ToLog();
    R_type *ToNum(){return this;}
    int interval(R_type *);
    int at(const std::set<unsigned int> &);
    std::set<unsigned int> get_tuple();
    double* kernel_at_num(int i) { return v[i];}
    int in(R_type *);
};

#endif
