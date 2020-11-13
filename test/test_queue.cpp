#include "stack.h"
#include <gtest.h>

TEST(Queue, can_create_int_queue)
{
	ASSERT_NO_THROW(Queue<> q(5));
}

TEST(Queue, can_create_double_queue)
{
	ASSERT_NO_THROW(Queue<double> q(3));
}

TEST(Queue, correct_work_of_push_and_pop)
{
	Queue<> q(3);
	cin >> q;
	q.push(9);		cout << q.GetSize() << ' ' << q.GetCapacity() << ' ' << q.GetStart() << ' ' << q.GetEnd() << ' ' << ' ' << q << '\n';
	q.push(80);		cout << q.GetSize() << ' ' << q.GetCapacity() << ' ' << q.GetStart() << ' ' << q.GetEnd() << ' ' << ' ' << q << '\n';
	q.pop();			cout << q.GetSize() << ' ' << q.GetCapacity() << ' ' << q.GetStart() << ' ' << q.GetEnd() << ' ' << ' ' << q << '\n';
	q.push(95);			cout << q.GetSize() << ' ' << q.GetCapacity() << ' ' << q.GetStart() << ' ' << q.GetEnd() << ' ' << ' ' << q << '\n';
	q.push(-89);		cout << q.GetSize() << ' ' << q.GetCapacity() << ' ' << q.GetStart() << ' ' << q.GetEnd() << ' ' << ' ' << q << '\n';
	q.pop();		cout << q.GetSize() << ' ' << q.GetCapacity() << ' ' << q.GetStart() << ' ' << q.GetEnd() << ' ' << ' ' << q << '\n';
	q.push(-75);		cout << q.GetSize() << ' ' << q.GetCapacity() << ' ' << q.GetStart() << ' ' << q.GetEnd() << ' ' << ' ' << q << '\n';
	q.push(-29);		cout << q.GetSize() << ' ' << q.GetCapacity() << ' ' << q.GetStart() << ' ' << q.GetEnd() << ' ' << ' ' << q << '\n';
//	cout << q.GetSize() << ' ' << q.GetCapacity() << ' ' << '\n' << q;
	EXPECT_EQ(7, q.GetSize());
}

TEST(Queue, throws_when_create_queue_with_negative_length)
{
	ASSERT_ANY_THROW(Queue<int> q(-8));
}

TEST(Queue, can_do_push)
{
	Queue<> q(2);

	ASSERT_NO_THROW(q.push(-7));
}

TEST(Queue, can_return_front)
{
	Queue<> q;
	q.push(-4);
	q.push(12);
	q.push(7);

	cout << q << '\n';
	EXPECT_EQ(-4, q.front());
}

TEST(Queue, can_return_back)
{
	Queue<> q(3);	//size=0; capacity=0
	q.push(-4);		//size=1; capacity=2
	q.push(12);		//size=2; capacity=2
	q.push(7);		//size=3; capacity=6	тут вызывается перепаковка. Порядок элементов будет сохранён, start как был равен 0, так и останется

	cout << q << '\n';
	EXPECT_EQ(7, q.back());
}

TEST(Queue, can_do_pop_correctly)
{
	Queue<> q;
	q.push(-4);
	q.push(12);
	q.push(7);
	q.push(-82);
	q.pop();

	EXPECT_EQ(12,q.front());
	EXPECT_EQ(-82, q.back());
}

TEST(Queue, can_do_full_correctly)
{
	Queue<> q(998);		//size=998, стек не полон
	q.push(-44);		//size=999, стек не полон

	EXPECT_NE(true, q.full());

	q.push(7);			//size=1000, стек полон

	EXPECT_EQ(true, q.full());
}

TEST(Queue, can_do_empty_correctly)
{
	Queue<> q;		//size=capacity=0
	q.push(-44);	//size=1, capacity=2
	q.push(7);		//size=2, capacity=2
	q.pop();		//size=1, capacity=2
	q.pop();		//size=0, capacity=2, очередь пуста

	EXPECT_EQ(true, q.empty());
}

TEST(Queue, can_get_size)
{
	Queue<> q;
	q.push(-44);
	q.push(-37);
	q.push(23);

	EXPECT_EQ(3, q.GetSize());
}

TEST(Queue, can_get_capacity)
{
	Queue<> q;			//size=0; capacity=0
	q.push(-44);		//size=1; capacity=2
	q.push(-37);		//size=2; capacity=2
	q.push(23);			//size=3; capacity=6

	EXPECT_EQ(6, q.GetCapacity());
}

TEST(Queue, can_do_resize_if_free_space_if_over)
{
	Queue<> q(2);	//очередь из элеметнов 0 0				size..2 capacity..4
	q.push(-14);	//очередь из элеметнов 0 0 -14			size..3 capacity..4
	q.push(-97);	//очередь из элеметнов 0 0 -14 -97		size..4 capacity..4		На следующем шаге при добавлении элемента должна вызываться перепаковка
	
	ASSERT_NO_THROW(q.push(85));		//очередь стала из элеметнов 0 0 -14 -97 85		size..5 capacity..10
	
	EXPECT_EQ(5, q.GetSize());
	EXPECT_EQ(10, q.GetCapacity());
}

TEST(Queue, can_rid_member_if_too_mush_free_space)	//может освобождать память, если слишком много неиспользуемой памяти (если size много меньше capacity)
{
	Queue<> q(4);	cout << q << '\n';//очередь из элеметнов 0 0 0 0			size..4 capacity..8
	q.pop();	cout << q << '\n';	//очередь из элеметнов 0 0 0			size..3 capacity..8		capacity пока меньше, чем 3 * size, всё в порядке
	q.pop();	cout << q << '\n';	//очередь из элеметнов 0 0				size..2 capacity..8		capacity уже больше, чем 3 * size, будем уменьшать размер памяти 
										//должно стать 		size..2 capacity..4
	EXPECT_EQ(4, q.GetCapacity());
}