#include "vector.hpp"
#include <gtest/gtest.h>

TEST(Vector, DefaultConstructor) {
	VBek::Vector<int> vector;
	EXPECT_EQ(vector.size(), 0);
}

TEST(Vector, PushBack) {
	VBek::Vector<int> vector;
	vector.push_back(100);
	EXPECT_EQ(vector.size(), 1);
	EXPECT_EQ(vector[0], 100);
}

TEST(Vector, HasItem) {
	VBek::Vector<int> vector;
	vector.push_back(100);
	EXPECT_TRUE(vector.has_item(100));
	EXPECT_FALSE(vector.has_item(5));
}

TEST(Vector, Insert) {
	VBek::Vector<int> vector;
	vector.push_back(100);
	vector.push_back(5);
	EXPECT_TRUE(vector.insert(1, 99));
	EXPECT_EQ(vector.size(), 3);
	EXPECT_EQ(vector[1], 99);
}

TEST(Vector, RemoveFirst) {
	VBek::Vector<int> vector;
	vector.push_back(100);
	vector.push_back(5);
	EXPECT_TRUE(vector.remove_first(100));
	EXPECT_EQ(vector.size(), 1);
	EXPECT_EQ(vector[0], 5);
}

TEST(Vector, RemoveFirstNotFound) {
	VBek::Vector<int> vector;
	vector.push_back(100);
	vector.push_back(5);
	EXPECT_FALSE(vector.remove_first(1));
	EXPECT_EQ(vector.size(), 2);
}

int main(int argc, char** argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}