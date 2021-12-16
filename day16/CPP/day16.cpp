#include <iostream>
#include <fstream>
#include <string>
#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <unistd.h>
using namespace std;

void print_title() {
    string stuff(25, '-');
    cout << "\033[1;33m";
    cout << stuff <<"Advent of Code - Day 16"  << stuff  << endl;
    cout << "\033[0m";
    cout << string(40, ' ') << endl;
    // run terminal command in c++
    string cmd = "figlet Packet Decoder -c -f small";
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
int main(){
    print_title();
    string command = "./binary/day16A";
    system(command.c_str());
    command = "./binary/day16B";
    system(command.c_str());
    string stuff_final(72, '=');
    cout << endl;
    cout << stuff_final << endl;
    return 0;
}