#include <iostream>
#include <fstream>
#include <map>
#include <unordered_map>
#include <string>
#include <vector>
#include <set>
#include <array>
#include <algorithm>

#include "Day9.h"


using namespace std;

class Day9
{
public:
	Day9()
	{

	}

	bool isClosing(char c)
	{
		switch (c)
		{
		case ']':
		case ')':
		case '}':
		case '>':
			return true;

		default:
			return false;
		}
	}

	bool isClosingValid(char potentialClose, char potentialOpen)
	{
		switch (potentialClose)
		{
			case ']':
				return potentialOpen == '[';
			case ')':
				return potentialOpen == '(';
			case '}':
				return potentialOpen == '{';
			case '>':
				return potentialOpen == '<';
			default:
				return false;
		}

		return false;
	}

	char GetClosing(char open)
	{
		switch (open)
		{
		case '(':
			return ')';
		case '{':
			return '}';
		case '[':
			return ']';
		case '<':
			return '>';

		}
	}

	void Run()
	{
		ifstream infile("inputDay10.txt");

		string line;

		 map<char, int> ScoreMap{ {')', 3}, {']', 57}, {'}', 1197}, {'>', 25137} };
		 map<char, int> IncompleteMap{ {')', 1}, {']', 2}, {'}', 3}, {'>', 4} };

		long long fileScore = 0;
		vector<long long> scores;

		if (infile.is_open())
		{

			while (getline(infile, line))
			{
				std::vector<char> Stack;
				int doContinue = true;

				for (int i = 0; doContinue && i < line.length(); ++i)
				{ 
					char currChar = line[i];
					if (Stack.size() == 0)
					{
						if (isClosing(currChar))
						{
							fileScore += ScoreMap[currChar];
							doContinue = false;

						}
						else
						{
							Stack.push_back(currChar);
						}
					}
					else
					{
						if (isClosing(line[i]))
						{
							char preOpen = Stack[Stack.size() - 1];
							if (isClosingValid(currChar, preOpen))
							{
								Stack.pop_back();
							}
							else
							{
								fileScore += ScoreMap[currChar];
								doContinue = false;
							}

						}
						else
						{
							Stack.push_back(line[i]);
						}

					}
				}


				if (doContinue && Stack.size() > 0)
				{
					long long currScore = 0;
					for (int i = Stack.size() - 1; i >= 0; --i)
					{
						char close = GetClosing(Stack[i]);
						int score = IncompleteMap[close];
						currScore = (currScore * 5) + score;
					}

					scores.push_back(currScore);


				}
			}

			int num = scores.size();
			sort(scores.begin(), scores.end());
			long long middle = (num / 2);
			cout << fileScore<<endl;
			cout << "Incomplte " << scores[middle] << endl;

			//part 2
		}


	}
};

void RunDay9()
{
	Day9 Day9Obj;
	Day9Obj.Run();
}
