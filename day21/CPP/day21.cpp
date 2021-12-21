/*
--- Day 21: Dirac Dice ---
There's not much to do as you slowly descend to the bottom of the ocean. The submarine computer challenges you to a nice game of Dirac Dice.

This game consists of a single die, two pawns, and a game board with a circular track containing ten spaces marked 1 through 10 clockwise. Each player's starting space is chosen randomly (your puzzle input). Player 1 goes first.

Players take turns moving. On each player's turn, the player rolls the die three times and adds up the results. Then, the player moves their pawn that many times forward around the track (that is, moving clockwise on spaces in order of increasing value, wrapping back around to 1 after 10). So, if a player is on space 7 and they roll 2, 2, and 1, they would move forward 5 times, to spaces 8, 9, 10, 1, and finally stopping on 2.

After each player moves, they increase their score by the value of the space their pawn stopped on. Players' scores start at 0. So, if the first player starts on space 7 and rolls a total of 5, they would stop on space 2 and add 2 to their score (for a total score of 2). The game immediately ends as a win for any player whose score reaches at least 1000.

Since the first game is a practice game, the submarine opens a compartment labeled deterministic dice and a 100-sided die falls out. This die always rolls 1 first, then 2, then 3, and so on up to 100, after which it starts over at 1 again. Play using this die.

For example, given these starting positions:

Player 1 starting position: 4
Player 2 starting position: 8
This is how the game would go:

Player 1 rolls 1+2+3 and moves to space 10 for a total score of 10.
Player 2 rolls 4+5+6 and moves to space 3 for a total score of 3.
Player 1 rolls 7+8+9 and moves to space 4 for a total score of 14.
Player 2 rolls 10+11+12 and moves to space 6 for a total score of 9.
Player 1 rolls 13+14+15 and moves to space 6 for a total score of 20.
Player 2 rolls 16+17+18 and moves to space 7 for a total score of 16.
Player 1 rolls 19+20+21 and moves to space 6 for a total score of 26.
Player 2 rolls 22+23+24 and moves to space 6 for a total score of 22.
...after many turns...

Player 2 rolls 82+83+84 and moves to space 6 for a total score of 742.
Player 1 rolls 85+86+87 and moves to space 4 for a total score of 990.
Player 2 rolls 88+89+90 and moves to space 3 for a total score of 745.
Player 1 rolls 91+92+93 and moves to space 10 for a final score, 1000.
Since player 1 has at least 1000 points, player 1 wins and the game ends. At this point, the losing player had 745 points and the die had been rolled a total of 993 times; 745 * 993 = 739785.

Play a practice game using the deterministic 100-sided die. The moment either player wins, what do you get if you multiply the score of the losing player by the number of times the die was rolled during the game?

Your puzzle answer was ___________.

--- Part Two ---
Now that you're warmed up, it's time to play the real game.

A second compartment opens, this time labeled Dirac dice. Out of it falls a single three-sided die.

As you experiment with the die, you feel a little strange. An informational brochure in the compartment explains that this is a quantum die: when you roll it, the universe splits into multiple copies, one copy for each possible outcome of the die. In this case, rolling the die always splits the universe into three copies: one where the outcome of the roll was 1, one where it was 2, and one where it was 3.

The game is played the same as before, although to prevent things from getting too far out of hand, the game now ends when either player's score reaches at least 21.

Using the same starting positions as in the example above, player 1 wins in 444356092776315 universes, while player 2 merely wins in 341960390180808 universes.

Using your given starting positions, determine every possible outcome. Find the player that wins in more universes; in how many universes does that player win?

Your puzzle answer was _____________________.
*/

#include <bits/stdc++.h>

using namespace std;
void print_title() {
    string stuff(25, '-');
    cout << "\033[1;33m";
    cout << stuff <<"Advent of Code - Day 21"  << stuff  << endl;
    cout << "\033[0m";
    cout << string(40, ' ') << endl;
    // run terminal command in c++
    string cmd = "figlet Dirac Dice -c -f small";
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
int N;
const string file = "../Input/day21.txt";
int countlines()
{
    int c = 0;
    string l;
    ifstream f(file);
    while (getline(f, l))
        c++;
    return c;
}

int part_1()
{
    cin.tie(0)->sync_with_stdio(0);
    N = countlines();
    freopen(file.c_str(), "r", stdin);
    int p1 = 2, p2 = 8;
    int s1 = 0, s2 = 0;
    for (int i = 3;; i += 3)
    {
        p1 = (p1 + 3 * i - 3);
        p1 = (p1 - 1) % 10 + 1;
        s1 += p1;
        if (s1 >= 1000)
        {
            cout <<"Puzzle 1: "<< i * s2 << '\n';
            break;
        }
        swap(p1, p2);
        swap(s1, s2);
    }
    return 0;
}
long long dp[50][50][11][11][2];

int part_2()
{
    cin.tie(0)->sync_with_stdio(0);
    N = countlines();
    freopen(file.c_str(), "r", stdin);
    int sp1 = 2, sp2 = 8;
    dp[0][0][sp1][sp2][0] = 1;
    long long win1 = 0, win2 = 0;
    for (int s1 = 0; s1 <= 30; ++s1)
    {
        for (int s2 = 0; s2 <= 30; ++s2)
        {
            for (int p1 = 1; p1 <= 10; ++p1)
            {
                for (int p2 = 1; p2 <= 10; ++p2)
                {
                    if (s1 >= 21 && s2 < 21)
                        win1 += dp[s1][s2][p1][p2][1];
                    else if (s2 >= 21 && s1 < 21)
                        win2 += dp[s1][s2][p1][p2][0];
                    else
                    {
                        for (int r1 = 1; r1 <= 3; ++r1)
                        {
                            for (int r2 = 1; r2 <= 3; ++r2)
                            {
                                for (int r3 = 1; r3 <= 3; ++r3)
                                {
                                    int roll = r1 + r2 + r3;
                                    int np1 = (p1 + roll - 1) % 10 + 1;
                                    dp[s1 + np1][s2][np1][p2][1] += dp[s1][s2][p1][p2][0];
                                    int np2 = (p2 + roll - 1) % 10 + 1;
                                    dp[s1][s2 + np2][p1][np2][0] += dp[s1][s2][p1][p2][1];
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    cout <<"Puzzle 2: "<< max(win1, win2) << '\n';
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