

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

#include "Day16.h"

using namespace std;

class Day16
{
public:
	Day16()
	{
	}

	map<char, string> HexToDec =
	{
		{'0', "0000"},
		{'1', "0001"},
		{'2', "0010"},
		{'3', "0011"},
		{'4', "0100"},
		{'5', "0101"},
		{'6', "0110"},
		{'7', "0111"},
		{'8', "1000"},
		{'9', "1001"},
		{'A', "1010"},
		{'B', "1011"},
		{'C', "1100"},
		{'D', "1101"},
		{'E', "1110"},
		{'F', "1111"},
	};

	string Binary;

	long long ProcessLiteral(int startIndex, int& endIndex, int depth)
	{
		int currentIndex = startIndex;
		bool shouldEnd = false;
		string numberString;
		while (!shouldEnd)
		{
			if (Binary[currentIndex] == '0')
			{
				shouldEnd = true;
			}
			currentIndex++;

			numberString.append(Binary, currentIndex, 4);
			currentIndex += 4;
		}

		long long numberToReturn = stoll(numberString, 0, 2);
				
		for (int i = 0; i < depth; ++i)
		{
			cout << "\t";
		}
		cout <<"N:"<< numberToReturn << endl;

		endIndex = currentIndex;

		return numberToReturn;
	}

	long long ProcessPacket(int startIndex, int& endIndex, unsigned long long& versionNumber, int depth, bool subPacket)
	{
		long long valueToReturn = 0;
		int currentIndex = startIndex;

		string packetVersionStr = Binary.substr(currentIndex, 3);
		int packetVersion = stoi(packetVersionStr, 0, 2);

		versionNumber += packetVersion;

		for (int i = 0; i < depth; ++i)
		{
			cout << "\t";
		}
		cout << "V:"<<packetVersion << endl;

		currentIndex += 3;

		string packetIDStr = Binary.substr(currentIndex, 3);
		int packetId = stoi(packetIDStr, 0, 2);

		currentIndex += 3;

		if (packetId == 4)
		{
			valueToReturn = ProcessLiteral(currentIndex, currentIndex, depth+1);
		}
		else
		{
			for (int i = 0; i < depth; ++i)
			{
				cout << "\t";
			}

			switch (packetId)
			{
			case 0:
				valueToReturn = 0;
				cout << "+\n";
				break;
			case 1:
				valueToReturn = 1;
				cout << "*\n";
				break;
			case 2:
				valueToReturn = LLONG_MAX;
				cout << "min\n";
				break;
			case 3:
				valueToReturn = LLONG_MIN;
				cout << "max\n";
				break;
			case 5:
				cout << ">\n";
				break;
			case 6:
				cout << "<\n";
				break;
			case 7:
				cout << "==\n";
				break;
			default: break;
			}

			//operator
			if (Binary[currentIndex] == '0')
			{
				currentIndex++;

				int numBits = 15;
				string numNexBitsString = Binary.substr(currentIndex, 15);
				currentIndex += 15;
				int numNexBits = stoi(numNexBitsString, 0, 2);

				int endIndex = currentIndex + numNexBits;
				long long valueOfFirstPacket = 0;
				int numIterations = 0;

				while (currentIndex != endIndex)
				{
					long long packetValue = ProcessPacket(currentIndex, currentIndex, versionNumber, depth + 1, true);

					if (numIterations == 0)
					{
						valueOfFirstPacket = packetValue;
					}

					switch (packetId)
					{
					case 0:
					{
						valueToReturn += packetValue;
						break;
					}
					case 1:
					{
						valueToReturn *= packetValue;
						break;
					}
					case 2:
					{
						valueToReturn = min(valueToReturn, packetValue);
						break;
					}
					case 3:
					{
						valueToReturn = max(valueToReturn, packetValue);
						break;
					}
					case 5:
					{
						if (numIterations == 1)
						{
							valueToReturn = valueOfFirstPacket > packetValue ? 1 : 0;
						}
						break;
					}
					case 6:
					{
						if (numIterations == 1)
						{
							valueToReturn = valueOfFirstPacket < packetValue ? 1 : 0;
						}
						break;
					}
					case 7:
					{
						if (numIterations == 1)
						{
							valueToReturn = valueOfFirstPacket == packetValue ? 1 : 0;
							break;
						}
					}
					default:
					{
						cout << "WTF";
						break;
					}
					}

					numIterations++;
				}

			}
			else
			{
				currentIndex++;

				int numBits = 11;
				string valueString = Binary.substr(currentIndex, 11);
				currentIndex += 11;
				long long valueOfFirstPacket = 0;
				int numIterations = 0;

				int value = stoi(valueString, 0, 2);
				for (int i = 0; i < value; i++)
				{
					long long packetValue = ProcessPacket(currentIndex, currentIndex, versionNumber, depth+1, true);

					if (numIterations == 0)
					{
						valueOfFirstPacket = packetValue;
					}

					switch (packetId)
					{
					case 0:
					{
						valueToReturn += packetValue;
						break;
					}
					case 1:
					{
						valueToReturn *= packetValue;
						break;
					}
					case 2:
					{
						valueToReturn = min(valueToReturn, packetValue);
						break;
					}
					case 3:
					{
						valueToReturn = max(valueToReturn, packetValue);
						break;
					}
					case 5:
					{
						if (numIterations == 1)
						{
							valueToReturn = valueOfFirstPacket > packetValue ? 1 : 0;
						}
						break;
					}
					case 6:
					{
						if (numIterations == 1)
						{
							valueToReturn = valueOfFirstPacket < packetValue ? 1 : 0;
						}
						break;
					}
					case 7:
					{
						if (numIterations == 1)
						{
							valueToReturn = valueOfFirstPacket == packetValue ? 1 : 0;
							break;
						}
					}
					default:
					{
						cout << "WTF";
						break;
					}
					}

					numIterations++;

				}

			}
		}

		if (!subPacket)
		{
			int numProcessed = currentIndex - startIndex;
			int numZerosToAppend = (numProcessed % 8) == 0 ? 0 : 8 - (numProcessed % 8);
			for (int i = 0; i < numZerosToAppend; ++i)
			{
				if (Binary[currentIndex] != '0')
				{
					cout << "WTF";
				}

				currentIndex++;
			}
		}

		endIndex = currentIndex;

		return valueToReturn;
	}

	void Run()
	{
		ifstream infile("inputDay16.txt");

		//string line = "005532447836402684AC7AB3801A800021F0961146B1007A1147C89440294D005C12D2A7BC992D3F4E50C72CDF29EECFD0ACD5CC016962099194002CE31C5D3005F401296CAF4B656A46B2DE5588015C913D8653A3A001B9C3C93D7AC672F4FF78C136532E6E0007FCDFA975A3004B002E69EC4FD2D32CDF3FFDDAF01C91FCA7B41700263818025A00B48DEF3DFB89D26C3281A200F4C5AF57582527BC1890042DE00B4B324DBA4FAFCE473EF7CC0802B59DA28580212B3BD99A78C8004EC300761DC128EE40086C4F8E50F0C01882D0FE29900A01C01C2C96F38FCBB3E18C96F38FCBB3E1BCC57E2AA0154EDEC45096712A64A2520C6401A9E80213D98562653D98562612A06C0143CB03C529B5D9FD87CBA64F88CA439EC5BB299718023800D3CE7A935F9EA884F5EFAE9E10079125AF39E80212330F93EC7DAD7A9D5C4002A24A806A0062019B6600730173640575A0147C60070011FCA005000F7080385800CBEE006800A30C023520077A401840004BAC00D7A001FB31AAD10CC016923DA00686769E019DA780D0022394854167C2A56FB75200D33801F696D5B922F98B68B64E02460054CAE900949401BB80021D0562344E00042A16C6B8253000600B78020200E44386B068401E8391661C4E14B804D3B6B27CFE98E73BCF55B65762C402768803F09620419100661EC2A8CE0008741A83917CC024970D9E718DD341640259D80200008444D8F713C401D88310E2EC9F20F3330E059009118019A8803F12A0FC6E1006E3744183D27312200D4AC01693F5A131C93F5A131C970D6008867379CD3221289B13D402492EE377917CACEDB3695AD61C939C7C10082597E3740E857396499EA31980293F4FD206B40123CEE27CFB64D5E57B9ACC7F993D9495444001C998E66B50896B0B90050D34DF3295289128E73070E00A4E7A389224323005E801049351952694C000";

		string line = "C200B40A82";
		//string line = "38006F45291200";


		for (int i = 0; i < line.length(); ++i)
		{
			Binary.append(HexToDec[line[i]]);
		}

		unsigned long long totalOfVersionNumber = 0;

		int currentIndex = 0;
		bool shouldBreak = false;
		long long value = 0;
		while (!shouldBreak)
		{
			value = ProcessPacket(currentIndex, currentIndex, totalOfVersionNumber, 0, false);

			shouldBreak = true;
			for (int i = currentIndex; i < Binary.length(); ++i)
			{
				if (Binary[i] != '0')
				{
					shouldBreak = false;
					break;
				}
			}

			shouldBreak = shouldBreak || currentIndex == Binary.length();
		}

		cout << "\n\n*********************************\n\n";
		cout << totalOfVersionNumber;
		cout << "\n\n*********************************\n\n";
		cout << value;
	}

};

void RunDay16()
{
	Day16 Day16Obj;
	Day16Obj.Run();
}