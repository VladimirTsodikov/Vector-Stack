#pragma once
#include <iostream>
using namespace std;

#define FACTOR 2	//множитель
#define FACTOR_LOW 3	//коэффициент, который нужен чтобы понять, насколько большое значение capacity относительно size 

template <class ValType = int>
class Vector
{
protected:
	ValType* data;
	size_t size;	//сколько элементов лежит в векторе с точки зрения пользователя
	size_t	capacity;	//реальльный размер вектора, вместе с запасной вместимостью
public:
	Vector();					//конструктор по умолчанию
	Vector(int passed_size);	//конструктор с параметром
	Vector(const Vector& v);	//конструктор копирования
	~Vector();					//деструктор

	void push_back(ValType elem);	//добавить в конец вектора ещё один элемент - elem
	void pop_back();	//удалить последний элемент из вектора
	void push_front(ValType elem);	//добавить в конец вектора ещё один элемент - elem
	void pop_front();	//удалить последний элемент из вектора

	void resize(int n);	//Оставляет в векторе n первых элементов. Если вектор содержит больше элементов, то его размер усекается до n элементов
						//Если размер вектора меньше n, то добавляются недостающие элементы и инициализируются значением по умолчанию
	void free_up_space();	//Если capacity в процессе работы стало намного больше, чем size, уменьшает значение capacity, освобождает неиспользуемую память

	int GetSize() { return size; }
	int GetCapacity() { return capacity; }

	ValType& operator[] (int index);	//возвращает само число, то есть ссылку на него, изменять будем само значение в ячейке. Например, v[5]=4;
	ValType operator[] (int index) const;	//возвращает значение хранящегося в ячейке числа. Чтобы, например, int k=v[5];

	void insert(ValType elem, int index);		// вставляет элемент elem на позицию, на которую указывает итератор index
	void erase(int index);		//удаляет элемент, на который указывает итератор index

	  // ввод-вывод
	friend istream& operator>>(istream& in, Vector& v)
	{
		for (int i = 0; i < v.size; i++)
			in >> v.data[i];
		return in;
	}
	friend ostream& operator<<(ostream& out, const Vector& v)
	{
		if (v.data != nullptr)
			for (int i = 0; i < v.size; i++)
				out << v.data[i] << ' ';
		return out;
	}
};

template <class ValType>	//конструктор по умолчанию
Vector<ValType>::Vector()
{
	data = nullptr;	//указатель равен нулю
	size = 0;
	capacity = 0;
}

template <class ValType>	//конструктор с параметром
Vector<ValType>::Vector(int passed_size)
{
	if (passed_size > 0)
	{
		data = new ValType[passed_size * FACTOR];
		size = passed_size;
		capacity = passed_size * FACTOR;
		for (int i = 0; i < size; i++)
			data[i] = 0;
	}
	else throw "Incorrect Vector's Size";
}

template <class ValType>	//конструктор копирования
Vector<ValType>::Vector(const Vector& v)
{
	size = v.size;
	capacity = v.capacity;
	data = new ValType[v.capacity];
	if (data != nullptr)
		for (int i = 0; i < v.size; i++)
			data[i] = v.data[i];
}

template <class ValType>	//деструктор
Vector<ValType>::~Vector()
{
	delete[] data;
	data = nullptr;	//остальные поля удалятся сами
}

template <class ValType>
void Vector<ValType>::push_back(ValType elem)
{
	resize(size + 1);		//размерность вектора стала size+1, самая правая ячейка - data[(size+1)-1]. Т.к. стало size=size+1, то самая правая ячейка - это data[size-1]
	data[size - 1] = elem;
	/* рабочее!
	if (size < capacity)	//если есть ещё место в конце нашего вектора, то дописываем туда
	{
		data[size] = elem;		//т.к. до сих пор заняты места от нуля до size-1 - всего ровно size штук.
		size++;
	}
	else
	{
		capacity = size * FACTOR;
		ValType* tmp = new ValType[capacity];
		for (int i = 0; i < size; i++)
			tmp[i] = data[i];
		delete[] data;
		data = tmp;
		data[size] = elem;
		size++;
	}
	*/
}

template <class ValType>
void Vector<ValType>::pop_back()	//удаляет последний элемент из вектора
{
	if (size > 0)
	{
		data[size - 1] = 0;	//присвоили значение по умолчанию, но в целом оно больше не используется
		size--;
		free_up_space(); //освободить память, если capacity много больше size
	}
	else throw "Vector size is not pozitive";
}

template <class ValType>
void Vector<ValType>::push_front(ValType elem)	//добавляет элемент в начало вектора
{
	resize(size + 1);
	for (int i = size - 2; i >= 0; i--)
		data[i + 1] = data[i];
	data[0] = elem;
	/*	рабочее!
	if (size < capacity)	//если есть ещё место в конце нашего вектора, то дописываем туда
	{
		for(int i=size-1; i>=0; i--)
			data[i + 1] = data[i];
		data[0] = elem;
		size++;
	}
	else
	{
		capacity = size * FACTOR;
		ValType* tmp = new ValType[capacity];
		for (int i = 0; i < size; i++)
			tmp[i+1] = data[i];		//копируем уже со сдвигом, освобождаем нулевую ячейку в tmp. Проблем с записью в tmp[(size-1)+1] не будет,
		tmp[0] = elem;											//т.к. размер у tmp не size, а capacity. Capacity больше size (если FACTOR>1)
		delete[] data;
		data = tmp;
		size++;
	}
	*/
}

template <class ValType>
void Vector<ValType>::pop_front()	//удаляет первый элемент из вектора	
{
	if (size > 1)
	{
		for (int i = 0; i < size - 1; i++)
			data[i] = data[i + 1];
		data[size - 1] = 0;	//присвоили значение по умолчанию, но в целом оно больше не используется
		size--;	//значение capacity сохраняется
		free_up_space();	//освободить память, если capacity много больше size
			//более красиво было бы просто сместить указатель data = (data + 1);  но тогда потери памяти слева
	}
	else if (size == 1)
		data = nullptr;
	else throw "Vector size is already not pozitive";
}

template <class ValType>
void Vector<ValType>::resize(int n)	//Оставляет в векторе n первых элементов. Если вектор содержит больше элементов, то его размер усекается до n элементов
{									//Если размер вектора меньше n, то добавляются недостающие элементы и инициализируются значением по умолчанию (нулём)
	if (n > 0)
	{
		if (n <= size)	//ничего не добавляем по памяти, просто ограничиваем выводимый размер. Значение capacity сохраняется
			size = n;				//сюда free_up_space не вставляем, т.к. само по себе урезание размера вектора ни о чём не говорит.
		else						//Возможно, далее пользователь будет заново вводить много чисел. Если же будет удалять, сработает проверка в функциях удаления
		{
			if (n <= capacity)	//т.е. если size < n <= capacity. Значение capacity сохраняется
			{
				for (int i = size; i < n; i++)
					data[i] = 0;
				size = n;
			}
			else	//т.е. если  n > capacity
			{
				ValType* tmp = new ValType[n * FACTOR];
				for (int i = 0; i < size; i++)
					tmp[i] = data[i];
				for (int i = size; i < n; i++)
					tmp[i] = 0;
				if (data != nullptr) 
					delete[] data;
				data = tmp;
				size = n;
				capacity = n * FACTOR;
			}
		}
	}
	else throw "Incorrect Vector's Size";
}

template <class ValType>
void Vector<ValType>::free_up_space()	//Если capacity в процессе работы стало намного больше, чем size (в три раза), уменьшает значение capacity
{
	if (capacity >= FACTOR_LOW * size)
	{
		capacity = size * FACTOR;		//Значение size сохраняется
		ValType* tmp = new ValType[capacity];
		for (int i = 0; i < size; i++)
			tmp[i] = data[i];
		delete[] data;
		data = tmp;
	}
}

template <class ValType>
ValType& Vector<ValType>::operator[](int index)
{
	if (index < size && index>0)
		return data[index];
	else throw "Incorrect position number";
}

template <class ValType>
ValType Vector<ValType>::operator[] (int index) const
{
	if (index < size && index>0)
	{
		ValType tmp = data[index];
		return ValType;
	}
	else throw "Incorrect position number";
}

template <class ValType>
void Vector<ValType>::insert(ValType elem, int index)	// вставляет элемент elem на позицию, на которую указывает итератор index
{
	if (index <= size && index >= 0)
	{
		this->resize(size + 1);
		for (int i = size - 1; i >= index; i--)
			data[i + 1] = data[i];
		data[index] = elem;
	}
	else throw "Incorrect Vector's Index";
}

template <class ValType>
void Vector<ValType>::erase(int index)	//удаляет элемент, на который указывает итератор p
{
	if (index < size && index >= 0)		//т.к. сама ячейка data[size] не входит в данный вектор 
	{
		for (int i = index; i < size - 1; i++)
			data[i] = data[i + 1];
		data[size - 1] = 0;//значение по умолчанию
		size--;	//размер уменьшился, элемент data[size - 1] в общем-то не рассматриваем. Capacity сохранилось 
		free_up_space();	//освободить память, если capacity много больше size
	}
	else throw "Incorrect Vector's Index";
}

template <class ValType = int>
class Stack : public Vector<ValType>
{
public:
	Stack() : Vector() {}
	Stack(int passed_value) : Vector(passed_value) {}
	Stack(const Stack& v) : Vector(v) {}
	~Stack() {}

	ValType top()		//возвращает значение верхнего элемента стека
	{
		return data[size - 1];
	}
	void push(ValType elem) //помещает на верх стека значение elem
	{	
		push_back(elem);
	}	
	void pop() 	//удаляет верхнее значение стека
	{
		pop_back();
	}
	bool empty() 	//возвращает true, если стек пуст
	{
		bool flag = false;
		if (size == 0)
			flag = true;
		return flag;

	}
	bool full() 	//возвращает true, если стек полон
	{
		bool flag = false;
		if (size == capacity)
			flag = true;
		return flag;
	}
	//узнать size и capacity стека можно из соответствующих Get функций вектора

private:	//реализацию функций, которые есть в векторе, но не должно быть в стеке, помещаем в private без инициализации, к ним нельзя будет обратиться
	void push_front(ValType elem) {}
	void pop_front(ValType elem) {}
	ValType& operator[] (int index) {}
	ValType operator[] (int index) const {}
	void insert(ValType elem, int index) {}
	void erase(int index) {}
};