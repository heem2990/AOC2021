#include <iostream>
#include <fstream>
#include <map>
#include <unordered_map>
#include <string>
#include <vector>
#include <set>
#include <array>
#include <algorithm>

#include "Day7.h"


using namespace std;

class Day7
{
public:
	Day7()
	{

	}

	void Run()
	{
		ifstream infile("inputDay7.txt");

		if (infile.is_open())
		{
			string line;
			long long total = 0;

			long long outputTotal = 0;
			while (getline(infile, line))
			{
				//cout << line << endl;

				char delim1 = '|';
				char spaceDelim = ' ';

				string signalStr = line.substr(0, line.find(delim1) - 1);
				string outputStr = line.substr(line.find(delim1) + 2);

				vector<string> SignalStrings;
				vector<string> OutputStrings;
				vector<string> AllStrings;

				while (true)
				{
					int index = signalStr.find(spaceDelim);
					string first = signalStr.substr(0, index);
					string second = index != string::npos ? signalStr.substr(index + 1) : "";

					int lengthOffirst = first.length();
					signalStr = second;

					//cout << first << endl;
					sort(first.begin(), first.end());
					SignalStrings.push_back(first);
					AllStrings.push_back(first);

					if (index == string::npos)
					{
						//cout << "|||||||||" << endl;
						break;
					}
				}

				while (true)
				{
					int index = outputStr.find(spaceDelim);
					string first = outputStr.substr(0, index);
					string second = index != string::npos ? outputStr.substr(index + 1) : "";

					int lengthOffirst = first.length();
					//cout << first << endl;

					sort(first.begin(), first.end());
					OutputStrings.push_back(first);
					AllStrings.push_back(first);

					//switch (lengthOffirst)
					//{
					//case 2:
					//	cout << "1" <<endl;
					//	break;
					//case 4:
					//	cout << "4: " <<endl;
					//	break;
					//case 3:
					//	cout << "7: " <<endl;
					//	break;
					//case 7:
					//	cout << "8: " <<endl;
					//	break;
					//default:
					//{
					//	break;
					//}
					//}

					outputStr = second;

					if (index == string::npos)
					{
						//cout << "*****" << endl;
						break;
					}

				}

				cout << "-----------------------------------------------------------" << endl;

				bool found1 = false;
				bool found4 = false;
				bool found7 = false;
				bool found8 = false;

				map<string, int> StringToInt;
				map<int, string> IntToString;

				vector<string> StringsFor235;
				vector<string> StringsFor069;

				for (int i = 0; i < AllStrings.size(); ++i)
				{
					string currString = AllStrings[i];

					int length = currString.length();
					switch (length)
					{
					case 2:
					{
						cout << "1 ";
						StringToInt.insert({ currString, 1 });
						IntToString.insert({ 1, currString });
						found1 = true;
						break;
					}
					case 3:
					{
						cout << "7 ";
						StringToInt.insert({ currString, 7 });
						IntToString.insert({ 7, currString });
						found7 = true;
						break;
					}
					case 4:
					{
						cout << "4 ";

						StringToInt.insert({ currString, 4 });
						IntToString.insert({ 4, currString });
						found4 = true;
						break;
					}
					case 5:
					{
						StringsFor235.push_back(currString);
						cout << "2,3,5 ";
						break;
					}
					case 6:
					{
						StringsFor069.push_back(currString);
						cout << "0,6,9 ";
						break;
					}
					case 7:
					{

						StringToInt.insert({ currString, 8 });
						IntToString.insert({ 8, currString });
						found8 = true;
						cout << "8";
						break;
					}
					}
					//cout << "********" << endl;
					//cout << *iter << endl;
				}
				if (!(found1 && found4 && found7 && found8))
				{
					cout << "WHAT?lSD" << endl;
				}
				auto string1 = IntToString.find(1);
				auto string4 = IntToString.find(4);

				set<char> CharsFor1(string1->second.begin(), string1->second.end());
				set<char> CharsFor4(string4->second.begin(), string4->second.end());

				for (int i = 0; i < StringsFor235.size(); ++i)
				{
					string currString = StringsFor235[i];
					set<char> CharsForCurr(currString.begin(), currString.end());

					set<int> intersectWith1Set;
					set<int> intersectWith4Set;

					set_intersection(CharsFor1.begin(), CharsFor1.end(), CharsForCurr.begin(), CharsForCurr.end(), std::inserter(intersectWith1Set, intersectWith1Set.begin()));
					set_intersection(CharsFor4.begin(), CharsFor4.end(), CharsForCurr.begin(), CharsForCurr.end(), std::inserter(intersectWith4Set, intersectWith4Set.begin()));

					if (intersectWith1Set.size() == 2)
					{
						StringToInt.insert({ currString, 3 });
						IntToString.insert({ 3, currString });
					}
					else if(intersectWith1Set.size() == 1)
					{
						if (intersectWith4Set.size() == 2)
						{
							StringToInt.insert({ currString, 2 });
							IntToString.insert({ 2, currString });
						}
						else if (intersectWith4Set.size() == 3)
						{

							StringToInt.insert({ currString, 5 });
							IntToString.insert({ 5, currString });
						}
						else
						{
							cout << "WTF";
						}
					}
					else
					{
						cout << "WTF";
					}
				}

				//069
				for (int i = 0; i < StringsFor069.size(); ++i)
				{
					string currString = StringsFor069[i];
					set<char> CharsForCurr(currString.begin(), currString.end());

					set<int> intersectWith1Set;
					set<int> intersectWith4Set;

					set_intersection(CharsFor1.begin(), CharsFor1.end(), CharsForCurr.begin(), CharsForCurr.end(), std::inserter(intersectWith1Set, intersectWith1Set.begin()));
					set_intersection(CharsFor4.begin(), CharsFor4.end(), CharsForCurr.begin(), CharsForCurr.end(), std::inserter(intersectWith4Set, intersectWith4Set.begin()));

					if (intersectWith1Set.size() == 1)
					{
						StringToInt.insert({ currString, 6 });
						IntToString.insert({ 6, currString });
					}
					else if (intersectWith1Set.size() == 2)
					{
						if (intersectWith4Set.size() == 4)
						{
							StringToInt.insert({ currString, 9 });
							IntToString.insert({ 9, currString });
						}
						else if (intersectWith4Set.size() == 3)
						{

							StringToInt.insert({ currString, 0 });
							IntToString.insert({ 0, currString });
						}
						else
						{
							cout << "WTF";
						}
					}
					else
					{
						cout << "WTF";
					}
				}

				int currNum = 0;
				for (auto iter = OutputStrings.begin(); iter != OutputStrings.end(); ++iter)
				{
					auto Entry = StringToInt.find(*iter);
					int currDig = Entry->second;
					currNum = ( currNum * 10 ) + currDig;
				}

				outputTotal += currNum;

			}

			cout << "Tot:" << outputTotal;
		}
	}
};

void RunDay7()
{
	Day7 Day7Obj;
	Day7Obj.Run();
}