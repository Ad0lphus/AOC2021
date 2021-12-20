/*
--- Day 20: Trench Map ---
With the scanners fully deployed, you turn their attention to mapping the floor of the ocean trench.

When you get back the image from the scanners, it seems to just be random noise. Perhaps you can combine an image enhancement algorithm and the input image (your puzzle input) to clean it up a little.

For example:

..#.#..#####.#.#.#.###.##.....###.##.#..###.####..#####..#....#..#..##..##
#..######.###...####..#..#####..##..#.#####...##.#.#..#.##..#.#......#.###
.######.###.####...#.##.##..#..#..#####.....#.#....###..#.##......#.....#.
.#..#..##..#...##.######.####.####.#.#...#.......#..#.#.#...####.##.#.....
.#..#...##.#.##..#...##.#.##..###.#......#.#.......#.#.#.####.###.##...#..
...####.#..#..#.##.#....##..#.####....##...##..#...#......#.#.......#.....
..##..####..#...#.#.#...##..#.#..###..#####........#..####......#..#

#..#.
#....
##..#
..#..
..###
The first section is the image enhancement algorithm. It is normally given on a single line, but it has been wrapped to multiple lines in this example for legibility. The second section is the input image, a two-dimensional grid of light pixels (#) and dark pixels (.).

The image enhancement algorithm describes how to enhance an image by simultaneously converting all pixels in the input image into an output image. Each pixel of the output image is determined by looking at a 3x3 square of pixels centered on the corresponding input image pixel. So, to determine the value of the pixel at (5,10) in the output image, nine pixels from the input image need to be considered: (4,9), (4,10), (4,11), (5,9), (5,10), (5,11), (6,9), (6,10), and (6,11). These nine input pixels are combined into a single binary number that is used as an index in the image enhancement algorithm string.

For example, to determine the output pixel that corresponds to the very middle pixel of the input image, the nine pixels marked by [...] would need to be considered:

# . . # .
#[. . .].
#[# . .]#
.[. # .].
. . # # #
Starting from the top-left and reading across each row, these pixels are ..., then #.., then .#.; combining these forms ...#...#.. By turning dark pixels (.) into 0 and light pixels (#) into 1, the binary number 000100010 can be formed, which is 34 in decimal.

The image enhancement algorithm string is exactly 512 characters long, enough to match every possible 9-bit binary number. The first few characters of the string (numbered starting from zero) are as follows:

0         10        20        30  34    40        50        60        70
|         |         |         |   |     |         |         |         |
..#.#..#####.#.#.#.###.##.....###.##.#..###.####..#####..#....#..#..##..##
In the middle of this first group of characters, the character at index 34 can be found: #. So, the output pixel in the center of the output image should be #, a light pixel.

This process can then be repeated to calculate every pixel of the output image.

Through advances in imaging technology, the images being operated on here are infinite in size. Every pixel of the infinite output image needs to be calculated exactly based on the relevant pixels of the input image. The small input image you have is only a small region of the actual infinite input image; the rest of the input image consists of dark pixels (.). For the purposes of the example, to save on space, only a portion of the infinite-sized input and output images will be shown.

The starting input image, therefore, looks something like this, with more dark pixels (.) extending forever in every direction not shown here:

...............
...............
...............
...............
...............
.....#..#......
.....#.........
.....##..#.....
.......#.......
.......###.....
...............
...............
...............
...............
...............
By applying the image enhancement algorithm to every pixel simultaneously, the following output image can be obtained:

...............
...............
...............
...............
.....##.##.....
....#..#.#.....
....##.#..#....
....####..#....
.....#..##.....
......##..#....
.......#.#.....
...............
...............
...............
...............
Through further advances in imaging technology, the above output image can also be used as an input image! This allows it to be enhanced a second time:

...............
...............
...............
..........#....
....#..#.#.....
...#.#...###...
...#...##.#....
...#.....#.#...
....#.#####....
.....#.#####...
......##.##....
.......###.....
...............
...............
...............
Truly incredible - now the small details are really starting to come through. After enhancing the original input image twice, 35 pixels are lit.

Start with the original input image and apply the image enhancement algorithm twice, being careful to account for the infinite size of the images. How many pixels are lit in the resulting image?

Your puzzle answer was ____.

--- Part Two ---
You still can't quite make out the details in the image. Maybe you just didn't enhance it enough.

If you enhance the starting input image in the above example a total of 50 times, 3351 pixels are lit in the final output image.

Start again with the original input image and apply the image enhancement algorithm 50 times. How many pixels are lit in the resulting image?

Your puzzle answer was _____.
*/

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