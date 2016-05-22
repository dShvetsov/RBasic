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



class Character_t:public R_type{
    std::vector<std::string *> v;
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
        R_type::size = 0;
    }
public:
    Character_t(std::string &s):R_type(Character){
        v.push_back(NULL);
        std::string *ps = new std::string(s);
        v.push_back(ps);
        R_type::size = 1;
    }
    Character_t():R_type(Character){v.push_back(NULL); R_type::size = 0;}
    void add(){
        v.push_back(NULL);
        R_type::size++;
    }
    void add(std::string &s)
    {
        std::string *ps  = new std::string(s);
        v.push_back(ps);
        R_type::size++;
    }
    void addaddr(std::string *s)
    {
        v.push_back(s);
        R_type::size++;
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
    int Beq(R_type *);
    int Eq(R_type *);
    int Neq(R_type *);
    int Bigger(R_type *);
    int Less(R_type *);
    int Leq(R_type *);
    int at(const std::set<unsigned int> &);
    int in(R_type *);
    std::string* kernel_at_char(int i){return v[i];}
    R_type * ToNum(){throw "Cannot assign character to numeric";}
    R_type * ToLog(){throw "Cannot assign character to logical";}
    R_type * ToChar(){return this;}
};


class Logical_t:public R_type{
    std::vector <bool *> v;
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
        R_type::size = 0;
    }
public:
    void add (bool a)
    {
        bool *tmp = new bool(a);
        v.push_back(tmp);
        R_type::size++;
    }
    void add(){ v.push_back(NULL); R_type::size++;}
    void addaddr(bool *a){ v.push_back(a); R_type::size++;}
    ~Logical_t()
    {
        clear();
    }
    Logical_t ():R_type(Logical){
        R_type::size = 0;
        v.push_back(NULL);
    }
    Logical_t (bool b) :R_type(Logical)
    {
        v.push_back(NULL);
        bool *tmp = new bool(b);
        v.push_back(tmp);
        R_type::size = 1;
    }
    void write()
    {
        for (unsigned int i = 1; i < v.size(); i++)
        {
            if (v[i] != NULL)
                (*v[i]) ?  std::cout << "TRUE" << ' ' : std::cout <<  "FALSE" << ' ';
            else
                std::cout << "NULL ";
        }
    }
    int Not();
    bool * kernel_at_log(int i){return v[i];}
    int And(R_type * );
    int Or(R_type * );
    int in(R_type *);
    std::set<unsigned int> get_tuple();
    int at(const std::set<unsigned int> &);
    R_type * ToChar();
    R_type * ToNum();
    R_type * ToLog(){return this;}
};


R_type* change_type(R_type *a, kind_of_type t)
{
    delete a;
    R_type *ans;
    switch(t)
    {
    case Nulltype: ans = new R_type; break;
    case Numeric: ans = new Numeric_t; break;
    case Logical: ans = new Logical_t; break;
    case Character: ans = new Character_t; break;
    }
    return ans;
}
