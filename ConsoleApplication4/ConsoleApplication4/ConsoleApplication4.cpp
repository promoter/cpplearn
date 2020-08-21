// ConsoleApplication4.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <algorithm>

#ifdef _WIN32
	#include <windows.h>
#else
#endif

using namespace std;

//-----------------------学习一个类占多少内存-------------------
//#define TEST_SIZEOF_CLASS
#ifdef TEST_SIZEOF_CLASS
class C_NULL {
public:

};

 class A{
public:
	virtual void fA() {}


};

class B : virtual public A{
public:
	virtual void fB() {}
};

class C : public A {
public:
	virtual void fC() {}
};

//*非静态成员变量总合。
//*加上编译器为了CPU计算，作出的数据对齐处理。
//*加上为了支持虚函数，产生的额外负担。
//GCC中, 无论是虚函数还是虚继承, 都需要将指针存储在虚函数表(virtual function table), 占用4个字节.
//VS中, 正常情况下, 所有虚函数都写在一个虚函数表中, 即派生类使用基类的虚函数表, 不会新建字节的虚函数表;
//如果使用虚继承, 则派生类, 新建虚函数表和虚继承表, 即额外增加8个字节(两个表);
//继承会继承基类的数据, 和虚函数表, 即继承基类的空间.

void TestClassSize()
{
	cout << "class C_NULL sizeof\t" << sizeof(C_NULL) << endl; //1
	cout << "class A sizeof\t" << sizeof(A) << endl; //4
	cout << "class B sizeof\t" << sizeof(B) << endl; //12
	cout << "class C sizeof\t" << sizeof(C) << endl; //4
}

#endif	//TEST_SIZEOF_CLASS

//-----------------------------------------------------------
//#define TEST_VIRTUAL_DERIVE
#ifdef TEST_VIRTUAL_DERIVE
//间接基类A
class A {
protected:
	int m_a;
};

//直接基类B
class B : virtual public A {  //虚继承
protected:
	int m_b;
};

//直接基类C
class C : virtual public A {  //虚继承
protected:
	int m_c;
};

//派生类D
class D : public B, public C {
public:
	void seta(int a) { m_a = a; }  //正确
	void setb(int b) { m_b = b; }  //正确
	void setc(int c) { m_c = c; }  //正确
	void setd(int d) { m_d = d; }  //正确
private:
	int m_d;
};
void TestVirtualDerive()
{
	class D;
}
#endif //TEST_VIRTUAL_DERIVE


//-----------------------------------------------------------
//#define TEST_AUTO_AND_DECLTYPE
#ifdef TEST_AUTO_AND_DECLTYPE
void testAuto()
{
	auto a = 23;
	auto b = 1.232;
	auto c = "dsfsf";
	auto d = 'd';
	auto e = 0x44;
	auto f = 0xFFFFFFFF;
	auto h = new int[5];
	auto j("jj");
}

template<typename T, typename U>
decltype(t + u) add(T t, U u) { 
	auto ret = t * 3 + u;
	return ret;
}

template<typename T, typename U>
auto add2(T t, U u) { 
	auto ret = t * 3 + u;
	return ret;
}

template <typename T>
T compare(const T &left, const T&right)
{
	std::cout << "in template<class T>..." << std::endl;
	return (left - right);
}

class A {
};

void testDecltype()
{
	const int &i = 1;
	int a = 2;
	decltype(i) b = 2; // b是const int&

	auto c = add2(a, i);//int
	auto d = compare(a, a);//int

	auto e = std::move(a); // e是将亡值
	A aa;
	auto f = static_cast<A&&>(aa); // f是将亡值
}

#endif //TEST_DECLTYPE

//-----------------------------------------------------------
#include <functional>
struct  AStruct
{
	int i;
	char c;
	string str;
	float f;
	char* arrC;

	AStruct() : i(0), c(0), str(""), f(6), arrC(nullptr) {};

	float Get1(int a) {
		return i + a + f * 1;
	}

};

float sumA(int i, float f)
{
	return i * f;
}

void testFunction_Bind_Lambda()
{
	//function<void(void)>  fun1 = testDecltype;
	//testDecltype();

	function<void(void)> fun2 = []() {
		int daf = 323;
		daf++;
	};
	fun2();

	function<float(AStruct&, int)>  fun3 = &AStruct::Get1;
	AStruct as;
	float f = fun3(as, 4);

	// 存储到 std::bind 调用的结果
	function<float()> fun4 = bind(sumA, 10, 15);
	float f2 = fun4();

	function<float()> fun5 = bind(&AStruct::Get1, as, 5);
	float f3 = fun5();
}

//https://mp.weixin.qq.com/s/G7HwKlSA1d8h2nRTs8s1DA


void findEmployee(const std::string& surname, const std::string& givenName, bool retired = false)
{
	cout << "findEmployee    1" << endl;
}
void findEmployee(const std::string& fullName, bool retired = false)
{
	cout << "findEmployee    2" << endl;
}

//#define TEST_MOVE
#ifdef TEST_MOVE
class A {
public:
	A(int size) : size_(size) {
		data_ = new int[size];
		cout << "construct " << size << endl;
	}
	A() {}
	A(const A& a) {
		size_ = a.size_;
		data_ =  new int[size_];
		cout << "copy " << endl;
	}
	A(A&& a) {
		this->data_ = a.data_;
		a.data_ = nullptr;
		cout << "move " << endl;
	}
	~A() {
		if (data_ != nullptr) {
			delete[] data_;
		}
		cout << "destruct " << endl;
	}
	int *data_;
	int size_;
};

void Test_Move()
{
	A a(10);
	A b = a;
	A c = std::move(a);//std::move函数强制把左值转换为右值
}
#endif // TEST_MOVE


#define TEST_ENUM
#ifdef  TEST_ENUM
#include "enumTest.h"
#endif //TEST_ENUM

int main()
{
	//testAuto();
	//testDecltype();
	//Test_Move();
	Test_Enum();

	findEmployee("Chen", "Shuo");

	while (true)
	{
		Sleep(10);
	}
    return 0;
}

