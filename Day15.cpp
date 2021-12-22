

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

#include "Day15.h"

using namespace std;

struct Point
{
	Point() : X(-1), Y(-1), TotalCost(-1), ParentX(-1), ParentY(-1)
	{

	}
	int X = -1;
	int Y = -1;
	int TotalCost = -1;
	int MyCost = -1;

	int ParentX = -1;
	int ParentY = -1;
};

Point InputMap[500][500];

struct compare
{
	bool operator()(const Point*& l, const Point*& r)
	{
		return l->TotalCost > r->TotalCost;
	}
};

class Day15
{
public:
	Day15()
	{
	}

	void Run()
	{
		ifstream infile("inputDay15.txt");

		string line;

		int len = 500;

		if (infile.is_open())
		{
			int Length = 0;
			int r = 0; 
			while (getline(infile, line))
			{
				Length = line.length();
				for (unsigned int c = 0; c < line.length(); c++)
				{
					InputMap[r][c].MyCost = (int)line[c] - (int)'0';
					InputMap[r][c].X = r;
					InputMap[r][c].Y = c;
					InputMap[r][c].TotalCost = INT_MAX;
					InputMap[r][c].ParentX = -1;
					InputMap[r][c].ParentY = -1;
				}

				r++;
			}

			for (int x = 0; x < 500; ++x)
			{
				for (int y = 0; y < 500; ++y)
				{
					int lookUpX = x % 100;
					int lookUpY = y % 100;

					const Point& Ref = InputMap[lookUpX][lookUpY];

					int xDiv100 = x / 100;
					int yDiv100 = y / 100;


					int Cost = (xDiv100 + yDiv100) + Ref.MyCost;
					if (Cost > 9)
					{
						Cost = Cost - 9;
					}

					Point& Curr = InputMap[x][y];
					Curr.MyCost = Cost;
					Curr.X = x;
					Curr.Y = y;
					Curr.TotalCost = INT_MAX;
					Curr.ParentX = -1;
					Curr.ParentY = -1;
				}
			}

			int StartX = 0;
			int StartY = 0;

			int EndX = 99;
			int EndY = 99;

			auto cmp = [](Point* l, Point* r)
			{
				return l->TotalCost < r->TotalCost;
			};

			vector<Point*> MyQueue;

			Point& StartPoint = InputMap[0][0];
			StartPoint.TotalCost = 0;

			MyQueue.push_back(&StartPoint);

			int numIterations = 0;

			while (!MyQueue.empty())
			{
				numIterations++;
				Point& CurrentPoint = *(*(MyQueue.begin()));
				
				if (CurrentPoint.X == len - 1 && CurrentPoint.Y == len - 1)
				{
					cout << InputMap[len - 1][len - 1].TotalCost;
					break;
				}

				MyQueue.erase(MyQueue.begin());

				auto ProcessPointLambda = [&](int x, int y)
				{
					if (x >= 0 && x < len && y >= 0 && y < len)
					{
						Point& NewPointEncountered = InputMap[x][y];
						if (NewPointEncountered.TotalCost > (CurrentPoint.TotalCost + NewPointEncountered.MyCost))
						{
							NewPointEncountered.TotalCost = CurrentPoint.TotalCost + NewPointEncountered.MyCost;
							NewPointEncountered.ParentX = CurrentPoint.X;
							NewPointEncountered.ParentY = CurrentPoint.Y;

							auto searchRes = find(MyQueue.begin(), MyQueue.end(), (&NewPointEncountered));
							if (searchRes != MyQueue.end())
							{
								MyQueue.erase(searchRes);
							}

							MyQueue.push_back(&NewPointEncountered);
						}

					}
				};

				ProcessPointLambda(CurrentPoint.X - 1, CurrentPoint.Y); // top
				ProcessPointLambda(CurrentPoint.X + 1, CurrentPoint.Y); //bot
				ProcessPointLambda(CurrentPoint.X, CurrentPoint.Y - 1); //left
				ProcessPointLambda(CurrentPoint.X, CurrentPoint.Y + 1); //right

				sort(MyQueue.begin(), MyQueue.end(), cmp);
			}

			int CurrX = len - 1;
			int CurrY = len - 1;

			auto ConvertToString = [](int x, int y)
			{
				string toRet = to_string(x) + "," + to_string(y);

				return toRet;
			};

			map<string, bool> Occuerences;

			while (true)
			{
				cout << "(" << CurrX << ", " << CurrY << ")" << endl;

				string curr = ConvertToString(CurrX, CurrY);
				Occuerences.insert({ curr, true });

				if (CurrX == 0 && CurrY == 0)
				{
					break;
				}

				int newX = InputMap[CurrX][CurrY].ParentX;
				int newY = InputMap[CurrX][CurrY].ParentY;

				CurrX = newX;
				CurrY = newY;
			}

			cout << "****************\n\n\n";

			for (int x = 0; x < len; x++)
			{
				for (int y = 0; y < len; y++)
				{
					string curr = ConvertToString(x, y);
					if (Occuerences.find(curr) != Occuerences.end())
					{
						cout << "#";
					}
					else
					{
						cout << "_";
					}
				}

				cout << "\n";
			}
		}
	}

};

void RunDay15()
{
	Day15 Day15Obj;
	Day15Obj.Run();
}