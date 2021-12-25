#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
#include <stack>
#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> PII;
vector<vector<string>> monad(14);
int max_v[14], min_v[14];
stack<PII> stk;

string T1 = "div z 1";
string T2 = "div z 26";
void print_title() {
    string stuff(25, '-');
    cout << "\033[1;33m";
    cout << stuff <<"Advent of Code - Day 24"  << stuff  << endl;
    cout << "\033[0m";
    cout << string(40, ' ') << endl;
    // run terminal command in c++
    string cmd = "figlet Arithmetic Logic Unit -c -f small";
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
void read_input()
{
    int n = -1;
    string s;
    ifstream f("../Input/day24.txt");
    while (getline(f, s))
    {
        if (s[0] == 'i')
        {
            n++;
        }
        monad[n].push_back(s);
    }
}

int part_1()
{
    read_input();
    for (int i = 0; i < 14; i++)
    {
        if (monad[i][4] == T1)
        {
            int t;
            sscanf(monad[i][15].c_str(), "add y %d", &t);
            stk.push({i, t});
        }
        else if (monad[i][4] == T2)
        {
            auto t = stk.top();
            stk.pop();
            int b = t.first, a = i;
            int x;
            sscanf(monad[i][5].c_str(), "add x %d", &x);
            int diff = x + t.second;
            if (diff < 0)
            {
                swap(a, b);
                diff = -diff;
            }
            max_v[a] = 9, max_v[b] = 9 - diff, min_v[a] = 1 + diff, min_v[b] = 1;
        }
    }
    long long ans = 0;
    for (int i = 0; i < 14; i++)
    {
        ans = ans * 10 + max_v[i];
    }
    cout << "Puzzle 1: " << ans << endl;
    return 0;
}
int part_2()
{
    read_input();
    for (int i = 0; i < 14; i++)
    {
        if (monad[i][4] == T1)
        {
            int t;
            sscanf(monad[i][15].c_str(), "add y %d", &t);
            stk.push({i, t});
        }
        else if (monad[i][4] == T2)
        {
            auto t = stk.top();
            stk.pop();
            int b = t.first, a = i;
            int x;
            sscanf(monad[i][5].c_str(), "add x %d", &x);
            int diff = x + t.second;
            if (diff < 0)
            {
                swap(a, b);
                diff = -diff;
            }
            max_v[a] = 9, max_v[b] = 9 - diff, min_v[a] = 1 + diff, min_v[b] = 1;
        }
    }
    long long ans = 0;
    for (int i = 0; i < 14; i++)
    {
        ans = ans * 10 + min_v[i];
    }
    cout << "Puzzle 2: " << ans << endl;
    return 0;
}
int main()
{
    print_title();
    part_1();
    part_2();
    string stuff_final(72, '=');
    cout << endl;
    cout << stuff_final << endl;
    return 0;
}