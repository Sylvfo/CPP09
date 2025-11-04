#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>
#include <sstream>
#include <cctype>
#include <sys/time.h>
#include <cmath>
#include <climits>
#include "./annexes/colors.hpp"

enum Labels {
	B1 = 0,
	TOMAIN = 1,
	TOPEND = 2,
};

enum RecLevels {
	FIRST = 0,
	WAYUP = 1,
	WAYDOWN = 2,
};

class PmergeMe
{
	protected:
	timeval _myChrono;
	int _containerSize;
	int JacobsthalNbr(int n);
	std::vector<int> _J;// JacobsthalNbr - 1
	void addTimeval(const struct timeval &start, const struct timeval &end);
	
	int oddeven;
	int els;//element size
	int _mainVsize;
	int _pendVsize;
	int labels;
	int RecLevels;
	int valueToSearch;
	
	virtual void FordJohnsonAlgo() = 0;
	virtual void swapNbrs() = 0;
	virtual void swapBlocks() = 0;
	virtual void ToMainPendRest() = 0;
	virtual void MergeInsert() = 0;
	virtual void MergePendinMain() = 0;
	virtual void BackInmyVect() = 0;
	virtual void loadOneArg(char *av) = 0;
	virtual void loadMultipleArg(char **av) = 0;

	public:
		PmergeMe(); 
		virtual ~PmergeMe(); 
		PmergeMe(const PmergeMe &src);
		PmergeMe &operator=(const PmergeMe &src);
		void load(int ac, char **av);
		virtual void printTime() = 0;
		void initJacobsthalNbr();
};

#endif

