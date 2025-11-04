#include "ShowPmergeMe.hpp"

	void ShowPmergeMe::printVectorEls(std::vector<int> vect, std::string comment, int nb)
	{
		std::cout << GRAY_6 << comment << std::endl;
		std::vector<int>::iterator it;
		int index = 0;
		for (it = vect.begin(); it != vect.end(); ++it)
		{
			if (index % nb == nb - 1)
				std::cout << BRIGHT_GREEN << *it << " " RESET ;
			else
				std::cout << DARK_CYAN << *it << " " RESET ;
			++index;
		}
			
		std::cout << "\n\n";
	}
	void ShowPmergeMe::printVectorElsBlock(std::vector<int> vect, std::string comment, int nb)
	{
		std::cout << GRAY_6 << comment << std::endl;
		std::vector<int>::iterator it;
		int index = 0;
		int nb2 = nb/ 2;
		for (it = vect.begin(); it != vect.end(); ++it)
		{ 
			if (index % nb == nb - 1)
				std::cout << BRIGHT_GREEN << *it << " " RESET ;
			else if (index % nb2 == nb2 - 1)
				std::cout << DARK_LIME << *it << " " RESET ;	
			else
				std::cout << DARK_CYAN << *it << " " RESET ;
			++index;
		}
		std::cout << "\n\n";
	}

	void ShowPmergeMe::print_block(std::vector<int>::iterator it1, std::vector<int>::iterator it2)
	{
		std::cout << GRAY_3 " from block: ";
		while(it1 != it2)
		{
			std::cout << DARK_AQUA << *it1 << " ";
			++it1;
		}
		std::cout << RESET << std::endl;
	}
