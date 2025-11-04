#include <iostream>
#include <stack>

#ifndef RPN_HPP
#define RPN_HPP

class RevPolishNot
{
	int _i;
	std::string _line;
	std::stack<float>  _calculette;
	float _right_operand;
	float _left_operand;

	public:
	RevPolishNot();
	~RevPolishNot();
	RevPolishNot(const RevPolishNot &src);
	RevPolishNot &operator=(const RevPolishNot &src);

	void pars(int ac, char **av);
	void calculate();
	void print();
};

#endif