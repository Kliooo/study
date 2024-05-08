#include "doubly_linked_list.hpp"

namespace VBek {

    template <typename T>
    DoublyLinkedList<T>::~DoublyLinkedList() noexcept {
        Node* current = begin;
        while (current != nullptr) {
            Node* next = current->next;
            delete current;
            current = next;
        }
    }

    template <typename T>
    void DoublyLinkedList<T>::push_back(const T& value) noexcept {
        Node* new_node = new Node(value);
        if (begin == nullptr) {
            begin = new_node;
            end = new_node;
        }
        else {
            end->next = new_node;
            new_node->prev = end;
            end = new_node;
        }
    }

    template <typename T>
    bool DoublyLinkedList<T>::has_item(const T& value) const noexcept {
        Node* current = begin;
        while (current != nullptr) {
            if (current->value == value) {
                return true;
            }
            current = current->next;
        }

        return false;
    }

    template <typename T>
    void DoublyLinkedList<T>::print() const noexcept {
        Node* current = begin;
        while (current != nullptr) {
            std::cout << ' ' << current->value;
            current = current->next;
        }
        std::cout << std::endl;
    }

    template <typename T>
    bool DoublyLinkedList<T>::remove_first(const T& value) noexcept {
        Node* current = begin;
        while (current != nullptr) {
            if (current->value == value) {
                if (current == begin) {
                    begin = begin->next;
                    if (begin != nullptr) {
                        begin->prev = nullptr;
                    }
                    else {
                        end = nullptr;
                    }
                }
                else if (current == end) {
                    end = end->prev;
                    end->next = nullptr;
                }
                else {
                    current->prev->next = current->next;
                    current->next->prev = current->prev;
                }
                delete current;
                return true;
            }
            current = current->next;
        }

        return false;
    }

    template <typename T>
    std::size_t DoublyLinkedList<T>::size() const noexcept {
        std::size_t count = 0;
        Node* current = begin;
        while (current != nullptr) {
            ++count;
            current = current->next;
        }

        return count;
    }

}