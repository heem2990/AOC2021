

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

#include "Day19.h"

using namespace std;


class Day19
{
public:


	Day19()
	{
	}

	struct Point
	{		
		int X{ 0 };
		int Y{ 0 };
		int Z{ 0 };
		int W{ 1 };

		int GetSqrdMag() const
		{
			return (X * X) + (Y * Y) + (Z * Z);
		}

		bool operator==(const Point& rhs) const
		{
			return (rhs.X == X && rhs.Y == Y && rhs.Z == Z);
		}

		void Print()
		{
			cout << "(" << X << ", " << Y << ", " << Z << ")\n";
		}
	};

	struct Offset
	{
		int SqrdMag{ 0 };
		set<int> MyOffsets;
		Point A;
		Point B;
	};

	Point CrossProduct(Point A, Point B)
	{
		Point ToReturn;

		ToReturn.X = (A.Y * B.Z) - (A.Z * B.Y);
		ToReturn.Y = -1 * ((A.X * B.Z) - (A.Z * B.X));
		ToReturn.Z = (A.X * B.Y) - (A.Y * B.X);
		ToReturn.W = 0;

		return ToReturn;
	}

	struct TransformMatrix
	{
		int x[4]{ 0, 0, 0, 0 };
		int y[4]{ 0, 0, 0, 0 };
		int z[4]{ 0, 0, 0, 0 };
		int w[4]{ 0, 0, 0, 0 };

		void MakeZero()
		{
			for (int i = 0; i < 4; ++i)
			{
				x[i] = 0;
				y[i] = 0;
				z[i] = 0;
				w[i] = 0;
			}
		}

		void SetTranslation(Point translation)
		{
			w[0] = translation.X;
			w[1] = translation.Y;
			w[2] = translation.Z;
			w[3] = 1;
		}
	};


	map<int, vector<Point>> ScannerToPoints;
	map<int, vector<Offset>> ScannerToOffsets;
	map<int, int> ScannerToScannerIntersections;
	map<int, TransformMatrix> ScannerToFirstTransform;
	vector<TransformMatrix> TransformMatrices;

	Point GetRowAsPoints(const TransformMatrix& matrix, int row)
	{
		Point ToReturn;

		switch (row)
		{
		case 0:
		{
			ToReturn.X = matrix.x[0];
			ToReturn.Y = matrix.x[1];
			ToReturn.Z = matrix.x[2];
			ToReturn.W = matrix.x[3];
			break;
		}
		case 1:
		{
			ToReturn.X = matrix.y[0];
			ToReturn.Y = matrix.y[1];
			ToReturn.Z = matrix.y[2];
			ToReturn.W = matrix.y[3];
			break;
		}
		case 2:
		{
			ToReturn.X = matrix.z[0];
			ToReturn.Y = matrix.z[1];
			ToReturn.Z = matrix.z[2];
			ToReturn.W = matrix.z[3];
			break;

		}
		default:
			cout << "WTF";
			break;
		}

		return ToReturn;
	}

	void PopulateRotationMatrices()
	{
		for (int x = 0; x < 3; ++x)
		{
			for (int xSign = 0; xSign < 2; ++xSign)
			{
				for (int y = 0; y < 3; ++y)
				{
					if (y == x) continue;
					for (int ySign = 0; ySign < 2; ++ySign)
					{
						TransformMatrix Current;
						Current.MakeZero();

						Current.x[x] = xSign == 0 ? 1 : -1;
						Current.y[y] = ySign == 0 ? 1 : -1;

						Point XRow = GetRowAsPoints(Current, 0);
						Point YRow = GetRowAsPoints(Current, 1);
						Point ZRow = CrossProduct(XRow, YRow);

						Current.z[0] = ZRow.X;
						Current.z[1] = ZRow.Y;
						Current.z[2] = ZRow.Z;
						Current.z[3] = ZRow.W;

						Current.w[0] = 0;
						Current.w[1] = 0;
						Current.w[2] = 0;
						Current.w[3] = 1;

						TransformMatrices.push_back(Current);
					}
				}
			}
		}
	}

	Point TransformPoint(Point toTransform, TransformMatrix Matrix)
	{
		Point Result;
		Result.X = (toTransform.X * Matrix.x[0]) + (toTransform.Y * Matrix.y[0]) + (toTransform.Z * Matrix.z[0]) + (toTransform.W * Matrix.w[0]);
		Result.Y = (toTransform.X * Matrix.x[1]) + (toTransform.Y * Matrix.y[1]) + (toTransform.Z * Matrix.z[1]) + (toTransform.W * Matrix.w[1]);
		Result.Z = (toTransform.X * Matrix.x[2]) + (toTransform.Y * Matrix.y[2]) + (toTransform.Z * Matrix.z[2]) + (toTransform.W * Matrix.w[2]);
		Result.W = (toTransform.X * Matrix.x[3]) + (toTransform.Y * Matrix.y[3]) + (toTransform.Z * Matrix.z[3]) + (toTransform.W * Matrix.w[3]);

		return Result;
	}

	bool AreOffsetsSameMagnitude(const Offset& A, const Offset& B)
	{
		return A.SqrdMag == B.SqrdMag;
	}

	bool AreOffsetsSameIndividualOffsets(const Offset& A, const Offset& B)
	{
		return A.MyOffsets == B.MyOffsets;
	}

	Offset GetOffset(Point a, Point b)
	{
		Point Result;
		Result.X = a.X - b.X;
		Result.Y = a.Y - b.Y;
		Result.Z = a.Z - b.Z;
		Result.W = a.W - b.W;

		Offset ToReturn;
		ToReturn.SqrdMag = Result.GetSqrdMag();
		ToReturn.A = a;
		ToReturn.B = b;
		ToReturn.MyOffsets.insert(abs(Result.X));
		ToReturn.MyOffsets.insert(abs(Result.Y));
		ToReturn.MyOffsets.insert(abs(Result.Z));

		return ToReturn;
	}

	bool CanIntersect(int scannerA, int scannerB, vector<pair<Offset, Offset>>& CommonPairs)
	{
		const vector<Offset>& OffsetsA = ScannerToOffsets[scannerA];
		const vector<Offset>& OffsetsB = ScannerToOffsets[scannerB];

		constexpr int MinRequiredCommonPoints = 12;
		constexpr int MinRequiredCommonOffsets = (MinRequiredCommonPoints * (MinRequiredCommonPoints - 1)) / 2;

		int NumCommonFound = 0;
		for (int i = 0; i < OffsetsA.size(); ++i)
		{
			for (int j = 0; j < OffsetsB.size(); ++j)
			{
				if (AreOffsetsSameMagnitude(OffsetsA[i], OffsetsB[j]))
				{
					CommonPairs.push_back(make_pair(OffsetsA[i], OffsetsB[j]));
					NumCommonFound++;
				}
			}
		}

		return NumCommonFound >= MinRequiredCommonOffsets;
	}

	TransformMatrix GetInverse(TransformMatrix matrix)
	{
		TransformMatrix ToReturn;
		ToReturn.MakeZero();

		ToReturn.x[0] = matrix.x[0];
		ToReturn.x[1] = matrix.y[0];
		ToReturn.x[2] = matrix.z[0];

		ToReturn.y[0] = matrix.x[1];
		ToReturn.y[1] = matrix.y[1];
		ToReturn.y[2] = matrix.z[1];

		ToReturn.z[0] = matrix.x[2];
		ToReturn.z[1] = matrix.y[2];
		ToReturn.z[2] = matrix.z[2];

		return ToReturn;
	}



	TransformMatrix GetTransformMatrixBetweenScanners(int scannerFrom, int scannerTo)
	{
		TransformMatrix toReturn;

		vector<pair<Offset, Offset>> CommonPairs;

		if (CanIntersect(scannerFrom, scannerTo, CommonPairs))
		{
			auto firstCommon = CommonPairs.begin();
			Point fromFirstPointA = firstCommon->first.A;
			Point fromFirstPointB = firstCommon->first.B;

			Point toFirstPointA = firstCommon->second.A;
			Point toFirstPointB = firstCommon->second.B;


			for (auto rot = TransformMatrices.begin(); rot != TransformMatrices.end(); ++rot)
			{
				for (int i = 0; i < 2; ++i)
				{
					Point fromA = fromFirstPointA;
					Point fromB = fromFirstPointB;
					Point toA = i == 0 ? toFirstPointA : toFirstPointB;
					Point toB = i == 0 ? toFirstPointB : toFirstPointA;

					TransformMatrix inverse = GetInverse(*rot);
					Point rotatedPoint = TransformPoint(fromA, inverse);

					Point TranslationRequired;
					TranslationRequired.X = toA.X - rotatedPoint.X;
					TranslationRequired.Y = toA.Y - rotatedPoint.Y;
					TranslationRequired.Z = toA.Z - rotatedPoint.Z;


					TransformMatrix transform = inverse;
					transform.SetTranslation(TranslationRequired);

					Point transformedPointA = TransformPoint(fromA, transform);
					
					if (!(transformedPointA == toA))
					{
						cout << "wtf";
					}

					Point transformedPointB = TransformPoint(fromB, transform);
					if (transformedPointB == toB)
					{
						const vector<Point>& fromScannerPoints = ScannerToPoints[scannerFrom];
						const vector<Point>& toScannerPoints = ScannerToPoints[scannerTo];

						int numPointsCommon = 0;

						for (auto iter = fromScannerPoints.begin(); iter != fromScannerPoints.end(); ++iter)
						{
							Point currentPointTransformed = TransformPoint(*iter, transform);
							if (find_if(toScannerPoints.begin(), toScannerPoints.end(), [currentPointTransformed](const Point& toPointToCheck)
							{
								return toPointToCheck == currentPointTransformed;
							}) != toScannerPoints.end())
							{
								++numPointsCommon;
							}
						}

						if (numPointsCommon >= 12)
						{
							toReturn = transform;

							return toReturn;
						}
					}
				}
			}
		}

		cout << "wtf";

		return toReturn;
	}

	void Run()
	{

		ifstream infile("inputDay19.txt");

		string line;

		int currentScanner = 0;
		int maxScanner = 0;

		PopulateRotationMatrices();

		if (infile.is_open())
		{
			while (getline(infile, line))
			{
				if (line[0] == '-' && line[1] == '-')
				{
					//cout << "\n\n****** Starting Scanner: " << currentScanner<<" ***************\n";

					vector<Point> emptyList;
					vector<Offset> emptyListOffsets;
					ScannerToPoints.insert({ currentScanner, emptyList });
					ScannerToOffsets.insert({ currentScanner, emptyListOffsets });
					ScannerToScannerIntersections.insert({ currentScanner, -1 });

					continue;
				}
				if (line.empty())
				{
					//cout << "\n\n*********************\n";
					++currentScanner;
					continue;
				}

				int firstComma = line.find(',');
				string Xstr = line.substr(0, firstComma);
				string YZStr = line.substr(firstComma + 1);
				int secondComma = YZStr.find(',');
				string Ystr = YZStr.substr(0, secondComma);
				string Zstr = YZStr.substr(secondComma + 1);

				int XVal = stoi(Xstr);
				int YVal = stoi(Ystr);
				int ZVal = stoi(Zstr);

				Point NewPoint;
				NewPoint.X = XVal;
				NewPoint.Y = YVal;
				NewPoint.Z = ZVal;
				NewPoint.W = 1;

				ScannerToPoints[currentScanner].push_back(NewPoint);

				//NewPoint.Print();
				//cout << "(" << XVal << ", " << YVal << ", " << ZVal << ")\n";

			}
		}

		maxScanner = currentScanner;

		for (int i = 0; i <= maxScanner; ++i)
		{
			const vector<Point>& PointsVector = ScannerToPoints[i];
			vector<Offset>& OffsetsVector = ScannerToOffsets[i];
			for (int i = 0; i < PointsVector.size() - 1; ++i)
			{
				for (int j = i + 1; j < PointsVector.size(); ++j)
				{			
					if (i == j) continue;

					Offset CalculatedOffset = GetOffset(PointsVector[i], PointsVector[j]);
					OffsetsVector.push_back(CalculatedOffset);
				}
			}
		}

		while(true)
		{
			for (int i = 0; i <= maxScanner - 1; ++i)
			{
				for (int j = i + 1; j <= maxScanner; ++j)
				{
					if (ScannerToScannerIntersections[j] != -1 && ScannerToScannerIntersections[i] != -1)
					{
						//This has a path to 0.
						continue;
					}

					vector<pair<Offset, Offset>> CommonPairs;

					if (CanIntersect(i, j, CommonPairs))
					{
						if (i == 0 || (ScannerToScannerIntersections[i] != -1 && ScannerToScannerIntersections[j] == -1))
						{
							ScannerToScannerIntersections[j] = i;
						}
						else if (ScannerToScannerIntersections[i] == -1 && ScannerToScannerIntersections[j] != -1)
						{
							ScannerToScannerIntersections[i] = j;
						}
					}
				}
			}

			bool shouldBreak = true;
			for (int i = 0; i <= maxScanner - 1; ++i)
			{
				if (i != 0 && ScannerToScannerIntersections[i] == -1)
				{
					shouldBreak = false;
					break;
				}
			}

			if (shouldBreak)
			{
				break;
			}
		}

		for (int i = 1; i <= maxScanner; ++i)
		{
			int ToScanner = ScannerToScannerIntersections[i];
			ScannerToFirstTransform[i] = GetTransformMatrixBetweenScanners(i, ToScanner);

			//Test
			cout << "Scanner: " << i << " Relative to " << ToScanner << endl;

			const vector<Point>& fromScannerPoints = ScannerToPoints[i];
			for (auto iter = fromScannerPoints.begin(); iter != fromScannerPoints.end(); ++iter)
			{
				Point transformedPoint = TransformPoint(*iter, ScannerToFirstTransform[i]);
				transformedPoint.Print();
			}
		}

		vector<Point> UniquePoints;


		vector<Point> ScannerTransforms;

		for (int i = 0; i <= maxScanner; ++i)
		{
			Point ScannerLocation;
			ScannerLocation.X = 0;
			ScannerLocation.Y = 0;
			ScannerLocation.Z = 0;
			ScannerLocation.W = 1;
			

			vector<Point> PointsArray = ScannerToPoints[i];
			int currentlyRelativeTo = i;

			while (true)
			{
				if (currentlyRelativeTo == 0)
				{
					ScannerTransforms.push_back(ScannerLocation);

					for (auto iter = PointsArray.begin(); iter != PointsArray.end(); ++iter)
					{
						if (find_if(UniquePoints.begin(), UniquePoints.end(), [iter](Point& A)
						{
							return (*iter == A);
						}) == UniquePoints.end())
						{
							UniquePoints.push_back(*iter);
						}
					}

					break;
				}
				else
				{
					int transformTo = ScannerToScannerIntersections[currentlyRelativeTo];
					TransformMatrix transform = ScannerToFirstTransform[currentlyRelativeTo];

					ScannerLocation = TransformPoint(ScannerLocation, transform);

					for (auto iter = PointsArray.begin(); iter != PointsArray.end(); ++iter)
					{
						Point currPoint = *iter;
						*iter = TransformPoint(currPoint, transform);
					}

					currentlyRelativeTo = transformTo;
				}
			}
		}

		int MaxManHattan = 0;

		for (int i = 0; i < ScannerTransforms.size() -1; ++i)
		{
			for (int j = i; j < ScannerTransforms.size(); ++j)
			{
				Point First = ScannerTransforms[i];
				Point Second = ScannerTransforms[j];

				int manhatan = abs(First.X - Second.X) + abs(First.Y - Second.Y) + abs(First.Z - Second.Z);
				if (manhatan > MaxManHattan)
				{
					MaxManHattan = manhatan;
				}
			}
		}

		cout << "Num Unique = " << UniquePoints.size()<<endl;
		cout << "Manhattan" << MaxManHattan;
	}

};

void RunDay19()
{
	Day19 Day19Obj;
	Day19Obj.Run();
}