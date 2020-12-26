#include "Header.h"
#include <iostream>
#include <cmath>
#define PI 3.1415926
#define e 2.7182818
using namespace std;
infix::infix()
{
	reset_infix();
	size = 0;
}

infix::~infix()
{
	while (size)
	{
		pop_back();
	}
}

void infix::reset_infix()
{
	head = nullptr;
	tail = nullptr;
}

void infix::input()
{
	string input; bool flag = 1; double answer=0;
	infix prefix;
	while (flag)
	{
		cout << "Enter expression: ";
		getline(cin, input);
		if (transfer(input))
		{
			cout << "infix form: ";
			print();
			if (check())
			{
				Translationprefix(prefix);
				cout << "prefix form: ";
				prefix.print();
				if (prefix.count(answer))
				{
					cout <<"answer: "<< answer;
				}
			}
		}
		cout<<endl<< "Do you want to continue ? (1 - yes, 0 - no): ";
		cin >> flag;
		remove_all();
		prefix.remove_all();
		cin.ignore();
		answer = 0;
	}
}

bool infix::transfer(string index)
{
	for (int i = 0;i < index.size();i++)
	{
		if ((index[i] == '-')&&((i==0)||(index[i-1]=='(')))
			push_operator('&');
		else if (((index[i] >= 40) && (index[i] <= 43)) || (index[i] == 47) || (index[i] == 45) || (index[i] == 94))
			push_operator(index[i]);
		else if ((index[i] == 'c') && (index[i + 1] == 'o') && (index[i + 2] == 's'))//cos="c"
		{
			push_operator(index[i]);i += 2;
		}
		else if ((index[i] == 's') && (index[i + 1] == 'i') && (index[i + 2] == 'n'))//sin="s"
		{
			push_operator(index[i]);i += 2;
		}
		else if ((index[i] == 't') && (index[i + 1] == 'g'))//tg="t"
		{
			push_operator(index[i]);i += 1;
		}
		else if ((index[i] == 'c') && (index[i + 1] == 't') && (index[i + 2] == 'g'))//ctg="g"
		{
			push_operator(index[i+2]);i += 2;
		}
		else if ((index[i] == 'l') && (index[i + 1] == 'n'))//ln="l"
		{
			push_operator(index[i]);i += 1;
		}
		else if ((index[i] == 'l') && (index[i + 1] == 'o') && (index[i + 2] == 'g'))//log = "o"
		{
			push_operator(index[i+1]);i += 2;
		}
		else if ((index[i] == 's') && (index[i + 1] == 'q') && (index[i + 2] == 'r') && (index[i + 3] == 't'))//sqrt = "q"
		{
			push_operator(index[i + 1]);i += 3;
		}
		else if ((index[i] == '%'))//% = "%"
		{
			push_operator(index[i]);
		}
		else if ((index[i] == 'e'))
		{
			push_operand(e);
		}
		else if ((index[i] == 'p')&& (index[i+1] == 'i'))
		{
			push_operand(PI);
		}
		else if (((index[i] >= 48) && (index[i] <= 57)) || (index[i] == 46))
		{
			string number;
			while (((index[i] >= 48) && (index[i] <= 57)) || (index[i] == 46))
			{
				number.push_back(index[i]);
				i++;
			} 
			push_operand(stod(number));
			i--;
		}
		else
		{
			cout << "Error: Unknown symbol - '" << index[i] << "'" << endl;
			remove_all();
			return false;
		}
	}
	return true;
}

void infix::push_operator(char index)
{
	int priority;
	switch (index)
	{
	case('('):
		priority = 0;break;
	case(')'):
		priority = 0;break;
	case('+'):
		priority = 1;break;
	case('-'):
		priority = 1;break;
	case('*'):
		priority = 2;break;
	case('/'):
		priority = 2;break;
	case ('^'):
		priority = 3;break;
	case ('c'):
		priority = 4;break;
	case ('s'):
		priority = 4;break;
	case ('t'):
		priority = 4;break;
	case ('g'):
		priority = 4;break;
	case ('l'):
		priority = 4;break;
	case ('o'):
		priority = 4;break;
	case ('q'):
		priority = 4;break;
	case ('%'):
		priority = 4;break;
	case('&'):
		priority = 4;break;
	default:
			break;
	}
	if (size == 0)//We add the new element first.
	{
		head = new Element(NULL, index, priority);
		tail = head;
	}
	else//We add the new element last.
	{
		Element* current = new Element(NULL, index, priority);
		tail->next = current;
		current->prev = tail;
		tail = current;
	}
	size++;
}

void infix::push_front_operator(char index)
{
	int priority;
	switch (index)
	{
	case('('):
		priority = 0;break;
	case(')'):
		priority = 0;break;
	case('+'):
		priority = 1;break;
	case('-'):
		priority = 1;break;
	case('*'):
		priority = 2;break;
	case('/'):
		priority = 2;break;
	case ('^'):
		priority = 3;break;
	case ('c'):
		priority = 4;break;
	case ('s'):
		priority = 4;break;
	case ('t'):
		priority = 4;break;
	case ('g'):
		priority = 4;break;
	case ('l'):
		priority = 4;break;
	case ('o'):
		priority = 4;break;
	case ('q'):
		priority = 4;break;
	case ('%'):
		priority = 4;break;
	case('&'):
		priority = 4;break;
	default:
		break;
	}
	if (size == 0)//We add the new element first.
	{
		head = new Element(NULL, index, priority);
		tail = head;
	}
	else//We add the new element first.
	{
		Element* current = new Element(NULL, index, priority);
		head->prev = current;
		current->next = head;
		head = current;
	}
	size++;
}

void infix::push_operand(double number)
{
	if (size == 0)//We add the new element first.
	{
		head = new Element(number,NULL,-1);
		tail = head;
	}
	else//We add the new element last.
	{
		Element* current = new Element(number, NULL, -1);
		tail->next = current;
		current->prev = tail;
		tail = current;
	}
	size++;
}

void infix::push_front_operand(double number)
{
	if (size == 0)//We add the new element first.
	{
		head = new Element(number, NULL, -1);
		tail = head;
	}
	else//We add the new element first.
	{
		Element* current = new Element(number, NULL, -1);
		head->prev = current;
		current->next = head;
		head = current;
	}
	size++;
}

void infix::Translationprefix(infix& prefix)
{
	Stack stack;
	Element* current = tail;
	while (current)
	{
		if (current->operator1 == 41)
			stack.push_operator(current->operator1, current->priority);
		if (current->priority == -1)
			prefix.push_front_operand(current->operand);
		if (current->operator1 == 40)
		{
			while (stack.top_data() != 41)
			{
				prefix.push_front_operator(stack.top_data());
				stack.pop();
			}
			stack.pop();
		}
		if (current->priority >= 1)
		{
			while ((stack.empty())&&(stack.top_priority() > current->priority))
			{
				prefix.push_front_operator(stack.top_data());
				stack.pop();
			}
			stack.push_operator(current->operator1, current->priority);
		}
		current = current->prev;
	}
	while (stack.empty())
	{
		prefix.push_front_operator(stack.top_data());
		stack.pop();
	}
}

void infix::print()
{
	Element* current = head;
	while (current)
	{
		if (current->priority == -1)
			if (current->operand == PI)
				cout << "pi ";
			else if (current->operand == e)
				cout << "e ";
			else cout << current->operand<<" ";
		else if (current->priority == 4)
		{
			switch (current->operator1)
			{
			case ('c'):
				cout<<"cos ";break;
			case ('s'):
				cout << "sin ";break;
			case ('t'):
				cout << "tg ";break;
			case ('g'):
				cout << "ctg ";break;
			case ('l'):
				cout << "ln ";break;
			case ('o'):
				cout << "log ";break;
			case ('q'):
				cout << "sqrt ";break;
			case ('%'):
				cout << "%";break;
			case('&'):
				cout << "-";break;
			}
		}
		else cout << current->operator1 << " ";
		current = current->next;
	}
	cout << endl;
}

bool infix::count(double&answer)
{
	Element* current = head; bool flag=1;
	int i = 0;
	while((size!=1)&&(flag))
	{
		if ((current->priority == 4)&&(current->next->priority==-1))
		{
			switch (current->operator1)
			{
			case ('c'):
				answer = cos(current->next->operand * PI / 180);break;
			case ('s'):
				answer = sin(current->next->operand * PI / 180);break;
			case ('t'):
				answer = tan(current->next->operand * PI / 180);break;
			case ('g'):
				answer = 1 / tan(current->next->operand * PI / 180);break;
			case ('l'):
				if (current->next->operand <= 0)
				{
					flag = 0;
					cout << "Error: This logarithm is undefined - 'ln (" << current->next->operand << ")'";break;
				}
				else
				{
					answer = log(current->next->operand);break;
				}
			case ('o'):
				if (current->next->operand <= 0)
				{
					flag = 0;
					cout << "Error: This logarithm is undefined - 'log (" << current->next->operand << ")'";break;
				}
				else
				{
					answer = log10(current->next->operand);break;
				}
			case ('q'):
				if (current->next->operand < 0)
				{
					flag = 0;
					cout << "Error: This square root is undefined. - 'sqrt (" << current->next->operand << ")'";break;
				}
				else
				{
					answer = sqrt(current->next->operand);break;
				}
			case ('%'):
				answer=current->next->operand/100;break;
			case('&'):
				answer = current->next->operand * (-1);break;
			}
			if (flag)
			{
				current->next->operand = answer;
				remove(i);
				i = 0;
				current = head;
			}
		}
		else if ((current->priority == -1) && (current->next->priority == -1))
		{
			switch (current->prev->operator1)
			{
			case(43):
				answer=current->operand+current->next->operand;break;
			case(45):
				answer = current->operand - current->next->operand;break;
			case(42):
				answer = current->operand * current->next->operand;break;
			case(47):
				if (current->next->operand == 0)
				{
					flag = 0;
					cout << "Error: Division by zero!";break;
				}
				else
				{
					answer = current->operand / current->next->operand;break;
				}
			case (94):
				answer = pow(current->operand, current->next->operand);break;
			default:
				break;
			}
			if (flag)
			{
				current->operand = answer;
				remove(i + 1);
				remove(i - 1);
				i = 0;
				current = head;
			}
		}
		else
		{
			current = current->next;
			i++;
		}
	}
	return flag;
}

void infix::remove(size_t index)
{
	if (index >= size)
		throw out_of_range("The index is outside the list.");
	else if (index == 0)
		pop_front();
	else if (index == size - 1)
		pop_back();
	else
	{
		Element* current = head;
		for (int i = 0;i < index;i++)//We reach the desired element.
			current = current->next;
		current->prev->next = current->next;
		current->next->prev = current->prev;
		current->prev = nullptr;
		current->next = nullptr;
		delete current;
		size--;
	}
}

void infix::remove_all()
{
	while (size)
	{
		pop_back();
	}
}

void infix::pop_back()
{
	if (size == 0)return;//Exit the function.
	if (size == 1)//We remove the first element and reset the list.
	{
		delete head;
		reset_infix();
	}
	else
	{
		Element* current = tail->prev;
		current->next = nullptr;
		tail->prev = nullptr;
		delete tail;
		tail = current;
	}
	size--;
}

void infix::pop_front()
{
	if (size == 0) return;//Exit the function.
	if (size == 1)//We remove the first element and reset the list.
	{
		delete head;
		reset_infix();
	}
	else//We remove the first element
	{
		Element* current = head->next;
		current->prev = nullptr;
		head->next = nullptr;
		delete head;
		head = current;
	}
	size--;
}

bool infix::check() 
{
	Element* current = head;
	int sumrightbracket = 0, sumleftbracket = 0;
	for(int indexerror = 0;indexerror<size;indexerror++)
	{
		if (indexerror < size - 1)
		{
			if ((current->priority == -1) && (current->next->operator1 == '('))
			{
				cout << "Error: ";
				for (int i = 0;i < size;i++)
				{
					if (indexerror != i) cout << ". ";
					else
					{
						cout << current->operand << " " << current->next->operator1 << " ";
						i++;
					}
				}
				cout << "- (no operator)" << endl;
				return false;
			}
			else if ((current->operator1 == ')') && (current->next->priority == -1))
			{
				cout << "Error: ";
				for (int i = 0;i < size;i++)
				{
					if (indexerror != i) cout << ". ";
					else
					{
						cout << current->operator1 << " " << current->next->operand << " ";
						i++;
					}
				}
				cout << "- (no operator)" << endl;
				return false;
			}
			else if ((current->priority > 0) && (current->next->priority > 0) && (current->next->priority < 4))
			{
				cout << "Error: ";
				for (int i = 0;i < size;i++)
				{
					if (indexerror != i) cout << ". ";
					else
					{
						cout << current->operator1 << " " << current->next->operator1 << " ";
						i++;
					}
				}
				cout << "- (no operand)" << endl;
				return false;
			}
			else if ((current->operator1 == '(') && (current->next->operator1 == ')'))
			{
				cout << "Error: ";
				for (int i = 0;i < size;i++)
				{
					if (indexerror != i) cout << ". ";
					else
					{
						cout << current->operator1 << " " << current->next->operator1 << " ";
						i++;
					}
				}
				cout << "- (no operand)" << endl;
				return false;
			}
			else if ((current->operator1 == ')') && (current->next->operator1 == '('))
			{
				cout << "Error: ";
				for (int i = 0;i < size;i++)
				{
					if (indexerror != i) cout << ". ";
					else
					{
						cout << current->operator1 << " " << current->next->operator1 << " ";
						i++;
					}
				}
				cout << "- (no operator)" << endl;
				return false;
			}
		}
		if (current->operator1 == '(')
		{
			sumleftbracket++;
		}
		if (current->operator1 == ')')
		{
			sumrightbracket++;
		}
		current=current->next;
	}
	if (sumleftbracket != sumrightbracket)
	{
		cout << "Error: Unequal left and right parentheses.";
		return false;
	}
	return true;
}

infix::Stack::Stack()
{
	reset_stack();
	size = 0;
}

infix::Stack::~Stack()
{
	while (empty())
	{
		pop();
	}
}

void infix::Stack::reset_stack()
{
	head = nullptr;
	tail = nullptr;
}

void infix::Stack::push_operator(char Newelement, int priority)
{
	if (size == 0)//We add the new element first.
	{
		head = new Element(Newelement,priority);
		tail = head;
	}
	else//We add the new element last.
	{
		Element* current = new Element(Newelement,priority);
		tail->next = current;
		current->prev = tail;
		tail = current;
	}
	size++;
}

void infix::Stack::pop()
{
	if (size == 0)return;//Exit the function.
	if (size == 1)//We remove the first element and reset the list.
	{
		delete head;
		reset_stack();
	}
	else
	{
		Element* current = tail->prev;
		current->next = nullptr;
		tail->prev = nullptr;
		delete tail;
		tail = current;
	}
	size--;
}

int infix::Stack::top_data()
{
	return tail->data;
}

int infix::Stack::top_priority()
{
	return tail->priority;
}

bool infix::Stack::empty()
{
	if (size == NULL)
		return false;
	else
		return true;
}
