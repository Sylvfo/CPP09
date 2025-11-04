#include "PmergeMeVect.hpp"

	void PmergeMeVect::FordJohnsonAlgo()
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

	void PmergeMeVect::swapNbrs()
	{
		oddeven = this->_myVect.size() % 2;
		for (_vit = _myVect.begin(); _vit < _myVect.end() - oddeven; _vit += 2)
		{
			if (*_vit > *(_vit + 1))
				std::swap(*_vit, *(_vit + 1));
		}
		els *= 2;
		if (els <= static_cast<int>(_myVect.size()))
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

	void PmergeMeVect::swapBlocks()
	{
		oddeven = _myVect.size() % els;
		for (_vit = _myVect.begin(); _vit < _myVect.end() - oddeven; _vit += els)
		{
			if (*(_vit + ((els / 2) - 1)) > *(_vit + (els - 1)))
				std::swap_ranges(_vit, (_vit + (els / 2)), _vit + (els / 2));
		}
		els *= 2;
		if (els <= static_cast<int>(_myVect.size()))
			FordJohnsonAlgo();
		else
		{
			els /= 2;
			RecLevels = WAYDOWN;
			FordJohnsonAlgo();
		}
	}

	void PmergeMeVect::MergeInsert()
	{
		ToMainPendRest();
		MergePendinMain();
		BackInmyVect();
		if (els == 1)
			return;
		els /= 2;
		FordJohnsonAlgo();
	}

	void PmergeMeVect::ToMainPendRest()
	{
		oddeven = _myVect.size() % els;
		_mvit = _mainV.begin();
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
		if (oddeven > 0)
		{
			_restV.resize(oddeven);
			std::copy(_myVect.end() - oddeven, _myVect.end(), _restV.begin());
		}
		_myVect.clear();
		_myVect.resize(_containerSize);// ou vect size de base... ou pas besoin?
		//_myVect.resize(_mainVsize + _pendV.size() +_restV.size());// ou vect size de base... ou pas besoin?
	}

	void PmergeMeVect::MergePendinMain()
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

	void PmergeMeVect::BackInmyVect()
	{
		_mainVsize = static_cast<int>(_mainV.size());
		std::copy(_mainV.begin(), _mainV.end(), _myVect.begin());
		if (oddeven > 0)
			std::copy(_restV.begin(), _restV.end(), _myVect.begin() + _mainVsize);
		_mainV.clear();
		_pendV.clear();
		_restV.clear();
	}

	std::vector<int>::iterator PmergeMeVect::findNext(std::vector<int> &vect, int n, int els)
	{
		std::vector<int>::iterator it_1;
		std::vector<int>::iterator it_2;
		
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