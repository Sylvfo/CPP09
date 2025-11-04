#include <iostream>
#include <algorithm>
#include <map>
#include <string>
#include <fstream>
#include <iomanip>

#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

struct myDate{
	int year;
	int month;
	int day;
	std::string error;
};

class BitCoinEx
{
	std::multimap<std::string, float> _data;
	std::string 	_line;
	std::string 	_date;
	float 			_value;
	myDate 			_myDate;

	public:
		BitCoinEx();
		~BitCoinEx();
		BitCoinEx(const BitCoinEx &src);
		BitCoinEx & operator=(const BitCoinEx &src);
		void DataLoad();
		void InputLoad(int argc, char **argv);
		bool checkFormat();
		void DateInMyDate();
		bool checkDate();
		bool checkValue();
		void BCEvaluate(const BitCoinEx &DB);
		void InputdataLoad();
		bool substrIsDigit(int begin, int end);
		bool substrIsDigitFloat(int begin);
		friend std::ostream& operator<<(std::ostream &out, const BitCoinEx &src);
};

#endif