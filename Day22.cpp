

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

#include "Day22.h"

using namespace std;

class Day22
{
public:

	Day22()
	{
	}

	struct Region
	{
		int MinX = -1;
		int MaxX = -1;
		int MinY = -1;
		int MaxY = -1;
		int MinZ = -1;
		int MaxZ = -1;
		int RegionSign = 1;

		bool DoesCollide(const Region& checkRegion) const
		{
			return !(	(MinX > checkRegion.MaxX || MaxX < checkRegion.MinX ) ||
						(MinY > checkRegion.MaxY || MaxY < checkRegion.MinY ) || 
						(MinZ > checkRegion.MaxZ || MaxZ < checkRegion.MinZ) );
		}

		Region GetCollisionRegion(const Region& other) const
		{
			Region CollisionRegion;
			
			CollisionRegion.MinX = max(MinX, other.MinX);
			CollisionRegion.MinY = max(MinY, other.MinY);
			CollisionRegion.MinZ = max(MinZ, other.MinZ);

			CollisionRegion.MaxX = min(MaxX, other.MaxX);
			CollisionRegion.MaxY = min(MaxY, other.MaxY);
			CollisionRegion.MaxZ = min(MaxZ, other.MaxZ);

			return CollisionRegion;
		}

		long long GetNumberOfPoints()
		{
			long long numOnX = abs(MaxX - MinX) + 1;
			long long numOnY = abs(MaxY - MinY) + 1;
			long long numOnZ = abs(MaxZ - MinZ) + 1;

			return numOnX * numOnY * numOnZ;
		}

	};

	map<string, bool> StateMap;
	vector<Region> AllRegions;

	void Run()
	{
		ifstream infile("inputDay22.txt");

		if (infile.is_open())
		{
			string line;
			while (getline(infile, line))
			{
				bool on = false;
				string state = line.substr(0, 2);
				on = (state == "on");
								
				int xLoc = line.find("x");
				int yLoc = line.find("y");
				int zLoc = line.find("z");

				//X
				string XString = line.substr(xLoc + 1, string::npos);
				int firstComma = XString.find(",");
				XString = XString.substr(0,firstComma);
				int equals = XString.find("=");
				XString = XString.substr(equals + 1, string::npos);
				int firstPeriod = XString.find(".");
				string minXString = XString.substr(0, firstPeriod);
				string maxXString = XString.substr(firstPeriod + 2, string::npos);

				int minX = stoi(minXString);
				int maxX = stoi(maxXString);

				//minX = max(-50, minX);
				//minX = min(50, minX);
				//maxX = max(-50, maxX);
				//maxX = min(50, maxX);

				//Y
				string YString = line.substr(yLoc + 1, string::npos);
				firstComma = YString.find(",");
				YString = YString.substr(0, firstComma);
				equals = YString.find("=");
				YString = YString.substr(equals + 1, string::npos);
				firstPeriod = YString.find(".");
				string minYString = YString.substr(0, firstPeriod);
				string maxYString = YString.substr(firstPeriod + 2, string::npos);

				int minY = stoi(minYString);
				int maxY = stoi(maxYString);

				//Z
				string ZString = line.substr(zLoc + 1, string::npos);
				equals = ZString.find("=");
				ZString = ZString.substr(equals + 1, string::npos);
				firstPeriod = ZString.find(".");
				string minZString = ZString.substr(0, firstPeriod);
				string maxZString = ZString.substr(firstPeriod + 2, string::npos);

				int minZ = stoi(minZString);
				int maxZ = stoi(maxZString);

				Region CurrentRegion;
				CurrentRegion.MinX = minX;
				CurrentRegion.MaxX = maxX;
				CurrentRegion.MinY = minY;
				CurrentRegion.MaxY = maxY;
				CurrentRegion.MinZ = minZ;
				CurrentRegion.MaxZ = maxZ;
				CurrentRegion.RegionSign = on ? 1 : -1;

				if (on)
				{
					if (AllRegions.size() == 0)
					{
						AllRegions.push_back(CurrentRegion);
					}
					else
					{
						vector<Region> NewRegionsToAdd;

						NewRegionsToAdd.push_back(CurrentRegion);

						for (auto iter = AllRegions.begin(); iter != AllRegions.end(); ++iter)
						{
							if (iter->DoesCollide(CurrentRegion))
							{
								Region CollisionRegion = iter->GetCollisionRegion(CurrentRegion);
								CollisionRegion.RegionSign = -1 * iter->RegionSign;
								NewRegionsToAdd.push_back(CollisionRegion);
							}
						}

						for (auto iter = NewRegionsToAdd.begin(); iter != NewRegionsToAdd.end(); ++iter)
						{
							AllRegions.push_back(*iter);
						}
					}
				}
				else
				{
					if (AllRegions.size() == 0)
					{
						continue;
					}
					else
					{
						vector<Region> NewRegionsToAdd;

						//NewRegionsToAdd.push_back(CurrentRegion);

						for (auto iter = AllRegions.begin(); iter != AllRegions.end(); ++iter)
						{
							if (iter->DoesCollide(CurrentRegion))
							{
								Region CollisionRegion = iter->GetCollisionRegion(CurrentRegion);
								CollisionRegion.RegionSign = -1 * iter->RegionSign;
								NewRegionsToAdd.push_back(CollisionRegion);
							}
						}

						for (auto iter = NewRegionsToAdd.begin(); iter != NewRegionsToAdd.end(); ++iter)
						{
							AllRegions.push_back(*iter);
						}

					}
				}
			}

			long long numOn = 0;

			for (auto iter = AllRegions.begin(); iter != AllRegions.end(); ++iter)
			{
				numOn = numOn + (iter->GetNumberOfPoints() * iter->RegionSign);
			}
			cout << numOn <<endl;
		}
	}

};

void RunDay22()
{
	Day22 Day22Obj;
	Day22Obj.Run();
}