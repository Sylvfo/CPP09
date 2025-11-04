#include "ShowPmergeMe.hpp"

	void ShowPmergeMe::swapNbrs()
	{
		gettimeofday(&_start1, NULL);
		_recursivityLevel++;
		oddeven = this->_myVect.size() % 2;
		std::cout << BRIGHT_PURPLE "Way up recursivity level: " << _recursivityLevel << " elem size: " << els  << RESET << std::endl;
		printVectorElsBlock(_myVect, "_myVect before", els);
		for (_vit = _myVect.begin(); _vit < _myVect.end() - oddeven; _vit += 2)
		{
			if (*_vit > *(_vit + 1))
				std::swap(*_vit, *(_vit + 1));
		}
		printVectorElsBlock(_myVect, "_myVect after ", els);
		els *= 2;

		if (els <= static_cast<int>(_myVect.size()))
		{
			RecLevels = WAYUP;
		//	mesuretime(WAYUP);
			FordJohnsonAlgo();
		}
		else
		{
			_recursivityLevel++;
			els /= 2;
			RecLevels = WAYDOWN;
		//	mesuretime(WAYUP);
			FordJohnsonAlgo();
		}
	}

	void ShowPmergeMe::swapBlocks()
	{
		gettimeofday(&_start1, NULL);
		_recursivityLevel++;
			oddeven = _myVect.size() % els;
			std::cout << BRIGHT_PURPLE "Way up recursivity level: " << _recursivityLevel << " elem size: " << els  << RESET << std::endl;
			printVectorElsBlock(_myVect, "_myVect before ", els);
			for (_vit = _myVect.begin(); _vit < _myVect.end() - oddeven; _vit += els)
			{
				if (*(_vit + ((els / 2) - 1)) > *(_vit + (els - 1)))
					std::swap_ranges(_vit, (_vit + (els / 2)), _vit + (els / 2));
			}
			printVectorElsBlock(_myVect, "_myVect after ", els);
			els *= 2;
		//	this->print();
		//	std::cout << "Next elem size: " << els << std::endl;
		//mesuretime(WAYUP);
			if (els <= static_cast<int>(_myVect.size()))
				FordJohnsonAlgo();
			else
			{
				_recursivityLevel++;//?? pk plus?
				els /= 2;
				RecLevels = WAYDOWN;
				FordJohnsonAlgo();
			}

	}

	void ShowPmergeMe::MergeInsert()
	{
		ToMainPendRest();
		MergePendinMain();
		BackInmyVect();
		if (els == 1)
			return;
		els /= 2;
		_recursivityLevel--;
		FordJohnsonAlgo();
	}

	void ShowPmergeMe::ToMainPendRest()
	{
		gettimeofday(&_start1, NULL);
		std::cout << BRIGHT_CYAN "Way down recursivity level " << _recursivityLevel << " element size " << els
				<< RESET << std::endl;
		oddeven = _myVect.size() % els; // =)
		_mvit = _mainV.begin();// =)
		_mainVsize = els;
		_mainV.resize(_mainVsize);
		_pendVsize = 0;
		_pvit = _pendV.begin();
		labels = B1;
		for (_vit = _myVect.begin(); _vit < (_myVect.end() - oddeven); _vit += els)
		{
			switch (labels)
			{
				case B1:
				{
					std::copy(_vit, _vit + els, _mvit);
					labels = TOMAIN;
					break;
				}
				case TOMAIN:
				{
					_mvit += els;
					_mainVsize += els;
					_mainV.resize(_mainVsize);
					std::copy(_vit, _vit + els, _mvit);
					labels = TOPEND;
					break;
				}
				case TOPEND:
				{
					_pendVsize += els;
					_pendV.resize(_pendVsize);
					std::copy(_vit, _vit + els, _pvit);
					_pvit += els;
					labels = TOMAIN;
					break;
				}
			}
		}
		//rest
		if (oddeven > 0)
		{
			_restV.resize(oddeven);
			std::copy(_myVect.end() - oddeven, _myVect.end(), _restV.begin());
		}
		printVectorEls(_myVect, "_myVect before ", els);
		printVectorEls(_mainV, "_mainV  ", els);
		printVectorEls(_pendV, "_pendV  ", els);
		printVectorEls(_restV, "_restV  ", els);
	//	printVector(_restV, "_restV  ");
		_myVect.clear();// or erase
		_myVect.resize(_mainVsize + _pendV.size() +_restV.size());// ou vect size de base... ou pas besoin?
	}

	void ShowPmergeMe::MergePendinMain()
	{
		int nbElemInPend;
		if (_pendV.size() > 0)
			nbElemInPend = (_pendV.size() - _pendV.size() % els) / els;
		else
			nbElemInPend = 0;
		std::cout << "nbElemInPend: " << nbElemInPend << std::endl;
		int i = 0;
		int count = 0;
		int index;
		while(count < nbElemInPend)
		{
			while (_J[i] > nbElemInPend - 1)
				i++;
			std::cout << GRAY_3 "Jacobsthal number: " << BRIGHT_AQUA << _J[i] << RESET;
			if (_J[i] * els < static_cast<int>(_pendV.size()))
			{
				_pvit = _pendV.begin();
				index = _J[i] * els; // debut block
				valueToSearch =  _pendV[(index + els- 1)]; // fin blcok
				std::cout << GRAY_3 <<" valueToSearch: " << BRIGHT_GREEN << valueToSearch; // << std::endl;
				_mvit = findNext(_mainV, valueToSearch, els);
				_mainV.insert(_mvit, _pvit + index, _pvit + index + els);
				print_block(_pvit + index, _pvit + index + els);
			}
			i++;
			count++;
		}
	}

	void ShowPmergeMe::BackInmyVect()
	{
		_mainVsize = static_cast<int>(_mainV.size());
		std::copy(_mainV.begin(), _mainV.end(), _myVect.begin());
		if (oddeven > 0)
			std::copy(_restV.begin(), _restV.end(), _myVect.begin() + _mainVsize);
		_mainV.clear();
		_pendV.clear();
		_restV.clear();
		printVectorEls(_myVect, "_myVect with sorted blocks", els);
		mesuretime(WAYDOWN); 
	}

	std::vector<int>::iterator ShowPmergeMe::findNext(std::vector<int> &vect, int n, int els)
	{
		gettimeofday(&_start2, NULL);
		std::vector<int>::iterator it_1;//deplacer les iteraots..
		std::vector<int>::iterator it_2;
		int value;
		int diff = INT_MAX;
		it_2 = vect.end();
		int elsM = els - 1;
	//	std::cout << "in find iterators value = ";
		for (it_1 = vect.begin() + elsM; it_1 < vect.end(); it_1 += els)
		{
			value = *it_1 - n;
		//	std::cout << *it_1 << " - ";
			if (value == 1 || value == 0)
			{
				mesuretime(4);
				return (it_1 - (elsM));
			}
			else if (value < diff && value > 0)
			{
				it_2 = it_1;
				diff = value;
			}
		}
		if (diff == INT_MAX)
		{
			mesuretime(4);
			std::cout << "vect.end " << std::endl;
			return (vect.end());
		}
		mesuretime(4);
		return (it_2 - (elsM));
	}