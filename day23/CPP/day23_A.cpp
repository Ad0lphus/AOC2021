#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <sstream>
#include <set>
#include <bits/stdc++.h>
using namespace std;
string order = "ABCD";
vector<string> doneState;
map<char, int> costs = {{'A', 1}, {'B', 10}, {'C', 100}, {'D', 1000}};
map<char, int> doorwayMap = {{'A', 2}, {'B', 4}, {'C', 6}, {'D', 8}};
map<char, int> orderMap = {{'A', 0}, {'B', 1}, {'C', 2}, {'D', 3}};
int standing[] = {0, 1, 3, 5, 7, 9, 10};
int doorway[] = {2, 4, 6, 8};
struct State
{
    int energy;
    vector<string> rooms;
    string hallway;
    vector<int> moves;
};

struct lazy
{
    bool operator()(const State &a, const State &b) { return a.energy > b.energy; }
};

bool isDone(State s)
{
    for (int i = 0; i < 4; i++)
        if (s.rooms[i] != doneState[i])
            return false;
    return true;
}
string stateString(State s)
{
    stringstream ss;
    ss << s.energy << "," << s.hallway << "," << s.rooms[0] << "," << s.rooms[1] << "," << s.rooms[2] << "," << s.rooms[3];
    return ss.str();
}
bool isValid(State s)
{
    for (auto r : s.rooms)
        if (r.size() > doneState[0].size())
            return false;
    if (s.energy < 0)
        return false;
    return true;
}

bool leave(State s, int i)
{
    for (auto space : s.rooms[i])
        if (space != order[i])
            return true;
    return false;
}

bool canMove(State s, int l, int r, int ignore)
{
    int i = min(l, r);
    int j = max(l, r);
    for (int k = i; k <= j; k++)
    {
        if (k == ignore || k == 2 || k == 4 || k == 6 || k == 8)
            continue;
        if (s.hallway[k] != '.')
            return false;
    }
    return true;
};

int main()
{
    string command, line;
    State baseState;
    baseState.energy = 0;
    baseState.hallway = "...........";
    for (int i = 0; i < 4; i++)
    {
        baseState.rooms.push_back("");
        doneState.push_back("");
    }
    // get input from ../Input/day23.txt
    ifstream input("../Input/day23.txt");
    for (int i = 0; i < 3; i++)
        getline(input, line);

    while (line[3] != '#')
    {
        baseState.rooms[0].push_back(line[3]);
        baseState.rooms[1].push_back(line[5]);
        baseState.rooms[2].push_back(line[7]);
        baseState.rooms[3].push_back(line[9]);
        getline(input, line);
        for (int i = 0; i < 4; i++)
            doneState[i].push_back(order[i]);
    }

    int roomDepth = baseState.rooms[0].size();

    vector<State> q;
    q.push_back(baseState);
    make_heap(q.begin(), q.end(), lazy());

    set<string> visited;
    while (!q.empty())
    {
        State s = q.front();
        pop_heap(q.begin(), q.end(), lazy());
        q.pop_back();
        string ss = stateString(s);
        if (visited.find(ss) != visited.end())
            continue;
        visited.insert(ss);

        if (isDone(s))
        {
            cout << "Puzzle 1: "<< (s.energy)<<endl;
            return 0;
        }

        for (int i = 0; i < 4; i++)
        {
            if (leave(s, i))
            {
                char c = s.rooms[i][0];
                if (!leave(s, orderMap[c]) && canMove(s, doorway[i], doorway[orderMap[c]], -1))
                {
                    State next = s;
                    next.rooms[i].erase(0, 1);
                    int e = roomDepth - next.rooms[i].size() + roomDepth - next.rooms[orderMap[c]].size() + abs(doorway[i] - doorway[orderMap[c]]);

                    next.rooms[orderMap[c]] = c + next.rooms[orderMap[c]];
                    next.energy += e * costs[c];
                    next.moves.push_back(e);
                    q.push_back(next);
                    push_heap(q.begin(), q.end(), lazy());
                }
                for (int j = 0; j < 7; j++)
                {
                    if (canMove(s, doorway[i], standing[j], -1))
                    {
                        State next = s;
                        next.rooms[i].erase(0, 1);
                        int e = roomDepth - next.rooms[i].size();

                        next.hallway[standing[j]] = c;
                        e += abs(doorway[i] - standing[j]);

                        next.energy += e * costs[c];
                        next.moves.push_back(e);
                        q.push_back(next);
                        push_heap(q.begin(), q.end(), lazy());
                    }
                }
            }
        }
        for (int i = 0; i < (int)s.hallway.size(); i++)
        {
            char c = s.hallway[i];
            if (c == '.')
                continue;
            if (!leave(s, orderMap[c]) && canMove(s, i, doorway[orderMap[c]], i))
            {
                State next = s;
                next.hallway[i] = '.';

                int e = roomDepth - next.rooms[orderMap[c]].size();
                e += abs(doorway[orderMap[c]] - i);

                next.rooms[orderMap[c]] = c + next.rooms[orderMap[c]];
                next.energy += e * costs[c];
                next.moves.push_back(e);
                q.push_back(next);
                push_heap(q.begin(), q.end(), lazy());
            }
        }
    }
    
}