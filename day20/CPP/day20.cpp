#include <iostream>
#include <fstream>
#include <stdio.h>
#include <vector>
#include <cstring>
#include <bits/stdc++.h>
using namespace std;

void print_title() {
    string stuff(25, '-');
    cout << "\033[1;33m";
    cout << stuff <<"Advent of Code - Day 20"  << stuff  << endl;
    cout << "\033[0m";
    cout << string(40, ' ') << endl;
    // run terminal command in c++
    string cmd = "figlet Trench Map -c -f small";
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
	ifstream f("../Input/day20.txt");

	string read_string;
	vector<bool> key;
	key.reserve(512);
	f >> read_string;
	for (char c : read_string)
		key.push_back(c == '#');

	int buffer_size = 55;

	vector<vector<bool>> grid;
	f >> read_string;
	int row_length = (buffer_size * 2) + read_string.length();
	for (int i = 0; i < buffer_size; i++) {
		grid.push_back({});
		grid.back().resize(row_length);
	}
	do {
		grid.push_back({});
		grid.back().reserve(row_length);
		grid.back().resize(buffer_size);
		for (char c : read_string)
			grid.back().push_back(c == '#');
		grid.back().resize(row_length);
	} while (f >> read_string);
	for (int i = 0; i < buffer_size; i++) {
		grid.push_back({});
		grid.back().resize(row_length);
	}
	vector<vector<bool>> newGrid = grid; // Mainly for copying size

	for (int iteration = 0; iteration < 50; iteration++) {
		for (int y = 0; y < grid.size(); y++) {
			for (int x = 0; x < row_length; x++) {
				int key_Index = 0;

				auto try_Position = [&](int x, int y) {
					key_Index <<= 1;

					if ((x < 0) || (x >= row_length) || (y < 0) || (y >= grid.size())) { // Check if out of grid
						key_Index |= grid[0][0];
					} else {
						key_Index |= grid[y][x];
					}
				};

				try_Position(x - 1, y - 1);
				try_Position(x    , y - 1);
				try_Position(x + 1, y - 1);
				try_Position(x - 1, y    );
				try_Position(x    , y    );
				try_Position(x + 1, y    );
				try_Position(x - 1, y + 1);
				try_Position(x    , y + 1);
				try_Position(x + 1, y + 1);

				newGrid[y][x] = key[key_Index];
			}
		}
		grid = newGrid;

		if (iteration == 1) {
			int T_Pixels = 0;
			for (auto i : grid) {
				for (auto j : i) 
					T_Pixels += j;
			}
			printf("Puzzle 1: %d\n", T_Pixels);
		}
	}

	int T_Pixels = 0;
	for (auto i : grid) {
		for (auto j : i) 
			T_Pixels += j;
	}
	printf("Puzzle 2: %d\n", T_Pixels);
    string stuff_final(72, '=');
    cout << endl;
    cout << stuff_final << endl;
	return 0;
}