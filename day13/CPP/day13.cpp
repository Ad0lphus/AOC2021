/*
--- Day 13: Transparent Origami ---
You reach another volcanically active part of the cave. It would be nice if you could do some kind of thermal imaging so you could tell ahead of time which caves are too hot to safely enter.

Fortunately, the submarine seems to be equipped with a thermal camera! When you activate it, you are greeted with:

Congratulations on your purchase! To activate this infrared thermal imaging
camera system, please enter the code found on page 1 of the manual.
Apparently, the Elves have never used this feature. To your surprise, you manage to find the manual; as you go to open it, page 1 falls out. It's a large sheet of transparent paper! The transparent paper is marked with random dots and includes instructions on how to fold it up (your puzzle input). For example:

6,10
0,14
9,10
0,3
10,4
4,11
6,0
6,12
4,1
0,13
10,12
3,4
3,0
8,4
1,10
2,14
8,10
9,0

fold along y=7
fold along x=5
The first section is a list of dots on the transparent paper. 0,0 represents the top-left coordinate. The first value, x, increases to the right. The second value, y, increases downward. So, the coordinate 3,0 is to the right of 0,0, and the coordinate 0,7 is below 0,0. The coordinates in this example form the following pattern, where # is a dot on the paper and . is an empty, unmarked position:

...#..#..#.
....#......
...........
#..........
...#....#.#
...........
...........
...........
...........
...........
.#....#.##.
....#......
......#...#
#..........
#.#........
Then, there is a list of fold instructions. Each instruction indicates a line on the transparent paper and wants you to fold the paper up (for horizontal y=... lines) or left (for vertical x=... lines). In this example, the first fold instruction is fold along y=7, which designates the line formed by all of the positions where y is 7 (marked here with -):

...#..#..#.
....#......
...........
#..........
...#....#.#
...........
...........
-----------
...........
...........
.#....#.##.
....#......
......#...#
#..........
#.#........
Because this is a horizontal line, fold the bottom half up. Some of the dots might end up overlapping after the fold is complete, but dots will never appear exactly on a fold line. The result of doing this fold looks like this:

#.##..#..#.
#...#......
......#...#
#...#......
.#.#..#.###
...........
...........
Now, only 17 dots are visible.

Notice, for example, the two dots in the bottom left corner before the transparent paper is folded; after the fold is complete, those dots appear in the top left corner (at 0,0 and 0,1). Because the paper is transparent, the dot just below them in the result (at 0,3) remains visible, as it can be seen through the transparent paper.

Also notice that some dots can end up overlapping; in this case, the dots merge together and become a single dot.

The second fold instruction is fold along x=5, which indicates this line:

#.##.|#..#.
#...#|.....
.....|#...#
#...#|.....
.#.#.|#.###
.....|.....
.....|.....
Because this is a vertical line, fold left:

#####
#...#
#...#
#...#
#####
.....
.....
The instructions made a square!

The transparent paper is pretty big, so for now, focus on just completing the first fold. After the first fold in the example above, 17 dots are visible - dots that end up overlapping after the fold is completed count as a single dot.

How many dots are visible after completing just the first fold instruction on your transparent paper?

Your puzzle answer was ___.

--- Part Two ---
Finish folding the transparent paper according to the instructions. The manual says the code is always eight capital letters.

What code do you use to activate the infrared thermal imaging camera system?

Your puzzle answer was ________________.
*/
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <set>
#include <utility>
#include <fstream>
#include <map>
#include <algorithm>
#include <bits/stdc++.h>
using namespace std;
struct Fold {
    char axis;
    int cord;
};

void print_title() {
    string stuff(25, '-');
    cout << "\033[1;33m";
    cout << stuff <<"Advent of Code - Day 13"  << stuff  << endl;
    cout << "\033[0m";
    cout << string(40, ' ') << endl;
    // run terminal command in c++
    string cmd = "figlet Transparent Origami -c -f small";
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
int part_1()
{
    print_title();
    set<pair<int, int>> points;
    string line;
    ifstream f("../Input/day13.txt");
    while (getline(f, line) && !line.empty()) {
        stringstream ss(line);
        int x, y;
        ss >> x;
        ss.ignore(1);
        ss >> y;
        points.insert({x, y});
    }
    vector<Fold> folds;
    while (getline(f, line)) {
        stringstream ss(line);
        ss.ignore(11);
        Fold fold;
        ss >> fold.axis;
        ss.ignore(1);
        ss >> fold.cord;
        folds.push_back(fold);
    }
    for (Fold fold : folds) {
        for (auto it = points.begin(); it != points.end();) {
            if (fold.axis == 'x' && it->first > fold.cord) {
                points.insert({2 * fold.cord - it->first , it->second});
                it = points.erase(it);
            } else if (fold.axis == 'y' && it->second < fold.cord) {
                points.insert({it->first, 2 * fold.cord - it->second});
                it = points.erase(it);
            } else {
                ++it;
            }
        }
        break;
    }
    cout << "Puzzle1: " << points.size() << endl;
    return 0;
}
int part_2()
{
    set<pair<int, int>> points;
    string line;
    ifstream f("../Input/day13.txt");
    while (getline(f, line) && !line.empty()) {
        stringstream ss(line);
        int x, y;
        ss >> x;
        ss.ignore(1);
        ss >> y;
        points.insert({x, y});
    }
    vector<Fold> folds;
    while (getline(f, line)) {
        stringstream ss(line);
        ss.ignore(11); 
        Fold fold;
        ss >> fold.axis;
        ss.ignore(1); 
        ss >> fold.cord;
        folds.push_back(fold);
    }
    for (Fold fold : folds) {
        for (auto it = points.begin(); it != points.end();) {
            if (fold.axis == 'x' && it->first > fold.cord) {
                points.insert({2 * fold.cord - it->first , it->second});
                it = points.erase(it);
            } else if (fold.axis == 'y' && it->second > fold.cord) {
                points.insert({it->first, 2 * fold.cord - it->second});
                it = points.erase(it);
            } else {
                ++it;
            }
        }
    }
    auto compx = [](auto& a, auto& b) { return a.first < b.first; };
    int maxCol = max_element(points.begin(), points.end(), compx)->first;
    auto compy = [](auto& a, auto& b) { return a.second < b.second; };
    int maxRow = max_element(points.begin(), points.end(), compy)->second;
    vector<vector<char>> paper(maxRow + 1, vector<char>(maxCol + 1, '.'));
    for (auto& [x, y] : points) {
        paper[y][x] = '#';
    }
    cout << "Puzzle2: " << endl;
    for (auto& row : paper) {
        for (auto& c : row) {
            if (c == '.') {
                c = ' ';
            }
            cout << c;
        }
        cout << endl;
    }
    return 0;
}

int main()
{
    part_1();
    part_2();
    cout << endl;
    string stuff_final(72, '=');
    cout << stuff_final << endl;
    return 0;
    return 0;
}