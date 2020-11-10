#include "stack.h"
#include <gtest.h>

TEST(Stack, can_create_int_stack)
{
	ASSERT_NO_THROW(Stack<> s(5));
}

TEST(Stack, can_create_double_stack)
{
	ASSERT_NO_THROW(Stack<double> s(2));
}

TEST(Stack, throws_when_create_stack_with_negative_length)
{
	ASSERT_ANY_THROW(Stack<int> s(-5));
}

TEST(Stack, can_do_push)
{
	Stack<> s(2);

	ASSERT_NO_THROW(s.push(-7));
}

TEST(Stack, can_return_top)
{
	Stack<> s(3);
	s.push(-4);
	s.push(12);
	s.push(7);

	EXPECT_EQ(7, s.top());
}

TEST(Stack, can_do_pop_correctly)
{
	Stack<> s(3);
	s.push(-4);
	s.push(12);
	s.push(7);
	s.pop();
	EXPECT_EQ(12, s.top());
}

TEST(Stack, can_do_full_correctly)
{
	Stack<> s(998);		//size=998, стек не полон
	s.push(-44);		//size=999, стек не полон

	EXPECT_NE(true, s.full());

	s.push(7);			//size=1000, стек полон

	EXPECT_EQ(true, s.full());
}

TEST(Stack, can_do_empty_correctly)
{
	Stack<> s;		//size=capacity=0
	s.push(-44);	//size=1, capacity=2
	s.push(7);		//size=2, capacity=2
	s.pop();		//size=1, capacity=2
	s.pop();		//size=0, capacity=2, стек пуст

	EXPECT_EQ(true, s.empty());
}

TEST(Stack, can_get_size)
{
	Stack<> s(4);

	EXPECT_EQ(4, s.GetSize());
}

TEST(Stack, can_get_capacity)
{
	Stack<> s(4);

	EXPECT_EQ(8, s.GetCapacity());
}

TEST(Stack, can_do_resize_if_free_space_if_over)
{
	Stack<> s(2);	//стек из элеметнов 0 0				size..2 capacity..4
	s.push(-14);	//стек из элеметнов 0 0 -14			size..3 capacity..4
	s.push(-97);	//стек из элеметнов 0 0 -14 -97		size..4 capacity..4		На следующем шаге при добавлении элемента должна вызываться перепаковка
	
	ASSERT_NO_THROW(s.push(85));		//стек стал из элеметнов 0 0 -14 -97 85		size..5 capacity..10
	
	EXPECT_EQ(5, s.GetSize());
	EXPECT_EQ(10, s.GetCapacity());
}

TEST(Stack, can_rid_member_if_too_mush_free_space)	//может освобождать память, если слишком много неиспользуемой памяти (если size много меньше capacity)
{
	Stack<> s(4);	//стек из элеметнов 0 0 0 0			size..4 capacity..8
	s.pop();		//стек из элеметнов 0 0 0			size..3 capacity..8		capacity пока меньше, чем 3 * size, всё в порядке
	s.pop();		//стек из элеметнов 0 0				size..2 capacity..8		capacity уже больше, чем 3 * size, будем уменьшать размер памяти 
										//должно стать 		size..2 capacity..4
	EXPECT_EQ(4, s.GetCapacity());
}

TEST(Stack, throw_when_stack_overflow)
{
	Stack<> s(999);		//создаётся стек, в нём лежит 999 нулей, size=999
	s.push(-88);		//норм, size станет равным 1000

	ASSERT_ANY_THROW(s.push(95));	//не норм, size должен стать 1001, что больше, чем MAX_VECTOR_SIZE
}
