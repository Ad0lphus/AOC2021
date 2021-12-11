#include <stdio.h>
#include <string>
#include <fstream>
#include <algorithm>
#include <map>
#include <stack>
#include <list>
#include <vector>
#include <iostream>
#include <bits/stdc++.h>
using namespace std;

void print_title() {
    string stuff(25, '-');
    cout << "\033[1;33m";
    cout << stuff <<"Advent of Code - Day 11"  << stuff  << endl;
    cout << "\033[0m";
    cout << string(40, ' ') << endl;
    // run terminal command in c++
    string cmd = "figlet Dumbo Octopus -c -f small";
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
static uint64_t increment(vector<vector<uint8_t>>& grid, int row, int col)
{
    grid[row][col]++;
    
    uint64_t fired = 0;

    if (grid[row][col] == 9 + 1)
    {
        fired++;

        if (row > 0)
        {
            if (col > 0)
            {
                fired += increment(grid, row-1, col-1);
            }

            fired += increment(grid, row-1, col);

            if (col < grid[row-1].size() - 1)
            {
                fired += increment(grid, row-1, col+1);
            }
        }

        if (col > 0)
        {
            fired += increment(grid, row, col-1);
        }

        if (col < grid[row].size() - 1)
        {
            fired += increment(grid, row, col+1);
        }

        if (row < grid.size() - 1)
        {
            if (col > 0)
            {
                fired += increment(grid, row+1, col-1);
            }

            fired += increment(grid, row+1, col);

            if (col < grid[row+1].size() - 1)
            {
                fired += increment(grid, row+1, col+1);
            }
        }
    }

    return fired;
}

static void reset_flashed(vector<vector<uint8_t>>& grid)
{
    for (auto& r:grid)
        for (auto& c:r)
            if (c > 9) c = 0;
}

static uint64_t puzzle1()
{
    ifstream f("../Input/day11.txt");

    if (f.fail())
    {
        printf("failed to open input file.");
        return -1;
    }

    vector<vector<uint8_t>> grid;
    string input_row;

    while(f >> input_row)
    {
        grid.push_back({});
        
        for (auto c: input_row)
        {
            grid.back().push_back(c - '0');
        }
    }

    f.close();

    uint64_t flashes = 0;

    for (auto step = 0; step < 100; step++)
    {
        for (auto row = 0; row < grid.size(); row++)
        {
            for (auto col = 0; col < grid[row].size(); col++)
            {
                flashes += increment(grid, row, col);
            }
        }

        reset_flashed(grid);
    }

    return flashes;
}

static uint64_t puzzle2()
{
    ifstream f("../Input/day11.txt");

    if (f.fail())
    {
        printf("failed to open input file.");
        return -1;
    }

    vector<vector<uint8_t>> grid;
    string input_row;

    while(f >> input_row)
    {
        grid.push_back({});
        
        for (auto c: input_row)
        {
            grid.back().push_back(c - '0');
        }
    }

    f.close();

    uint64_t steps = 1;

    for (;; steps++)
    {
        uint64_t flashes = 0;

        for (auto row = 0; row < grid.size(); row++)
        {
            for (auto col = 0; col < grid[row].size(); col++)
            {
                flashes += increment(grid, row, col);
            }
        }

        if (flashes == 100) break;

        reset_flashed(grid);
    }

    return steps;
}

int main()
{
    print_title();
    auto part_1 = puzzle1();
    auto part_2 = puzzle2();

    printf("Puzzle 1: %lu\nPuzzle 2: %lu\n", part_1, part_2);
    string stuff_final(72, '=');
    cout << endl;
    cout << stuff_final << endl;
}