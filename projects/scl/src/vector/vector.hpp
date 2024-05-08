#pragma once

#include <iostream>
#include <stdexcept>

namespace VBek {
	template <typename T> 
	class Vector {
		private:
			T* arr;
			std::size_t capacity = 10;
			std::size_t _size = 0;

		public:
			Vector() noexcept;
			Vector(const Vector&) = delete;
			Vector& operator = (const Vector&) = delete;
			~Vector() noexcept;
			
			void push_back(const T& value) noexcept;
			bool has_item(const T& value) const noexcept;
			bool insert(const int position, const T& value);
			void print() const noexcept;
			bool remove_first(const T& value) noexcept;
			std::size_t size() const noexcept;

			T& operator[](std::size_t index); // метод для доступа к элементу массива по индексу и возвращающий ссылку на элемент
			const T& operator[](std::size_t index) const; //метод для доступа к элементу массива по индексу и возвращающий константную ссылку на элемент
	};
}
