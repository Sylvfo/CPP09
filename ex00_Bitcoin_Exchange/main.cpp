#include "BitcoinExchange.hpp"

int main(int argc, char **argv)
{
	BitCoinEx Input;
	BitCoinEx DB;
	try
	{
		Input.InputLoad(argc, argv);
		DB.DataLoad();
		Input.BCEvaluate(DB);
		std::cout << "date | value " << std::endl;
		std::cout << Input << std::endl;
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	return 0;
}