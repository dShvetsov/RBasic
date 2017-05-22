#ifndef Logical__h
#define Logical__h

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


#endif
