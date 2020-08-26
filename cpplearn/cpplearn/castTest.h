#pragma once


//�����μ��������ת��ʱ��dynamic_cast��static_cast��Ч����һ���ģ�
//�ڽ�������ת��ʱ��dynamic_cast�������ͼ��Ĺ��ܣ���static_cast����ȫ��

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
//�����԰�һ��ָ��ת����һ��������Ҳ���԰�һ������ת����һ��ָ��
//���Ȱ�һ��ָ��ת����һ���������ڰѸ�����ת����ԭ���͵�ָ�룬�����Եõ�ԭ�ȵ�ָ��ֵ����
//* ��ָ�����͵�һ���㹻�����������
//* ���������ͻ���ö�����͵�ָ������
//* ��һ��ָ������ָ�뵽��һ����ͬ���͵�ָ������ָ��
//* ��һ��ָ������ָ�뵽��һ����ͬ���͵�ָ������ָ��
//* ��һ��ָ���ຯ����Ա��ָ�뵽��һ��ָ��ͬ���͵ĺ�����Ա��ָ��
//* ��һ��ָ�������ݳ�Ա��ָ�뵽��һ��ָ��ͬ���͵����ݳ�Ա��ָ��
//һ�������ǣ�����hash����

unsigned short Hash(void* p)
{
#
    unsigned int val = reinterpret_cast<unsigned int>(p);//�����64λϵͳ����Ҫunsigned long
    return (unsigned short)(val ^ (val >> 16));
}

void Test_Hash() 
{
    int a[20];
    for (int i = 0; i < 20; i++)
        cout << Hash(a + i) << endl;
}


//const_cast
//�����޸����͵�const��volatile���ԡ�

void Test_Cast()
{
    Derived1* pd1 = new Derived1();
    pd1->m_iNum = 100;

    //Derived2* pd2 = static_cast<Derived2*>(pd1); //compile error

    Derived2* pd3 = dynamic_cast<Derived2*>(pd1); //pd2 is NULL

    delete pd1;
}