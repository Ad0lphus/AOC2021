/*
with open('day3.txt','r') as f:
    binaryNumbers = [line.strip() for line in f.readlines()]

length_of_bits = len(binaryNumbers[0])
gammaRate = []
epsilonRate = []

for i in range(0,length_of_bits):
    counterOne, counterZero = (0,0)
    currentPosBits = [n[i] for n in binaryNumbers]
    counterOne = currentPosBits.count('1')
    counterZero = currentPosBits.count('0')

    if counterOne > counterZero:
        gammaRate.append('1')
        epsilonRate.append('0')
    else:
        gammaRate.append('0')
        epsilonRate.append('1')
    
gammaRate = ''.join(gammaRate)
epsilonRate = ''.join(epsilonRate)

print("puzzle 1: ",int(gammaRate,2)*int(epsilonRate,2))
  


convert python to c++
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int initial()
{
    ifstream f("../Input/day3.txt");
    vector<string> binaryNumbers;
    string line;
    while (getline(f, line))
    {
        binaryNumbers.push_back(line);
    }
    f.close();

    int length_of_bits = binaryNumbers[0].length();
    vector<char> gammaRate;
    vector<char> epsilonRate;

    for (int i = 0; i < length_of_bits; i++)
    {
        int counterOne = 0;
        int counterZero = 0;
        for (int j = 0; j < binaryNumbers.size(); j++)
        {
            if (binaryNumbers[j][i] == '1')
            {
                counterOne++;
            }
            else
            {
                counterZero++;
            }
        }
        if (counterOne > counterZero)
        {
            gammaRate.push_back('1');
            epsilonRate.push_back('0');
        }
        else
        {
            gammaRate.push_back('0');
            epsilonRate.push_back('1');
        }
    }

    string gammaRateString = "";
    for (int i = 0; i < gammaRate.size(); i++)
    {
        gammaRateString += gammaRate[i];
    }
    string epsilonRateString = "";
    for (int i = 0; i < epsilonRate.size(); i++)
    {
        epsilonRateString += epsilonRate[i];
    }

    cout << "puzzle 1: " << stoi(gammaRateString, nullptr, 2) * stoi(epsilonRateString, nullptr, 2) << endl;
    return 0;
}


int main()
{
    initial();
    return 0;
}