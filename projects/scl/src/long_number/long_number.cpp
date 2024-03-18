#include "long_number.hpp"

namespace VBek {
	LongNumber::LongNumber() {
		numbers = new int[1];
		length = 1;
		NEGATIVE = 0;
		numbers[0] = 0;
	}

	LongNumber::LongNumber(const char* const str) { //инициализирует объект LongNumber на основе строки str, представляющей число
		length = get_length(str);
		NEGATIVE = 0;

		int start_b = 0;
		if (str[0] == MINUS) {
			NEGATIVE = 1;
			start_b = 1;
			length = length - 1;
		}

		numbers = new int[length];
		for (int i = start_b; i < length + NEGATIVE; ++i) {
			numbers[i - start_b] = str[i] - ZERO; // Преобразование символов в числа и сохранение в массиве
		}
	}

	LongNumber::LongNumber(const LongNumber& x) { // инициализация нового объекта LongNumber на основе существующего объекта x
		length = x.length; // Копирование длины объекта x
		NEGATIVE = x.NEGATIVE; // Копирование информации о знаке
		numbers = new int[length];

		for (int i = 0; i < length; ++i) {
			numbers[i] = x.numbers[i];
		}
	}

	LongNumber::LongNumber(LongNumber&& x) { // конструктор перемещения
		length = x.length;
		NEGATIVE = x.NEGATIVE;
		numbers = x.numbers;

		x.numbers = nullptr; // Указываем, что временный объект x больше не владеет памятью
		x.length = 0; // Сбрасываем длину временного объекта
		x.NEGATIVE = 0; // Сбрасываем информацию о знаке
	}

	LongNumber::~LongNumber() { // освобождение ресурсов
		delete[] numbers; // освобождаем выделенную память для массива numbers
	}

	LongNumber& LongNumber::operator = (const char* const str) {
		delete[] numbers;
		NEGATIVE = 0;
		length = get_length(str);

		int start_b = 0;
		if (str[0] == MINUS) {
			NEGATIVE = 1; // Устанавливаем отрицательность при наличии знака минус
			start_b = 1; // Сдвигаем начальную позицию
			--length;
		}

		numbers = new int[length];
		for (int i = start_b; i < length + NEGATIVE; ++i) {
			numbers[i - start_b] = str[i] - ZERO; // Преобразование символов в числа и сохранение в массиве
		}

		return *this;
	}

	LongNumber& LongNumber::operator = (const LongNumber& x) {
		delete[] numbers;
		length = x.length;
		NEGATIVE = x.NEGATIVE;

		numbers = new int[length];
		for (int i = 0; i < length; ++i) {
			numbers[i] = x.numbers[i];
		}
		return *this;
	}


	LongNumber& LongNumber::operator = (LongNumber&& x) {
		delete[] numbers;
		length = x.length;
		NEGATIVE = x.NEGATIVE;
		numbers = x.numbers;

		x.numbers = new int[1];
		x.numbers[0] = 0;
		x.length = 1;
		x.NEGATIVE = 0;

		return *this;
	}

	bool LongNumber::operator == (const LongNumber& x) const { // второй const нужен что бы показать что метод не меняет поле класса
		if (NEGATIVE != x.NEGATIVE) {
			return false;
		}

		if (length != x.length) {
			return false;
		}

		for (int i = 0; i < length; ++i) {
			if (numbers[i] != x.numbers[i]) {
				return false;
			}
		}

		return true;
	}

	bool LongNumber::operator > (const LongNumber& x) const {
		if (NEGATIVE != x.NEGATIVE) {
			if (NEGATIVE) {
				return true;
			}
			else {
				return false;
			}
		}
		else {
			if (length != x.length) {
				if (NEGATIVE) {
					return length < x.length;
				}
				else {
					return length > x.length;
				}
			}

			for (int i = 0; i < length; ++i) {
				if (numbers[i] != x.numbers[i]) {
					if (NEGATIVE) {
						return numbers[i] < x.numbers[i];
					}
					else {
						return numbers[i] > x.numbers[i];
					}
				}
			}
		}
		return false;
	}

	bool LongNumber::operator < (const LongNumber& x) const {
		return x > *this;
	}

	LongNumber LongNumber::operator -() const { // логика, чтобы применить унарный минус к числу
		LongNumber change(*this);

		if (NEGATIVE) {
			change.NEGATIVE = 0;
		}
		else {
			change.NEGATIVE = 1;
		}

		return change;
	}

	LongNumber LongNumber::operator + (const LongNumber& x) const {
		if (NEGATIVE != x.NEGATIVE)
			if (NEGATIVE) {
				LongNumber res_of_denial_this = -(*this);
				return x - res_of_denial_this;
			}
			else {
				LongNumber res_of_denial_x = -(x);
				return *this - res_of_denial_x;
			}
		else {

			LongNumber answer; // создаем новый объект LongNumber для хранения результата сложения
			int max_length;

			if (length > x.length) {
				max_length = length + 1;
			}
			else {
				max_length = x.length + 1;
			}

			answer.length = max_length;
			delete answer.numbers;
			answer.numbers = new int[answer.length];

			int i = length - 1; // инициализация переменной i для прохода по разрядам первого числа справа налево
			int j = x.length - 1; // инициализация переменной i для прохода по разрядам второго числа справа налево
			int k = answer.length - 1; // инициализация переменной k для записи разрядов результата справа налево
			int a = 0; // переменная для хранения переноса при сложении разрядов

			while ((i >= 0) or (j >= 0)) {
				int sum = a; // инициализация переменной sum как разности с учетом переноса a
				if (i >= 0) {
					sum = sum + numbers[i];
					i--;
				}
				if (j >= 0) {
					sum = sum + x.numbers[j];
					j--;
				}
				answer.numbers[k] = sum % 10;
				k--;
				a = sum / 10;
			}
			answer.numbers[k] = a;
			k--;

			answer.NEGATIVE = NEGATIVE;

			// удаление ведущих нулей

			int b = 0; // количество ведущих нулей
			while ((b < answer.length) and (answer.numbers[b] == 0)) {
				b = b + 1;
			}
			if (b == answer.length) { // проверяем, если переменная b равна длине числа, то есть все разряды числа равны нулю
				answer.length = 1;
				delete[] answer.numbers;
				answer.numbers = new int[1];
				answer.numbers[0] = 0;
			}
			else { // если найдены ненулевые разряды в числе
				answer.length = answer.length - b;
				int* temp = new int[answer.length]; // создаем временный массив для хранения числа без ведущих нулей
				for (int i = 0; i < answer.length; ++i) {
					temp[i] = answer.numbers[b + i];
				}
				delete[] answer.numbers;
				answer.numbers = temp; // перезаписываем массив без ведущих нулей
			}

			return answer;
		}
	}

	LongNumber LongNumber::operator - (const LongNumber& x) const {
		if (*this == x) {
			return LongNumber("0");
		}
		
		if ((!NEGATIVE and !x.NEGATIVE) == false) {
			if (NEGATIVE and x.NEGATIVE) {
				return ((-LongNumber(x)) - (-LongNumber(*this)));
			}
			else {
				return ((-LongNumber(x)) + *this);
			}
		}

		LongNumber answer; // создаем новый объект LongNumber для хранения результата вычитания
		if (*this < x) {
			answer = (LongNumber(x) - LongNumber(*this));
			answer.NEGATIVE = 1;
			return answer;
		}

		int max_length;
		if (length > x.length) {
			max_length = length;
		}
		else {
			max_length = x.length;
		}

		answer.length = max_length;
		delete[] answer.numbers;
		answer.numbers = new int[answer.length];

		int i = length - 1;
		int j = x.length - 1;
		int k = answer.length - 1;
		int a = 0;

		while (i >= 0 || j >= 0) {
			int dif = a;
			if (i >= 0) {
				dif += numbers[i];
				i--;
			}
			if (j >= 0) {
				dif -= x.numbers[j];
				j--;
			}
			if (dif < 0) {
				dif += 10;
				a = -1;
			}
			else {
				a = 0;
			}
			answer.numbers[k] = dif;
			k--;
		}

		// удаляем ведущие нули из результата

		int b = 0;
		while (b < answer.length && answer.numbers[b] == 0) {
			++b;
		}
		if (b == answer.length) {
			answer.length = 1;
			delete[] answer.numbers;
			answer.numbers = new int[1];
			answer.numbers[0] = 0;
		}
		else {
			answer.length -= b;
			int* temp = new int[answer.length];
			for (int i = 0; i < answer.length; ++i) {
				temp[i] = answer.numbers[b + i];
			}
			delete[] answer.numbers;
			answer.numbers = temp;
		}

		return answer;
	}

	LongNumber LongNumber::operator * (const LongNumber& x) const {
		if (*this == LongNumber("0") or x == LongNumber("0")) {
			return LongNumber("0");
		}

		int size_ = length + x.length; // размер массива для хранения результата умножения
		int* comp = new int[size_];
		for (int i = 0; i < size_; ++i) {
			comp[i] = 0;
		}
		for (int i = length - 1; i >= 0; --i) { // умножение в столбик
			int a = 0;
			for (int j = x.length - 1; j >= 0; --j) {
				int result = numbers[i] * x.numbers[j] + comp[i + j + 1] + a;
				comp[i + j + 1] = result % 10;
				a = result / 10;
			}
			comp[i] += a;
		}

		int t = 0;
		while (t < size_ && comp[t] == 0) { // находим индекс первой ненулевой цифры
			++t;
		}

		LongNumber answer;
		answer.length = size_ - t; // длина ответа
		answer.numbers = new int[answer.length];
		for (int i = 0; i < answer.length; ++i) {
			answer.numbers[i] = comp[t + i];
		}
		
		if (NEGATIVE == x.NEGATIVE) {
			answer.NEGATIVE = 0;
		}
		else {
			answer.NEGATIVE = 1;
		}
		delete[] comp;

		return answer;
	}

	LongNumber LongNumber::operator / (const LongNumber& x) const {
		// TODO
		LongNumber result;
		return result;
	}


	LongNumber LongNumber::operator % (const LongNumber& x) const {
		// TODO
		LongNumber result;
		return result;
	}

	int LongNumber::get_digits_number() const {
		return length;
	}

	bool LongNumber::is_negative() const { // возвращает булевое значение, показывающее, является ли число отрицательным
		return NEGATIVE;
	}

	std::ostream& operator << (std::ostream& os, const LongNumber& x) { // оператор для вывода объекта LongNumber в поток os
		if (x.NEGATIVE) {
			os << '-';
		}
		for (int i = 0; i < x.length; ++i) {
			os << x.numbers[i];
		}

		return os;
	}

	int LongNumber::get_length(const char* const str) const {
		const char* s = str;
		while (*s != 0) {
			++s;
		}
		return (s - str);
	}
}
