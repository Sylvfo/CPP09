#include "PmergeMe.hpp"

	PmergeMe::PmergeMe() : oddeven(0), els(2)
	{
		_myChrono.tv_sec = 0;
		_myChrono.tv_usec = 0;
		RecLevels = 0;
	}

	PmergeMe::~PmergeMe(){}

	PmergeMe::PmergeMe(const PmergeMe &src)
	{
		*this = src;
	}
	
	PmergeMe &PmergeMe::operator=(const PmergeMe &src)
	{
		if (this != &src)
		{
		}
		return *this;
	}

	void PmergeMe::addTimeval(const struct timeval &start, const struct timeval &end)
	{
		_myChrono.tv_sec  += end.tv_sec - start.tv_sec;
		_myChrono.tv_usec += end.tv_usec - start.tv_usec;

		while (_myChrono.tv_usec >= 1000000) {
			_myChrono.tv_usec -= 1000000;
			_myChrono.tv_sec++;
		}
		while (_myChrono.tv_usec < 0) {
			_myChrono.tv_usec += 1000000;
			_myChrono.tv_sec--;
		}
	}

	int PmergeMe::JacobsthalNbr(int n)
	{
		if (n <= 0)
			return 0;
		else if (n == 1)
			return 1;
		return JacobsthalNbr(n - 1) + 2 * JacobsthalNbr(n -2);
	}

// on peut faire mieux
	void PmergeMe::initJacobsthalNbr()
	{
		int n = 3;
		int J_numb;
		int prev_J_numb;
		int many_el = 0;
		while (many_el < _containerSize )
		{
			J_numb = JacobsthalNbr(n);
			prev_J_numb = JacobsthalNbr(n - 1) ;
		//	std::cout << "J_numb " << J_numb << "prev_J_numb" << prev_J_numb << std::endl;
			while (J_numb > prev_J_numb)
			{
				_J.push_back(J_numb - 2);// -1 a cause index et -1 a cause que b3...??
				J_numb--;
				many_el++;
			}
			n++;
		}
	}

	void PmergeMe::load(int ac, char **av)
	{
		if (ac < 2)
			throw std::invalid_argument("Usage: ./PmergeMe \"arguments\" or ./PmergeMe arg1 arg2 arg3");
		if (ac == 2)
			this->loadOneArg(av[1]);
		else
			this->loadMultipleArg(av);
	}
