#pragma once


//在类层次间进行上行转换时，dynamic_cast和static_cast的效果是一样的；
//在进行下行转换时，dynamic_cast具有类型检查的功能，比static_cast更安全。

class Base
{
public:
    int m_iNum;
    virtual void f() {}
};

class Derived1 : public Base
{

};

class Derived2 : public Base
{

};


//reinpreter_cast
//它可以把一个指针转换成一个整数，也可以把一个整数转换成一个指针
//（先把一个指针转换成一个整数，在把该整数转换成原类型的指针，还可以得到原先的指针值）。
//* 从指针类型到一个足够大的整数类型
//* 从整数类型或者枚举类型到指针类型
//* 从一个指向函数的指针到另一个不同类型的指向函数的指针
//* 从一个指向对象的指针到另一个不同类型的指向对象的指针
//* 从一个指向类函数成员的指针到另一个指向不同类型的函数成员的指针
//* 从一个指向类数据成员的指针到另一个指向不同类型的数据成员的指针
//一个例子是，计算hash函数

unsigned short Hash(void* p)
{
#
    unsigned int val = reinterpret_cast<unsigned int>(p);//如果是64位系统，需要unsigned long
    return (unsigned short)(val ^ (val >> 16));
}

void Test_Hash() 
{
    int a[20];
    for (int i = 0; i < 20; i++)
        cout << Hash(a + i) << endl;
}


//const_cast
//用来修改类型的const或volatile属性。

void Test_Cast()
{
    Derived1* pd1 = new Derived1();
    pd1->m_iNum = 100;

    //Derived2* pd2 = static_cast<Derived2*>(pd1); //compile error

    Derived2* pd3 = dynamic_cast<Derived2*>(pd1); //pd2 is NULL

    delete pd1;
}