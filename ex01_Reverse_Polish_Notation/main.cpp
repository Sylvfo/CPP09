#include "RPN.hpp"

//music
//https://www.youtube.com/watch?v=rrby-2QnGZQ&list=RDSpQ8-xiDYWI&index=18
//https://www.youtube.com/watch?v=_WzCnz8goTM&list=RDSpQ8-xiDYWI&index=27

//https://www.rpn-calc.com/?q=8+4+%2F+5+%2B
int main(int argc, char **argv)
{
	RevPolishNot instanceI;
	try
	{
		instanceI.pars(argc, argv);
		instanceI.calculate();
		instanceI.print();
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	return 0;
}
