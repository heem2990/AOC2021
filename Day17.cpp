

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

#include "Day17.h"

using namespace std;

class Day17
{
public:
	Day17()
	{
	}

	struct Point
	{
		Point(int x, int y) : X(x), Y(y) {}
		int X;
		int Y;
	};

	//bool IsPointWithinBox(Point BoxMin, Point BoxMax, Point InPoint)
	//{
	//	if (InPoint.X >= BoxMin.X && InPoint.X <= BoxMax.X && InPoint.Y >= BoxMin.Y && InPoint.Y <= BoxMax.Y)
	//	{
	//		return true;
	//	}

	//	return false;
	//}

	//float DistanceOfPointToBox(Point BoxMin, Point BoxMax, Point InPoint)
	//{
	//	int HalfX = BoxMin.X + BoxMax.X;
	//	HalfX = HalfX >> 1;

	//	int HalfY = BoxMin.Y + BoxMax.Y;
	//	HalfY = HalfY >> 1;

	//	sqrt( ((HalfX - InPoint.X) ^ 2 ) + ((HalfY - InPoint.Y) ^ 2));
	//}

	void Run()
	{
		ifstream infile("inputDay17.txt");
		string line;
		string current;

		if (infile.is_open())
		{
			while (getline(infile, line))
			{
				cout << line <<endl;
			}
		}

		//Input
		//const Point TargetMin{ 20, -10 };
		//const Point TargetMax{30, -5};

		const Point TargetMin{ 57, -198 };
		const Point TargetMax{116, -148};

		const Point Drag{ -1, 0 };
		const Point Grav{ 0, -1 };

		int StartX = 0;
		int sum = 0;
		for (int i = 1; i < TargetMin.X; ++i)
		{
			sum += i;
			if (sum > TargetMin.X)
			{
				StartX = i;
				break;
			}
		}


		int MaxYPos = INT_MIN;
		int MaxYPosVelY = -1;
		int MaxYPosVelX = -1;
		int IntersectX = -1;
		int IntersectY = -1;
		int numIntersects = 0;
		set<pair<int, int>> Intersects;

		for (int xVel = StartX; xVel <= TargetMax.X; ++xVel)
		{
			int currXLocation = 0;
			int numSteps = 0;
			for (int i = xVel; i > 0; --i )
			{
				currXLocation += i;
				numSteps++;

				if (currXLocation >= TargetMin.X && currXLocation <= TargetMax.X)
				{
					int yVel = TargetMin.Y;
					while (true)
					{
						int currYVel = yVel;
						int currYLoc = 0;
						for (int i = 0; i < numSteps; ++i)
						{
							currYLoc += currYVel;

							currYVel -= 1;
						}

						int yLocationInNSteps = currYLoc;//(yVel * numSteps) + ((numSteps * (numSteps - 1)) / 2);
						int currYVelocity = currYVel;
						int currYLocation = yLocationInNSteps;
						//int tempCurrXLocation = currXLocation;
						//int prevYLocation = currYLocation - (currYVelocity - (-1));
						while (true)
						{
							if (currYLocation >= TargetMin.Y && currYLocation <= TargetMax.Y)
							{
								//Lands in the box.

								++numIntersects;
								auto point = pair<int, int>{xVel, yVel};
								if (Intersects.count(point) <= 0)
								{
									Intersects.insert({ xVel, yVel });
								}
								int highestY = (yVel * (yVel + 1)) / 2;
								if (highestY > MaxYPos)
								{
									MaxYPos = highestY;
									MaxYPosVelY = yVel;
									MaxYPosVelX = xVel;
									IntersectX = currXLocation;
									IntersectY = currYLocation;
								}
								break;
							}

							if (i > 1)
							{
								break;
							}
							//prevYLocation = currYLocation;
							currYLocation += currYVelocity;
							currYVelocity -= 1;

							if (currYVelocity < 0)
							{
								if (currYLocation < TargetMin.Y)
								{
									break;
								}
							}
						}

						++yVel;
						if (yVel > abs(TargetMin.Y))
						{
							break;
						}
					}
				}
				else if (currXLocation > TargetMax.X)
				{
					break;
				}
			}
		}

		cout << MaxYPos << " "<<numIntersects;

	}

};

void RunDay17()
{
	Day17 Day17Obj;
	Day17Obj.Run();
}