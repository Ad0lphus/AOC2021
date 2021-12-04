#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <bits/stdc++.h>

using namespace std;

constexpr bool win_checker(const array<int, 25> &board, int row, int col)
{
	int sum = 0;
	for (int c = 0; c < 5; ++c)
		sum += board[row * 5 + c];
	if (sum == 0)
		return true;
	sum = 0;
	for (int r = 0; r < 5; ++r)
		sum += board[r * 5 + col];
	return sum == 0;
}

int main()
{
	string line;
	ifstream in("../Input/day4.txt");
	getline(in, line);
	vector<int> storage_vector;
	stringstream string_stream(line);
	for (string x; getline(string_stream, x, ',');)
		storage_vector.push_back(stoi(x));

	vector<array<int, 25>> boards;
	array<int, 25> board;
	int i = 0, x = 0;
	while (in >> x)
	{
		board[i++] = x;
		if (i == 25)
		{
			boards.push_back(board);
			i = 0;
		}
	}

	vector<int> vector_X(((int)(boards).size()));
	iota(begin((vector_X)), end((vector_X)), 0);
	bool is_first = true;
	int score = -1;
	for (int draw : storage_vector)
	{
		vector<int> remaining;
		for (auto b : vector_X)
		{
			bool wins = false;
			for (int i = 0; i < ((int)(boards[b]).size()); ++i)
			{
				if (boards[b][i] == draw)
				{
					boards[b][i] = 0;
					int row = i / 5;
					int col = i % 5;
					if (win_checker(boards[b], row, col))
					{
						int unmarked = accumulate(begin((boards[b])), end((boards[b])), 0);
						wins = true;
						score = unmarked * draw;
						if (is_first)
						{
							cout << "puzzle 1: " << score << endl;
							is_first = false;
						}
						break;
					}
				}
			}
			if (!wins)
				remaining.push_back(b);
		}
		vector_X = move(remaining);
	}
	cout << "puzzle 2: " << score << endl;
	return 0;
}