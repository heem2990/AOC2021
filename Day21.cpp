

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

#include "Day21.h"

using namespace std;

class Day21
{
public:

	Day21()
	{
	}

	long long P1Location = 4;
	long long P2Location = 3;

	//Sample input
	//long long P1Location = 4;
	//long long P2Location = 8;

	long long NumP1Wins;
	long long NumP2Wins;

	int RollValueToOccurences[10];

	int minRollVal = 3;
	int maxRollVal = 9;

	void RunSim(int currP1Location, int currP2Location, int currP1Score, int currP2Score, int playerId, long long numSituations)
	{
		int& CurrentPlayerLocation = playerId == 0 ? currP1Location : currP2Location;
		int& CurrentPlayerScore = playerId == 0 ? currP1Score : currP2Score;
		long long& CurrentPlayerWins = playerId == 0 ? NumP1Wins : NumP2Wins;

		int totalRoll = 0;

		for (int currRollVal = minRollVal; currRollVal <= maxRollVal; ++currRollVal)
		{
			int tempLocation = CurrentPlayerLocation;
			int tempScore = CurrentPlayerScore;

			int deltaScore = ((CurrentPlayerLocation + currRollVal) % 10);
			deltaScore = deltaScore == 0 ? 10 : deltaScore;
			CurrentPlayerScore += deltaScore;
			CurrentPlayerLocation = deltaScore;

			int RollOccurences = RollValueToOccurences[currRollVal];

			if (CurrentPlayerScore >= 21)
			{
				CurrentPlayerWins += (numSituations * RollOccurences);
				//cout << CurrentPlayerWins << endl;
			}
			else
			{
				RunSim(currP1Location, currP2Location, currP1Score, currP2Score, (playerId + 1) % 2, numSituations * RollOccurences);
			}

			CurrentPlayerLocation = tempLocation;
			CurrentPlayerScore = tempScore;
		}

	}

	void P1()
	{

		//P1
		{
			//long long P1Score = 0;
			//long long P2Score = 0;

			//long long NumRolls = 0;
			//long long CurrentDiceVal = 1;
			//int winningIndex = -1;

			//long long round = 0;

			//while (winningIndex == -1)
			//{
			//	cout << "\n\n***********Round " << round + 1 << "****************\n";
			//	for (int i = 0; i < 2; ++i)
			//	{

			//		long long& CurrentPlayerLocation = i == 0 ? P1Location : P2Location;
			//		long long& CurrentPlayerScore = i == 0 ? P1Score : P2Score;

			//		cout << "\t Player: " << i + 1 << " Location: "<< CurrentPlayerLocation <<" Score: "<<CurrentPlayerScore<<endl;

			//		long long totalRoll = 0;

			//		for (int roll = 0; roll < 3; ++roll)
			//		{
			//			cout << "\t\t Roll: " << CurrentDiceVal << endl;
			//		
			//			totalRoll += CurrentDiceVal;
			//			CurrentDiceVal++;
			//			CurrentDiceVal = CurrentDiceVal > 100 ? 1 : CurrentDiceVal;
			//			NumRolls++;
			//		}

			//		cout << "\t Dice total : " << totalRoll<<endl;

			//		long long DeltaScore = (totalRoll + CurrentPlayerLocation) %10;
			//		DeltaScore = DeltaScore == 0 ? 10 : DeltaScore;
			//		CurrentPlayerLocation = DeltaScore;
			//		CurrentPlayerScore += DeltaScore;

			//		cout << "\t Player: " << i + 1 << " New Location: " << CurrentPlayerLocation << " New Score: " << CurrentPlayerScore << endl;
			//		cout << "-----------------------------------\n";

			//		if (CurrentPlayerScore >= 1000)
			//		{
			//			winningIndex = i;
			//			break;
			//		}
			//	}

			//	round++;
			//}


			//long long minScore = min(P1Score, P2Score);
			//cout << (minScore * NumRolls);
		}
	}

	void Run()
	{
		ifstream infile("inputDay20.txt");

		for (int i = 0; i < 10; ++i)
		{
			RollValueToOccurences[i] = 0;
		}

		for (int i = 1; i < 4; ++i)
		{
			for (int j = 1; j < 4; ++j)
			{
				for (int k = 1; k < 4; ++k)
				{
					int Roll = i + j + k;
					RollValueToOccurences[Roll] = RollValueToOccurences[Roll] + 1;
				}
			}
		}


		int newP1Location = 4;
		int newP2Location = 3;
		NumP1Wins = 0;
		NumP2Wins = 0;
		int newP1Score = 0;
		int newP2Score = 0;

		RunSim(newP1Location, newP2Location, newP1Score, newP2Score, 0, 1);

		cout << "\n\nP1: " << NumP1Wins << "\n P2: " << NumP2Wins;
	}

};

void RunDay21()
{
	Day21 Day21Obj;
	Day21Obj.Run();
}