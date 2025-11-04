#include "PmergeMeDq.hpp"

	PmergeMeDq::PmergeMeDq(){}
	PmergeMeDq::~PmergeMeDq(){} 
	PmergeMeDq::PmergeMeDq(const PmergeMeDq &src): PmergeMe(src){*this = src;} ;// =)
	PmergeMeDq &PmergeMeDq::operator=(const PmergeMeDq &src)
	{
		if (this != &src)
		{
			this->_myDeque = src._myDeque;
		}
		return *this;
	}

	void PmergeMeDq::loadOneArg(char *av)
	{
		int i = 0;
		std::string sNumber;
		long int iNumber;

		if (isdigit(av[i]) == 0)
					throw std::invalid_argument("Please enter arguments");
		while(av[i])
		{
			while(av[i] == ' ')
				i++;
			if (!av[i])
				break;
			if (isdigit(av[i]) == false)
				throw std::invalid_argument("Please enter only positive integers");
			sNumber = "";
			while(av[i] && isdigit(av[i]))
			{
				sNumber += av[i];
				i++;
			}
			iNumber = atol(sNumber.c_str());
			if (iNumber < 0 || iNumber > INT_MAX)
				throw std::invalid_argument("Please enter only integers MAX_INT");
			_myDeque.push_back(static_cast<int>(iNumber));
		}
		_containerSize = static_cast<int>(_myDeque.size());
	}

	void PmergeMeDq::loadMultipleArg(char **av)
	{
		int i = 1;
		int j;
		long int iNumber;

		while (av[i] != NULL)
		{
			j = 0;
			while(av[i][j])
			{
				if (!isdigit(av[i][j]))
					throw std::invalid_argument("Please enter only positive integers");
				j++;
			}
			iNumber = atol(av[i]);
			if (iNumber < 0 || iNumber > INT_MAX)
				throw std::invalid_argument("Please enter only integers MAX_INT");
			_myDeque.push_back(static_cast<int>(iNumber));
			i++;
		}
		_containerSize = static_cast<int>(_myDeque.size());
	}

	void PmergeMeDq::printTime()
	{
		std::cout << "Time to process a range of " << _myDeque.size() << " with std::deque: " ;
		if (this->_myChrono.tv_sec != 0)
			std::cout << _myChrono.tv_sec << "'s ";
		std::cout << _myChrono.tv_usec << " µs" << std::endl ;
	}

	void PmergeMeDq::printNumbers(std::string comment, const char * color)
	{
		std::cout << color << comment;
		for (_dit = _myDeque.begin(); _dit != _myDeque.end(); ++_dit)
		{
			std::cout << *_dit;
			if (_dit + 1 != _myDeque.end())
				std::cout << " ";
		}
		std::cout << RESET << std::endl;
	}

	void PmergeMeDq::sortDeque()
	{
		timeval start, end;
		gettimeofday(&start, NULL);
		if (_myDeque.size() == 2)
		{
			if (_myDeque[0] > _myDeque[1])
				std::swap(_myDeque[0], _myDeque[1]);
		}
		else if (_myDeque.size() > 2)
			FordJohnsonAlgo();
		gettimeofday(&end, NULL);
		addTimeval(start, end);
	}
