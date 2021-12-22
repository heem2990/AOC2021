

#include <iostream>
#include <fstream>
#include <map>
#include <unordered_map>
#include <string>
#include <vector>
#include <set>
#include <array>
#include <algorithm>

#include "Day12.h"


using namespace std;


class Day12
{
public:
	Day12()
	{
	}

	bool IsLowerCase(char c)
	{
		return c >= 'a' && c <= 'z';
	}


	map<string, string> Connections;
	map<string, vector<string>> NodeToNeighbors;

	const string Start = "start";
	const string End = "end";


	long long numPaths{ 0 };

	vector<string> ToProcess;
	map<string, int> NumTimesProcessed;
	string SingleSmallCaveVisitedTwice = "";


	void Run()
	{
		ifstream infile("inputDay12.txt");

		string line;

		if (infile.is_open())
		{

			while (getline(infile, line))
			{
				int locOfDash = line.find('-');
				string first = line.substr(0, locOfDash);
				string second = line.substr(locOfDash + 1);

				Connections.insert({ first, second });

				if (NodeToNeighbors.find(first) == NodeToNeighbors.end())
				{
					vector<string> NewNeighbors;
					NewNeighbors.push_back(second);

					NodeToNeighbors.insert({ first, NewNeighbors });

				}
				else
				{
					auto foundElement = NodeToNeighbors.find(first);
					foundElement->second.push_back(second);
				}

				if (NodeToNeighbors.find(second) == NodeToNeighbors.end())
				{
					vector<string> NewNeighbors;
					NewNeighbors.push_back(first);

					NodeToNeighbors.insert({ second, NewNeighbors });

				}
				else
				{
					auto foundElement = NodeToNeighbors.find(second);
					foundElement->second.push_back(first);
				}

				cout << first << " " << second << endl;
			}
		}
				
		Process(Start, true);

		cout << "Answer P1: "<<numPaths<<endl;
	}

	void Process(string toProcess, bool ignoreStart)
	{
		if (toProcess == End)
		{
			++numPaths;
			return;
		}

		if (!ignoreStart && toProcess == Start)
		{
			return;
		}

		bool smallCaveVisitedTwiceThisRound = false;

		auto entry = NumTimesProcessed.find(toProcess);

		if (entry == NumTimesProcessed.end())
		{
			NumTimesProcessed.insert({ toProcess , 1 });
		}
		else if (entry->second == 0)
		{
			entry->second = 1;
		}
		else if (entry->second == 1)
		{
			if (IsLowerCase(toProcess[0]))
			{
				if (SingleSmallCaveVisitedTwice != "")
				{
					return;
				}
				else
				{
					smallCaveVisitedTwiceThisRound = true;
					SingleSmallCaveVisitedTwice = toProcess;
				}
			}

			entry->second = 2;
		}
		else
		{
			if (IsLowerCase(toProcess[0]))
			{
				return;
			}

			entry->second++;
		}

		auto foundElement = NodeToNeighbors.find(toProcess);
		for (auto iter = foundElement->second.begin(); iter != foundElement->second.end(); ++iter)
		{
			Process(*iter, false);
		}

		if (smallCaveVisitedTwiceThisRound)
		{
			SingleSmallCaveVisitedTwice = "";
		}

		auto newEntry = NumTimesProcessed.find(toProcess);
		newEntry->second--;
	}
};

void RunDay12()
{
	Day12 Day12Obj;
	Day12Obj.Run();
}
