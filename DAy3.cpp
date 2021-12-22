#include <iostream>
#include <fstream>
#include <map>
#include <unordered_map>
#include <string>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

class Day3
{
public:
	Day3()
	{

	}

	void Run()
	{
		ifstream infile("inputDay3.txt");

		if (infile.is_open())
		{
			constexpr int StringLength = 12;
			string line;
			const std::string forward = "forward";
			const std::string down = "down";
			const std::string up = "up";
			const std::string delimiter = " ";

			int NumZeros[StringLength];
			int NumOnes[StringLength];

			for (int i = 0; i < StringLength; ++i)
			{
				NumZeros[i] = 0;
				NumOnes[i] = 0;
			}

			std::vector<std::string> EligibleListForO2;
			EligibleListForO2.empty();

			std::vector<std::string> EligibleListForCO2;
			EligibleListForCO2.empty();

			while (getline(infile, line))
			{
				EligibleListForO2.push_back(line);
				EligibleListForCO2.push_back(line);
				for (int i = 0; i < StringLength; ++i)
				{
					if (line[i] == '0')
					{
						NumZeros[i] += 1;
					}
					else
					{
						NumOnes[i] += 1;
					}
				}
			}

			unsigned long long GammaRate = 0;
			unsigned long long Epsilon = 0;

			for (int i = 0; i < StringLength; ++i)
			{
				GammaRate = GammaRate << 1;
				Epsilon = Epsilon << 1;

				if (NumZeros[i] < NumOnes[i])
				{
					GammaRate += 1;
				}
				else if(NumZeros[i] > NumOnes[i])
				{
					Epsilon += 1;
				}
				else
				{
					Epsilon += 1;
				}
			}


			for (int i = 0; i < StringLength; ++i)
			{
				if (EligibleListForO2.size() > 1)
				{
					int numOnes = 0;
					int numZeros = 0;
					char CheckForO2 = '0';

					for (int j = 0; j < EligibleListForO2.size(); ++j)
					{
						string toCheck = EligibleListForO2[j];
						if (toCheck[i] == '0')
						{
							++numZeros;
						}
						else
						{
							++numOnes;
						}
					}

					if (numOnes < numZeros)
					{
						CheckForO2 = '0';
					}
					else 
					{
						CheckForO2 = '1';
					}

					EligibleListForO2.erase(std::remove_if(EligibleListForO2.begin(), EligibleListForO2.end(),
						[i, CheckForO2](const std::string& input)
					{
						return input[i] != CheckForO2;
					}), EligibleListForO2.end());

				}

				if (EligibleListForCO2.size() > 1)
				{
					int numOnes = 0;
					int numZeros = 0;
					char CheckForCO2 = '0';

					for (int j = 0; j < EligibleListForCO2.size(); ++j)
					{
						string toCheck = EligibleListForCO2[j];
						if (toCheck[i] == '0')
						{
							++numZeros;
						}
						else
						{
							++numOnes;
						}
					}

					if (numOnes < numZeros)
					{
						CheckForCO2 = '1';
					}
					else
					{
						CheckForCO2 = '0';
					}

					EligibleListForCO2.erase(std::remove_if(EligibleListForCO2.begin(), EligibleListForCO2.end(),
						[i, CheckForCO2](const std::string& input)
					{
						return input[i] != CheckForCO2;
					}), EligibleListForCO2.end());

				}

			}

			unsigned long long O2 = 0;
			unsigned long long CO2= 0;

			string O2Str = EligibleListForO2[0];
			string CO2Str = EligibleListForCO2[0];

			for (int i = 0; i < StringLength; ++i)
			{
				O2 = O2 << 1;
				CO2 = CO2 << 1;

				if (O2Str[i] == '1')
				{
					O2 += 1;
				}

				if (CO2Str[i] == '1')
				{
					CO2 += 1;
				}
			}

			unsigned long long PowerCons = (Epsilon * GammaRate);
			unsigned long long lifeSuppo = (O2 * CO2);

			cout << "Gamma :" << GammaRate << " Epsi: " << Epsilon << " Power Cons: " << PowerCons<<endl;
			cout << "O2 :" << O2 << " CO2: " << CO2 << " Life : " << lifeSuppo;
		}

	}
};

void RunDay3()
{
	Day3 Day3Obj;
	Day3Obj.Run();
}