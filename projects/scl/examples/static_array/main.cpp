#include "..\..\src\static_array\static_array.hpp"

#include <iostream>

int main() {
    const int data[4] = {1, 2, 3, 4};
    try {
        {
			int tmp[] = {5, 5, 5, 5, 5};
		}
        IBusko::StaticArray<int, 5> arr(data, data + sizeof(data) / sizeof(data[0]));
        std::cout << arr.get_size() << std::endl;
        for (int i = 0; i < arr.get_size(); i++) {
            std::cout << arr[i] << ' ';
        }
    } catch(const std::out_of_range& e) {
        std::cerr << e.what() << std::endl;
    }
	
	std::cout << std::endl;
	
    try {
        IBusko::StaticArray<int, 5> arr = {1, 2, 3, 4};
        for (int i = 0; i < arr.get_size(); i++) {
            std::cout << arr[i] << ' ';
        }
    } catch(const std::out_of_range& e) {
        std::cerr << e.what() << std::endl;
    }
    
    return 0;
}
