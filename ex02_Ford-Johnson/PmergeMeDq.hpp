#ifndef PMERGEMEDQ_HPP
#define PMERGEMEDQ_HPP

#include "PmergeMe.hpp"

class PmergeMeDq : public PmergeMe
{
	protected:
	std::deque<int> _myDeque;
	std::deque<int>::iterator _dit;
	std::deque<int> _mainV;
	std::deque<int>::iterator _mvit;
	std::deque<int> _pendV;
	std::deque<int>::iterator _pvit;
	std::deque<int> _restV;
	
	void FordJohnsonAlgo();
	void swapNbrs();
	void swapBlocks();
	void ToMainPendRest();  
	void MergeInsert();
	void MergePendinMain();  
	std::deque<int>::iterator findNext(std::deque<int> &vect, int n, int els);
	void BackInmyVect();

	void loadOneArg(char *av);
	void loadMultipleArg(char **av);

	public:
		PmergeMeDq(); 
		virtual ~PmergeMeDq(); 
		PmergeMeDq(const PmergeMeDq &src);
		PmergeMeDq &operator=(const PmergeMeDq &src);
		void printNumbers(std::string comment, const char * color); 
		void sortDeque(); 
		void printTime();
};

#endif