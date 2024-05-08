#include "vector.hpp"

namespace VBek {
    template <typename T>
    Vector<T>::Vector() noexcept {
        arr = new T[capacity];
    }

    template <typename T>
    Vector<T>::~Vector() noexcept {
        delete[] arr;
    }

    template <typename T>
    void Vector<T>::push_back(const T& value) noexcept {
        if (_size == capacity) {
            capacity *= 2;
            T* new_arr = new T[capacity];
            for (std::size_t i = 0; i < _size; ++i) {
                new_arr[i] = arr[i];
            }
            delete[] arr;
            arr = new_arr;
        }

        arr[_size++] = value;
    }

    template <typename T>
    bool Vector<T>::has_item(const T& value) const noexcept {
        for (std::size_t i = 0; i < _size; ++i) {
            if (arr[i] == value) {
                return true;
            }
        }

        return false;
    }

    template <typename T>
    bool Vector<T>::insert(const int position, const T& value) {
        if (position < 0 or position > _size) {
            return false;
        }
        if (_size == capacity) {
            capacity *= 2;
            T* new_arr = new T[capacity];
            for (std::size_t i = 0; i < position; ++i) {
                new_arr[i] = arr[i];
            }
            new_arr[position] = value;
            for (std::size_t i = position + 1; i < _size + 1; ++i) {
                new_arr[i] = arr[i - 1];
            }
            delete[] arr;
            arr = new_arr;
        }
        else {
            for (std::size_t i = _size; i > position; --i) {
                arr[i] = arr[i - 1];
            }

            arr[position] = value;
        }

        ++_size;

        return true;
    }

    template <typename T>
    void Vector<T>::print() const noexcept {
        for (std::size_t i = 0; i < _size; ++i) {
            std::cout << ' ' << arr[i];
        }
        std::cout << std::endl;
    }

    template <typename T>
    bool Vector<T>::remove_first(const T& value) noexcept {
        for (std::size_t i = 0; i < _size; ++i) {
            if (arr[i] == value) {
                for (std::size_t j = i; j < _size - 1; ++j) {
                    arr[j] = arr[j + 1];
                }
                --_size;
                return true;
            }
        }

        return false;
    }

    template <typename T>
    std::size_t Vector<T>::size() const noexcept {
        return _size;
    }

    template <typename T>
    T& Vector<T>::operator[](std::size_t index) {
        if (index >= _size) {
            throw std::out_of_range("Index out of range");
        }

        return arr[index];
    }

    template <typename T>
    const T& Vector<T>::operator[](std::size_t index) const {
        if (index >= _size) {
            throw std::out_of_range("Index out of range");
        }

        return arr[index];
    }
}
