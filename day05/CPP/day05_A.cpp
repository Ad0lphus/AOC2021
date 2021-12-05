#include <iostream>
#include <vector>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <bits/stdc++.h>
#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <unistd.h>
using namespace std;

vector<string> split(string in, const string& delimiter) {
    long long pos;
    vector<string> split;
    while ((pos = in.find(delimiter)) != string::npos) {
        split.push_back(in.substr(0, pos));
        in.erase(0, pos + delimiter.length());
    }
    split.push_back(in);
    return split;
}

int main() {
    vector<vector<int>> ocean(1000, vector<int>(1000));
    string next;
	ifstream in("../Input/day5.txt");
    while (in >> next) {
        int x1 = stoi(split(next, ",")[0]);
        int y1 = stoi(split(next, ",")[1]);
        in >> next;
        in >> next;
        int x2 = stoi(split(next, ",")[0]);
        int y2 = stoi(split(next, ",")[1]);
        if (x1 == x2) {
            int minn = min(y1, y2);
            int maxx = max(y1, y2);
            for (int i = minn; i <= maxx; i++) {
                ocean[x1][i]++;
            }
        }
        else if (y1 == y2) {
            int minn = min(x1, x2);
            int maxx = max(x1, x2);
            for (int i = minn; i <= maxx; i++) {
                ocean[i][y1]++;
            }
        }
    }
    long long ans = 0;
    for (const vector<int>& v : ocean) {
        for (int i : v) {
            if (i > 1) {
                ans++;
            }
        }
    }
    cout << "puzzle 1: " <<  ans << endl;
    return 0;
}