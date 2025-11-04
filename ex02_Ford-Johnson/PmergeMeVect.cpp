#include "PmergeMeVect.hpp"

	PmergeMeVect::PmergeMeVect(){} 
	PmergeMeVect::~PmergeMeVect(){} 
	PmergeMeVect::PmergeMeVect(const PmergeMeVect &src): PmergeMe(src){*this = src;};
	PmergeMeVect &PmergeMeVect::operator=(const PmergeMeVect &src)
	{
		if (this != &src)
		{
			this->_myVect = src._myVect;
		}
		return *this;
	}

	void PmergeMeVect::loadOneArg(char *av)
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
			_myVect.push_back(static_cast<int>(iNumber));
		}
		_containerSize = static_cast<int>(_myVect.size());
	}

	void PmergeMeVect::loadMultipleArg(char **av)
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
			_myVect.push_back(static_cast<int>(iNumber));
			i++;
		}
		_containerSize = static_cast<int>(_myVect.size());
	}

	void PmergeMeVect::printTime()
	{
		std::cout << "Time to process a range of " << _myVect.size() << " with std::vector: ";
		if (this->_myChrono.tv_sec != 0)
			std::cout << _myChrono.tv_sec << "'s ";
		std::cout << _myChrono.tv_usec << " µs" << std::endl;
	}

	void PmergeMeVect::printNumbers(std::string comment, const char * color)
	{
		std::cout << color << comment;
		for (_vit = _myVect.begin(); _vit != _myVect.end(); ++_vit)
		{
			std::cout << *_vit;
			if (_vit + 1 != _myVect.end())
				std::cout << " ";
		}
		std::cout << RESET << std::endl;
	}

	void PmergeMeVect::sortVector()
	{
		timeval start, end;
		_mainV.reserve(_myVect.size());
		_pendV.reserve(_myVect.size());
		gettimeofday(&start, NULL);
		if (_myVect.size() == 2)
		{
			if (_myVect[0] > _myVect[1])
				std::swap(_myVect[0], _myVect[1]);
		}
		else if (_myVect.size() > 2)
			FordJohnsonAlgo();
		gettimeofday(&end, NULL);
		addTimeval(start, end);
	}
