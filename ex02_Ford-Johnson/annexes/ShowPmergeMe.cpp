#include "ShowPmergeMe.hpp"

	ShowPmergeMe::ShowPmergeMe()
	{
		_timeup.tv_sec = 0;
		_timeup.tv_usec = 0;
		_timedown.tv_sec = 0;
		_timedown.tv_usec = 0;
		_find.tv_sec = 0;
		_find.tv_usec = 0;
		_start1.tv_sec = 0;
		_start1.tv_usec = 0;
		_start2.tv_sec = 0;
		_start2.tv_usec = 0;
		_recursivityLevel= 0;
	}

	ShowPmergeMe::~ShowPmergeMe(){}

	ShowPmergeMe::ShowPmergeMe(const ShowPmergeMe &src) :PmergeMeVect(src)
	{
		*this = src;
	}

	ShowPmergeMe &ShowPmergeMe::operator=(const ShowPmergeMe &src)
	{
		if (this != &src)
		{
		//	this->_myDeque = src._myDeque;
		//	this->_myVect = src._myVect;
		}
		return *this;
	}

		void ShowPmergeMe::addTimevalfind(struct timeval &acc, const struct timeval &start, const struct timeval &end)
	{
		acc.tv_sec  += end.tv_sec - start.tv_sec;
		acc.tv_usec += end.tv_usec - start.tv_usec;

		while (acc.tv_usec >= 1000000) {
			acc.tv_usec -= 1000000;
			acc.tv_sec++;
		}
		while (acc.tv_usec < 0) {
			acc.tv_usec += 1000000;
			acc.tv_sec--;
		}
	}

