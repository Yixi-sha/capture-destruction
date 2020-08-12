#include <iostream>
#include <memory>

using namespace std;

class A{
public:
    A(){
        cout << "A()" << endl;
    }
    ~A(){
        cout << "~A()" << endl;
    }
};

class B : public A{
public:
    B(){
        cout << "B()" << endl;
    }
    ~B(){
        cout << "~B()" << endl;
    }
};

class base{
public:
    base() {

    }
    virtual void des() = 0;
};

template <typename T, typename D>
class derive : public base{
    T* pointer;
    D deleter;
public:
    derive(T* p): pointer(p) {}
    virtual void des() override{ 
        deleter(pointer);
    }
};

template <typename B>
class ptr{

    template <typename U>
    struct Des
    {
        void operator()(B* b) { delete static_cast<U*>(b); }
    };
    
    base* des;
public:
    template <typename D>
    ptr(D *target){
        des = new derive<B, Des<D>>(target);
    }

    ~ptr(){
        des->des();
        delete des;
    }
};

int main()
{
    cout << "yixi-test" << endl;
    ptr<A> tmp(new B());
   
    cout << "yixi-test end" << endl;
    return 0;
}
