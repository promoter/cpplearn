// ConsoleApplication4.cpp : �������̨Ӧ�ó������ڵ㡣
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

//-----------------------ѧϰһ����ռ�����ڴ�-------------------
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

//*�Ǿ�̬��Ա�����ܺϡ�
//*���ϱ�����Ϊ��CPU���㣬���������ݶ��봦��
//*����Ϊ��֧���麯���������Ķ��⸺����
//GCC��, �������麯��������̳�, ����Ҫ��ָ��洢���麯����(virtual function table), ռ��4���ֽ�.
//VS��, ���������, �����麯����д��һ���麯������, ��������ʹ�û�����麯����, �����½��ֽڵ��麯����;
//���ʹ����̳�, ��������, �½��麯�������̳б�, ����������8���ֽ�(������);
//�̳л�̳л��������, ���麯����, ���̳л���Ŀռ�.

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
//��ӻ���A
class A {
protected:
	int m_a;
};

//ֱ�ӻ���B
class B : virtual public A {  //��̳�
protected:
	int m_b;
};

//ֱ�ӻ���C
class C : virtual public A {  //��̳�
protected:
	int m_c;
};

//������D
class D : public B, public C {
public:
	void seta(int a) { m_a = a; }  //��ȷ
	void setb(int b) { m_b = b; }  //��ȷ
	void setc(int c) { m_c = c; }  //��ȷ
	void setd(int d) { m_d = d; }  //��ȷ
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
	decltype(i) b = 2; // b��const int&

	auto c = add2(a, i);//int
	auto d = compare(a, a);//int

	auto e = std::move(a); // e�ǽ���ֵ
	A aa;
	auto f = static_cast<A&&>(aa); // f�ǽ���ֵ
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

	// �洢�� std::bind ���õĽ��
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
	A c = std::move(a);//std::move����ǿ�ư���ֵת��Ϊ��ֵ
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

