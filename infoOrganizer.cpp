#include <iostream>
#include <windows.h>
#include <time.h>
#include <exception>
using namespace std;

template <typename T>
struct Node {
	T value;
	time_t* creationTime;
	Node* next;
	Node* prev;
};

class ListException : public exception {
private:
	string m_error;
public:
	ListException(int code)
	{
		switch (code)
		{
		case 1:
			m_error = "\nError: any elements in list";
			break;
		case 2:
			m_error = "\nError: unexpected id";
		}
	}
	const char* what() const noexcept override {
		return m_error.c_str();
	}
};

template <typename T>
class List {
private:
	Node<T>* head;
	Node<T>* tail;
	unsigned long long size;
public:

	List()
	{
		this->head = nullptr;
		this->tail = nullptr;
		size = 0;
	}

	void add(int num) {

		if (head == nullptr) {
			this->head = new Node<T>;

			this->head->next = nullptr;
			this->head->value = num;
			this->head->prev = nullptr;

			this->tail = this->head;
		}
		else {
			Node<T>* tmp = this->head;
			while (tmp->next != nullptr) {
				tmp = tmp->next;
			}
			tmp->next = new Node<T>;

			tmp->next->prev = tmp;
			tmp->next->next = nullptr;
			tmp->next->value = num;

			this->tail = tmp->next;
		}
		this->size++;
	}

	void show() {
		try {
			if (size == 0) {
				throw(ListException(1));
			}
		}
		catch (ListException error) {
			cout << error.what();
			throw;
		}
		Node<T>* tmp = this->head;

		while (tmp != nullptr) {
			cout << "value: " << tmp->value << "\n";
			tmp = tmp->next;
		}
	}

	void changeElem(T value, int id) {
		try {
			if (id > this->size || id < 0) {
				throw(ListException(2));
			}
		}
		catch (ListException error) {
			cout << error.what();
			throw;
		}

		Node<T>* tmp = this->head;
		for (int i = 0; i < id - 1; i++) {
			tmp = tmp->next;
		}
		tmp->value = value;
	}
	
	void Debug() {
		try {
			if (size == 0) {
				throw(ListException(1));
			}
		}
		catch (ListException error) {
			cout << error.what();
			throw;
		}

		Node<T>* tmp = this->head;

		while (tmp != nullptr) {
			cout << "prev: " << tmp->prev << "\tthis: " << tmp << "\tTnext: " << tmp->next << "\tvalue: " << tmp->value << "\n";
			tmp = tmp->next;
		}

	}

	void remove(int num) {

		if (isIn(num) == true) {
			Node<T>* tmp = this->head;
			if (this->head->value == num) {
				this->head->next->prev = nullptr;
				this->head = this->head->next;
			}
			else {
				if (this->tail->value == num) {
					this->tail->prev->next = nullptr;
					this->tail = this->tail->prev;
				}
				else {
					while (tmp->next != nullptr) {

						if (tmp->value == num) {
							break;
						}
						tmp = tmp->next;
					}
					tmp->next->prev = tmp->prev;
					tmp->prev->next = tmp->next;
				}
			}
			this->size--;
		}
	}

	bool isIn(int num) {

		try {
			if (num > this->size || num < 0) {
				throw(ListException(2));
			}
		}
		catch (ListException error) {
			cout << error.what();
			throw;
		}

		Node<T>* tmp = this->head;
		bool checker = false;
		while (tmp != nullptr) {
			if (tmp->value == num) {
				checker = true;
			}
			tmp = tmp->next;
		}
		return checker;
	}
	unsigned long long getsize() {
		return size;
	}

};
int main()
{
	List<int> MyTestList;

	int check;
	do {
		system("cls");
		cout << "\tMenu";
		cout << "\n1 - Add element";
		cout << "\n2 - Remove element";
		cout << "\n3 - Edit element";
		cout << "\n4 - Show elements";
		cout << "\n5 - Debug mode";
		cout << "\n0 - Exit";

		cout << "\n\nВаш выбор: ";
		cin >> check;


		system("cls");
		int num;
		switch (check)
		{
		case 1:
			cout << "\nInput your num: ";
			cin >> num;
			MyTestList.add(num);
			cout << "\n\nInputing done\n\n";
			Sleep(2000);
			break;

		case 2:
			cout << "\nInput your num: ";
			cin >> num;
			MyTestList.remove(num);
			cout << "\n\nRemoving done\n\n";
			Sleep(2000);
			break;

		case 3:
			int id;
			cout << "\nInput id of this num: ";
			cin >> id;

			cout << "\nInput your num: ";
			cin >> num;

			MyTestList.changeElem(num,id);
			cout << "\n\nEditing done\n\n";
			Sleep(2000);
			break;

		case 4:
			MyTestList.show();
			system("pause");
			break;
		case 5:
			MyTestList.Debug();
			system("pause");
			break;
		}
	} while (check != 0);
}

