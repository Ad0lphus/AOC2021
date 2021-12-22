#include <fstream>
#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <memory>
#include <cstring>
#include <unordered_map>
using namespace std;
void print_title() {
    string stuff(25, '-');
    cout << "\033[1;33m";
    cout << stuff <<"Advent of Code - Day 22"  << stuff  << endl;
    cout << "\033[0m";
    cout << string(40, ' ') << endl;
    // run terminal command in c++
    string cmd = "figlet Reactor Reboot -c -f small";
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
struct Cube
{
    int lx, ly, lz, hx, hy, hz;
    bool is_on = false;

    Cube() = default;
    Cube(int lx_, int ly_, int lz_, int hx_, int hy_, int hz_)
        : lx(lx_), ly(ly_), lz(lz_), hx(hx_), hy(hy_), hz(hz_) { }

    bool is_inside(Cube const& other) const
    {
        return (lx >= other.lx && ly >= other.ly && lz >= other.lz) &&
               (hx <= other.hx && hy <= other.hz && lz <= other.hz);
    }

    bool is_intersect(Cube const& other) const
    {
        if (lx > other.hx || hx < other.lx) return false;
        if (ly > other.hy || hy < other.ly) return false;
        if (lz > other.hz || hz < other.lz) return false;
        return true; 
    }

    size_t volume() const
    {
        return size_t(hx - lx + 1) * size_t(hy - ly + 1) * size_t(hz - lz + 1);
    }
};

ostream& operator<<(ostream& os, Cube const& cube)
{
    os << (cube.is_on ? "on " : "off ") << '[' << cube.lx << ", " << cube.ly << ", " << cube.lz << "], [" << cube.hx << ", " << cube.hy << ", " << cube.hz << ']';
    return os;
}

using Cubes = vector<Cube>;

ostream& operator<<(ostream& os, Cubes const& cubes)
{
    for (auto const& cube : cubes)
        os << cube << '\n';
    return os;
}

void read_all(ifstream& ifs, Cubes& cubes)
{
    string line;
    while(getline(ifs, line))
    {
        Cube cube;
        // on or off
        auto space_pos = line.find(' ');
        cube.is_on = line.substr(0, space_pos) == "on" ? true : false;
        auto position = line.substr(space_pos + 1);
        sscanf(position.c_str(), "x=%d..%d,y=%d..%d,z=%d..%d", &cube.lx, &cube.hx, &cube.ly, &cube.hy, &cube.lz, &cube.hz);
        cubes.push_back(cube);
    }
}

void substract(Cube const& c0, Cube const& c1, Cubes& res_cubes)
{
    Cube overlap(max(c0.lx, c1.lx), max(c0.ly, c1.ly), max(c0.lz, c1.lz),
                 min(c0.hx, c1.hx), min(c0.hy, c1.hy), min(c0.hz, c1.hz));
    
    // z direction
    if (c0.lz < overlap.lz)  // bottom part
        res_cubes.emplace_back(c0.lx, c0.ly, c0.lz, c0.hx, c0.hy, overlap.lz - 1);
    if (c0.hz > overlap.hz)  // top part
        res_cubes.emplace_back(c0.lx, c0.ly, overlap.hz + 1, c0.hx, c0.hy, c0.hz);
    
    // x direction
    if (c0.lx < overlap.lx)  // front
        res_cubes.emplace_back(c0.lx, c0.ly, overlap.lz, overlap.lx - 1, c0.hy, overlap.hz);
    if (c0.hx > overlap.hx)  // back
        res_cubes.emplace_back(overlap.hx + 1, c0.ly, overlap.lz, c0.hx, c0.hy, overlap.hz);
    
    // y direction
    if (c0.ly < overlap.ly)  // left
        res_cubes.emplace_back(overlap.lx, c0.ly, overlap.lz, overlap.hx, overlap.ly - 1, overlap.hz);
    if (c0.hy > overlap.hy)  // right
        res_cubes.emplace_back(overlap.lx, overlap.hy + 1, overlap.lz, overlap.hx, c0.hy, overlap.hz);
}

size_t part_1()
{
    ifstream ifs("../Input/day22.txt");
    Cubes cubes;
    read_all(ifs, cubes);
    //cout << cubes << endl;

    Cubes res;
    for (auto const& cube : cubes)
    {
        Cubes tmp;
        for (auto const &c : res)
            if (c.is_intersect(cube))
                substract(c, cube, tmp);
            else
                tmp.push_back(c);
        if (cube.is_on)
            tmp.push_back(cube);
        res = move(tmp);
    }
    size_t cnt = 0;
    Cube region(-50, -50, -50, 50, 50, 50);
    for (auto const& c : res)
        if (c.is_inside(region))
            cnt += c.volume();

    return cnt;
}

size_t part_2()
{
    ifstream ifs("../Input/day22.txt");
    Cubes cubes;
    read_all(ifs, cubes);


    Cubes res;
    for (auto const& cube : cubes)
    {
        Cubes tmp;
        for (auto const &c : res)
            if (c.is_intersect(cube))
                substract(c, cube, tmp);
            else
                tmp.push_back(c);
        if (cube.is_on)
            tmp.push_back(cube);
        res = move(tmp);
    }
    size_t cnt = 0;
    for (auto const& c : res)
        cnt += c.volume();

    return cnt;
}

int main(int argc, char* argv[])
{
    print_title();
    cout << "Puzzle 1: "<< part_1() << endl;
    cout << "Puzzle 2: "<< part_2() << endl;
    string stuff_final(72, '=');
    cout << endl;
    cout << stuff_final << endl;
    return 0;
}