#include "PmergeMe.hpp"

#ifndef PMERGEMEVECT_HPP
#define PMERGEMEVECT_HPP

class PmergeMeVect : public PmergeMe
{
	protected:
	std::vector<int> _myVect;
	std::vector<int>::iterator _vit;
	std::vector<int> _mainV;
	std::vector<int>::iterator _mvit;
	std::vector<int> _pendV;
	std::vector<int>::iterator _pvit;
	std::vector<int> _restV;
	
	void FordJohnsonAlgo();
	void swapNbrs();
	void swapBlocks();
	void ToMainPendRest();
	void MergeInsert();
	void MergePendinMain();
	std::vector<int>::iterator findNext(std::vector<int> &vect, int n, int els);
	void BackInmyVect(); 

	void loadOneArg(char *av);
	void loadMultipleArg(char **av);

	public:
		PmergeMeVect(); 
		virtual ~PmergeMeVect(); 
		PmergeMeVect(const PmergeMeVect &src);
		PmergeMeVect &operator=(const PmergeMeVect &src);
		void printNumbers(std::string comment, const char * color); 
		void sortVector();
		void printTime();
};

#endif