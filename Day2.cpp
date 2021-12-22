#include <iostream>
#include <fstream>
#include <map>
#include <unordered_map>
#include <string>
#include <vector>
#include <set>

using namespace std;

unordered_map< int, string > unparsedRules;
unordered_map< int, bool > isParsed;
unordered_map< int, set<string> > validStringsForRule;
unordered_map< int, int > numTimesEvaluated;

static const string A_STRING_INPUT = "\"a\"";
static const string B_STRING_INPUT = "\"b\"";

static const string A_STRING = "a";
static const string B_STRING = "b";

class Day2
{
public:
	Day2()
	{

	}

	void Run()
	{
		ifstream infile("inputDay2.txt");

		if (infile.is_open())
		{
			string line;
			const std::string forward = "forward";
			const std::string down = "down";
			const std::string up = "up";
			const std::string delimiter = " ";

			long long result = 0;
			long long depth = 0;
			long long hor = 0;
			long long aim = 0;

			while (getline(infile, line))
			{				
				const int delimiterPos = line.find(delimiter);
				const std::string number = line.substr(delimiterPos + 1);
				const int num = std::stoi(number);

				char first = line[0];
				switch (first)
				{
					case 'u':
					{
						aim -= num;
						break;
					}
					case 'd':
					{
						aim += num;
						break;
					}
					case 'f':
					{
						hor += num;
						depth += (aim * num);
						break;
					}
					default: break;
				}
				
			}

			cout << " Hor:= " << hor << " Dept:= " << depth << " Res = " << hor * depth << std::endl;
		}

	}
};

void RunDay2()
{
	Day2 Day2Obj;
	Day2Obj.Run();
}