#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <bits/stdc++.h>
#include <cstring>
#include <cstdlib>
#include <unistd.h>
#include <fstream>

using namespace std;
void print_title() {
    string stuff(25, '-');
    cout << "\033[1;33m";
    cout << stuff <<"Advent of Code - Day 7"  << stuff  << endl;
    cout << "\033[0m";
    cout << string(40, ' ') << endl;
    // run terminal command in c++
    string cmd = "figlet The Treachery of Whales -c -f small";
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
    }
    while (fgets(buffer, sizeof(buffer), fp) != NULL)
    {
        output += buffer;
    }
    pclose(fp);
    cout << "\033[0;32m";
    cout << output << endl;
    cout << "\033[0m" << endl;
    string stufff(33, '-');
    cout << "\033[1;33m";
    cout << stufff <<"Output"  << stufff  << endl;
    cout << "\033[0m" << endl;
}
int main() {
    print_title();
    vector<int> pos;
    ifstream f("../Input/day7.txt");
    while (f) {
        int p;
        f >> p;
        if (!f) break;
        pos.push_back(p); 
        f.ignore(1);
    }

    auto minmax_Pos = minmax_element(pos.cbegin(), pos.cend());

    int fuel_min = 1000000000;
    for (int i=*minmax_Pos.first;i<=*minmax_Pos.second;i++) {
        int fuel = 0;
        for (auto p : pos) {
            fuel += abs(p-i);
        }
        fuel_min = min(fuel, fuel_min);
    }
    int fuel_min_2 = 1000000000;
    for (int i=*minmax_Pos.first;i<=*minmax_Pos.second;i++) {
        int fuel = 0;
        for (auto p : pos) {
            int dist = abs(p-i);
            fuel += (dist*(1+dist))/2;
        }
        fuel_min_2 = min(fuel, fuel_min_2);
    }

    cout << "Puzzle 1: " << fuel_min << endl;
    cout << "Puzzle 2: " << fuel_min_2 << endl;
    string stuff_final(72, '=');
    cout << endl;
    cout << stuff_final << endl;

}