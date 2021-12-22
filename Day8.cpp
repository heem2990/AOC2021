#include <iostream>
#include <fstream>
#include <map>
#include <unordered_map>
#include <string>
#include <vector>
#include <set>
#include <array>
#include <algorithm>

#include "Day8.h"


using namespace std;

class Day8
{
public:
	Day8()
	{

	}

	struct Coordinates
	{
		Coordinates(int r, int c) : Row(r), Col(c)
		{

		}
		int Row;
		int Col;

		bool operator==(const Coordinates& rhs)
		{
			return rhs.Row == Row && rhs.Col == Col;
		}
	};

	int Input[100][100];
	int BasinInclusion[100][100];

	void Run()
	{
		ifstream infile("inputDay8.txt");

		string line;

		if (infile.is_open())
		{
			int r = 0;
			int c = 0;

			while (getline(infile, line))
			{
				c = 0;

				for (int i = 0; i < line.length(); ++i)
				{
					int currInt = (int)(line[i] - '0');

					Input[r][c] = currInt;
					c++;
				}

				r++;
			}			
		}

		vector<int> RiskLevels;

		for (int r = 0; r < 100; ++r)
		{
			for (int c = 0; c < 100; ++c)
			{
				int currVal = Input[r][c];

				int valueOfUp = r - 1 < 0 ? 10000 : Input[r - 1][c];
				int valueOfDown = r + 1 >= 100 ? 1000 : Input[r + 1][c];
				int valueOfLeft = c - 1 < 0 ? 1000 : Input[r][c - 1];
				int valueOfRight = c + 1 >= 100 ? 1000 : Input[r][c + 1];

				bool UpGreater = valueOfUp > currVal;
				bool DownGreater = valueOfDown > currVal;
				bool LeftGreater = valueOfLeft > currVal;
				bool RightGReater = valueOfRight > currVal;

				if (UpGreater && DownGreater && LeftGreater && RightGReater)
				{
					RiskLevels.push_back(currVal+1);
				}

			}
		}

		long long total = 0;

		for (auto iter = RiskLevels.begin(); iter != RiskLevels.end(); ++iter)
		{
			total += *iter;
		}

		cout << "Total Risk " << total<< endl;

		vector<int> BasinSizes;

		for (int r = 0; r < 100; ++r)
		{
			for (int c = 0; c < 100; ++c)
			{
				BasinInclusion[r][c] = -1;
			}
		}

		int currentBasin = 0;

		for (int r = 0; r < 100; r++)
		{
			for (int c = 0; c < 100; c++)
			{
				if (Input[r][c] == 9)
				{
					BasinInclusion[r][c] = 1000;
					continue;
				}

				if (BasinInclusion[r][c] != -1)
				{
					continue;
				}

				int sizeOfCurrentBasin = 0;
				currentBasin++;

				vector<Day8::Coordinates> CoordinatesToAnalyze;
				CoordinatesToAnalyze.emplace(CoordinatesToAnalyze.begin(), Coordinates(r, c));

				while (CoordinatesToAnalyze.size() > 0)
				{
					Day8::Coordinates CurrentCoordinateToAnalyse = CoordinatesToAnalyze[CoordinatesToAnalyze.size() - 1];
					CoordinatesToAnalyze.pop_back();

					if (Input[CurrentCoordinateToAnalyse.Row][CurrentCoordinateToAnalyse.Col] == 9)
					{
						BasinInclusion[CurrentCoordinateToAnalyse.Row][CurrentCoordinateToAnalyse.Col] = 1000;
						continue;
					}

					Coordinates Up(CurrentCoordinateToAnalyse.Row - 1, CurrentCoordinateToAnalyse.Col);
					Coordinates Down(CurrentCoordinateToAnalyse.Row + 1, CurrentCoordinateToAnalyse.Col);
					Coordinates Left(CurrentCoordinateToAnalyse.Row, CurrentCoordinateToAnalyse.Col - 1);
					Coordinates Right(CurrentCoordinateToAnalyse.Row, CurrentCoordinateToAnalyse.Col + 1);

					if (Up.Row >= 0 && std::find(CoordinatesToAnalyze.begin(), CoordinatesToAnalyze.end(), Up) == CoordinatesToAnalyze.end() && BasinInclusion[Up.Row][Up.Col] == -1)
					{
						CoordinatesToAnalyze.emplace(CoordinatesToAnalyze.begin(), Up);
					}

					if (Down.Row < 100 && std::find(CoordinatesToAnalyze.begin(), CoordinatesToAnalyze.end(), Down) == CoordinatesToAnalyze.end() && BasinInclusion[Down.Row][Down.Col] == -1)
					{
						CoordinatesToAnalyze.emplace(CoordinatesToAnalyze.begin(), Down);
					}

					if (Left.Col >= 0 && std::find(CoordinatesToAnalyze.begin(), CoordinatesToAnalyze.end(), Left) == CoordinatesToAnalyze.end() && BasinInclusion[Left.Row][Left.Col] == -1)
					{
						CoordinatesToAnalyze.emplace(CoordinatesToAnalyze.begin(), Left);
					}

					if (Right.Col < 100 && std::find(CoordinatesToAnalyze.begin(), CoordinatesToAnalyze.end(), Right) == CoordinatesToAnalyze.end() && BasinInclusion[Right.Row][Right.Col] == -1)
					{
						CoordinatesToAnalyze.emplace(CoordinatesToAnalyze.begin(), Right);
					}

					BasinInclusion[CurrentCoordinateToAnalyse.Row][CurrentCoordinateToAnalyse.Col] = currentBasin;
					sizeOfCurrentBasin++;
				}

				BasinSizes.push_back(sizeOfCurrentBasin);
			}
		}


		sort(BasinSizes.begin(), BasinSizes.end());
		int size = BasinSizes.size();
		long long SecondOutput = BasinSizes[size-1] * BasinSizes[size-2] * BasinSizes[size-3];

		cout << "2nd = " << SecondOutput << endl;
	}
};

void RunDay8()
{
	Day8 Day8Obj;
	Day8Obj.Run();
}

//int StartRow = r - 1 < 0 ? r : r - 1;
//int EndRow = r + 1 >= 100 ? r : r + 1;

//int StartCol = c - 1 < 0 ? c : c - 1;
//int EndCol = c + 1 < 0 ? c : c + 1;

//bool IsAnyLower = false;

//for (int miniR = StartRow; miniR <= EndRow; miniR++)
//{
//	for (int miniC = StartCol; miniC <= EndCol; miniC++)
//	{
//		if (miniR == r && miniC == c)
//		{
//			continue
//		}
//	}
//}
