#pragma once
#include <iostream>
#include <memory>
#include <functional>
#include <list>
using namespace std;

/* reference 
* http://mp.weixin.qq.com/mp/homepage?__biz=MzU4Mzc3MzM3NA==&hid=3&sn=fd8a3e32f449c74965938c6134e544b0&scene=18#wechat_redirect
* https://www.jianshu.com/p/1061103ab216
*/

/*
* 桥接模式
*/
#define BRIDGE_PATTERN
#ifdef BRIDGE_PATTERN
class AbstractPhoneSoft
{
public:
	AbstractPhoneSoft() {};
	~AbstractPhoneSoft() {};
	virtual void Operate() = 0;
};

class PhoneSoftGame : public AbstractPhoneSoft
{
public:
	PhoneSoftGame() {};
	~PhoneSoftGame() {};

	void Operate()
	{
		cout << "PhoneSoftGame operate...." << endl;
	};
};

class PhoneSoftMsg : public AbstractPhoneSoft
{
public:
	PhoneSoftMsg() {};
	~PhoneSoftMsg() {};

	void Operate()
	{
		cout << "PhoneSoftMsg operate...." << endl;
	};
};

class AbstractPhoneBrand
{
public:
	AbstractPhoneBrand() {};
	~AbstractPhoneBrand() {};
	virtual void Operate() = 0;
};

class PhoneSoftHuaWei : public AbstractPhoneBrand
{
public:
	PhoneSoftHuaWei(const shared_ptr<AbstractPhoneSoft>& _impl) : impl(_impl){};
	~PhoneSoftHuaWei() {};

	void Operate()
	{
		cout << "PhoneSoftHuaWei operate...." << endl;
		impl->Operate();
	};

private:
	shared_ptr<AbstractPhoneSoft> impl;
};

class PhoneSoftXiaoMi : public AbstractPhoneBrand
{
public:
	PhoneSoftXiaoMi(const shared_ptr<AbstractPhoneSoft>& _impl) : impl(_impl) {};
	~PhoneSoftXiaoMi() {};

	void Operate()
	{
		cout << "PhoneSoftXiaoMi operate...." << endl;
		impl->Operate();
	};
private:
	shared_ptr<AbstractPhoneSoft> impl;
};

void Test_bridge_pattern()
{
	shared_ptr<AbstractPhoneSoft> soft1 = make_unique<PhoneSoftGame>();
	shared_ptr<AbstractPhoneSoft> soft2 = make_unique<PhoneSoftMsg>();

	unique_ptr<AbstractPhoneBrand> brand1 = make_unique<PhoneSoftHuaWei>(soft1);
	unique_ptr<AbstractPhoneBrand> brand2 = make_unique<PhoneSoftHuaWei>(soft2);

	unique_ptr<AbstractPhoneBrand> brand3 = make_unique<PhoneSoftXiaoMi>(soft1);
	unique_ptr<AbstractPhoneBrand> brand4 = make_unique<PhoneSoftXiaoMi>(soft2);

	brand1->Operate();
	brand2->Operate();
	brand3->Operate();
	brand4->Operate();
}
#endif // BRIDGE_PATTERN

/*
* 策略模式
*/
#define STRATEGY_PATTERN
#ifdef STRATEGY_PATTERN
class Hurt
{
public:
	virtual void RedBuff() = 0;
};

class AdcHurt : public Hurt
{
public:
	void RedBuff() 
	{
		cout << "AdcHurt RedBuff... " << endl;
	};
};

class ApcHurt : public Hurt
{
public:
	void RedBuff()
	{
		cout << "ApcHurt RedBuff... " << endl;
	};
};


class Master
{
public:
	typedef void (*HurtFun)();
	typedef std::function<void()> HurtFunc;

	enum HURT_TYPE
	{
		HURT_TYPE_ADC,
		HURT_TYPE_APC
	};
	Master() {}
	//方式1 
	Master(const shared_ptr<Hurt>& _hurt) : hurt(_hurt) { cout << "Master construct 1... " << endl; };
	//方式2
	Master(HURT_TYPE hurtType) 
	{
		cout << "Master construct 2... " << endl;
		switch (hurtType)
		{
		case Master::HURT_TYPE_ADC:
			hurt = make_shared<AdcHurt>();
			break;
		case Master::HURT_TYPE_APC:
			hurt = make_shared<ApcHurt>();
			break;
		}
	};
	//方式3

	static void RedBuff()
	{
		cout << " RedBuff... " << endl;
	};

	void SetFun(const HurtFun& _hurtFun)
	{
		cout << "SetFun... " << endl;
		hurtfun = _hurtFun;
	};
	//方式4
	Master(int i, const HurtFunc& _hurtFun) : hurtfun2(_hurtFun) { cout << "Master construct 4... " << endl; };

	//执行
	void BeInjured()
	{
		cout << "Master BeInjured... " << endl;
		if(hurt != nullptr)
			hurt->RedBuff();
		
		if (hurtfun != nullptr)
			hurtfun();

		if (hurtfun2 != nullptr)
			hurtfun2();
	}
private:
	shared_ptr<Hurt> hurt;
	HurtFun hurtfun;
	HurtFunc hurtfun2;
};

//方式5
template<typename T>
class Solder
{
public:
	Solder(const shared_ptr<T>& _hurt) : hurt(_hurt) {}
	//执行
	void BeInjured()
	{
		cout << "Solder BeInjured... " << endl;
		if (hurt != nullptr)
			hurt->RedBuff();
	}
private:
	shared_ptr<T> hurt;
};

void Test_Startegy_Pattern()
{
	shared_ptr<AdcHurt> hurt = make_shared<AdcHurt>();
	unique_ptr<Master> master1 = make_unique<Master>(hurt);
	unique_ptr<Master> master2 = make_unique<Master>(Master::HURT_TYPE_APC);

	unique_ptr<Master> master3 = make_unique<Master>();
	master3->SetFun(Master::RedBuff);
	unique_ptr<Master> master4 = make_unique<Master>(0, bind(&AdcHurt::RedBuff, hurt));

	unique_ptr<Solder<AdcHurt>> solder = make_unique<Solder<AdcHurt>>(hurt);

	master1->BeInjured();
	master2->BeInjured();
	master3->BeInjured();
	master4->BeInjured();
	solder->BeInjured();

}

#endif // STRATEGY_PATTERN

/*
* 观察者模式
*/
#define OBSERVER_PATTERN
#ifdef OBSERVER_PATTERN

class AbstractView
{
public:
	virtual void Update() = 0;
protected:
	AbstractView() {}
};

class TreeView : public AbstractView
{
public:
	void Update()
	{
		cout << "tree view update" << endl;
	};
};

class AbstractDataModel
{
public:
	virtual void Add(const shared_ptr<AbstractView>& v) = 0;
	virtual void Remove(const shared_ptr<AbstractView>& v) = 0;
	virtual void Notify() = 0;

protected:
	AbstractDataModel() {}
};

class FloatDataModel : public AbstractDataModel
{
public:
	FloatDataModel() {}
	void Add(const shared_ptr<AbstractView>& v)
	{
		//for_each(viewList.begin(), viewList.end(), [v](shared_ptr<AbstractView> view) {
		//	if (view == v)
		//	{
		//		cout << "view had added." << endl;
		//		return;
		//	}
		//});
		for (shared_ptr<AbstractView>& view : viewList)
		{
			if (view == v)
			{
				cout << "view had added." << endl;
				return;
			}
		}
		viewList.push_back(v);
		cout << "view add." << endl;
	}

	void Remove(const shared_ptr<AbstractView>& v)
	{
		//for_each(viewList.begin(), viewList.end(), [this, v](shared_ptr<AbstractView> view) {
		//	if (view == v)
		//	{
		//		viewList.remove(view);
		//		cout << "view remove." << endl;
		//		return;
		//	}
		//});
		for (shared_ptr<AbstractView>& view : viewList)
		{
			if (view == v)
			{
				viewList.remove(view);
				cout << "view remove." << endl;
				return;
			}
		}
		cout << "view remove not found." << endl;
	}
	void Notify()
	{
		for_each(viewList.begin(), viewList.end(), [](shared_ptr<AbstractView> view) {
			view->Update();
		});
	}

private:
	list<shared_ptr<AbstractView>> viewList;
};


void Test_Observer_Pattern()
{
	shared_ptr<AbstractView> tv1 = make_shared<TreeView>();
	shared_ptr<AbstractView> tv2 = make_shared<TreeView>();
	shared_ptr<AbstractView> tv3 = make_shared<TreeView>();
	
	unique_ptr<AbstractDataModel> dataModel = make_unique<FloatDataModel>();
	dataModel->Add(tv1);
	dataModel->Add(tv2);
	dataModel->Add(tv2);
	dataModel->Notify();
	dataModel->Remove(tv2);
	dataModel->Add(tv3);
	dataModel->Notify();
}

#endif // OBSERVER_PATTERN

/*
* 模板模式
*/
#define TEMPLATE_PATTERN
#ifdef TEMPLATE_PATTERN

class AbstractComputer
{
public:
	void Produce()
	{
		InstallBrand();
		InstallCPU();
		InstallMemory();
	}
protected:
	virtual void InstallCPU() = 0;
	virtual void InstallMemory() = 0;
	virtual void InstallBrand() = 0;
};

class ComputerA : public AbstractComputer
{
protected:
	void InstallCPU()
	{
		cout << "ComputerA install cpu." << endl;
	}
	void InstallMemory()
	{
		cout << "ComputerA install memory." << endl;
	}
	void InstallBrand()
	{
		cout << "ComputerA install brand." << endl;
	}
};

class ComputerB : public AbstractComputer
{
protected:
	void InstallCPU()
	{
		cout << "ComputerB install cpu." << endl;
	}
	void InstallMemory()
	{
		cout << "ComputerB install memory." << endl;
	}
	void InstallBrand()
	{
		cout << "ComputerB install brand." << endl;
	}
};

void Test_Template_Pattern()
{
	unique_ptr<AbstractComputer> computeA = make_unique<ComputerA>();
	unique_ptr<AbstractComputer> computeB = make_unique<ComputerB>();

	computeA->Produce();
	computeB->Produce();
}

#endif // TEMPLATE_PATTERN


/*
* 原型模式
*/
#define PROTOTYPE_PATTERN
#ifdef PROTOTYPE_PATTERN

class AbstractClone
{
public:
	AbstractClone() {}

	virtual shared_ptr<AbstractClone> Clone() = 0;
	virtual void Show() = 0;
};

class Sheep : public AbstractClone
{
public:
	Sheep(string _name) : AbstractClone(), name(_name) {}

	Sheep(const Sheep& right) : name(right.name){}

	shared_ptr<AbstractClone> Clone()
	{
		return make_shared<Sheep>(*this);
	}

	void Show() 
	{
		cout << "sheep show." << endl;
	}

	string name;
};
void Test_Prototype_Pattern()
{
	shared_ptr<AbstractClone> sheep1 = make_shared<Sheep>("duli 1");
	shared_ptr<AbstractClone> sheep2 = sheep1->Clone();

	sheep1->Show();
	sheep2->Show();
}
#endif //PROTOTYPE_PATTERN

/*
* 工厂模式 ：简单工厂、工厂方法、抽象工厂
*/
#define FACTORY_PATTERN
#ifdef FACTORY_PATTERN
//简单工厂
typedef enum 
{
	TANK_88,
	TANK_90
}TANK_TYPE;

class AbstractTank
{
public:
	virtual void Message() = 0;
};

class Tank88 : public AbstractTank
{
public:
	void Message()
	{
		cout << "Tank88 messsage..." << endl;
	}
};

class Tank90 : public AbstractTank
{
public:
	void Message()
	{
		cout << "Tank90 messsage..." << endl;
	}
};

class SimpleFactory
{
public:
	shared_ptr<AbstractTank> CreatTrank(TANK_TYPE type)
	{
		shared_ptr<AbstractTank> ret;
		switch (type)
		{
		case TANK_88:
			ret = make_shared<Tank88>();
			ret->Message();
			break;		
		case TANK_90:
			ret = make_shared<Tank90>();
			ret->Message();
			break;
		}
		return ret;
	}
};

class AbstractFactoryMethod
{
public:
	virtual shared_ptr<AbstractTank> CreatTrank() = 0;
};

class Tank88FactoryMethod : public AbstractFactoryMethod
{
public:
	shared_ptr<AbstractTank> CreatTrank()
	{
		shared_ptr<AbstractTank> ret = make_shared<Tank88>();
		ret->Message();
		return ret;
	}
};

class Tank90FactoryMethod : public AbstractFactoryMethod
{
public:
	shared_ptr<AbstractTank> CreatTrank()
	{
		shared_ptr<AbstractTank> ret = make_shared<Tank90>();
		ret->Message();
		return ret;
	}
};


class AbstractPlain
{
public:
	virtual void Message() = 0;
};

class Plain88 : public AbstractPlain
{
public:
	void Message()
	{
		cout << "Plain88 messsage..." << endl;
	}
};

class Plain90 : public AbstractPlain
{
public:
	void Message()
	{
		cout << "Plain90 messsage..." << endl;
	}
};

class AbstractFactory
{
public:
	virtual shared_ptr<AbstractTank> CreatTrank() = 0;
	virtual shared_ptr<AbstractPlain> CreatPlain() = 0;
};

class Tank88AbstractFactory
{
public:
	shared_ptr<AbstractTank> CreatTrank()
	{
		shared_ptr<AbstractTank> ret = make_shared<Tank88>();
		ret->Message();
		return ret;
	}
	shared_ptr<AbstractPlain> CreatPlain()
	{
		shared_ptr<AbstractPlain> ret = make_shared<Plain88>();
		ret->Message();
		return ret;
	}
};

class Tank90AbstractFactory
{
public:
	shared_ptr<AbstractTank> CreatTrank()
	{
		shared_ptr<AbstractTank> ret = make_shared<Tank90>();
		ret->Message();
		return ret;
	}
	shared_ptr<AbstractPlain> CreatPlain()
	{
		shared_ptr<AbstractPlain> ret = make_shared<Plain90>();
		ret->Message();
		return ret;
	}
};

void Test_Factory_Pattern()
{
	SimpleFactory simpleFactory;
	simpleFactory.CreatTrank(TANK_TYPE::TANK_88);
	simpleFactory.CreatTrank(TANK_TYPE::TANK_90);

	Tank88FactoryMethod tank88factory;
	tank88factory.CreatTrank();

	Tank90FactoryMethod tank90factory;
	tank90factory.CreatTrank();

	Tank88AbstractFactory tank88abstractfactory;
	tank88abstractfactory.CreatTrank();
	tank88abstractfactory.CreatPlain();

	Tank90AbstractFactory tank90abstractfactory;
	tank90abstractfactory.CreatTrank();
	tank90abstractfactory.CreatPlain();


}
#endif //FACTORY_PATTERN

/*
* 适配器模式
*/
#define ADAPTER_PATTERN
#ifdef ADAPTER_PATTERN

template<typename T>
class Deque
{
public:
	void push_back(T& t)
	{
		cout << "push_back " << t << endl;
	}

	void push_front(T& t)
	{
		cout << "push_front " << t << endl;
	}

	T pop_back()
	{
		T t(0);
		cout << "pop_back " << t << endl;
		return t;
	}
	T pop_front()
	{
		T t(0);
		cout << "pop_front " << t << endl;
		return t;
	}
};

template<typename T>
class Sequence
{
public:
	virtual void push(T& t) = 0;
	virtual T pop() = 0;
};
//聚合实现方式
template<typename T>
class Stack1 : public Sequence<T>
{
public:
	void push(T& t)
	{
		deque.push_front(t);
	}

	T pop()
	{
		return deque.pop_front();
	}

private:
	Deque<T> deque;
};

template<typename T>
class Queue1 : public Sequence<T>
{
public:
	void push(T& t)
	{
		deque.push_front(t);
	}
	T pop()
	{
		return deque.pop_back();
	}
private:
	Deque<T> deque;
};

//继承实现方式
template<typename T>
class Stack2 : public Sequence<T>, private Deque<T>
{
public:
	void push(T& t)
	{
		this->push_front(t);
	}

	T pop()
	{
		return this->pop_front();
	}
};

template<typename T>
class Queue2 : public Sequence<T>, private Deque<T>
{
public:
	void push(T& t)
	{
		this->push_front(t);
	}
	T pop()
	{
		return this->pop_back();
	}
};


void Test_Adapter_pattern()
{
	int a = 10;
	Stack1<int> stack1;
	stack1.push(a);
	stack1.pop();

	Queue1<int> queue1;
	queue1.push(a);
	queue1.pop();

	Stack2<int> stack2;
	stack2.push(a);
	stack2.pop();

	Queue2<int> queue2;
	queue2.push(a);
	queue2.pop();
}
#endif //ADAPTER_PATTERN