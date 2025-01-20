#include <myQueue.h>
#include <gtest.h>

TEST(myQueue, can_create_queue_with_no_operands) {
	ASSERT_NO_THROW(myQueue<int> q());
}

TEST(myQueue, can_create_copied_queue) {
	myQueue<int> q;
	q.push(1);
	q.push(2);
	q.push(3);

	ASSERT_NO_THROW(myQueue<int> t(q));
}

TEST(myQueue, copied_queue_is_equal_to_source_one) {
	myQueue<int> q;
	q.push(1);
	q.push(2);
	q.push(3);

	myQueue<int> t = q;
	while (!q.isEmpty() || !t.isEmpty()) {
		EXPECT_EQ(q.back(), t.back());
	}
}

TEST(myQueue, copied_queue_has_its_own_memory) {
	myQueue<int> q;
	q.push(1);

	myQueue<int> t = q;
	t.back();
	EXPECT_EQ(q.isEmpty(), false);
}

TEST(myQueue, can_assign_queue_to_itself) {
	myQueue<int> q;
	q.push(1);
	q.push(2);
	q.push(3);

	ASSERT_NO_THROW(q = q);
}

TEST(myQueue, assign_queue_to_itself_is_correct) {
	myQueue<int> q;
	q.push(1);
	q.push(2);
	q.push(3);

	myQueue<int> t = q;
	q = q;

	while (!q.isEmpty() || !t.isEmpty()) {
		EXPECT_EQ(q.back(), t.back());
	}
}

TEST(myQueue, can_assign_queues) {
	myQueue<int> q;
	q.push(1);
	q.push(2);
	q.push(3);

	myQueue<int> t;

	ASSERT_NO_THROW(t = q);
}

TEST(myQueue, assign_queues_is_correct) {
	myQueue<int> q;
	q.push(1);
	q.push(2);
	q.push(3);

	myQueue<int> t;
	t = q;

	while (!q.isEmpty() || !t.isEmpty()) {
		EXPECT_EQ(q.back(), t.back());
	}
}

TEST(myQueue, newcreated_empty_queue_is_empty) {
	myQueue<int> q;
	EXPECT_EQ(q.isEmpty(), true);
}

TEST(myQueue, assign_changes_emptiness) {
	myQueue<int> q;
	q.push(1);
	q.push(2);
	q.push(3);

	myQueue<int> t;
	t = q;
	EXPECT_EQ(q.isEmpty(), false);
}

TEST(myQueue, isEmpty_returns_true) {
	myQueue<int> q;
	q.push(1);

	q.back();
	EXPECT_EQ(q.isEmpty(), true);
}

TEST(myQueue, isEmpty_returns_false) {
	myQueue<int> q;
	q.push(1);

	EXPECT_EQ(q.isEmpty(), false);
}

TEST(myQueue, clear_is_correct) {
	myQueue<int> q;
	q.push(1);
	q.push(2);
	q.push(3);

	q.clear();
	EXPECT_EQ(q.isEmpty(), true);
}

TEST(myQueue, can_get_last) {
	myQueue<int> q;
	q.push(1);
	q.push(2);
	q.push(3);

	EXPECT_EQ(q.back(), 1);
}

TEST(myQueue, can_push_and_back_element) {
	myQueue<int> q;
	q.push(0);
	q.push(1);
	q.push(2);
	q.push(3);
	q.push(4);
	q.push(5);

	int it = 0;
	while (!q.isEmpty()) {
		EXPECT_EQ(it++, q.back());
	}
}