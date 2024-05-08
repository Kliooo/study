#include <gtest/gtest.h>

#include "doubly_linked_list.hpp"

TEST(DoublyLinkedList, PushBack) {
    VBek::DoublyLinkedList<int> list;
    list.push_back(100);
    EXPECT_EQ(list.size(), 1);
}

TEST(DoublyLinkedList, HasItem) {
    VBek::DoublyLinkedList<int> list;
    list.push_back(100);
    EXPECT_TRUE(list.has_item(100));
    EXPECT_FALSE(list.has_item(5));
}

TEST(DoublyLinkedList, RemoveFirst) {
    VBek::DoublyLinkedList<int> list;
    list.push_back(100);
    list.push_back(5);
    EXPECT_TRUE(list.remove_first(100));
    EXPECT_EQ(list.size(), 1);
    EXPECT_FALSE(list.size() == 0);
    EXPECT_FALSE(list.size() == 2);
}

TEST(DoublyLinkedList, RemoveFirstNotFound) {
    VBek::DoublyLinkedList<int> list;
    list.push_back(100);
    list.push_back(5);
    EXPECT_FALSE(list.remove_first(1));
    EXPECT_EQ(list.size(), 2);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
