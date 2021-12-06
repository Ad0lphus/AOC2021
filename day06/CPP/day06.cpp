#include <iostream>
#include <vector>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <bits/stdc++.h>
#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <unistd.h>
#include <fstream>
using namespace std;
void print_title() {
    string stuff(25, '-');
    cout << "\033[1;33m";
    cout << stuff <<"Advent of Code - Day 6"  << stuff  << endl;
    cout << "\033[0m";
    cout << string(40, ' ') << endl;
}
static uint64_t solver(array<uint64_t, 9> fishes, int days)
{
    uint64_t temp = 0;
    for (int i = 0; i < days; i++)
    {
        temp = fishes[0];
        for (uint8_t j = 1; j < fishes.size(); j++)
        {
            fishes[j - 1] = fishes[j];
        }
        fishes[8] = temp;
        fishes[6] += temp;
    }

    uint64_t sum = 0;
    for_each(fishes.begin(), fishes.end(), [&sum](uint64_t n)
                  { sum += n; });

    return sum;
}

int main()
{
    print_title();
    // run terminal command in c++
    string cmd = "figlet Lanternfish -c -f small";
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
    array<uint64_t, 9> fishes = {0};
    uint64_t n;
    ifstream in("../Input/day6.txt");
    while (in >> n)
    {
        in.ignore(1);
        fishes[n]++;
    }

    cout << "puzzle 1: " << solver(fishes, 80) << '\n';
    cout << "puzzle 2: " << solver(fishes, 256) << '\n';
    string stuff_final(72, '=');
    cout << endl;
    cout << stuff_final << endl;
    return 0;
}