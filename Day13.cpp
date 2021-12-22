

#include <iostream>
#include <fstream>
#include <map>
#include <unordered_map>
#include <string>
#include <vector>
#include <set>
#include <array>
#include <algorithm>

#include "Day13.h"


using namespace std;

int FoldInputs[12][2] = 
{
	{   655, 0   },//{0, 7},//
	{   0, 447 },//{5, 0},//
	{ 327, 0   },
	{   0, 223 },
	{ 163, 0   },
	{   0, 111 },
	{	81, 0  },
	{   0, 55  },
	{  40, 0   },
	{   0, 27  },
	{   0, 13  },
	{   0, 6   }
};



class Day13
{
public:
	Day13()
	{
	}

	int GetStateValue(int r, int c, int* stateArray)
	{
		return stateArray[((r * 1500) + c)];
	}


	void SetStateValue(int r, int c, int* stateArray, int valToSet)
	{
		stateArray[((r * 1500) + c)] = valToSet;
	}

	//fold at y = 
	void HorizontalFold(int* stateArray, int foldVal, int& modifiedMaxR, const int& modifiedMaxC)
	{
		int* TempState = new int[1500 * 1500];

		for (int r = 0; r < 1500; ++r)
		{
			for (int c = 0; c < 1500; ++c)
			{
				SetStateValue(r, c, TempState, 0);
			}
		}

		int currMaxR = modifiedMaxR;

		int halfR = (currMaxR / 2);

		int numNewOnTop = (currMaxR - (2 * foldVal));
		int absNumOnTop = abs(numNewOnTop);

		int numOverlap = (currMaxR - absNumOnTop) / 2;

		modifiedMaxR = absNumOnTop + numOverlap - 1;

		for (int r = 0; r < absNumOnTop; ++r)
		{
			for (int c = 0; c <= modifiedMaxC; ++c)
			{
				int newVal = -1;
				if (numNewOnTop > 0)
				{
					newVal = GetStateValue(currMaxR - r, c, stateArray);
				}
				else if (numNewOnTop < 0)
				{
					newVal = GetStateValue(r, c, stateArray);
				}
				else
				{
					cout << "WTF";
				}

				SetStateValue(r, c, TempState, newVal);
			}
		}

		for (int r = 0; r < numOverlap; ++r)
		{
			for (int c = 0; c <= modifiedMaxC; ++c)
			{
				int newVal = 0;
				if (numNewOnTop > 0)
				{
					int valFromTopHalf = GetStateValue(r, c, stateArray);
					int valFromBotHalf = GetStateValue(currMaxR - r - absNumOnTop, c, stateArray);

					newVal = (valFromTopHalf == 0 && valFromBotHalf == 0) ? 0 : 1;
				}
				else if (numNewOnTop < 0)
				{
					int valFromTopHalf = GetStateValue(r + absNumOnTop, c, stateArray);
					int valFromBotHalf = GetStateValue(currMaxR - r, c, stateArray);

					newVal = (valFromTopHalf == 0 && valFromBotHalf == 0) ? 0 : 1;
				}
				else
				{
					int valFromTopHalf = GetStateValue(r, c, stateArray);
					int valFromBotHalf = GetStateValue(currMaxR - r, c, stateArray);

					newVal = (valFromTopHalf == 0 && valFromBotHalf == 0) ? 0 : 1;
				}
				SetStateValue(absNumOnTop + r, c, TempState, newVal);

			}
		}

		for (int r = 0; r < 1500; ++r)
		{
			for (int c = 0; c < 1500; ++c)
			{
				if (r <= modifiedMaxR && c <= modifiedMaxC)
				{
					int newVal = GetStateValue(r, c, TempState);
					SetStateValue(r, c, stateArray, newVal);
					//cout << newVal << " ";
				}
			}

			if (r <= modifiedMaxR)
			{

				//cout << endl;
			}
		}

		delete[] TempState;
	}

	//fold x = 
	void VerticalFold(int * stateArray, int foldVal, const int& modifiedMaxR, int& modifiedMaxC)
	{
		int* TempState = new int[1500 * 1500];

		for (int r = 0; r < 1500; ++r)
		{
			for (int c = 0; c < 1500; ++c)
			{
				SetStateValue(r, c, TempState, 0);
			}
		}

		int currMaxR = modifiedMaxR;
		int currMaxC = modifiedMaxC;

		int halfC = ( currMaxC / 2 );

		int numNewOnTop = (currMaxC  - ( 2 * foldVal ) );  
		int absNumOnTop = abs(numNewOnTop);

		int numOverlap = (currMaxC - absNumOnTop) / 2;

		modifiedMaxC = absNumOnTop + numOverlap -1;

		for (int c = 0; c < absNumOnTop; ++c)
		{
			for (int r = 0; r <= modifiedMaxR; ++r)
			{
				int newVal = -1;
				if (numNewOnTop > 0)
				{
					newVal = GetStateValue(r, currMaxC - c, stateArray);
				}
				else if (numNewOnTop < 0)
				{
					newVal = GetStateValue(r, c, stateArray);
				}
				else
				{
					cout << "WTF";
				}

				SetStateValue(r, c, TempState, newVal);

			}
		}

		for (int c = 0; c < numOverlap; ++c)
		{
			for (int r = 0; r <= modifiedMaxR; ++r)
			{
				int newVal = 0;
				if (numNewOnTop > 0)
				{
					int valFromTopHalf = GetStateValue(r, c, stateArray);
					int valFromBotHalf = GetStateValue(r, currMaxC - c - absNumOnTop, stateArray);

					newVal = (valFromTopHalf == 0 && valFromBotHalf == 0) ? 0 : 1;
				}
				else if (numNewOnTop < 0)
				{
					int valFromTopHalf = GetStateValue(r, c + absNumOnTop, stateArray);
					int valFromBotHalf = GetStateValue(r, currMaxC - c, stateArray);

					newVal = (valFromTopHalf == 0 && valFromBotHalf == 0) ? 0 : 1;
				}
				else
				{
					int valFromTopHalf = GetStateValue(r, c, stateArray);
					int valFromBotHalf = GetStateValue(r, currMaxC - c, stateArray);

					newVal = (valFromTopHalf == 0 && valFromBotHalf == 0) ? 0 : 1;
				}
				SetStateValue(r, absNumOnTop + c, TempState, newVal);

			}
		}

		for (int r = 0; r < 1500; ++r)
		{
			for (int c = 0; c < 1500; ++c)
			{
				int newVal = GetStateValue(r, c, TempState);
				SetStateValue(r, c, stateArray, newVal);
			}
		}

		delete[] TempState;
	}

	void Run()
	{
		ifstream infile("inputDay13.txt");

		string line;

		int* State = new int[1500 * 1500];

		for (int r = 0; r < 1500; ++r)
		{
			for (int c = 0; c < 1500; ++c)
			{
				SetStateValue(r, c, State, 0);
			}
		}

		int maxR = 0;
		int maxC = 0;

		if (infile.is_open())
		{

			while (getline(infile, line))
			{
				int indexToSplit = line.find(',');

				int cVal = stoi(line.substr(0, indexToSplit));
				int rVal = stoi(line.substr(indexToSplit + 1));

				if (rVal > maxR)
				{
					maxR = rVal;
				}

				if (cVal > maxC)
				{
					maxC = cVal;
				}

				if (rVal >= 1500)
				{
					continue;
				}

				if (cVal > 1500)
				{
					continue;
				}

				SetStateValue(rVal, cVal, State, 1);
			}

			//for (int r = 0; r <= maxR; ++r)
			//{
			//	for (int c = 0; c <= maxC; ++c)
			//	{
			//		cout << GetStateValue(r, c, State) << " ";
			//	}
			//	cout << endl;
			//}


			//cout <<"**************************************"<<endl;

			for (int i = 0; i < 12; ++i)
			{
				if (FoldInputs[i][0] != 0)
				{
					VerticalFold(State, FoldInputs[i][0], maxR, maxC);
				}
				else
				{
					HorizontalFold(State, FoldInputs[i][1], maxR, maxC);
				}

				//cout << endl;
				//cout << "*************************************";
				//cout << endl;

				//for (int r = 0; r <= maxR; ++r)
				//{
				//	for (int c = 0; c <= maxC; ++c)
				//	{
				//		if (GetStateValue(r, c, State) == 1)
				//		{
				//			cout << "# ";
				//		}
				//		else
				//		{
				//			cout << ". ";
				//		}
				//	}
				//	cout << endl;
				//}
			}

			long long total = 0;

			//for (int r = 0; r <= maxR; ++r)
			//{
			//	for (int c = 0; c <= maxC; ++c)
			//	{
			//		if (GetStateValue(r, c, State) == 1)
			//		{
			//			total++;
			//		}
			//	}
			//}

			for (int r = 0; r <= maxR; ++r)
			{
				for (int c = 0; c <= maxC; ++c)
				{
					if (GetStateValue(r, c, State) == 1)
					{
						cout <<"# ";
					}
					else
					{
						cout <<". ";
					}
				}
				cout << endl;
			}

			cout << total;
		}

	}

};

void RunDay13()
{
	Day13 Day13Obj;
	Day13Obj.Run();
}
