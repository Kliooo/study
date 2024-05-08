#pragma once

#include <iostream>

namespace IBusko {
	class LongNumber {
		static const char END;
		static const char ZERO;
		static const char MINUS;
		static const int NEGATIVE;
		static const int POSITIVE;
		
		int* numbers;
		int length;
		int sign;
		
		public:
			LongNumber();
			LongNumber(int length, int sign);
			LongNumber(const char* const str);
			LongNumber(const LongNumber& x);
			LongNumber(LongNumber&& x);
			
			~LongNumber();
			
			LongNumber& operator = (const char* const str);
			LongNumber& operator = (const LongNumber& x);
			LongNumber& operator = (LongNumber&& x);
			
			bool operator == (const LongNumber& x) const;
			bool operator != (const LongNumber& x) const;
			bool operator > (const LongNumber& x) const;
			bool operator < (const LongNumber& x) const;
			
			LongNumber operator + (const LongNumber& x) const;
			LongNumber operator - (const LongNumber& x) const;
			LongNumber operator * (const LongNumber& x) const;
			LongNumber operator / (const LongNumber& x) const;
			LongNumber operator % (const LongNumber& x) const;
			
			int get_digits_number() const;
			int get_rank_number(int rank) const;
			bool is_negative() const;
			
			friend std::ostream& operator << (std::ostream &os, const LongNumber& x);
			
		private:
			int get_length(const char* const str) const;
	};
}
