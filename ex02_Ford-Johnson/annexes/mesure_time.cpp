	#include "ShowPmergeMe.hpp"
	
	void ShowPmergeMe::printTimeUpDown()
	{
		std::cout << "Time to sort up ";
		if (this->_timeup.tv_sec != 0)
			std::cout << _timeup.tv_sec << "'s ";
		std::cout << _timeup.tv_usec << " µs" << std::endl;
		std::cout << "Time to sort down ";
		if (this->_timedown.tv_sec != 0)
			std::cout << _timedown.tv_sec << "'s ";
		std::cout << _timedown.tv_usec << " µs" << std::endl;
		std::cout << "Time to find ";
		if (this->_find.tv_sec != 0)
			std::cout << _find.tv_sec << "'s ";
		std::cout << _find.tv_usec << " µs" << std::endl;
	}

	void ShowPmergeMe::mesuretime(int RecLevels)
	{
		if (RecLevels == WAYUP)
		{
			gettimeofday(&_end1, NULL);
			addTimevalfind(this->_timeup, _start1, _end1);
		}
		else if (RecLevels == WAYDOWN)
		{
			gettimeofday(&_end1, NULL);
			addTimevalfind(this->_timedown, _start1, _end1);
		}
		else if (RecLevels == 4) // find
		{
			gettimeofday(&_end2, NULL);
			addTimevalfind(this->_find, _start2, _end2);
		}
	}