#include <iomanip>
#include <iostream>
#include <stack>
#include <string>

using namespace std;

class Stack {
	int* arr;
	int top;
	int capacity;
public:
	Stack(int size) {
		arr = new int[size];
		capacity = size;
		top = -1;
	}
	~Stack() {
		delete[] arr;
	}
	bool isValid(string s) {
		stack<char> st;
		if (s.size() == 0) {
			return true;
		}
		int i = 0;
		while (i < s.size()) {
			if (s[i] == '(' || s[i] == '[' || s[i] == '{') {
				st.push(s[i]);
			}
			else if ((s[i] == ')' && !st.empty() && st.top() == '(') ||
				(s[i] == '}' && !st.empty() && st.top() == '{') ||
				(s[i] == ']' && !st.empty() && st.top() == '[')
				) {
				st.pop();
			}
			else {
				return false;
			}
			i++;
		}
		if (st.empty()) {
			return true;
		}
		return false;
	}
	bool isFull() {
		return top == capacity - 1;
	}
	void push(int x) {
		if (isFull())
		{
			cout << "Стек переполнен";
		}
		else {
			cout << "Вставляем " << x << endl;
			arr[++top] = x;
		}
	}

	int pop() {
		if (isEmpty())
		{
			cout << "Стек пустой";
		}
		else {
			cout << "Removing " << peek() << endl;
			return arr[top--];
		}
	}
	int peek() {
		if (!isEmpty()) {
			return arr[top];
		}
		else {
			cout << "Стек пустой, невозможно определить первый элемент";
		}
	}
	bool isEmpty() {
		return top == -1;
	}

};
class dynMass {
private:
	int* mass;
	int massSize;
	void Create() {
		mass = new int[massSize];
		for (int i = 0; i < massSize; i++) {
			mass[i] = rand() % 11;
		}
	}
public:
	dynMass() {
		int amount;
		cin >> amount;
		massSize = amount;
		Create();
	}
	void massOutput() {
		for (int i = 0; i < massSize; i++) {
			cout << mass[i] << " ";
		}
	}
	int size() {
		return massSize;
	}
	bool isEmpty() {
		if (massSize == 0) {
			return true;
		}
		else return false;
	}
	void add(int index, int elementToPaste) // функция для вставки элемента в массив по заданному индексу
	{
		if (index > massSize + 1) {
			cout << "Выход за пределы массива, вставка невозможна";
			
		}
		else {
			int newSize = massSize + 1;
			int* new_arr = new int[massSize + 1];

			for (int i = 0; i < index; i++)
				new_arr[i] = mass[i];
			new_arr[index] = elementToPaste;

			for (int i = index + 1; i < massSize + 1; i++)
				new_arr[i] = mass[i - 1];

			massSize++;

			delete[] mass;
			mass = new_arr;
		}
	}
	int get(int index) {
		if (index <0 || index>massSize) { cout << "Невозможно найти индекс, т.к он меньше 0 или превышает размеры массива"; return false; }
		else return mass[index];
	}
	void set(int index, int newElem) {
		if (index<0 || index>=massSize) { cout << "Невозможно найти индекс, т.к он меньше 0 или превышает размеры массива";}
		else {
			mass[index] = newElem;
		}
	}
	bool count(int toFind) {
		for (int i = 0; i < massSize; i++) {
			if (mass[i] == toFind) {
				cout << "Элемент найден под индексом: " << i;
				return true;
			}
		} 
		cout << "Элемент не удалось обнаружить";
		return false;
	}
	void clear() { // По поводу реализации этого метода завис. Можно либо занулять все элементы, либо просто удалить массив. Я удалил.
		delete[] mass;
	}
	void bubbleSort()
	{
		int amount = massSize;
		while (amount--)
		{
			bool swapped = false;

			for (int i = 0; i < amount; i++)
			{
				if (mass[i] > mass[i + 1])
				{
					swap(mass[i], mass[i + 1]);
					swapped = true;
				}
			}

			if (swapped == false)
				break;
		}
	}
};
void callDynMass (dynMass myMass) {
	int toAdd, placeToAdd, index, newElem, toFind;
	cout << "Исходный массив: ";
	myMass.massOutput();
	cout << endl;
	cout << "Размер массива: ";
	cout << myMass.size();
	cout << endl;
	cout << "Проверка массива на пустоту. Если массив заполненный - выводит 0, пустой - выводит 1: ";
	cout << myMass.isEmpty();
	cout << endl;
	cout << "Добавление элемента в массив по заданноу индексу" << endl;
	cout << "Первым значением введите куда вставить, вторым значением что: ";
	cin >> placeToAdd >> toAdd;
	myMass.add(placeToAdd, toAdd);
	cout << endl;
	cout << "Вывод массива после вставки элементов: ";
	myMass.massOutput();
	cout << endl;
	cout << "Вывод элемента по индексу, введите индекс, элемент по которому вы хотите найти: ";
	cin >> index;
	cout << "Найденный элемент:" << myMass.get(index);
	cout << endl;
	cout << "Введите индекс элемента, который хотите заменить: ";
	cin >> index;
	cout << endl;
	cout << "Введите элемент, на который хотите заменить: ";
	cin >> newElem;
	cout << endl;
	myMass.set(index, newElem);
	cout << "Получившийся массив: "; 
	myMass.massOutput();
	cout << endl;
	cout << "Введите элемент, который желаете найти в массиве: ";
	cin >> toFind;
	myMass.count(toFind);
	cout << endl;
	myMass.bubbleSort();
	myMass.massOutput();
}
void calculating(char* OPZSTR, int len)
{
	string answer;
	float stack[100];
	// sp = index where number will be pushed //индекс ячейки, куда будет push-иться очередное число
	int sp = 0;      // (sp-1) = HEAD index of stack //индекс ячейки, являющейся вершиной стека
	for (int j = 0; j <= len; j++) {
		char c = OPZSTR[j];
		if (c == 'x')
			break;
		else if (c == ' ' || c == '\n' || c == NULL)
			continue;

		else if (c == '+') {
			stack[sp - 2] = stack[sp - 2] + stack[sp - 1];
			sp--;
			continue;
		}
		else if (c == '-') {
			stack[sp - 2] = stack[sp - 2] - stack[sp - 1];
			sp--;
			continue;
		}
		else if (c == '*') {
			stack[sp - 2] = stack[sp - 1] * stack[sp - 2];
			sp--;
			continue;
		}
		else if (c == '/') {
			stack[sp - 2] = stack[sp - 2] / stack[sp - 1];
			sp--;
			continue;
		}

		else {
			for (int y = j; y < len; y++) { //revewing current RPNstring from j //просматриваем текущую строку начиная j
				if (isdigit(OPZSTR[y]) || OPZSTR[y] == ',') {//if RPNstring contains number or comma //если элемент строки число или запятая
					answer += OPZSTR[y]; //add this element to an answer string //вносим элемент строки в выходную строку
				}
				else {
					j = y; //else end reviewing //иначе заканчиваем просмотр строки
					break;
				}
			}
			stack[sp] = stof(answer);  //input our answer string in to stack of answers, converting to float //в стэк ответов заносим нашу выходную строку переведённую в тип float
			sp++;
			answer.clear(); //clearing answer string // очищаем выходную строку
		}
	}

	cout << endl;
	cout << "Result= " << stack[sp - 1] << endl;
}
void callCalc()
{

	//setlocale(LC_ALL, "Russian");
	int i = 0, s = 0, e = 0;
	char vr[100], stek[100], exit[100];

	cin >> vr;
	for (i = 0; vr[i] != '\0'; i++)
		switch (vr[i])
		{
		case '+':
			while ((s != 0) && (stek[s - 1] != '('))
			{
				exit[e] = stek[s - 1]; //to exit //на выход 
				e++;
				s--;
			}
			stek[s] = '+'; //to stack //в стек 
			s++;
			break;

		case '-':
			while ((s != 0) && (stek[s - 1] != '('))
			{
				exit[e] = stek[s - 1];
				e++;
				s--;
			}
			stek[s] = '-';
			s++;
			break;
		case '*':

			while ((s != 0) && (stek[s - 1] != '(') && (stek[s - 1] != '+') && (stek[s - 1] != '-'))
			{
				exit[e] = stek[s - 1];
				e++;
				s--;
			}
			stek[s] = '*';
			s++;
			break;
		case '/':

			while ((s != 0) && (stek[s - 1] != '(') && (stek[s - 1] != '+') && (stek[s - 1] != '-'))
			{
				exit[e] = stek[s - 1];
				e++;
				s--;
			}
			stek[s] = '/';
			s++;

			break;
		case '(':
		{
			stek[s] = '(';
			s++;
			break; }
		case ')':

			while ((stek[s - 1] != '(') && (s != 0))
			{
				exit[e] = stek[s - 1];
				e++;
				s--;
			}
			stek[s - 1] = ' ';
			s--;
			break;


		default:

		{
			exit[e] = vr[i];
			e++;
			if ((vr[i + 1] == '+') ||
				(vr[i + 1] == '-') ||
				(vr[i + 1] == '*') ||
				(vr[i + 1] == '/') ||
				(vr[i + 1] == '(') ||
				(vr[i + 1] == ')'))
			{
				exit[e] = ' ';
				e++;
			}
		}
		}

	exit[e] = ' ';
	e++;

	while (s != 0)
	{
		exit[e] = stek[s - 1];
		e++;
		s--;
	}
	cout << "RPN: "; //cout << "ОПН: ";
	exit[e] = 'x';
	for (i = 0; i < e; i++)
	{
		cout << exit[i];
	}
	calculating(exit, i); // calculating // считаем

}

int main()
{
	setlocale(LC_ALL, "rus");
	//dynMass myMass;
	//callDynMass(myMass);
}
