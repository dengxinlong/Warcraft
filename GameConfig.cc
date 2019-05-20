 ///
 /// @file    GameConfig.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2019-05-19 21:00:07
 ///
 
#include "GameConfig.h"
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;
 
namespace warcraft
{

GameConfig * GameConfig::_pInstance = getInstance();

void GameConfig::readFromFile(const string & filename)
{
	ifstream ifs(filename);
	if(!ifs) {
		cout << ">>> ifstream open file " << filename << "error!" << endl;
		return;
	}
	readFromStream(ifs);
	ifs.close();
}

void GameConfig::readFromConsole()
{
	cout << ">>> pls input test data:" << endl;
	readFromStream(cin);
}


size_t GameConfig::headquartersInitialElements()
{
	return _groups[_currentGroupId]._initElements;
}

size_t GameConfig::warriorInitalLife(WARRIOR_TYPE key)
{
	return _groups[_currentGroupId]._initLifes[key];
}

void GameConfig::debug() const
{
	for(auto & initdata : _groups) {
		cout << ">> elements:" << initdata._initElements << endl;
		cout << ">> ";
		for(auto & pair : initdata._initLifes) {
			cout << pair.second << " ";
		}
		cout << endl << endl;
	}
}

void GameConfig::readFromStream(istream & is)
{
	//第一行:
	//ifs >> groupCount;
	string line;
	getline(is, line);
	int groupCount;
	{
	istringstream iss(line);
	iss >> groupCount;
	}
	//cout << "groupCount " << groupCount << endl;
	for(int idx = 0; idx < groupCount; ++idx) {
		InitData initData;
		//数据第一行
		getline(is, line);
		{
		istringstream iss(line);
		iss >> initData._initElements;
		//cout << "_initElements:" << initData._initElements << endl;
		}// 语句块

		//数据第二行
		getline(is, line);
		{
		istringstream iss(line);
		int value, warriorIdx = 0;
		while(iss >> value) {
			//cout << value << "- ";
			initData._initLifes.insert(std::make_pair(_initOrder[warriorIdx++], value));
		}
		}// 语句块
		_groups.push_back(std::move(initData));
	}
}
}// end of namespace warcraft