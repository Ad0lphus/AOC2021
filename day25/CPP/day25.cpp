#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <queue>
#include <algorithm>
#include <cstring>
#include <set>
#include <chrono>
using namespace std::chrono;
using namespace std;
typedef unsigned long long lld;
void print_title() {
    string stuff(25, '-');
    cout << "\033[1;33m";
    cout << stuff <<"Advent of Code - Day 25"  << stuff  << endl;
    cout << "\033[0m";
    cout << string(40, ' ') << endl;
    // run terminal command in c++
    string cmd = "figlet Sea Cucumber -c -f small";
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
bool move(vector<string> &state)
{
    int H, W;
    H = state.size();
    W = state[0].size();
    bool moved = false;

    for (int i = 0; i < H; i++)
        for (int j = 0; j < W; j++)
            if (state[i][j] == '>' && state[i][(j + 1) % W] == '.')
                state[i][j] = 'M';

    for (int i = 0; i < H; i++)
        for (int j = 0; j < W; j++)
            if (state[i][j] == 'M')
            {
                moved = true;
                state[i][j] = '.';
                state[i][(j + 1) % W] = '>';
            }
    for (int i = 0; i < H; i++)
        for (int j = 0; j < W; j++)
            if (state[i][j] == 'v' && state[(i + 1) % H][j] == '.')
                state[i][j] = 'M';
    for (int i = 0; i < H; i++)
        for (int j = 0; j < W; j++)
            if (state[i][j] == 'M')
            {
                moved = true;
                state[i][j] = '.';
                state[(i + 1) % H][j] = 'v';
            }
    return moved;
}

void print(vector<string> &state)
{
    for (int i = 0; i < state.size(); i++)
    {
        cout << state[i] << endl;
    }
}

int main()
{
    print_title();
    ifstream input("../Input/day25.txt");
    vector<string> state;
    for (string line; getline(input, line);)
    {
        state.push_back(line);
    }
    int steps = 0;
    while (move(state))
    {
        steps++;
    }
    cout <<"Puzzle 1: "<< ++steps << endl;
    cout <<"Puzzle 2: "<< "Completed :))" << endl;
    string stuff_final(72, '=');
    cout << endl;
    cout << stuff_final << endl;
    return 0;
}