#include <iostream>
#include <fstream>
#include <vector>
#include <tuple>
#include <regex>
#include <set>
#include <map>
using namespace std;

void print_title() {
    string stuff(25, '-');
    cout << "\033[1;33m";
    cout << stuff <<"Advent of Code - Day 14"  << stuff  << endl;
    cout << "\033[0m";
    cout << string(40, ' ') << endl;
    // run terminal command in c++
    string cmd = "figlet Extended Polymerization -c -f small";
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
vector<string> getStrings() {
    vector<string> strings;
    string line;

    ifstream input_file("../Input/day14.txt");
    
    while (getline(input_file, line)) {
        strings.push_back(line);
    }

    input_file.close();
    return strings;
}

tuple<string,vector<string>,vector<string>> parseInput() {
    vector<string> strings = getStrings();
    regex rule("(.+) -> (.+)");
    vector<string> ruleInputs;
    vector<string> RO;
    string Poly;
    Poly = strings[0];
    for (int i = 1; i < strings.size(); i++) {
        string s = strings[i];
        smatch match;
        regex_match(s, match, rule);
        if (match.size() == 3) {
            ruleInputs.push_back(match[1].str());
            RO.push_back(match[2].str());
        }
    }
    return {Poly, ruleInputs, RO};
}

int part_1(int argc, char** argv) {
    vector<string> ruleInputs;
    vector<string> RO;
    string Poly;
    tie(Poly, ruleInputs, RO) = parseInput();
    int steps = 10;
    set<char> All_chars;
    for (char c : Poly) {
        All_chars.insert(c);
    }
    for (string s : RO) {
        All_chars.insert(s[0]);
    }
    for (int i = 0; i < steps; i++) {
        string pair = "  "; 
        string newPoly = Poly;
        for (int i = 0; i < Poly.size(); i++) {
            char c = Poly[i];
            pair[0] = pair[1];
            pair[1] = c;
            auto foundPair = find(ruleInputs.begin(),ruleInputs.end(),pair);
            if (foundPair != ruleInputs.end()) {
                newPoly.insert(i + newPoly.size()-Poly.size(), RO[foundPair-ruleInputs.begin()]);
            }
        }
        Poly = newPoly;
    }
    vector<unsigned long> char_Frequency;
    for (char c : All_chars) {
        char_Frequency.push_back(count(Poly.begin(), Poly.end(), c));
    }
    cout << "Puzzle 1: "<< *max_element(char_Frequency.begin(), char_Frequency.end()) - *min_element(char_Frequency.begin(), char_Frequency.end()) << endl;
    return 0;
}

int part_2(int argc, char** argv) {
    vector<string> ruleInputs;
    vector<string> RO;
    string Poly;
    tie(Poly, ruleInputs, RO) = parseInput();
    int steps = 40;
    set<char> All_chars;
    for (char c : Poly) {
        All_chars.insert(c);
    }
    for (string s : RO) {
        All_chars.insert(s[0]);
    }
    map<string,unsigned long long> pairs;
    for (int i = 1; i < Poly.size(); i++) {
        string pair = ""; 
        pair.push_back(Poly[i-1]);
        pair.push_back(Poly[i]);
        pairs[pair] += 1;
    }
    map<char, long long> characterFrequencyMap;
    for (int i = 0; i < steps; i++) {
        auto pairsCopy = pairs;
        for (int i = 0; i < ruleInputs.size(); i++) {
            auto ri = ruleInputs[i];
            auto ro = RO[i];
            unsigned long long howManyPairs = pairs[ri];
            string pair1 = "";
            pair1.push_back(ri[0]);
            pair1.push_back(ro[0]); 
            string pair2 = "";
            pair2.push_back(ro[0]); 
            pair2.push_back(ri[1]);
            pairsCopy[ri] -= pairs[ri];
            pairsCopy[pair1] += howManyPairs;
            pairsCopy[pair2] += howManyPairs;
        }
        pairs = pairsCopy;
    }
    for (auto pair : pairs) {
        characterFrequencyMap[pair.first[0]] += pair.second;
        characterFrequencyMap[pair.first[1]] += pair.second;
    }
    vector<unsigned long long> char_Frequency;
    for (auto f : characterFrequencyMap) {
        char_Frequency.push_back(f.second);
    }
    cout << "Puzzle 2: "<<(*max_element(char_Frequency.begin(), char_Frequency.end()) - *min_element(char_Frequency.begin(), char_Frequency.end())) / 2 + 1 << endl << endl; 
    return 0;
}

int main(int argc, char** argv) {
    print_title();
    part_1(argc, argv);
    part_2(argc, argv);
    string stuff_final(72, '=');
    cout << stuff_final << endl;
    return 0;
}
