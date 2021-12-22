

#include <iostream>
#include <fstream>
#include <map>
#include <unordered_map>
#include <string>
#include <vector>
#include <set>
#include <array>
#include <algorithm>
#include <queue>
#include <stack>

#include "Day20.h"

using namespace std;

//actual input
string Algo = "##..#.####..#.#.##.#######.######.#####..#...##.###....#..#.##..#....#.#.##.#.#.#...###..###..#.#..#.#####.#.#.##..##.#.###.#..##.###.###...####.#####....#....#..#.#...#.#.#.#.#...#####...##..####.##.##...#.##.#####........#..#####..##.##..###########....#.##.#####.##..#####...#..#.#.##...#.#.#..#...####......#.#.####....##.#.##.####..##..##.#.......#...#.###########.....###.#######....##.#.#######..#.......###.##....#.#..#....##..#.###.#..#.###.###.##..##.#.#...#.#.....###.#.#....###..#.....##.#.#####.....";
//test
//string Algo = "..#.#..#####.#.#.#.###.##.....###.##.#..###.####..#####..#....#..#..##..###..######.###...####..#..#####..##..#.#####...##.#.#..#.##..#.#......#.###.######.###.####...#.##.##..#..#..#####.....#.#....###..#.##......#.....#..#..#..##..#...##.######.####.####.#.#...#.......#..#.#.#...####.##.#......#..#...##.#.##..#...##.#.##..###.#......#.#.......#.#.#.####.###.##...#.....####.#..#..#.##.#....##..#.####....##...##..#...#......#.#.......#.......##..####..#...#.#.#...##..#.#..###..#####........#..####......#..#";

class Day20
{
public:



	string ToStringKey(int r, int c) const
	{
		return "(" + to_string(r) + "," + to_string(c) + ")";
	}

	Day20()
	{
	}

	map<string, bool> State;

	int minR = 0;
	int minC = 0;
	int maxR = 0;
	int maxC = 0;
	const int NumIterations = 50;

	void PrintCurrentImage()
	{
		for (int r = minR; r < maxR; ++r)
		{
			for (int c = minC; c < maxC; ++c)
			{
				string key = ToStringKey(r, c);
				if (State[key])
				{
					cout << "#";
				}
				else
				{
					cout << ".";
				}
			}
			cout << "\n";
		}
	}

	bool IsLit(char C)
	{
		return C == '#';
	}

	void Run()
	{
		ifstream infile("inputDay20.txt");

		string line;

		if (infile.is_open())
		{
			int currR = 0;
			int currC = 0;
			while (getline(infile, line))
			{
				maxC = line.length() > maxC ? line.length() : maxC;

				for (int i = 0; i < line.length(); ++i)
				{
					string key = ToStringKey(currR, currC);

					State[key] = IsLit(line[i]);
					currC++;
				}
				currR++;
				currC = 0;
			}

			maxR = currR;
		}

		//PrintCurrentImage();

		bool defaultLit = false;
		bool doesChange = (Algo[0] == '#');

		for (int currIteration = 0; currIteration < NumIterations; ++currIteration)
		{
			cout << "iteration: " << currIteration<<endl;
			map<string, bool> StateCopy = State;
			for (int r = minR - 1; r <= maxR; ++r)
			{
				for (int c = minC - 1; c <= maxC; ++c)
				{
					string lookUpString = "0123456789";
					int currentIndex = 0;

					for (int rDelta = -1; rDelta <= 1; ++rDelta)
					{
						for (int cDelta = -1; cDelta <= 1; ++cDelta)
						{
							string innerKey = ToStringKey(r + rDelta, c + cDelta);
							bool shouldConsiderLit = false;

							if (State.find(innerKey) == State.end())
							{
								shouldConsiderLit = defaultLit;
							}
							else
							{
								shouldConsiderLit = State[innerKey];
							}

							if (shouldConsiderLit)
							{
								lookUpString[currentIndex] = '1';
							}
							else
							{
								lookUpString[currentIndex] = '0';
							}
							++currentIndex;
						}
					}

					int loopUpNumber = stoi(lookUpString, nullptr, 2);
					string currentKey = ToStringKey(r, c);

					if (IsLit(Algo[loopUpNumber]))
					{
						StateCopy[currentKey] = true;
					}
					else
					{
						StateCopy[currentKey] = false;
					}
				}
			}


			minR = minR - 1;
			minC = minC - 1;
			maxR = maxR + 1;
			maxC = maxC + 1;

			if (doesChange)
			{
				defaultLit = !defaultLit;
			}

			State = StateCopy;
			//cout << "\n\n After iteration: " << currIteration + 1<<"\n\n";
			//PrintCurrentImage();
			//cout << "\n*****************\n";
		}

		int NumLit = 0;
		for (int r = minR; r < maxR; ++r)
		{
			for (int c = minC; c < maxC; ++c)
			{
				string currentKey = ToStringKey(r, c);
				if (State[currentKey])
				{
					++NumLit;
				}

			}
		}

		cout << NumLit;
	}

};

void RunDay20()
{
	Day20 Day20Obj;
	Day20Obj.Run();
}