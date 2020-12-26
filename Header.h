#pragma once
#include <string>
using namespace std; 
	class infix
	{
	private:
		class Element
		{
		public:
			Element(double operand,char operator1, int priority, Element* next = nullptr, Element* prev = nullptr) {
				this->operand = operand;
				this->operator1 = operator1;
				this->priority = priority;
				this->next = next;
				this->prev = prev;
			};
			~Element() {};
			double operand;
			char operator1;
			int priority;
			Element* next;
			Element* prev;
		};
		Element* head;
		Element* tail;
		size_t size;
	public:
		infix();
		~infix();
		void reset_infix();
		void input();
		bool transfer(string);
		void push_operator(char);
		void push_front_operator(char);
		void push_operand(double);
		void push_front_operand(double);
		void Translationprefix(infix&);
		void print();
		bool count(double&);
		void remove(size_t);
		void remove_all();
		void pop_back(); // удаление последнего элемента
		void pop_front();
		bool check();
		class Stack
		{
		private:
			class Element
			{
			public:
				Element(char data, int priority, Element* next = nullptr, Element* prev = nullptr) {
					this->data = data;
					this->priority = priority;
					this->next = next;
					this->prev = prev;
				};
				~Element() {};
				char data;
				int priority;
				Element* next;
				Element* prev;
			};
			Element* head;
			Element* tail;
			size_t size;
		public:
			Stack();
			~Stack();
			void reset_stack();
			void push_operator(char,int); // добавление в конец списка
			void pop(); // удаление последнего элемент
			int top_data();
			int top_priority();
			bool empty();
		};
	};
	