#include "../PmergeMeVect.hpp"
#include "../PmergeMe.hpp"

#ifndef SHOWPMERGEME_HPP
#define SHOWPMERGEME_HPP

class ShowPmergeMe : public PmergeMeVect
{
	public:

	void printTimeUpDown(); // POUR PRINT

	void swapNbrs();
	void swapBlocks();
	void MergeInsert();
	void BackInmyVect();
	void MergePendinMain();
	void ToMainPendRest();
	std::vector<int>::iterator findNext(std::vector<int> &vect, int n, int els);

	//pour opti et print
	timeval _timeup;
	timeval _timedown;
	timeval _timefind;
	timeval _start1;
	timeval _end1;
	timeval _start2;
	timeval _end2;
	timeval _find;

	//fonctions optimisation et print

	//void printVector(std::vector<int> vect, std::string comment);
	void printVectorEls(std::vector<int> vect, std::string comment, int els);
	void printVectorElsBlock(std::vector<int> vect, std::string comment, int els);
	void print_block(std::vector<int>::iterator it1, std::vector<int>::iterator it2);
	//void test_index();
	//void test_insert();
	void mesuretime(int RecLevels);
	void addTimevalfind(struct timeval &acc, const struct timeval &start, const struct timeval &end);

	public:
		ShowPmergeMe(); // =)
		~ShowPmergeMe(); // =)
		ShowPmergeMe(const ShowPmergeMe &src);// =)
		ShowPmergeMe &operator=(const ShowPmergeMe &src);// =)
		int _recursivityLevel; // pour print
};



#endif