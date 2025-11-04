#include "PmergeMeDq.hpp"

	void PmergeMeDq::FordJohnsonAlgo()
	{
		switch (RecLevels)
		{
			case FIRST:
			{
				swapNbrs();
				RecLevels = WAYUP;
				break;
			}
			case WAYUP:
			{
				swapBlocks();
				break;
			}
			case WAYDOWN:
			{
				MergeInsert();
				break;
			}	
		}
	}

	void PmergeMeDq::swapNbrs()
	{
		oddeven = this->_myDeque.size() % 2;
		for (_dit = _myDeque.begin(); _dit < _myDeque.end() - oddeven; _dit += 2)
		{
			if (*_dit > *(_dit + 1))
				std::swap(*_dit, *(_dit + 1));
		}
		els *= 2;
		if (els <= static_cast<int>(_myDeque.size()))
		{
			RecLevels = WAYUP;
			FordJohnsonAlgo();
		}
		else
		{
			els /= 2;
			RecLevels = WAYDOWN;
			FordJohnsonAlgo();
		}
	}

	void PmergeMeDq::swapBlocks()
	{
		oddeven = _myDeque.size() % els;
		for (_dit = _myDeque.begin(); _dit < _myDeque.end() - oddeven; _dit += els)
		{
			if (*(_dit + ((els / 2) - 1)) > *(_dit + (els - 1)))
				std::swap_ranges(_dit, (_dit + (els / 2)), _dit + (els / 2));
		}
		els *= 2;
		if (els <= static_cast<int>(_myDeque.size()))
			FordJohnsonAlgo();
		else
		{
			els /= 2;
			RecLevels = WAYDOWN;
			FordJohnsonAlgo();
		}
	}

	void PmergeMeDq::MergeInsert()
	{
		ToMainPendRest();
		MergePendinMain();
		BackInmyVect();
		if (els == 1)
			return;
		els /= 2;
		FordJohnsonAlgo();
	}

	void PmergeMeDq::ToMainPendRest()
	{
		oddeven = _myDeque.size() % els; // 
		_mvit = _mainV.begin();// 
		labels = B1;
		_mainV.empty();
		_pendV.empty();
		int nbElemInMyDeque;
		if (_myDeque.size() > 0)
			nbElemInMyDeque = (_myDeque.size() - _myDeque.size() % els) / els;
		else
			nbElemInMyDeque = 0;
		
		_dit = _myDeque.begin();
		for (int i = 0; i < nbElemInMyDeque; i++)
		{
			switch (labels)
			{
				case B1:
				{
					_mvit = _mainV.end();
					_mainV.insert(_mvit , _dit, _dit + els);
					labels = TOMAIN;
					std::advance(_dit, els);
					break;
				}
				case TOMAIN:
				{
					_mvit = _mainV.end();
					_mainV.insert(_mvit , _dit, _dit + els);
					labels = TOMAIN;
					labels = TOPEND;
					std::advance(_dit, els);
					break;
				}
				case TOPEND:
				{
					_pvit = _pendV.end();
					_pendV.insert(_pvit , _dit, _dit + els);
					labels = TOMAIN;
					std::advance(_dit, els);
					break;
				}
			}
		}
		if (oddeven > 0)
		{
			_restV.insert(_restV.end(), _dit, _dit + oddeven);
		}
		_myDeque.clear();
	}

	void PmergeMeDq::MergePendinMain()
	{
		int nbElemInPend;
		if (_pendV.size() > 0)
			nbElemInPend = (_pendV.size() - _pendV.size() % els) / els;
		else
			nbElemInPend = 0;
		int i = 0;
		int count = 0;
		int index;
		while(count < nbElemInPend)
		{
			while (_J[i] > nbElemInPend - 1)
				i++;
			if (_J[i] * els < static_cast<int>(_pendV.size()))
			{
				_pvit = _pendV.begin();
				index = _J[i] * els; // debut block
				valueToSearch =  _pendV[(index + els- 1)]; // fin blcok
				_mvit = findNext(_mainV, valueToSearch, els);
				_mainV.insert(_mvit, _pvit + index, _pvit + index + els);
			}
			i++;
			count++;
		}
	}

	void PmergeMeDq::BackInmyVect()
	{
		_myDeque.insert(_myDeque.end(), _mainV.begin(), _mainV.end());
		if (oddeven > 0)
			_myDeque.insert(_myDeque.end(),_restV.begin(), _restV.end());
		_mainV.clear();
		_pendV.clear();
		_restV.clear();
	}

	std::deque<int>::iterator PmergeMeDq::findNext(std::deque<int> &vect, int n, int els)
	{
		std::deque<int>::iterator it_1;
		std::deque<int>::iterator it_2;
		
		int value;
		int diff = INT_MAX;
		it_2 = vect.end();
		int elsM = els - 1;
		for (it_1 = vect.begin() + elsM; it_1 < vect.end(); it_1 += els)
		{
			value = *it_1 - n;
			if (value == 1 || value == 0)
				return (it_1 - (elsM));
			else if (value < diff && value > 0)
			{
				it_2 = it_1;
				diff = value;
			}
		}
		if (diff == INT_MAX)
			return (vect.end());
		return (it_2 - (elsM));
	}