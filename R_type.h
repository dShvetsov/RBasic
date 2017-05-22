#ifndef R_type__h
#define R_type__h

#include <iostream>
#include <vector>
#include <iterator>
#include <typeinfo>
#include <set>

enum kind_of_type{ Nulltype, Numeric, Logical, Character};

inline int max(int a, int b){ return a > b ? a : b; }
inline int min(int a, int b){ return a < b ? a : b; }



class R_type
{
    bool fake;
    kind_of_type type;
    virtual void clear(){ size = 0;}
protected:
    int size;
public:
    int Rsize(){ return size;}
    void fake_on() {fake = true;}
  //  extern friend int tabl_temp::put(kind_of_type t);
    bool isfake(){return fake;}
    R_type():fake(false), type(Nulltype){};
    R_type(kind_of_type t):type(t){fake = false;};
    kind_of_type get_type(){return type;}
    void put_type(kind_of_type t){type = t;}
    virtual R_type *ToLog();
    virtual R_type *ToNum();
    virtual R_type *ToChar();

    virtual int Not()
    {
        return ToLog()->Not();
    }
    virtual int And(R_type * a){
        return ToLog()->And(a);
    }
    virtual int Or(R_type *a){
        return ToLog()->Or(a);
    }
    virtual int Plus(R_type *a){
        return ToNum()->Plus(a);
    }
    virtual int Minus(R_type *a){
        return ToNum()->Minus(a);
    }
    virtual int Mul(R_type *a){
        return ToNum()->Mul(a);
        }
    virtual int Div(R_type *a){
        return ToNum()->Div(a);
    }
    virtual int interval(R_type *a)
    {
        return ToNum()->interval(a);
    }
    virtual int Eq(R_type *) {return 1;}
    virtual int Neq(R_type *) {return 1;}
    virtual int Bigger(R_type *) {return 1;}
    virtual int Beq(R_type *) {return 1;}
    virtual int Less(R_type *) {return 1;}
    virtual int Leq(R_type*) {return 1;}
    virtual int at(const std::set<unsigned int> & q) {return 1;}
    virtual double * kernel_at_num(int i) {throw "!";}
    virtual std::string * kernel_at_char(int i) { throw "!";}
    virtual bool * kernel_at_log(int i) {throw "!";}
    virtual int Unmin() {
        return ToNum()->Unmin();
    }
//    virtual int Unpl() {return 1;}
    virtual std::set<unsigned int> get_tuple()
    {
        throw "cannt be used as index";
    }
    virtual void add(){size++;}
    virtual void add(std::string &){throw "Error";}
    virtual void add(double x){throw "Error";}
    virtual void add(bool b){throw "Error";}
    virtual void addaddr(std::string *){throw "Error";}
    virtual void addaddr(double *){throw "Error";}
    virtual void addaddr(bool *){throw "Error";}
    virtual int in(R_type *a){
        if (a->get_type() != Nulltype)
            return -1;
        return 0;
    }
    virtual void write(){std::cout << "NULL" << std::endl;}
    virtual ~R_type(){}
};

int Eq(R_type *a, R_type *b);
int Neq(R_type *a, R_type *b);
int Bigger(R_type *a, R_type *b);
int Beq(R_type *a, R_type *b);
int Less(R_type *a, R_type *b);
int Leq(R_type *a, R_type *b);
#endif
