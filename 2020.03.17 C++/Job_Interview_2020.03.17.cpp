#include <iostream>
using namespace std;

template<typename T>
struct List
{
	List();
	~List();
	void push_back(T data);
	void pop_front();
	void clear();
	T& operator[](const int index);
	int GetSize();
private:
	template<typename TT>
	struct Node
	{
		Node* pNext;
		TT data;
		Node(TT data = TT(), Node* pNext = nullptr)
		{
			this->data = data;
			this->pNext = pNext;
		}
	};
	Node<T>* head;
};

template<typename T>
List<T>::List()
{
	head = nullptr;
}

template<typename T>
List<T>::~List()
{
	clear();
}

template<typename T>
void List<T>::push_back(T data)
{
	if (head == nullptr)
	{
		head = new Node<T>(data);
	}
	else
	{
		Node<T>* current = this->head;
		while (current->pNext != nullptr)
		{
			current = current->pNext;
		}
		current->pNext = new Node<T>(data);
	}
}

template<typename T>
void List<T>::pop_front()
{
	Node<T>* temp = head;
	head = head->pNext;
	delete temp;
}

template<typename T>
void List<T>::clear()
{
	while (GetSize() != 0)
	{
		pop_front();
	}
}

template<typename T>
T& List<T>::operator[](const int index)
{
	int counter = 0;
	Node<T>* current = this->head;
	while (current != nullptr)
	{
		if (counter == index)
		{
			return current->data;
		}
		current = current->pNext;
		++counter;
	}
}

template<typename T>
int List<T>::GetSize()
{
	int size = 0;
	Node<T>* current = this->head;
	while (current != nullptr)
	{
		current = current->pNext;
		++size;
	}
	return size;
}

int main()
{
	List<int> lst;
	int numbersCount;
	cin >> numbersCount;
	for (int i = 0; i < numbersCount; ++i)
	{
		lst.push_back(rand() % 10);
	}
	cout << "Direct order:\n";
	for (int i = 0; i < lst.GetSize(); ++i)
	{
		cout << lst[i] << ' ';
	}
	cout << "\nReverse order:\n";
	for (int i = lst.GetSize() - 1; i >= 0; --i)
	{
		cout << lst[i] << ' ';
	}
	return 0;
}
