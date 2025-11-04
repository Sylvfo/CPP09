#include "BitcoinExchange.hpp"

void BitCoinEx::DataLoad()
{
	std::ifstream myinfile("data.csv");
	if (myinfile.is_open() == false)
		throw std::runtime_error("Could not open the data.csv file");
	while(getline(myinfile, this->_line))
	{
		this->_date = this->_line.substr(0, 10);
		this->_value = atof(this->_line.substr(11).c_str());
		this->_data.insert(std::pair<std::string, float>(this->_date, this->_value));
	}
	myinfile.close();
}

void BitCoinEx::InputLoad(int argc, char **argv)
{
	int a = 1;
	if (argc != 2)
		throw std::invalid_argument("Usage: btc./[input.txt]");
	std::ifstream myinfile(argv[1]);
	if (myinfile.is_open() == false)
		throw std::runtime_error("Could not open the input file");
	while(getline(myinfile, this->_line))
	{
		if (this->_line != "date | value")
			this->InputdataLoad();
		a++;
	}
	myinfile.close();
}

void BitCoinEx::BCEvaluate(const BitCoinEx &DB)
{
	std::map<std::string, float>::iterator it;
	std::map<std::string, float>::const_iterator val;
	for (it = this->_data.begin(); it != this->_data.end(); ++it)
	{
		if (it->second != -1)
		{
			val = DB._data.upper_bound(it->first);
			--val;
			it->second *= val->second;
		}	
	}
}

//****************************************************************************************************
//parsing

void BitCoinEx::InputdataLoad()
{
	if (this->checkFormat() == false)
		return;
	if (this->checkDate() == false)
		return;
	if (this->checkValue() == false)
		return;
	this->_data.insert(std::pair<std::string, float>(this->_date, this->_value));
}

static bool isLeapYear(int year)
{
	if (year % 4 != 0)
		return false;
	if (year % 100 != 0)
		return true;
	if (year % 400 == 0)
		return true;
	return false;
}

bool BitCoinEx::checkDate()
{
	DateInMyDate();
	if (this->_myDate.year < 2010)
	{
		this->_data.insert(std::pair<std::string, float>(_line.substr(0, 10) + " => " + "BitCoin was first used in 2010", -1));
		return false;
	}
	if (this->_myDate.year > 2025)
	{
		this->_data.insert(std::pair<std::string, float>(_line.substr(0, 10) + " => " + "Date in the future", -1));
		return false;
	}
	if (this->_myDate.month < 1 || this->_myDate.month > 12)
	{
		this->_data.insert(std::pair<std::string, float>(_line.substr(0, 10) + " => " + "Invalid month", -1));
		return false;
	}
	if ((this->_myDate.month == 4 || this->_myDate.month == 6 || this->_myDate.month == 9 || this->_myDate.month == 11))
	{
		if ((this->_myDate.day < 1 || this->_myDate.day > 30))
		{
			this->_data.insert(std::pair<std::string, float>(_line.substr(0, 10) + " => " + "Invalid date. This month has 30 days => ", -1));
			return false;
		}
	}
	else if (this->_myDate.month == 2)
	{
		if (isLeapYear(this->_myDate.year) == true && (this->_myDate.day < 1 || this->_myDate.day > 29))
		{
			std::cout << "enter bissextile " << std::endl;
			this->_data.insert(std::pair<std::string, float>(_line.substr(0, 10) + " => " + "Invalid date. February leap year has 29 days", -1));
			return false;
		}
		if (isLeapYear(this->_myDate.year) == false && (this->_myDate.day < 1 || this->_myDate.day > 28))
		{
			std::cout << "enter bissextile " << std::endl;
			this->_data.insert(std::pair<std::string, float>(_line.substr(0, 10) + " => " + "Invalid date. February has 28 days", -1));
			return false;
		}
	}
	else
	{
		if (this->_myDate.day < 1 || this->_myDate.day > 31)
		{
			this->_data.insert(std::pair<std::string, float>(_line.substr(0, 10) + " => " + "Invalid date. This month has 31 days", -1));
			return false;
		}
	}
	this->_date = this->_line.substr(0, 10);
	return true;
}

bool BitCoinEx::checkValue()
{
	float rawValue;
	rawValue = atof(this->_line.substr(13).c_str());
	if (rawValue < 0)
	{
		this->_data.insert(std::pair<std::string, float>(_line + " => " + "Error: not a positive number", -1));
		return false;
	}
	if (rawValue > 1000)
	{
		this->_data.insert(std::pair<std::string, float>(_line + " => " + "Error: too large number", -1));
		return false;
	}
	this->_value = rawValue;
	return true;
}

bool BitCoinEx::substrIsDigit(int begin, int end)
{
	int i = 0;
	std::string test = this->_line.substr(begin, end).c_str();
	while(test[i])
	{
		if (isdigit(test[i]) == false)
			return false;
		i++;
	}
	return true;
}

bool BitCoinEx::substrIsDigitFloat(int begin)
{
	int point = 0;
	int i = 0;
	std::string test = this->_line.substr(begin).c_str();
	while(test[i])
	{
		
		if (isdigit(test[i]) == false && test[i] != '.')
			return false;
		if (test[i] == '.')
			point++;
		if (point > 1)
			return false;
		i++;
	}
	return true;
}

bool BitCoinEx::checkFormat()
{
	if (this->substrIsDigit(0, 4) == false || this->substrIsDigit(5, 2) == false || this->substrIsDigit(8, 2) == false)
	{
		this->_data.insert(std::pair<std::string, float>(_line + " => " + "Error: Date not a number", -1));
		return false;
	}
	if (this->_line[4] != '-' || this->_line[7] != '-' )
	{
		this->_data.insert(std::pair<std::string, float>(_line + " => " + "Error: Invalid format. Please check '-'", -1));
		return false;
	}
	if (this->_line[10] != ' ' || this->_line[12] != ' ' )
	{
		this->_data.insert(std::pair<std::string, float>(_line + " => " + "Error: Invalid format. Please check ' '", -1));
		return false;
	}
	if (this->_line[11] != '|')
	{
		this->_data.insert(std::pair<std::string, float>(_line + " => " + "Error: Invalid format. Please check '|'", -1));
		return false;
	}
	if (this->substrIsDigitFloat(13) == false && this->_line[13] != '-')
	{
		this->_data.insert(std::pair<std::string, float>(_line + " => " + "Error: Invalid value format", -1));
		return false;
	}
	return true;
}

void BitCoinEx::DateInMyDate()
{
	this->_myDate.year = atoi(this->_line.substr(0, 4).c_str());
	this->_myDate.month = atoi(this->_line.substr(5, 2).c_str());
	this->_myDate.day = atoi(this->_line.substr(8, 2).c_str());
}

//****************************************************************************************************
//canonical class

BitCoinEx::BitCoinEx(){}

BitCoinEx::~BitCoinEx(){}

BitCoinEx::BitCoinEx(const BitCoinEx &src)
{
	*this = src;
}

BitCoinEx& BitCoinEx::operator=(const BitCoinEx &src)
{
	if (this != &src)
	{
		this->_data = src._data;
	}
	return *this;
}

std::ostream& operator<<(std::ostream &out, const BitCoinEx &src)
{
	std::map<std::string, float>::const_iterator it;
	for (it = src._data.begin(); it != src._data.end(); ++it)
	{
		out << it->first;
		if (it->second != -1)
			out  <<  " => " << std::fixed  << std::setprecision(2) <<  it->second;
		std::cout << std::endl;
	}
	return out;
}