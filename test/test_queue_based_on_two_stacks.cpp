#include "stack.h"
#include <gtest.h>

TEST(QueueByStacks, can_create_int_QueueByStacks)
{
	ASSERT_NO_THROW(QueueByStacks<> qbs(5));
}

TEST(QueueByStacks, can_create_double_QueueByStacks)
{
	ASSERT_NO_THROW(QueueByStacks<double> qbs(3));
}

TEST(QueueByStacks, correct_work_of_push_and_pop)
{
	QueueByStacks<> qbs(3);
	cin >> qbs;
	qbs.push(9);		cout << qbs.GetSize() << ' '<<qbs.first.GetSize() <<' ' <<qbs.second.GetSize()<< ' ' << ' ' << qbs << '\n';
	qbs.push(80);		cout << qbs.GetSize() << ' ' << qbs.first.GetSize() << ' ' << qbs.second.GetSize() << ' '<< ' ' << qbs << '\n';
	qbs.pop();			cout << qbs.GetSize() << ' ' << qbs.first.GetSize() << ' ' << qbs.second.GetSize() << ' ' << ' ' << qbs << '\n';
	qbs.push(95);			cout << qbs.GetSize() << ' ' << qbs.first.GetSize() << ' ' << qbs.second.GetSize() << ' ' << ' ' << qbs << '\n';
	qbs.push(-89);		cout << qbs.GetSize() << ' '<< qbs.first.GetSize() << ' ' << qbs.second.GetSize() << ' ' <<  ' ' << qbs << '\n';
	qbs.pop();		cout << qbs.GetSize() << ' ' << qbs.first.GetSize() << ' ' << qbs.second.GetSize() << ' ' <<  ' ' << qbs << '\n';
	qbs.push(-75);		cout << qbs.GetSize() << ' ' << qbs.first.GetSize() << ' ' << qbs.second.GetSize() << ' ' << ' ' << qbs << '\n';
	qbs.push(-29);		cout << qbs.GetSize() << ' ' << qbs.first.GetSize() << ' ' << qbs.second.GetSize() << ' ' << ' ' << qbs << '\n';
	//	cout << qbs.GetSize() << ' ' << qbs.GetCapacity() << ' ' << '\n' << qbs;
	EXPECT_EQ(7, qbs.GetSize());
}

TEST(QueueByStacks, throws_when_create_QueueByStacks_with_negative_length)
{
	ASSERT_ANY_THROW(QueueByStacks<int> qbs(-8));
}

TEST(QueueByStacks, can_do_push)
{
	QueueByStacks<> qbs(2);

	ASSERT_NO_THROW(qbs.push(-7));
}

TEST(QueueByStacks, can_return_front)
{
	QueueByStacks<> qbs;
	qbs.push(-4);
	qbs.push(12);
	qbs.push(7);

	cout << qbs << '\n';
	EXPECT_EQ(-4, qbs.front());
}

TEST(QueueByStacks, can_return_back)
{
	QueueByStacks<> qbs(3);	//0 0 0
	qbs.push(-4);		//0 0 0 -4
	qbs.push(12);		//0 0 0 -4 12
	qbs.push(7);		//0 0 0 -4 12 7

	cout << qbs << '\n';
	EXPECT_EQ(7, qbs.back());
}

TEST(QueueByStacks, can_do_pop_correctly)
{
	QueueByStacks<> qbs;
	qbs.push(-4);
	qbs.push(12);
	qbs.push(7);
	qbs.push(-82);
	qbs.pop();

	EXPECT_EQ(12, qbs.front());
	EXPECT_EQ(-82, qbs.back());
}

TEST(QueueByStacks, can_do_full_correctly)
{
	QueueByStacks<> qbs(998);		//size=998, очередь не полна
	qbs.push(-44);		//size=999, очередь не полна

	EXPECT_NE(true, qbs.full());

	qbs.push(7);			//size=1000, очередь полна

	EXPECT_EQ(true, qbs.full());
}

TEST(QueueByStacks, can_do_empty_correctly)
{
	QueueByStacks<> qbs;	//size=0
	qbs.push(-44);		//size=1
	qbs.push(7);			//size=2
	qbs.pop();			//size=1
	qbs.pop();			//size=0, очередь пуста

	EXPECT_EQ(true, qbs.empty());
}

TEST(QueueByStacks, can_get_size)
{
	QueueByStacks<> qbs;
	qbs.push(-44);
	qbs.push(-37);
	qbs.push(23);

	EXPECT_EQ(3, qbs.GetSize());

	qbs.pop();
	EXPECT_EQ(2, qbs.GetSize());
}

//Тест на capacity здесь не нужен: в нашей очереди на двух стеках capacity не используется
//Аналогично с тестами "can_do_resize_if_free_space_if_over" и "can_rid_member_if_too_mush_free_space"