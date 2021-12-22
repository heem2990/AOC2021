#include <iostream>
#include <fstream>
#include <map>
#include <unordered_map>
#include <string>
#include <vector>
#include <set>
#include <array>

#include "Day4.h"

using namespace std;

const int InputNums[] =
{
	83,69,34,46,30,23,19,75,22,37,89,78,32,39,11,44,95,43,26,48,84,53,94,88,18,40,62,35,27,42,15,2,91,20,4,64,99,71,54,97,52,36,28,7,74,45,70,86,98,1,61,50,68,6,77,8,57,47,51,72,65,3,49,24,79,13,17,92,41,80,63,67,82,90,55,0,10,93,38,21,59,73,33,31,9,76,5,66,16,58,85,87,12,29,25,14,96,56,60,81
};

struct BingoBoard
{
	int Board[5][5];

	BingoBoard()
	{
		HasWon = false;
		Numbers.clear();
	}

	void Clear()
	{
		Numbers.clear();
		for (int r = 0; r < 5; ++r)
		{
			for (int c = 0; c < 5; ++c)
			{
				Board[r][c] = -1;
			}
		}
	}

	void SetNumber(int r, int c, int val)
	{
		Board[r][c] = val;
		Numbers.push_back(val);
	}

	int CalculateTotalOfRemaining() const
	{
		int sum = 0;
		for (int r = 0; r < 5; ++r)
		{
			for (int c = 0; c < 5; ++c)
			{
				if (Board[r][c] != -1)
				{
					sum += Board[r][c];
				}
			}
		}

		return sum;
	}

	bool NumberCalled(int val)
	{
		if (HasNumber(val))
		{
			int foundRow = -1;
			int foundCol = -1;
			for (int r = 0; r < 5; ++r)
			{
				for (int c = 0; c < 5; ++c)
				{
					if (Board[r][c] == val)
					{
						Board[r][c] = -1;

						foundRow = r;
						foundCol = c;

						break;
					}
				}
			}

			if (foundRow != -1 && foundCol != -1)
			{
				bool isRowFinished = true;
				for (int c = 0; c < 5; ++c)
				{
					if (Board[foundRow][c] != -1)
					{
						isRowFinished = false;
						break;
					}
				}

				bool isColFinished = true;
				for (int r = 0; r < 5; ++r)
				{
					if (Board[r][foundCol] != -1)
					{
						isColFinished = false;
						break;
					}
				}

				if (isRowFinished || isColFinished)
				{
					HasWon = true;
					return true;
				}
			}
			else
			{
				cout << "WTF";
			}
		}

		return false;
	}

	bool GetHasWon() const { return HasWon; };

private:
	bool HasNumber(int number) const
	{
		return (std::find(Numbers.begin(), Numbers.end(), number) != Numbers.end());
	}

	std::vector<int> Numbers;
	bool HasWon = false;
};

class Day4
{
public:
	Day4()
	{

	}

	void Run()
	{
		ifstream infile("inputDay4.txt");
		
		std::vector<BingoBoard> BingoBoards;
		BingoBoards.clear();

		if (infile.is_open())
		{
			string line;
			int currR = 0;
			BingoBoard currBoard;
			while (getline(infile, line))
			{
				string currNumbers = line;
				if (line.empty())
				{
					BingoBoards.push_back(currBoard);
					currBoard.Clear();
					currR = 0;
				}
				else
				{
					int currC = 0;

					for (int currC = 0; currC < 5; ++currC)
					{
						if (currC < 4)
						{
							bool encounteredNumber = false;
							int indexToBreak = -1;
							for (int i = 0; i < currNumbers.length(); ++i)
							{
								if (currNumbers[i] != ' ')
								{
									encounteredNumber = true;
								}
								else
								{
									if (encounteredNumber)
									{
										indexToBreak = i;
										break;
									}
								}
							}
							string currNumberString = currNumbers.substr(0, indexToBreak);
							currNumberString.erase(remove(currNumberString.begin(), currNumberString.end(), ' '), currNumberString.end());
							int currNumber = stoi(currNumberString);
							currNumbers = currNumbers.substr(indexToBreak + 1);

							currBoard.SetNumber(currR, currC, currNumber);
						}
						else
						{
							string currNumberString = currNumbers;
							currNumberString.erase(remove(currNumberString.begin(), currNumberString.end(), ' '), currNumberString.end());
							int currNumber = stoi(currNumberString);

							currBoard.SetNumber(currR, currC, currNumber);
						}
					}

					currR++;
				}
			}
		}

		int countInputs = sizeof(InputNums) / sizeof(InputNums[0]);
		int NumBoards = BingoBoards.size();
		for (int i = 0; i < countInputs; ++i)
		{
			int currInput = InputNums[i];
			for (auto iter = BingoBoards.begin(); iter != BingoBoards.end(); ++iter)
			{
				if (!iter->GetHasWon() && iter->NumberCalled(currInput))
				{
					NumBoards--;
					if (NumBoards == 0)
					{
						int Total = iter->CalculateTotalOfRemaining();
						int res = Total * currInput;
						cout << "Result = " << res;
					}

				}
			}
		}

	}
};

void RunDay4()
{
	Day4 Day4Obj;
	Day4Obj.Run();
}