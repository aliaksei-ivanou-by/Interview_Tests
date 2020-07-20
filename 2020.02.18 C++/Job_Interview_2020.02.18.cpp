#include "iostream"

class Base
{
public:
	Base() { std::cout << "Base created" << std::endl; }
	virtual ~Base() { std::cout << "Base destroyed" << std::endl; }

	virtual void foo1() { std::cout << "Base::foo1" << std::endl; }
	void foo2() { std::cout << "Base::foo2" << std::endl; }
};

class Child : public Base
{
public:
	Child() { std::cout << "Child created" << std::endl; }
	~Child() { std::cout << "Child destroyed" << std::endl; }

	void foo1() { std::cout << "Child::foo1" << std::endl; };
	void foo2() { std::cout << "Child::foo2" << std::endl; };
};

void process1(Base* obj)
{
	std::cout << "In process1" << std::endl;
	obj->foo1();
	obj->foo2();
}

void process2(Base obj)
{
	std::cout << "In process2" << std::endl;
	obj.foo1();
	obj.foo2();
}

int main()
{
	Base* p = new Child; // Base created, Child created

	std::cout << '\n';

	process1(p); // In process1, Child::foo1, Base::foo2

	std::cout << '\n';

	process2(*p); // In process2, Base::foo1, Base::foo2, Base destroyed

	std::cout << '\n';

	delete p; // Child destroyed, Base destroyed

	return 0;
}
