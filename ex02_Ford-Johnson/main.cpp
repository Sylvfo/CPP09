#include "PmergeMe.hpp"
#include "PmergeMeVect.hpp"
#include "annexes/ShowPmergeMe.hpp"
#include "PmergeMeDq.hpp"

int main(int argc, char **argv)
{
	PmergeMeVect* VectorDatas = new PmergeMeVect();
//	ShowPmergeMe ShVectorDatas;
	PmergeMeDq * DequeDatas = new PmergeMeDq();
	
	try
	{
/*		ShVectorDatas.load(argc, argv);
		ShVectorDatas.printNumbers("Before: ", DARK_LIME);
		ShVectorDatas.initJacobsthalNbr();
		ShVectorDatas.sortVector();
		ShVectorDatas.printNumbers("After: ", DARK_CYAN);
		ShVectorDatas.printTime();*/

		VectorDatas->load(argc, argv);
		VectorDatas->printNumbers("Before: ", DARK_LIME);
		VectorDatas->initJacobsthalNbr();
		VectorDatas->sortVector();
		VectorDatas->printNumbers("After: ", DARK_CYAN);
		VectorDatas->printTime();

		DequeDatas->load(argc, argv);
		DequeDatas->initJacobsthalNbr();
		DequeDatas->sortDeque();
		DequeDatas->printTime();
		delete VectorDatas;
		delete DequeDatas;
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	return 0;
}



//	./PmergeMe 2 11 0 17 8 16 6 15 3 10 1 21 9 18 14 19 5 12 4 20 7 13 78 44 1 66 5 1 4 47 56 6 3 74 41 98 96 34 81 56
