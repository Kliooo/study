#pragma once

#include <iostream>

namespace VBek {
	class LongNumber {
		static const char END = '\0';
		static const char MINUS = '-';
		static const int POSITIVE = 1;
		static const char ZERO = '0';

		int* numbers;
		int length;
		int NEGATIVE;
		
		public:
			LongNumber();
			LongNumber(const char* const str);
			LongNumber(const LongNumber& x);
			LongNumber(LongNumber&& x);
			
			~LongNumber();
			
			LongNumber& operator = (const char* const str);
			LongNumber& operator = (const LongNumber& x);
			LongNumber& operator = (LongNumber&& x);
			
			bool operator == (const LongNumber& x) const;
			bool operator > (const LongNumber& x) const;
			bool operator < (const LongNumber& x) const;
			
			LongNumber operator -() const;

			LongNumber operator + (const LongNumber& x) const;
			LongNumber operator - (const LongNumber& x) const;
			LongNumber operator * (const LongNumber& x) const;
			LongNumber operator / (const LongNumber& x) const;
			LongNumber operator % (const LongNumber& x) const;
			
			int get_digits_number() const;
			bool is_negative() const;
			
			friend std::ostream& operator << (std::ostream &os, const LongNumber& x);
			
		private:
			int get_length(const char* const str) const;
	};
}
