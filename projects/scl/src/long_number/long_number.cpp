#include "long_number.hpp"

using IBusko::LongNumber;

const char LongNumber::END = '\0';
const char LongNumber::ZERO = '0';
const char LongNumber::MINUS = '-';
const int LongNumber::NEGATIVE = -1;
const int LongNumber::POSITIVE = 1;
		
LongNumber::LongNumber() : length(1), sign(POSITIVE) {
	numbers = new int[length];
	numbers[0] = 0;
}

LongNumber::LongNumber(int length, int sign) : length(length), sign(sign) {
	numbers = new int[length];
	for (int i = 0; i < length; i++) {
		numbers[i] = 0;
	}
}

LongNumber::LongNumber(const char* const str) {
	int str_length = get_length(str);
	if (str[0] == MINUS) {
		sign = -1;
		length = str_length - 1;
	} else {
		sign = 1;
		length = str_length;
	}
	
	numbers = new int[length];
	for (int i = 0; i < length; i++) {
		numbers[i] = str[str_length - i - 1] - ZERO;
	}
}

LongNumber::LongNumber(const LongNumber& x) {
	length = x.length;
	sign = x.sign;
	numbers = new int[length];
	for (int i = 0; i < length; i++) {
		numbers[i] = x.numbers[i];
	}
}

LongNumber::LongNumber(LongNumber&& x) {
	length = x.length;
	sign = x.sign;
	numbers = x.numbers;
	x.numbers = nullptr;
}

LongNumber::~LongNumber() {
	length = 0;
	delete [] numbers;
	numbers = nullptr;
}

LongNumber& LongNumber::operator = (const char* const str) {
	int str_length = get_length(str);
	if (str[0] == MINUS) {
		sign = -1;
		length = str_length - 1;
	} else {
		sign = 1;
		length = str_length;
	}
	
	delete [] numbers;
	numbers = new int[length];
	for (int i = 0; i < length; i++) {
		numbers[i] = str[str_length - i - 1] - ZERO;
	}
	
	return *this;
}

LongNumber& LongNumber::operator = (const LongNumber& x) {
	if (this == &x) return *this;
	
	length = x.length;
	sign = x.sign;
	
	delete [] numbers;
	numbers = new int[length];
	for (int i = 0; i < length; i++) {
		numbers[i] = x.numbers[i];
	}
	
	return *this;
}

LongNumber& LongNumber::operator = (LongNumber&& x) {
	length = x.length;
	sign = x.sign;
	
	delete [] numbers;
	numbers = x.numbers;
	x.numbers = nullptr;
	
	return *this;
}

bool LongNumber::operator == (const LongNumber& x) const {
	if (this == &x) return true;
	
	if (length != x.length) return false;
	if (sign != x.sign) return false;
	
	for (int i = 0; i < length; i++) {
		if (numbers[i] != x.numbers[i]) return false;
	}
	
	return true;
}

bool LongNumber::operator != (const LongNumber& x) const {
	return !(*this == x);
}

bool LongNumber::operator > (const LongNumber& x) const {
	if (this == &x) return false;
	
	if (sign != x.sign) {
		if (sign == POSITIVE) return true;
		else return false;
	} else {
		bool is_bigger = false;
		
		if (length > x.length) {
			is_bigger = true;
		} else if (length == x.length) {
			int i = 0;
			while (
				i < length - 1
				&& numbers[length - i - 1] == x.numbers[length - i - 1]
			) {
				i++;
			}
			if (numbers[length - i - 1] > x.numbers[length - i - 1]) {
				is_bigger = true;
			}
		}
		
		if (sign == POSITIVE) return is_bigger;
		else return !is_bigger;
	}
}

bool LongNumber::operator < (const LongNumber& x) const {
	return (*this != x) && !(*this > x);
}

LongNumber LongNumber::operator + (const LongNumber& x) const {
	LongNumber result;
	LongNumber min, max;
	if (sign * x.sign > 0) {
		if (length >= x.length) {
			result = LongNumber(length + 1, sign);
			min = x; 
			max = *this; 
		} else {
			result = LongNumber(x.length + 1, sign);
			min = *this; 
			max = x;
		}
		
		for (int i = 0; i < min.length; i++) {
			result.numbers[i] = min.numbers[i] + max.numbers[i];
		}
			
		for (int i = min.length; i < max.length; i++) {
			result.numbers[i] = max.numbers[i];				
		}

		for (int i = 0; i < result.length - 1; i++) {
			if (result.numbers[i] > 9) {
				result.numbers[i + 1]++;
				result.numbers[i] = result.numbers[i] % 10;
			}
		}
		
		if (result.numbers[result.length - 1] == 0 ) {
			result.length--;
		}
	} else {
		LongNumber absx = x, abs_this = *this;
		absx.sign = 1;
		abs_this.sign = 1;
		if (abs_this > absx) {
			result = LongNumber(length + 1, sign);
			min = x; 
			max = *this;
		} else {
			result = LongNumber(x.length + 1, x.sign);
			min = *this; 
			max = x;
		}

		for (int i = 0; i < max.length; i++) {
			result.numbers[i] = max.numbers[i];
		}
		
		for (int i = 0; i < min.length; i++) {
			result.numbers[i] = result.numbers[i] - min.numbers[i];
		}
		
		for (int i = 0; i < result.length - 1; i++) {
			if (result.numbers[i] < 0) {
				result.numbers[i + 1]--;
				result.numbers[i] +=10;
			}
		}
	   
		while (
			result.length > 1
			&& result.numbers[result.length - 1] == 0
		) {
			result.length--;
		}
	}
	
	if (result.length == 1 && result.numbers[0] == 0) {
		result.sign = POSITIVE;
	}
	
	return result;
}

LongNumber LongNumber::operator - (const LongNumber& x) const {
	LongNumber result = x;
	result.sign = -result.sign;
	result = *this + result;
	return result;
}

LongNumber LongNumber::operator * (const LongNumber& x) const {
	LongNumber result(length + x.length, sign * x.sign);
	
	for (int i = 0; i < x.length; i++) {
		for (int j = 0; j < length; j++) {
			result.numbers[j + i] += x.numbers[i] * numbers[j];
			if (result.numbers[i + j] > 9){
				int q = result.numbers[i + j] / 10;
				result.numbers[i + j + 1] += q;
				result.numbers[i + j] -= q * 10;
			}
		}
	}
	
	while (result.length > 1 && result.numbers[result.length - 1] == 0) {
		result.length--;
	}
	
	return result;
}

LongNumber LongNumber::operator / (const LongNumber& x) const {
	LongNumber result;
   
	if (x.length == 1 && x.numbers[0] == 0) {
		// TODO ZeroDivisionException
	}
	
	LongNumber divident = *this;
	divident.sign = 1;
	if (divident < x) {
		return result;
	} else {
		result = LongNumber(length - x.length + 1, sign * x.sign);

		for(int i = 0; i < result.length; i++) {
			LongNumber divider = LongNumber(length - i, 1);
			
			for (int j = 0; j < x.length; j++) {
				divider.numbers[length - x.length - i + j] = x.numbers[j];
			}
			
			int k = 0;
			while (divident > divider || divident == divider) {
				k++;
				divident = divident - divider;
			}
			result.numbers[result.length - i - 1] = k;
		}
	}
	
	while (
		result.length > 1
		&& result.numbers[result.length - 1] == 0
	) {
		result.length--;
	}
	
	return result;
}

LongNumber LongNumber::operator % (const LongNumber& x) const {
	if (is_negative()) {
		LongNumber np_1 = x.is_negative() ? "1" : "-1";
		return *this - (*this / x + np_1) * x;
	} else {
		return *this - (*this / x) * x;
	}
}

int LongNumber::get_digits_number() const {
	return length;
}

int LongNumber::get_rank_number(int rank) const {
	// TODO OutOfBoundException
	return numbers[rank - 1];
}

bool LongNumber::is_negative() const {
	return sign == NEGATIVE;
}

// ----------------------------------------------------------
// PRIVATE
// ----------------------------------------------------------
int LongNumber::get_length(const char* const str) const {
	if (!str) return 0;
	
	int length = 0;
	while (str[length] != END) {
		length++;
	}
	
	/* Или вариант через указатель
	while (*str) {
		str++;
		length++;
	}
	*/	
	
	return length;
}

// ----------------------------------------------------------
// FRIENDLY
// ----------------------------------------------------------
namespace IBusko {
	std::ostream& operator << (std::ostream &os, const LongNumber& x) {
		if (x.sign == LongNumber::NEGATIVE) {
			os << LongNumber::MINUS;
		}
		for (int i = 0; i < x.length; i++) {
			os << x.numbers[x.length - i - 1];
		}
		return os;
	}
}
