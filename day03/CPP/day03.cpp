/*
--- Day 3: Binary Diagnostic ---
The submarine has been making some odd creaking noises, so you ask it to produce a diagnostic report just in case.

The diagnostic report (your puzzle input) consists of a list of binary numbers which, when decoded properly, can tell you many useful things about the conditions of the submarine. The first parameter to check is the power consumption.

You need to use the binary numbers in the diagnostic report to generate two new binary numbers (called the gamma rate and the epsilon rate). The power consumption can then be found by multiplying the gamma rate by the epsilon rate.

Each bit in the gamma rate can be determined by finding the most common bit in the corresponding position of all numbers in the diagnostic report. For example, given the following diagnostic report:

00100
11110
10110
10111
10101
01111
00111
11100
10000
11001
00010
01010
Considering only the first bit of each number, there are five 0 bits and seven 1 bits. Since the most common bit is 1, the first bit of the gamma rate is 1.

The most common second bit of the numbers in the diagnostic report is 0, so the second bit of the gamma rate is 0.

The most common value of the third, fourth, and fifth bits are 1, 1, and 0, respectively, and so the final three bits of the gamma rate are 110.

So, the gamma rate is the binary number 10110, or 22 in decimal.

The epsilon rate is calculated in a similar way; rather than use the most common bit, the least common bit from each position is used. So, the epsilon rate is 01001, or 9 in decimal. Multiplying the gamma rate (22) by the epsilon rate (9) produces the power consumption, 198.

Use the binary numbers in your diagnostic report to calculate the gamma rate and epsilon rate, then multiply them together. What is the power consumption of the submarine? (Be sure to represent your answer in decimal, not binary.)

Your puzzle answer was _____________.

--- Part Two ---
Next, you should verify the life support rating, which can be determined by multiplying the oxygen generator rating by the CO2 scrubber rating.

Both the oxygen generator rating and the CO2 scrubber rating are values that can be found in your diagnostic report - finding them is the tricky part. Both values are located using a similar process that involves filtering out values until only one remains. Before searching for either rating value, start with the full list of binary numbers from your diagnostic report and consider just the first bit of those numbers. Then:

Keep only numbers selected by the bit criteria for the type of rating value for which you are searching. Discard numbers which do not match the bit criteria.
If you only have one number left, stop; this is the rating value for which you are searching.
Otherwise, repeat the process, considering the next bit to the right.
The bit criteria depends on which type of rating value you want to find:

To find oxygen generator rating, determine the most common value (0 or 1) in the current bit position, and keep only numbers with that bit in that position. If 0 and 1 are equally common, keep values with a 1 in the position being considered.
To find CO2 scrubber rating, determine the least common value (0 or 1) in the current bit position, and keep only numbers with that bit in that position. If 0 and 1 are equally common, keep values with a 0 in the position being considered.
For example, to determine the oxygen generator rating value using the same example diagnostic report from above:

Start with all 12 numbers and consider only the first bit of each number. There are more 1 bits (7) than 0 bits (5), so keep only the 7 numbers with a 1 in the first position: 11110, 10110, 10111, 10101, 11100, 10000, and 11001.
Then, consider the second bit of the 7 remaining numbers: there are more 0 bits (4) than 1 bits (3), so keep only the 4 numbers with a 0 in the second position: 10110, 10111, 10101, and 10000.
In the third position, three of the four numbers have a 1, so keep those three: 10110, 10111, and 10101.
In the fourth position, two of the three numbers have a 1, so keep those two: 10110 and 10111.
In the fifth position, there are an equal number of 0 bits and 1 bits (one each). So, to find the oxygen generator rating, keep the number with a 1 in that position: 10111.
As there is only one number left, stop; the oxygen generator rating is 10111, or 23 in decimal.
Then, to determine the CO2 scrubber rating value from the same example above:

Start again with all 12 numbers and consider only the first bit of each number. There are fewer 0 bits (5) than 1 bits (7), so keep only the 5 numbers with a 0 in the first position: 00100, 01111, 00111, 00010, and 01010.
Then, consider the second bit of the 5 remaining numbers: there are fewer 1 bits (2) than 0 bits (3), so keep only the 2 numbers with a 1 in the second position: 01111 and 01010.
In the third position, there are an equal number of 0 bits and 1 bits (one each). So, to find the CO2 scrubber rating, keep the number with a 0 in that position: 01010.
As there is only one number left, stop; the CO2 scrubber rating is 01010, or 10 in decimal.
Finally, to find the life support rating, multiply the oxygen generator rating (23) by the CO2 scrubber rating (10) to get 230.

Use the binary numbers in your diagnostic report to calculate the oxygen generator rating and CO2 scrubber rating, then multiply them together. What is the life support rating of the submarine? (Be sure to represent your answer in decimal, not binary.)

Your puzzle answer was ______________.
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <bitset>
#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <unistd.h>
using namespace std;

void print_title() {
    string stuff(25, '-');
    cout << "\033[1;33m";
    cout << stuff <<"Advent of Code - Day 3"  << stuff  << endl;
    cout << "\033[0m";
    cout << string(40, ' ') << endl;
}
int part_1()
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

void part_2(const string &path)
{
    fstream stream;
    vector<string> binNumbers;
    stream.open(path);

    int k = 1;
    binNumbers.resize(k);
    while(!stream.eof())
    {
        binNumbers.resize(k);
        getline(stream, binNumbers[k - 1]);
        k++;
    }
    stream.close();

    vector<string> ogRate;
    ogRate.resize(binNumbers.size());
    int o = 0;
    for(const string& f : binNumbers)
    {
        ogRate[o] = f;
        o++;
    }

    int m = 0;
    while(ogRate.size() != 1)
    {
        int zero(0), one(0);
        for(string j : ogRate)
        {
                int currentInt = (int)j[m] - 48;
                if(currentInt == 1) one++;
                else zero++;
        }

        char bitCriteria;
        if(one >= zero)
        {
            bitCriteria = '1';
        }
        else
        {
            bitCriteria = '0';
        }

        bool isAllAtCriteria = false;
        int i = 0;
        while(!isAllAtCriteria)
        {
            if(ogRate[i].at(m) != bitCriteria)
            {
                ogRate.erase(ogRate.begin() + i);
                i = 0;
                isAllAtCriteria = true;

                for(string k : ogRate)
                    if(k.at(m) != bitCriteria)
                    {
                        isAllAtCriteria = false;
                        break;
                    }
            }
            else i++;
        }
        m++;
    }

    vector<string> co2Rate;
    co2Rate.resize(binNumbers.size());
    int o1 = 0;
    for(const string& f : binNumbers)
    {
        co2Rate[o1] = f;
        o1++;
    }
    int l = 0;
    while(co2Rate.size() != 1)
    {
        int zero(0), one(0);
        for(string j : co2Rate)
        {
            int currentInt = (int)j[l] - 48;
            if(currentInt == 1) one++;
            else zero++;
        }

        char bitCriteria;
        if(zero <= one)
        {
            bitCriteria = '0';
        }
        else
        {
            bitCriteria = '1';
        }

        bool isAllAtCriteria = false;
        int i = 0;
        while(!isAllAtCriteria)
        {
            if(co2Rate[i].at(l) != bitCriteria)
            {
                co2Rate.erase(co2Rate.begin() + i);
                i = 0;
                isAllAtCriteria = true;

                for(string u : co2Rate)
                    if(u.at(l) != bitCriteria)
                        isAllAtCriteria = false;
            }
            else i++;
        }

        l++;
    }

    unsigned long ogRateInt = bitset<64>(ogRate[0]).to_ulong(), co2RateInt = bitset<64>(co2Rate[0]).to_ulong();

    cout << ogRateInt * co2RateInt;
}

struct Bits
{
    int zero;
    int one;
};

int main()
{
    print_title();
    // run terminal command in c++
    string cmd = "figlet Binary Diagnostic -c -f small";
    char *command_char = new char[cmd.length() + 1];
    strcpy(command_char, cmd.c_str());
    // store the output of the command in a string
    string output = "";
    char buffer[128];
    FILE *fp;
    fp = popen(command_char, "r");
    if (fp == NULL)
    {
        cout << "Failed to run command" << endl;
        return 1;
    }
    while (fgets(buffer, sizeof(buffer), fp) != NULL)
    {
        output += buffer;
    }
    pclose(fp);
    cout << "\033[0;32m";
    cout << output << endl;
    cout << "\033[0m" << endl;
    string stuff(33, '-');
    cout << "\033[1;33m";
    cout << stuff <<"Output"  << stuff  << endl;
    cout << "\033[0m" << endl;
    part_1();
    string path;
    fstream fileStream;
    
    fileStream.open("../Input/day3.txt");
    if(fileStream.is_open())
    {
        fileStream.close();
        cout << "puzzle 2: ";
        part_2("../Input/day3.txt");

    }
    string stuff_final(72, '=');
    cout << endl << endl;
    cout << stuff_final << endl;
    return 0;
}