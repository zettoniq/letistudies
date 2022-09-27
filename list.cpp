#include <iostream>
#include <vector>
#include <string>

using namespace std;

template <typename T>
class LinkedList
{
	/* Структура связного списка:
	head -> node_1 -> ... -> node_n -> nullptr
	head так же node, но самый первый
	Linked List[0] = head
	Linked List[1] = head.next
	Linked List[2] = head.next.next
	*/
private:
	//Узел списка, содержит данные и указатель на следующий элемент
	struct Node
	{
		T data;
		Node* next;
		Node(T data, Node* next = nullptr) : data(data), next(next)
		{
		}
	};
	Node* _head;
	unsigned _nodesCount;

	// Удаляет элемент, сохраняя целосность списка
	// previous = nullptr для удаления головного объекта
	void _remove_node(Node* node, Node* previous = nullptr)
	{
		if (node == nullptr) return;
		if (previous != nullptr)
			previous->next = node->next;
		else
			_head = node->next;
		delete node;
	}
	// Ищет элемент с начала списка по индексу
	// В стучае успеха возвращает указатель на него, иначе nullptr
	Node* _get_element(unsigned index)
	{
		if (index >= _nodesCount)
			return nullptr;
		Node* current = _head;
		unsigned i = 0;
		while (current != nullptr && i < index)
		{
			current = current->next;
			i++;
		}
		return current;
	}
	// Получает предыдущий Node
	// Возвращает указатель на него в случае успеха, иначе nullptr
	Node* _get_previous(Node* node)
	{
		Node* previousElement = nullptr;
		for (Node* startElement = _head;
			startElement != nullptr;
			startElement = startElement->next)
		{
			if (startElement == node)
				return previousElement;
			previousElement = startElement;
		}
		return nullptr;
	}
	// Ищет Node, данные в которой равны value
	// Возвращает указатель на него в случае успеха, иначе nullptr
	Node* _search(T value, Node* startElement = nullptr)
	{
		Node* current = startElement;
		if (startElement == nullptr)
			current = _head;
		for (; current != nullptr; current = current->next)
			if (current->data == value)
				return current;
		return nullptr;
	}

public:
	static unsigned const NOT_FOUND = ~0;
	LinkedList() : _head(nullptr), _nodesCount(0)
	{
	}

#pragma region Adding elements

	// Добавление элемента на указанную позицию
	void insert(unsigned pos, T element)
	{
		if (_nodesCount == 0)
			_head = new Node(element);
		else
		{
			if (pos == 0)
				_head = new Node(element, _head);
			else
			{
				Node* current = _get_element(pos - 1);
				current->next = new Node(element, current->next);
			}
		}
		_nodesCount++;
	}

	// Добавление элемента в конец списка
	void push_back(T element)
	{
		insert(_nodesCount, element);
	}

	// Добавление элемента в начало	списка
	void push_front(T element)
	{
		insert(0, element);
	}

#pragma endregion		 

#pragma region Methods remove

	// Удаление одного (первого) элемента по значению value
	// Вернёт true в случае успешного удаления, иначе false
	bool remove(T value)
	{
		Node* foundElem = _search(value);
		if (foundElem == nullptr)
			return false;
		_remove_node(foundElem, _get_previous(foundElem));
		_nodesCount--;
		return true;
	}

	// Удаление элемента на позиции pos
	// Вернёт true в случае успешного удаления, иначе false
	bool remove_at(unsigned pos)
	{
		if (pos >= _nodesCount)
			return false;
		if (pos == 0)
			_remove_node(_head);
		else
		{
			Node* previous = _get_element(pos - 1);
			if (previous == nullptr)
				return false;
			_remove_node(previous->next, previous);
		}
		_nodesCount--;
		return true;
	}

	// Удаление всех элементов со значением value
	// Вернёт количество удалённых элементов
	unsigned remove_all(T value)
	{
		unsigned count = 0;
		while (remove(value))
			count++;
		return count;
	}

#pragma endregion

#pragma region Methods find

	// Поиск одного элемента по значению
	// В случае успеха вернёт позицию первого элемента, иначе константу NOT_FOUND
	unsigned find(T value, unsigned start_pos = 0)
	{
		for (Node* current = _get_element(start_pos);
			current != nullptr;
			current = current->next, start_pos++)
			if (current->data == value)
				return start_pos;
		return NOT_FOUND;
	}

	// Поиск всех элементов со значением value
	// Вернёт список (vector<unsigned>) всех позиций найденных элементов
	vector<unsigned> find_all(T value)
	{
		vector<unsigned> founds = {};
		unsigned i = 0;
		do
		{
			i = find(value, i);
			if (i != NOT_FOUND)
				founds.push_back(i);
			else
				break;
		} while (i++ < _nodesCount);
		return founds;
	}

#pragma endregion

#pragma region Methods update


	// Изменяет значение первого найденного элемента old_value на new_value 
	bool update(T old_value, T new_value)
	{
		Node* current = _search(old_value);
		if (current == nullptr)
			return false;
		current->data = new_value;
		return true;
	}
	// Изменяет значение всех найденных вхождения old_value на new_value
	// Вернёт количество замен
	unsigned update_all(T old_value, T new_value)
	{
		unsigned i = 0;
		Node* current = nullptr;
		do
		{
			current = _search(old_value, current);
			if (current == nullptr)
				return i;
			current->data = new_value;
		} while (i++ < _nodesCount);
		return i;
	}

#pragma endregion

#pragma region Useful methods

	// Обмен местами элементов двух элементов
	void swap(unsigned firstIndex, unsigned secondIndex)
	{
		if (_nodesCount == 0)
			throw out_of_range("Ошибка! Список пуст!");
		if (firstIndex >= _nodesCount || secondIndex >= _nodesCount)
			throw out_of_range("Ошибка! Некорректный индекс!");
		T data = _get_element(firstIndex)->data;
		_get_element(firstIndex)->data = _get_element(secondIndex)->data;
		_get_element(secondIndex)->data = data;
	}

	// Возвращает количество элементов в списке
	unsigned size()
	{
		return _nodesCount;
	}

	// Оператор [] позволяет по индексу получить ссылку на элемент списка
	T& operator[](unsigned index)
	{
		Node* element = _get_element(index);
		if (element == nullptr)
			throw out_of_range("Ошибка, некорректно задан индекс!");
		return element->data;
	}

	// Выводит список на экран
	void print_all()
	{
		cout << "Список:" << endl;
		Node* current = _head;
		while (current != nullptr)
		{
			cout << current->data << endl; // вывод значения элемента
			current = current->next; // переход к следующему узлу
		}
		if (_nodesCount != 0)
			cout << endl;
	}

#pragma endregion

#pragma region Methods erase clear

	// Удаляет все элементы из диапазона [start..stop]
	// stopIndex индекс включается в диапазон
	void erase(unsigned startIndex, unsigned stopIndex)
	{
		if (_nodesCount == 0)
			return;
		if (stopIndex >= _nodesCount)
			throw out_of_range("Ошибка! Некорректно задан индекс!");
		while (startIndex <= stopIndex)
		{
			remove_at(startIndex);
			stopIndex--;
		}
	}

	// Удаляет все элементы начиная со start
	void erase(unsigned start)
	{
		erase(start, _nodesCount);
	}

	// Очищает весь список
	void clear()
	{
		erase(0);
	}

	// Очистка памяти, удаление списка
	~LinkedList()
	{
		clear();
	}

#pragma endregion

};

class Person
{
private:

	string _name;
	string _surname;

public:
	Person();

	Person(string surname, string name);

	// Сравнение двух экземпляров класса Person на равность
	bool operator==(Person& other);

	// Для копирования объектов
	Person& operator =(Person other);

	// Для вывода на консоль
	friend ostream& operator <<(ostream& out, Person& p);
};

Person::Person()
{
}

Person::Person(string surname, std::string name) : _name(name), _surname(surname)
{
}

bool Person::operator==(Person& other)
{
	return _name == other._name && _surname == other._surname;
}

Person& Person::operator =(Person other)
{
	if (this == &other)
		return *this;
	_name = other._name;
	_surname = other._surname;
	return *this;
}

ostream& operator <<(ostream& out, Person& p)
{
	return out << p._name << ' ' << p._surname;
}

unsigned SelectOption(string name, vector<string> options);
unsigned EnterPos(const string msg = "Введите позицию: ");
Person InputPerson();
void AddElement();
void RemoveElement();
void FindElement();
void UpdateElement();
void SwapElements();
void GetSize();
void test();

LinkedList<Person> list;

int main()
{
	setlocale(LC_ALL, "RUS");
	test();

	cout << endl;
	while (true)
	{
		switch (SelectOption("Список доступных действий:", {
			"Добавить элемент",
			"Удалить элемент",
			"Найти элемент",
			"Изменить элемент",
			"Поменять два элемента местами",
			"Вывести длину списка",
			"Вывести список",
			"Очистить список",
			"Завершить программу"
			}))
		{
		case 0:
			system("cls");
			break;

		case 1:
			AddElement();
			break;

		case 2:
			RemoveElement();
			break;

		case 3:
			FindElement();
			break;

		case 4:
			UpdateElement();
			break;

		case 5:
			SwapElements();
			break;

		case 6:
			cout << "Размер списка:\t" << list.size() << endl;
			break;

		case 7:
			list.print_all();
			break;

		case 8:
			list.clear();
			break;

		case 9:
			cout << "\nПрограмма завершила свою работу.";
			return 0;

		default:
			cout << "\n Некорректный ввод! Программа завершила свою работу.";
			return 0;
		}
		cout << endl;
	}
}

unsigned SelectOption(string description, vector<string> options)
{
	cout << description << endl;

	for (int i = 0; i < options.size(); i++)
		cout << '\t' << i + 1 << ".\t" << options[i] << endl;

	cout << "Ваш выбор: ";
	unsigned choise;
	cin >> choise;
	return choise;
}

unsigned EnterPos(const string msg)
{
	cout << msg;

	unsigned pos;
	cin >> pos;

	if (pos < 0 || pos >= list.size())
	{
		cout << "Некорретно указан индекс!\n";
		return list.NOT_FOUND;
	}
	return pos;
}

Person InputPerson()
{
	cout << "Введите имя и фамилию через пробел: ";
	string name, surname;
	cin >> name >> surname;
	Person person(surname, name);
	return person;
}

void AddElement()
{
	switch (SelectOption("Выберите место:", {
		"В начало",
		"В конец",
		"В произвольное место"
		}))
	{
	case 1:
		list.push_front(InputPerson());
		break;

	case 2:
		list.push_back(InputPerson());
		break;

	case 3:
		unsigned pos = EnterPos();
		if (pos != list.NOT_FOUND)
			list.insert(pos, InputPerson());
		break;
	}
}

void RemoveElement()
{
	switch (SelectOption("Удалить элемент:", {
		"Первый",
		"Последний",
		"По значению"
		}))
	{
	case 1:
		list.remove_at(0);
		break;

	case 2:
		list.remove_at(list.size() - 1);
		break;

	case 3:
		switch (SelectOption("Выберите количество удалений:", {
			"Только первое найденное значение",
			"Все найденные значения"
			}))
		{
		case 1:
			list.remove(InputPerson());
			break;

		case 2:
			list.remove_all(InputPerson());
			break;
		}
		break;
	}
}

void FindElement()
{
	unsigned nFound;
	vector<unsigned> founds;

	switch (SelectOption("Найти:", {
		"Первый",
		"Все"
		}))
	{
	case 1:
		nFound = list.find(InputPerson());
		if (nFound == list.NOT_FOUND)
		{
			cout << "Элемент не найден.\n";
			break;
		}
		cout << "Элемент найден в [" << nFound << "]\n";
		break;

	case 2:
		founds = list.find_all(InputPerson());
		if (founds.empty())
		{
			cout << "Элемент не найден.\n";
			break;
		}
		cout << "Элемент найден на позициях: ";

		for (auto& element : founds)
			cout << "[" << element << "] ";

		cout << endl;
		break;
	}
}

void UpdateElement()
{
	Person oldHuman, newHuman;
	switch (SelectOption("Изменить элемент по:", {
		"Значению",
		"Позиции"
		}))
	{
	case 1:
		cout << "\tСтарое значение\n";
		oldHuman = InputPerson();
		cout << "\tНовое значение\n";
		newHuman = InputPerson();

		switch (SelectOption("Количество замен:", {
			"Заменить первый",
			"Заменить все" }))
		{
		case 1:
			list.update(oldHuman, newHuman);
			break;

		case 2:
			list.update_all(oldHuman, newHuman);
			break;
		}
		break;

	case 2:
		unsigned pos = EnterPos();
		if (pos != list.NOT_FOUND)
			list[pos] = InputPerson();
		break;
	}
}

void SwapElements()
{
	unsigned pos1 = EnterPos("Введите первую позицию: ");
	if (pos1 == list.NOT_FOUND)
		return;

	unsigned pos2 = EnterPos("Введите вторую позицию: ");

	if (pos2 != list.NOT_FOUND)
		list.swap(pos1, pos2);
}

void GetSize()
{
	cout << "Размер списка:\t" << list.size() << endl;
}

void test()
{
	LinkedList<int> list1;
	list1.push_back(8);
	list1.push_back(860);
	list1.push_back(525);
	list1.push_front(111);
	list1.push_back(35);
	list1.push_front(123);
	list1.push_back(35);
	list1.push_front(456);
	list1.push_front(35);

	cout << "Начальный список. ";
	list1.print_all();

	cout << "Remove 860. ";
	list1.remove(860);
	list1.print_all();
	cout << "Количество элементов: " << list1.size() << endl << endl;

	list1.remove_all(35);
	cout << "Remove_all 35. ";
	list1.print_all();
	cout << "Количество элементов: " << list1.size() << endl << endl;

	list1.remove(35);
	cout << "Swap (0, list1.size() - 1). ";
	list1.swap(0, list.size() - 1);
	list1.print_all();

	cout << "Insert(2, 555). ";
	list1.insert(2, 555);
	list1.print_all();
	cout << "Количество элементов: " << list1.size() << endl << endl;

	cout << "insert(4, 667).";
	list1.insert(4, 667);
	list1.print_all();

	cout << "Количество элементов: " << list1.size() << endl << endl;

	auto count = list1.update_all(667, 0);
	cout << "list1.update_all(667, 0). ";
	list1.print_all();

	cout << "Количество замен: " << count << endl;
	cout << "Количество элементов: " << list1.size() << endl << endl;

	auto element = 0;
	list1.print_all();
	cout << "Позиция элемента " << element << " : " << list1.find(element) << endl;
	auto mas = list1.find_all(element);
	cout << "Позиция всех элементов " << element << " : ";
	for (auto& i : mas)
		cout << i << " ";
	cout << endl;

	list1.print_all();
	cout << "\nИзмение элементов по [0] и [1] на 1. ";
	list1[0] = 1;
	list1[1] = 1;
	list1.print_all();

	auto index = 1;
	cout << "Элемент с индексом " << index << " : " << list1[1] << endl;

	list1.print_all();
	cout << "\nТест++ и find для <int> : " << ++list1[list1.find(111)] << endl;
	list1.print_all();
}
