#include <iostream>
#include <string>
#include <memory>

using namespace std;
using std::string;

//智能指针 包裹类，优先使用 "前置声明"， 而不是include header

class C_SP
{
public:
    void begin_release()
    {
        cout << "C_SP begin_release.." << endl;
    }
};

class C_SP_Shared : public enable_shared_from_this<C_SP_Shared>
{
public:
    //正确做法
    std::shared_ptr<C_SP_Shared> getSef()
    {
        return shared_from_this();
    }
    
    //错误用法，会导致外部二次析构，出错
    std::shared_ptr<C_SP_Shared> getSp()
    {
        return std::shared_ptr<C_SP_Shared>(this);
    }

    void func()
    {
        cout << "C_SP_Shared::func()" << endl;
    }
};

void unique_ptr_()
{
    //可以用move转移 unique_ptr
    std::unique_ptr<int> sp1(std::make_unique<int>(123));
    std::unique_ptr<int> sp2(std::move(sp1));
    std::unique_ptr<int> sp3;
    sp3 = std::move(sp2);

    //可以自定义 智能指针析构时的动作
    auto csp_deleter = [](C_SP* psp){
        psp->begin_release();
    };

    std::unique_ptr<C_SP, decltype(csp_deleter)> cp1(new C_SP, csp_deleter);
    std::unique_ptr<C_SP, void(*)(C_SP* psp)> cp2(new C_SP, csp_deleter);

    //大小 一个指针
    cout << "sizeof(unique_ptr):" << sizeof(sp1) << endl;
}

void shared_ptr_()
{
    std::shared_ptr<C_SP_Shared> sp1 = std::make_shared<C_SP_Shared>();
    std::shared_ptr<C_SP_Shared> sp2 = sp1->getSef();
    std::shared_ptr<C_SP_Shared> sp3 = sp1->getSp(); //析构时 会多次析构 导致崩溃

 
    //大小 2个指针
    cout << "sizeof(shared_ptr):" << sizeof(sp1) << endl;

    //注意 引用导致的崩溃问题
    std::shared_ptr<C_SP_Shared> sp4(new C_SP_Shared());
    //const std::shared_ptr<C_SP_Shared> &sp5 = sp4;
    const auto &sp5 = sp4;
    sp4.reset();
    sp5->func(); //此时 sp4 sp5已经为空了， 崩溃; todo 实际测试过程中不会崩溃？？？？ 
     
}

#if 0

int main()
{
    unique_ptr_();
    shared_ptr_();
    return 0;
}

#endif