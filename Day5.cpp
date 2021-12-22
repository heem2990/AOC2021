#include <iostream>
#include <fstream>
#include <map>
#include <unordered_map>
#include <string>
#include <vector>
#include <set>
#include <array>

#include "Day5.h"

using namespace std;

struct Point
{
	int X{ -1 };
	int Y{ -1 };

	Point(int x, int y)
		:X(x)
		,Y(y)
	{

	}

	string ToString() const
	{
		return "(" + to_string(X) + "," + to_string(Y) + ")";
	}
};

struct Line
{
	Point Point1;
	Point Point2;
	int X1{ -1 };
	int Y1{ -1 };
	int X2{ -1 };
	int Y2{ -1 };

	Line(int x1, int y1, int x2, int y2)
		: Point1(x1, y1)
		, Point2(x2, y2)
	{

	}

	void Print()
	{
		cout << "X1 = " << Point1.X << " Y1 = " << Point1.Y << " X2 = " << Point2.X << " Y2 = " << Point2.Y << endl;
	}

	bool IsHorizontalOrVertical() const
	{
		return IsHorizontal() || IsVertical();
	}

	bool IsHorizontal() const
	{
		return Point1.X == Point2.X;
	}

	bool IsVertical() const
	{
		return Point1.Y == Point2.Y;
	}
};

Line GetLineParamsFromString(const string& input)
{
	constexpr char delimiter = '-';
	constexpr char comma = ',';
	
	const int delimiterPos = input.find(delimiter);
	const string firstSet = input.substr(0, delimiterPos - 1);
	const string secondSet = input.substr(delimiterPos + 3);

	const int commaFirstSet = firstSet.find(comma);
	const int commaSecondSet = secondSet.find(comma);

	const int x1 = stoi(firstSet.substr(0, commaFirstSet));
	const int y1 = stoi(firstSet.substr(commaFirstSet + 1));

	const int x2 = stoi(secondSet.substr(0, commaSecondSet));
	const int y2 = stoi(secondSet.substr(commaSecondSet + 1));

	Line toReturn(x1, y1, x2, y2);

	return toReturn;
}

class Day5
{
public:
	Day5()
	{

	}

	void Run()
	{
		ifstream infile("inputDay5.txt");

		std::vector<Line> Inputs;
		std::vector<Line> OnlyHorizontalOrVerticalInputs;
		std::vector<Line> OnlyDiagonals;

		if (infile.is_open())
		{
			string line;
			while (getline(infile, line))
			{
				Line converted = GetLineParamsFromString(line);
				cout << line <<endl;
							
				Inputs.push_back(converted);

				if (converted.IsHorizontalOrVertical())
				{
					OnlyHorizontalOrVerticalInputs.push_back(converted);
					converted.Print();
				}
				else
				{
					OnlyDiagonals.push_back(converted);
				}
			}

			std::map<string, int> PointToOccurencesMap;

			for (auto iter = OnlyHorizontalOrVerticalInputs.begin(); iter != OnlyHorizontalOrVerticalInputs.end(); ++iter)
			{
				const int xStart = min(iter->Point1.X, iter->Point2.X);
				const int xEnd = max(iter->Point1.X, iter->Point2.X);

				const int yStart = min(iter->Point1.Y, iter->Point2.Y);
				const int yEnd = max(iter->Point1.Y, iter->Point2.Y);

				for (int i = xStart; i <= xEnd; ++i)
				{
					for (int j = yStart; j <= yEnd; ++j)
					{
						const Point Curr(i, j);
						const string pointString = Curr.ToString();
						auto search = PointToOccurencesMap.find(pointString);
						if (search == PointToOccurencesMap.end())
						{
							PointToOccurencesMap.insert({ pointString, 1 });
						}
						else
						{
							search->second++;
						}
					}
				}

			}

			for (auto iter = OnlyDiagonals.begin(); iter != OnlyDiagonals.end(); ++iter)
			{
				const int x1 = iter->Point1.X;
				const int x2 = iter->Point2.X;

				const int xDelta = x1 < x2 ? 1 : -1;

				const int y1 = iter->Point1.Y;
				const int y2 = iter->Point2.Y;

				const int yDelta = y1 < y2 ? 1 : -1;

				if (abs(x2 - x1) == abs(y2 - y1))
				{
					int i = x1;
					int j = y1;

					while (true)
					{

						const Point Curr(i, j);
						const string pointString = Curr.ToString();
						auto search = PointToOccurencesMap.find(pointString);
						if (search == PointToOccurencesMap.end())
						{
							PointToOccurencesMap.insert({ pointString, 1 });
						}
						else
						{
							search->second++;
						}

						if (i == x2 || j == y2)
						{
							break;
						}

						i += xDelta;
						j += yDelta;
					}

				}
				else
				{
					cout << "WTF";
				}


				const int xStart = min(iter->Point1.X, iter->Point2.X);
				const int xEnd = max(iter->Point1.X, iter->Point2.X);

				const int yStart = min(iter->Point1.Y, iter->Point2.Y);
				const int yEnd = max(iter->Point1.Y, iter->Point2.Y);

				

			}


			int count = 0;

			for (auto iter = PointToOccurencesMap.begin(); iter != PointToOccurencesMap.end(); ++iter)
			{
				if (iter->second >= 2)
				{
					++count;
				}
			}

			cout << "\n\n Result = " << count << endl;
		}

	}
};

void RunDay5()
{
	Day5 Day5Obj;
	Day5Obj.Run();
}