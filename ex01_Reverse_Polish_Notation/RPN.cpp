#include "RPN.hpp"

	RevPolishNot::RevPolishNot(): _i(1), _line("") {}
	RevPolishNot::~RevPolishNot(){}
	RevPolishNot::RevPolishNot(const RevPolishNot &src)
	{
		*this = src;
	}
	RevPolishNot& RevPolishNot::operator=(const RevPolishNot &src)
	{
		if (this !=& src)
			this->_calculette = src._calculette;
		return *this;
	}

	void printStack(std::stack<float> st, int i)
	{
		(void) i;
	//	std::cout << "i " << i << std::endl;
		while(!st.empty())
		{
			std::cout << " " << st.top();
			st.pop();
		}
		std::cout << std::endl;
	}

	void RevPolishNot::pars(int ac, char **av)
	{
		_i = 1;
		if (ac != 2)
		{
			throw std::invalid_argument("Usage: ./RPN \"arguments\" ");
		}
		else if (ac == 2)
			_line = av[1];
		_i = 0;
		while (_line[_i])
		{
			if (!isdigit(_line[_i]) && _line[_i] != '+' && _line[_i] != '-' &&
				_line[_i] != '*' && _line[_i] != '/' && _line[_i] != ' ')
			{
				throw std::invalid_argument("Error use only int digit and + - * /");

			}
			_i++;
		}
	}

	void RevPolishNot::calculate()
	{
		if (isdigit(_line[0]) == true)
			_left_operand = static_cast<float>(_line[0] - 48);
		_i = 0;
		while (_line[_i] != 0)
		{
			if (isdigit(_line[_i]))
				_calculette.push(static_cast<float>(_line[_i] - 48));
			else if (_line[_i] == '+' || _line[_i] == '-' || _line[_i] == '*' || _line[_i] == '/')
			{
				_right_operand = _calculette.top();
				_calculette.pop();
				if (_calculette.empty() == true)
				{
					throw std::invalid_argument("Error");
				}
				_left_operand = _calculette.top();
				_calculette.pop();
				if (_line[_i] == '+')
					_left_operand += _right_operand;
				else if (_line[_i] == '-')
					_left_operand -= _right_operand;
				else if (_line[_i] == '*')
					_left_operand *= _right_operand;
				else if (_line[_i] == '/')
					_left_operand /= _right_operand;
				_calculette.push(_left_operand);
			}
			_i++;
		}
	}

	void RevPolishNot::print()
	{
		_calculette.pop();
		if (_calculette.empty() == false)
		{
			throw std::invalid_argument("Error. Miss + - * /");
		}
		std::cout << _left_operand << std::endl;
	}