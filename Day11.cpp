

#include <iostream>
#include <fstream>
#include <map>
#include <unordered_map>
#include <string>
#include <vector>
#include <set>
#include <array>
#include <algorithm>

#include "Day11.h"


using namespace std;



int Input[10][10] =
{
	{ 4,7,2,1,2,2,4,6,6,3 },
	{ 6,8,7,5,4,1,5,2,7,6 },
	{ 2,7,4,2,4,4,8,4,2,8 },
	{ 4,8,7,8,2,3,1,5,5,6 },
	{ 5,6,8,4,6,4,3,7,4,3 },
	{ 3,5,5,3,6,8,1,8,6,6 },
	{ 4,7,8,8,1,8,3,6,2,5 },
	{ 4,2,5,5,8,5,6,5,3,2 },
	{ 1,4,1,5,8,1,8,7,7,5 },
	{ 2,3,2,6,8,8,6,1,2,5 }
};

//example
int Example[10][10] =
{
	{ 5,4,8,3,1,4,3,2,2,3 },
	{ 2,7,4,5,8,5,4,7,1,1 },
	{ 5,2,6,4,5,5,6,1,7,3 },
	{ 6,1,4,1,3,3,6,1,4,6 },
	{ 6,3,5,7,3,8,5,4,7,8 },
	{ 4,1,6,7,5,2,4,6,4,5 },
	{ 2,1,7,6,8,4,1,7,2,1 },
	{ 6,8,8,2,8,8,1,1,3,4 },
	{ 4,8,4,6,8,4,8,5,5,4 },
	{ 5,2,8,3,7,5,1,5,2,6 }
};

class Day11
{
public:
	Day11()
	{

	}

	void Run()
	{
		long long NumFlashes = 0;
		for (int step = 0; step < 1000; ++step)
		{
			//Increase by 1
			vector<tuple<int, int>> FlashesRemainingToProcess;

			for (int r = 0; r < 10; ++r)
			{
				for (int c = 0; c < 10; ++c)
				{
					Input[r][c]++;
					if (Input[r][c] == 10)
					{
						FlashesRemainingToProcess.emplace(FlashesRemainingToProcess.begin(), make_tuple( r,c ));
					}
				}
			}

			while (FlashesRemainingToProcess.size() > 0)
			{
				tuple<int, int> Curr = FlashesRemainingToProcess[FlashesRemainingToProcess.size() - 1];				
				FlashesRemainingToProcess.pop_back();
				
				NumFlashes++;

				int Row = get<0>(Curr);
				int Col = get<1>(Curr);

				for (int rD = Row-1; rD <= Row + 1; ++rD)
				{
					if (rD < 0)
					{
						continue;
					}
					if (rD >= 10)
					{
						continue;
					}

					for (int cD = Col-1; cD <= Col+1; ++cD)
					{
						if (rD == Row && cD == Col)
						{
							continue;
						}

						if (cD < 0)
						{
							continue;
						}
						if (cD >= 10)
						{
							continue;
						}

						Input[rD][cD]++;
						if (Input[rD][cD] == 10)
						{
							if (count(FlashesRemainingToProcess.begin(), FlashesRemainingToProcess.end(), make_tuple(rD, cD)) == 0)
							{
								FlashesRemainingToProcess.emplace(FlashesRemainingToProcess.begin(), make_tuple(rD, cD));
							}
						}

					}
				}
			}

			bool allFlashed = true;

			for (int r = 0; r < 10; ++r)
			{
				for (int c = 0; c < 10; ++c)
				{
					if (Input[r][c] >= 10)
					{
						Input[r][c] = 0;
					}
					else
					{
						allFlashed = false;
					}
				}
			}

			if (allFlashed)
			{
				cout << "All Flashed " << step;

				break;
			}

		}

		cout << "Num flashes " << NumFlashes << endl;

	}
};

void RunDay11()
{
	Day11 Day11Obj;
	Day11Obj.Run();
}
