/*
--- Day 12: Passage Pathing ---
With your submarine's subterranean subsystems subsisting suboptimally, the only way you're getting out of this cave anytime soon is by finding a path yourself. Not just a path - the only way to know if you've found the best path is to find all of them.

Fortunately, the sensors are still mostly working, and so you build a rough map of the remaining caves (your puzzle input). For example:

start-A
start-b
A-c
A-b
b-d
A-end
b-end
This is a list of how all of the caves are connected. You start in the cave named start, and your destination is the cave named end. An entry like b-d means that cave b is connected to cave d - that is, you can move between them.

So, the above cave system looks roughly like this:

    start
    /   \
c--A-----b--d
    \   /
     end
Your goal is to find the number of distinct paths that start at start, end at end, and don't visit small caves more than once. There are two types of caves: big caves (written in uppercase, like A) and small caves (written in lowercase, like b). It would be a waste of time to visit any small cave more than once, but big caves are large enough that it might be worth visiting them multiple times. So, all paths you find should visit small caves at most once, and can visit big caves any number of times.

Given these rules, there are 10 paths through this example cave system:

start,A,b,A,c,A,end
start,A,b,A,end
start,A,b,end
start,A,c,A,b,A,end
start,A,c,A,b,end
start,A,c,A,end
start,A,end
start,b,A,c,A,end
start,b,A,end
start,b,end
(Each line in the above list corresponds to a single path; the caves visited by that path are listed in the order they are visited and separated by commas.)

Note that in this cave system, cave d is never visited by any path: to do so, cave b would need to be visited twice (once on the way to cave d and a second time when returning from cave d), and since cave b is small, this is not allowed.

Here is a slightly larger example:

dc-end
HN-start
start-kj
dc-start
dc-HN
LN-dc
HN-end
kj-sa
kj-HN
kj-dc
The 19 paths through it are as follows:

start,HN,dc,HN,end
start,HN,dc,HN,kj,HN,end
start,HN,dc,end
start,HN,dc,kj,HN,end
start,HN,end
start,HN,kj,HN,dc,HN,end
start,HN,kj,HN,dc,end
start,HN,kj,HN,end
start,HN,kj,dc,HN,end
start,HN,kj,dc,end
start,dc,HN,end
start,dc,HN,kj,HN,end
start,dc,end
start,dc,kj,HN,end
start,kj,HN,dc,HN,end
start,kj,HN,dc,end
start,kj,HN,end
start,kj,dc,HN,end
start,kj,dc,end
Finally, this even larger example has 226 paths through it:

fs-end
he-DX
fs-he
start-DX
pj-DX
end-zg
zg-sl
zg-pj
pj-he
RW-he
fs-DX
pj-RW
zg-RW
start-pj
he-WI
zg-he
pj-fs
start-RW
How many paths through this cave system are there that visit small caves at most once?

Your puzzle answer was _____.

--- Part Two ---
After reviewing the available paths, you realize you might have time to visit a single small cave twice. Specifically, big caves can be visited any number of times, a single small cave can be visited at most twice, and the remaining small caves can be visited at most once. However, the caves named start and end can only be visited exactly once each: once you leave the start cave, you may not return to it, and once you reach the end cave, the path must end immediately.

Now, the 36 possible paths through the first example above are:

start,A,b,A,b,A,c,A,end
start,A,b,A,b,A,end
start,A,b,A,b,end
start,A,b,A,c,A,b,A,end
start,A,b,A,c,A,b,end
start,A,b,A,c,A,c,A,end
start,A,b,A,c,A,end
start,A,b,A,end
start,A,b,d,b,A,c,A,end
start,A,b,d,b,A,end
start,A,b,d,b,end
start,A,b,end
start,A,c,A,b,A,b,A,end
start,A,c,A,b,A,b,end
start,A,c,A,b,A,c,A,end
start,A,c,A,b,A,end
start,A,c,A,b,d,b,A,end
start,A,c,A,b,d,b,end
start,A,c,A,b,end
start,A,c,A,c,A,b,A,end
start,A,c,A,c,A,b,end
start,A,c,A,c,A,end
start,A,c,A,end
start,A,end
start,b,A,b,A,c,A,end
start,b,A,b,A,end
start,b,A,b,end
start,b,A,c,A,b,A,end
start,b,A,c,A,b,end
start,b,A,c,A,c,A,end
start,b,A,c,A,end
start,b,A,end
start,b,d,b,A,c,A,end
start,b,d,b,A,end
start,b,d,b,end
start,b,end
The slightly larger example above now has 103 paths through it, and the even larger example now has 3509 paths through it.

Given these new rules, how many paths through this cave system are there?

Your puzzle answer was _______.
*/

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
    cout << stuff <<"Advent of Code - Day 12"  << stuff  << endl;
    cout << "\033[0m";
    cout << string(40, ' ') << endl;
    // run terminal command in c++
    string cmd = "figlet Passage Pathing -c -f small";
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
const int mod = 1e9 + 7, inf = 0x3f3f3f3f;
const int MN = 30;
int N;
const string file = "../Input/day12.txt";
int countlines()
{
    int c = 0;
    string l;
    ifstream f("../Input/day12.txt");
    while (getline(f, l))
        c++;
    return c;
}
map<string, vector<string>> adj;
set<string> vis;
map<string, int> vis1;
bool small(string s) { return s[0] >= 'a' && s[0] <= 'z'; }
int ans;
int ans1;
void dfs(string v)
{
    if (v == "end")
    {
        ans++;
        return;
    }
    if (small(v))
        vis.insert(v);
    for (string to : adj[v])
    {
        if (small(to) && vis.count(to))
            continue;
        dfs(to);
    }
    vis.erase(v);
}
void dfs1(string v, bool twice)
{
    if (v == "end")
    {
        ans1++;
        return;
    }
    if (small(v))
        vis1[v]++;
    for (string to : adj[v])
    {
        if (to == "start")
            continue;
        if (twice && small(to) && vis1[to] >= 1)
            continue;
        if (!twice && small(to) && vis1[to] >= 2)
            continue;
        dfs1(to, twice | vis1[to] == 1);
    }
    vis1[v]--;
}
int part_1()
{
    cin.tie(0)->sync_with_stdio(0);
    N = countlines();
    freopen(file.c_str(), "r", stdin);
    for (int i = 1; i <= N; ++i)
    {
        string s;
        cin >> s;
        int idx = s.find('-');
        string a = s.substr(0, idx);
        string b = s.substr(idx + 1);
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    dfs("start");
    cout << "Puzzle 1: " << ans << '\n';
    return 0;
}
int part_2()
{
    cin.tie(0)->sync_with_stdio(0);
    N = countlines();
    freopen(file.c_str(), "r", stdin);
    for (int i = 1; i <= N; ++i)
    {
        string s;
        cin >> s;
        int idx = s.find('-');
        string a = s.substr(0, idx);
        string b = s.substr(idx + 1);
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    dfs1("start", 0);
    cout << "Puzzle 2: " << ans1 << '\n';
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