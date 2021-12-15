#include <bits/stdc++.h>
#define debug(x) cerr << #x << ": " << x << '\n'
#define all(x) begin(x), end(x)
#define rall(x) rbegin(x), rend(x)
#define sz(x) (int)(x).size()
#define pb(x) push_back(x)
#define mp(x, y) make_pair(x, y)
using namespace std;
using pi = pair<int, int>;
using ll = long long;
const int INF = 1e9;

vector<vector<int>> Cave;
void print_title() {
    string stuff(25, '-');
    cout << "\033[1;33m";
    cout << stuff <<"Advent of Code - Day 14"  << stuff  << endl;
    cout << "\033[0m";
    cout << string(40, ' ') << endl;
    // run terminal command in c++
    string cmd = "figlet Chiton -c -f small";
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
int solve(int mul){
	int init_h = sz(Cave);
	int init_l = sz(Cave[0]);
	int height = init_h*mul;
	int length = init_l*mul;
	vector<vector<int>> cave(height, vector<int>(length, 0));

	for(int y = 0; y<mul; ++y){
		for(int x = 0; x<mul; ++x){
			for(int i = 0; i<init_h; ++i){
				for(int j = 0; j<init_l; ++j){
					int new_val = Cave[i][j]+x+y;
					if(new_val>9) new_val -= 9;
					cave[i+init_h*y][j+init_l*x] = new_val;
				}
			}
		}
	}

	vector<vector<int>> cost(sz(cave), vector<int>(sz(cave[0]), INF));
	vector<vector<bool>> seen(sz(cave), vector<bool>(sz(cave[0]), false));
	priority_queue<pair<int, pi>> q;

	cost[0][0] = 0;
	pi start = mp(0, 0);
	q.push(mp(0, start));
	while(!q.empty()){
		pi a = q.top().second; q.pop();
		int y = a.first, x = a.second;
		if(seen[y][x]) continue;
		seen[y][x] = true;
		vector<pi> moves = {
			mp(1, 0),
			mp(0, 1),
			mp(-1, 0),
			mp(0, -1)
		};
		for(auto move : moves){
			int new_y = y + move.first;
			int new_x = x + move.second;
			if(new_y >= 0 && new_y < sz(cave) && new_x >= 0 && new_x < sz(cave[0])){
				int weight = cave[new_y][new_x];
				if(cost[y][x]+weight < cost[new_y][new_x]){
					cost[new_y][new_x] = cost[y][x]+weight;
					q.push(mp(-cost[new_y][new_x], mp(new_y, new_x)));
				}
			}
		}
	}

	return cost[sz(cave)-1][sz(cave[0])-1];
}

int main(){
	print_title();
	ios::sync_with_stdio(false);
    ifstream input_file("../Input/day15.txt");
	string line;
	while(input_file >> line){
		vector<int> temp;
		for(char c : line)
			temp.pb(c-48);
		Cave.pb(temp);
	}

	int p1 = solve(1);
	int p2 = solve(5);
	cout << "Puzzle 1: " << p1 << '\n';
	cout << "Puzzle 2: " << p2 << "\n\n";
	string stuff_final(72, '=');
    cout << stuff_final << endl;
}