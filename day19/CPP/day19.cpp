#include <bits/stdc++.h>
#include <regex>
using namespace std;
void print_title() {
    string stuff(25, '-');
    cout << "\033[1;33m";
    cout << stuff <<"Advent of Code - Day 19"  << stuff  << endl;
    cout << "\033[0m";
    cout << string(40, ' ') << endl;
    // run terminal command in c++
    string cmd = "figlet Beacon Scanner -c -f small";
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
void fast() {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
}

std::vector<std::string> split(const std::string& s, std::string rgx_str = "\\s+") {
    std::vector<std::string> elems;

    std::regex rgx(rgx_str);

    std::sregex_token_iterator iter(s.begin(), s.end(), rgx, -1);
    std::sregex_token_iterator end;

    while (iter != end) {
        elems.push_back(*iter);
        ++iter;
    }

    return elems;
}

bool isInt(const std::string& s) {
    return !s.empty() && std::all_of(s.begin(), s.end(), ::isdigit);
}

inline std::string trim(const std::string& s) {
    auto wsfront = std::find_if_not(s.begin(), s.end(), [](int c) {return std::isspace(c); });
    auto wsback = std::find_if_not(s.rbegin(), s.rend(), [](int c) {return std::isspace(c); }).base();
    return (wsback <= wsfront ? std::string() : std::string(wsfront, wsback));
}

int sign(int n) {
    if (n == 0) return 0;
    if (n > 0) return 1;
    return -1;
}

string hexToBin(char c) {
    switch (c) {
    case '0':
        return "0000";
    case '1':
        return "0001";
    case '2':
        return "0010";
    case '3':
        return "0011";
    case '4':
        return "0100";
    case '5':
        return "0101";
    case '6':
        return "0110";
    case '7':
        return "0111";
    case '8':
        return "1000";
    case '9':
        return "1001";
    case 'A':
    case 'a':
        return "1010";
    case 'B':
    case 'b':
        return "1011";
    case 'C':
    case 'c':
        return "1100";
    case 'D':
    case 'd':
        return "1101";
    case 'E':
    case 'e':
        return "1110";
    case 'F':
    case 'f':
        return "1111";
    default:
        return "";
    }
}

long long toLong(string n) {
    long long result = 0;
    long long pow = 1;

    for (int i = (int)(n.length() - 1); i >= 0; i--) {
        if (n[i] == '1') result += pow;
        pow *= 2;
    }

    return result;
}

// ------------------------------------------------------------------------------------------------
#pragma endregion HELPERS



struct Vec3 {
    int x, y, z;

    Vec3(int x, int y, int z) : x(x), y(y), z(z) {}
    Vec3() : x(0), y(0), z(0) {}

    void rotateX() {
        int z2 = z;
        z = y;
        y = -z2;
    }

    void rotateY() {
        int x2 = x;
        x = z;
        z = -x2;
    }

    void rotateZ() {
        int x2 = x;
        x = y;
        y = -x2;
    }

    void invert() {
        x = -x;
        y = -y;
        z = -z;
    }

    Vec3 operator+(const Vec3& o) const {
        return Vec3(x + o.x, y + o.y, z + o.z);
    }

    Vec3 operator-(const Vec3& o) const {
        return Vec3(x - o.x, y - o.y, z - o.z);
    }

    bool operator==(const Vec3& o) const {
        return x == o.x && y == o.y && z == o.z;
    }

    bool operator<(const Vec3& o) const {
        if (x < o.x) return true;
        else if (x == o.x) {
            if (y < o.y) return true;
            else if (y == o.y) {
                if (z < o.z) return true;
            }
        }
        return false;
    }

    int manhattanDistance(const Vec3& o) {
        return abs(x - o.x) + abs(y - o.y) + abs(z - o.z);
    }
};

ostream& operator<<(ostream& s, const Vec3& v)
{
    s << "(" << v.x << ", " << v.y << ", " << v.z << ")";
    return s;
}

struct Scanner {
    vector<Vec3> beacons;
    bool aligned = false;
    int curRot = 0;

    Vec3 translation;

    Scanner() {}

    void rotate() {
        assert(!aligned);

        for (Vec3& v : beacons) v.rotateY();

        if ((curRot + 1) % 8 == 0) for (Vec3& v : beacons) v.rotateZ();
        else if ((curRot + 1) % 4 == 0) for (Vec3& v : beacons) v.rotateX();
        
        curRot++;
    }

    void translate(const Vec3& offset) {
        assert(!aligned);

        for (int i = 0; i < beacons.size(); i++) {
            beacons[i] = beacons[i] + offset;
        }

        translation = translation + offset;
    }

    bool align(Scanner& o) {
        for (int r = 0; r < 24; r++) {

            for (int i = 0; i < beacons.size(); i++) {
                for (int j = 0; j < o.beacons.size(); j++) {
                    Vec3 delta = beacons[i] - o.beacons[j];
                    o.translate(delta);

                    int matches = 0;
                    for (int a = 0; a < beacons.size(); a++) {
                        for (int b = 0; b < o.beacons.size(); b++) {
                            if (beacons[a] == o.beacons[b]) matches++;

                            if (matches >= 12) {
                                aligned = true;
                                o.aligned = true;
                                return true;
                            }
                        }
                    }

                    delta.invert();
                    o.translate(delta);
                }
            }

            o.rotate();
        }

        return false;
    }

    void print() {
        for (int i = 0; i < beacons.size(); i++) {
        }
    }
};

vector<Scanner> scanners;

void readInput(const std::string& filename) {
    ifstream cin(filename);

    scanners = vector<Scanner>();

    Scanner s;
    string l;
    int skip = 1;

    while (getline(cin, l)) {
        if (skip > 0) {
            skip--;
            continue;
        }

        if (l == "") {
            scanners.push_back(s);
            s = Scanner();
            skip = 1;
            continue;
        }

        auto a = split(l, ",");
        Vec3 b(stoi(a[0]), stoi(a[1]), stoi(a[2]));
        s.beacons.push_back(b);
    }

    scanners.push_back(s);
}

bool align(int a, int b) {
    bool success = scanners[b].align(scanners[a]);
    return success;
}

void alignAll() {
    for (int i = 0; i < scanners.size(); i++) {
        for (int j = i + 1; j < scanners.size(); j++) {
            if (align(i, j)) goto found_pair;
        }
    }

    found_pair:
    bool active = true;

    while (active) {
        active = false;

        for (int i = 0; i < scanners.size(); i++) {
            if (scanners[i].aligned) continue;

            for (int j = 0; j < scanners.size(); j++) {
                if (!scanners[j].aligned) continue;

                if (align(i, j)) {
                    active = true;
                    break;
                }
            }
        }
    }
}

void printPositions() {
    for (int i = 0; i < scanners.size(); i++) {
        if (!scanners[i].aligned) continue;
        Vec3 t = scanners[i].translation - scanners[0].translation;
    }
}

void printVisibleBeacons() {
    set<Vec3> visibleBeacons;
    for (int i = 0; i < scanners.size(); i++) {
        for (int j = 0; j < scanners[i].beacons.size(); j++) {
            visibleBeacons.insert(scanners[i].beacons[j]);
        }
    }
    // print puzzle 1 
    cout << "Puzzle 1: " << visibleBeacons.size() << "\n";
}

void printDistance() {
    int maxDist = 0;

    for (int i = 0; i < scanners.size(); i++)
        for (int j = 0; j < scanners.size(); j++)
            maxDist = max(maxDist, scanners[i].translation.manhattanDistance(scanners[j].translation));
    // print puzzle 2
    cout << "Puzzle 2: " << maxDist << "\n";
}

void solve(const std::string& filename) {
    readInput(filename);
    alignAll();

    printPositions();
    printVisibleBeacons();
    printDistance();   
}

int main() {
    print_title();
    fast();
    solve("../Input/day19.txt");
    string stuff_final(72, '=');
    cout << endl;
    cout << stuff_final << endl;
}