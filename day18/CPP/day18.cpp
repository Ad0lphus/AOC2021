/*
--- Day 18: Snailfish ---
You descend into the ocean trench and encounter some snailfish. They say they saw the sleigh keys! They'll even tell you which direction the keys went if you help one of the smaller snailfish with his math homework.

Snailfish numbers aren't like regular numbers. Instead, every snailfish number is a pair - an ordered list of two elements. Each element of the pair can be either a regular number or another pair.

Pairs are written as [x,y], where x and y are the elements within the pair. Here are some example snailfish numbers, one snailfish number per line:

[1,2]
[[1,2],3]
[9,[8,7]]
[[1,9],[8,5]]
[[[[1,2],[3,4]],[[5,6],[7,8]]],9]
[[[9,[3,8]],[[0,9],6]],[[[3,7],[4,9]],3]]
[[[[1,3],[5,3]],[[1,3],[8,7]]],[[[4,9],[6,9]],[[8,2],[7,3]]]]
This snailfish homework is about addition. To add two snailfish numbers, form a pair from the left and right parameters of the addition operator. For example, [1,2] + [[3,4],5] becomes [[1,2],[[3,4],5]].

There's only one problem: snailfish numbers must always be reduced, and the process of adding two snailfish numbers can result in snailfish numbers that need to be reduced.

To reduce a snailfish number, you must repeatedly do the first action in this list that applies to the snailfish number:

If any pair is nested inside four pairs, the leftmost such pair explodes.
If any regular number is 10 or greater, the leftmost such regular number splits.
Once no action in the above list applies, the snailfish number is reduced.

During reduction, at most one action applies, after which the process returns to the top of the list of actions. For example, if split produces a pair that meets the explode criteria, that pair explodes before other splits occur.

To explode a pair, the pair's left value is added to the first regular number to the left of the exploding pair (if any), and the pair's right value is added to the first regular number to the right of the exploding pair (if any). Exploding pairs will always consist of two regular numbers. Then, the entire exploding pair is replaced with the regular number 0.

Here are some examples of a single explode action:

[[[[[9,8],1],2],3],4] becomes [[[[0,9],2],3],4] (the 9 has no regular number to its left, so it is not added to any regular number).
[7,[6,[5,[4,[3,2]]]]] becomes [7,[6,[5,[7,0]]]] (the 2 has no regular number to its right, and so it is not added to any regular number).
[[6,[5,[4,[3,2]]]],1] becomes [[6,[5,[7,0]]],3].
[[3,[2,[1,[7,3]]]],[6,[5,[4,[3,2]]]]] becomes [[3,[2,[8,0]]],[9,[5,[4,[3,2]]]]] (the pair [3,2] is unaffected because the pair [7,3] is further to the left; [3,2] would explode on the next action).
[[3,[2,[8,0]]],[9,[5,[4,[3,2]]]]] becomes [[3,[2,[8,0]]],[9,[5,[7,0]]]].
To split a regular number, replace it with a pair; the left element of the pair should be the regular number divided by two and rounded down, while the right element of the pair should be the regular number divided by two and rounded up. For example, 10 becomes [5,5], 11 becomes [5,6], 12 becomes [6,6], and so on.

Here is the process of finding the reduced result of [[[[4,3],4],4],[7,[[8,4],9]]] + [1,1]:

after addition: [[[[[4,3],4],4],[7,[[8,4],9]]],[1,1]]
after explode:  [[[[0,7],4],[7,[[8,4],9]]],[1,1]]
after explode:  [[[[0,7],4],[15,[0,13]]],[1,1]]
after split:    [[[[0,7],4],[[7,8],[0,13]]],[1,1]]
after split:    [[[[0,7],4],[[7,8],[0,[6,7]]]],[1,1]]
after explode:  [[[[0,7],4],[[7,8],[6,0]]],[8,1]]
Once no reduce actions apply, the snailfish number that remains is the actual result of the addition operation: [[[[0,7],4],[[7,8],[6,0]]],[8,1]].

The homework assignment involves adding up a list of snailfish numbers (your puzzle input). The snailfish numbers are each listed on a separate line. Add the first snailfish number and the second, then add that result and the third, then add that result and the fourth, and so on until all numbers in the list have been used once.

For example, the final sum of this list is [[[[1,1],[2,2]],[3,3]],[4,4]]:

[1,1]
[2,2]
[3,3]
[4,4]
The final sum of this list is [[[[3,0],[5,3]],[4,4]],[5,5]]:

[1,1]
[2,2]
[3,3]
[4,4]
[5,5]
The final sum of this list is [[[[5,0],[7,4]],[5,5]],[6,6]]:

[1,1]
[2,2]
[3,3]
[4,4]
[5,5]
[6,6]
Here's a slightly larger example:

[[[0,[4,5]],[0,0]],[[[4,5],[2,6]],[9,5]]]
[7,[[[3,7],[4,3]],[[6,3],[8,8]]]]
[[2,[[0,8],[3,4]]],[[[6,7],1],[7,[1,6]]]]
[[[[2,4],7],[6,[0,5]]],[[[6,8],[2,8]],[[2,1],[4,5]]]]
[7,[5,[[3,8],[1,4]]]]
[[2,[2,2]],[8,[8,1]]]
[2,9]
[1,[[[9,3],9],[[9,0],[0,7]]]]
[[[5,[7,4]],7],1]
[[[[4,2],2],6],[8,7]]
The final sum [[[[8,7],[7,7]],[[8,6],[7,7]]],[[[0,7],[6,6]],[8,7]]] is found after adding up the above snailfish numbers:

  [[[0,[4,5]],[0,0]],[[[4,5],[2,6]],[9,5]]]
+ [7,[[[3,7],[4,3]],[[6,3],[8,8]]]]
= [[[[4,0],[5,4]],[[7,7],[6,0]]],[[8,[7,7]],[[7,9],[5,0]]]]

  [[[[4,0],[5,4]],[[7,7],[6,0]]],[[8,[7,7]],[[7,9],[5,0]]]]
+ [[2,[[0,8],[3,4]]],[[[6,7],1],[7,[1,6]]]]
= [[[[6,7],[6,7]],[[7,7],[0,7]]],[[[8,7],[7,7]],[[8,8],[8,0]]]]

  [[[[6,7],[6,7]],[[7,7],[0,7]]],[[[8,7],[7,7]],[[8,8],[8,0]]]]
+ [[[[2,4],7],[6,[0,5]]],[[[6,8],[2,8]],[[2,1],[4,5]]]]
= [[[[7,0],[7,7]],[[7,7],[7,8]]],[[[7,7],[8,8]],[[7,7],[8,7]]]]

  [[[[7,0],[7,7]],[[7,7],[7,8]]],[[[7,7],[8,8]],[[7,7],[8,7]]]]
+ [7,[5,[[3,8],[1,4]]]]
= [[[[7,7],[7,8]],[[9,5],[8,7]]],[[[6,8],[0,8]],[[9,9],[9,0]]]]

  [[[[7,7],[7,8]],[[9,5],[8,7]]],[[[6,8],[0,8]],[[9,9],[9,0]]]]
+ [[2,[2,2]],[8,[8,1]]]
= [[[[6,6],[6,6]],[[6,0],[6,7]]],[[[7,7],[8,9]],[8,[8,1]]]]

  [[[[6,6],[6,6]],[[6,0],[6,7]]],[[[7,7],[8,9]],[8,[8,1]]]]
+ [2,9]
= [[[[6,6],[7,7]],[[0,7],[7,7]]],[[[5,5],[5,6]],9]]

  [[[[6,6],[7,7]],[[0,7],[7,7]]],[[[5,5],[5,6]],9]]
+ [1,[[[9,3],9],[[9,0],[0,7]]]]
= [[[[7,8],[6,7]],[[6,8],[0,8]]],[[[7,7],[5,0]],[[5,5],[5,6]]]]

  [[[[7,8],[6,7]],[[6,8],[0,8]]],[[[7,7],[5,0]],[[5,5],[5,6]]]]
+ [[[5,[7,4]],7],1]
= [[[[7,7],[7,7]],[[8,7],[8,7]]],[[[7,0],[7,7]],9]]

  [[[[7,7],[7,7]],[[8,7],[8,7]]],[[[7,0],[7,7]],9]]
+ [[[[4,2],2],6],[8,7]]
= [[[[8,7],[7,7]],[[8,6],[7,7]]],[[[0,7],[6,6]],[8,7]]]
To check whether it's the right answer, the snailfish teacher only checks the magnitude of the final sum. The magnitude of a pair is 3 times the magnitude of its left element plus 2 times the magnitude of its right element. The magnitude of a regular number is just that number.

For example, the magnitude of [9,1] is 3*9 + 2*1 = 29; the magnitude of [1,9] is 3*1 + 2*9 = 21. Magnitude calculations are recursive: the magnitude of [[9,1],[1,9]] is 3*29 + 2*21 = 129.

Here are a few more magnitude examples:

[[1,2],[[3,4],5]] becomes 143.
[[[[0,7],4],[[7,8],[6,0]]],[8,1]] becomes 1384.
[[[[1,1],[2,2]],[3,3]],[4,4]] becomes 445.
[[[[3,0],[5,3]],[4,4]],[5,5]] becomes 791.
[[[[5,0],[7,4]],[5,5]],[6,6]] becomes 1137.
[[[[8,7],[7,7]],[[8,6],[7,7]]],[[[0,7],[6,6]],[8,7]]] becomes 3488.
So, given this example homework assignment:

[[[0,[5,8]],[[1,7],[9,6]]],[[4,[1,2]],[[1,4],2]]]
[[[5,[2,8]],4],[5,[[9,9],0]]]
[6,[[[6,2],[5,6]],[[7,6],[4,7]]]]
[[[6,[0,7]],[0,9]],[4,[9,[9,0]]]]
[[[7,[6,4]],[3,[1,3]]],[[[5,5],1],9]]
[[6,[[7,3],[3,2]]],[[[3,8],[5,7]],4]]
[[[[5,4],[7,7]],8],[[8,3],8]]
[[9,3],[[9,9],[6,[4,9]]]]
[[2,[[7,7],7]],[[5,8],[[9,3],[0,2]]]]
[[[[5,2],5],[8,[3,7]]],[[5,[7,5]],[4,4]]]
The final sum is:

[[[[6,6],[7,6]],[[7,7],[7,0]]],[[[7,7],[7,7]],[[7,8],[9,9]]]]
The magnitude of this final sum is 4140.

Add up all of the snailfish numbers from the homework assignment in the order they appear. What is the magnitude of the final sum?

Your puzzle answer was ____.

--- Part Two ---
You notice a second question on the back of the homework assignment:

What is the largest magnitude you can get from adding only two of the snailfish numbers?

Note that snailfish addition is not commutative - that is, x + y and y + x can produce different results.

Again considering the last example homework assignment above:

[[[0,[5,8]],[[1,7],[9,6]]],[[4,[1,2]],[[1,4],2]]]
[[[5,[2,8]],4],[5,[[9,9],0]]]
[6,[[[6,2],[5,6]],[[7,6],[4,7]]]]
[[[6,[0,7]],[0,9]],[4,[9,[9,0]]]]
[[[7,[6,4]],[3,[1,3]]],[[[5,5],1],9]]
[[6,[[7,3],[3,2]]],[[[3,8],[5,7]],4]]
[[[[5,4],[7,7]],8],[[8,3],8]]
[[9,3],[[9,9],[6,[4,9]]]]
[[2,[[7,7],7]],[[5,8],[[9,3],[0,2]]]]
[[[[5,2],5],[8,[3,7]]],[[5,[7,5]],[4,4]]]
The largest magnitude of the sum of any two snailfish numbers in this list is 3993. This is the magnitude of [[2,[[7,7],7]],[[5,8],[[9,3],[0,2]]]] + [[[0,[5,8]],[[1,7],[9,6]]],[[4,[1,2]],[[1,4],2]]], which reduces to [[[[7,8],[6,6]],[[6,0],[7,7]]],[[[7,8],[8,8]],[[7,9],[0,6]]]].

What is the largest magnitude of any sum of two different snailfish numbers from the homework assignment?

Your puzzle answer was ____.
*/

#include <iostream>
#include <cstdio>
#include <stdio.h>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <set>
#include <regex>
#include <stack>
#include <queue>

using namespace std;
void print_title() {
    string stuff(25, '-');
    cout << "\033[1;33m";
    cout << stuff <<"Advent of Code - Day 18"  << stuff  << endl;
    cout << "\033[0m";
    cout << string(40, ' ') << endl;
    // run terminal command in c++
    string cmd = "figlet Snailfish -c -f small";
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
int isThereAPairNestedInside4Pairs(string s, pair<int, int>& p)
{
  int noOfOpenings = 0;
  char lastCh = -1;
  char beforelastCh = -1;
  int indexLastOpenBracket = -1;
  for (int i = 0; i != s.size(); i++)
  {
    if (noOfOpenings > 4 && beforelastCh == '[' && lastCh == ',' && s[i] == ']')
    {
      p = { indexLastOpenBracket, i };
      return true;
    }

    if (s[i] == '[')
    {
      noOfOpenings++;
      beforelastCh = lastCh;
      lastCh = s[i];
      indexLastOpenBracket = i;
    }
    else if (s[i] == ']')
    {
      noOfOpenings--;
      beforelastCh = lastCh;
      lastCh = s[i];
    }
    else if (s[i] == ',')
    {
      beforelastCh = lastCh;
      lastCh = s[i];
    }
  }

  return false;
}

pair <int, int> getIndexRightRegularNumber(string s, int i)
{
  int j = 0;
  while (i < s.size())
  {
    if (isdigit(s[i]))
    {
      j = i;
      while (i < s.size() && isdigit(s[i]))
      {
        i++;
      }
      return { j, i - 1 };
    }
    i++;
  }
  return { -1,-1 };
}

pair <int, int> getIndexLeftRegularNumber(string s, int i)
{
  int j = 0;
  while (i >= 0)
  {
    if (isdigit(s[i]))
    {
      j = i;
      while (i >= 0 && isdigit(s[i]))
      {
        i--;
      }
      return { i + 1,j };
    }
    i--;
  }
  return { -1,-1 };
}

pair<int, int> parseStringToInt(string s, pair<int, int> i)
{
  string s2 = s.substr(i.first + 1, i.second - i.first - 1);
  int index = s2.find_first_of(",");
  int value = stoi(s2.substr(0, index));
  return { value,stoi(s2.substr(index + 1, s2.size() - index - 1)) };
}
string explode(string s, pair<int, int> i)
{

  bool isCurrentRegular = 0;
  int isNextRegular = 0;
  int endOfPair = 0;
  auto value = parseStringToInt(s, i);
  pair<int, int> left = getIndexLeftRegularNumber(s, i.first);

  bool replacedWith0 = false;
  pair<int, int> right = getIndexRightRegularNumber(s, i.second);
  if (right != make_pair(-1, -1))
  {
    int rightValue = stoi(s.substr(right.first, right.second - right.first + 1));
    rightValue += value.second;

    s.replace(right.first, right.second - right.first + 1, to_string(rightValue));
    s.replace(i.first, i.second - i.first + 1, "0");
    replacedWith0 = true;
  }

  if (left != make_pair(-1, -1))
  {
    int leftValue = stoi(s.substr(left.first, left.second - left.first + 1));
    leftValue += value.first;
    int i2 = i.first;
    while (s[i2] != ',')
    {
      i2++;
    }
    i2--;
    if (!replacedWith0)
    {
      s.replace(i.first, i.second - i.first + 1, "0");
    }
    s.replace(left.first, left.second - left.first + 1, to_string(leftValue));
  }
  return s;
}

bool canSplit(string s, pair<int, int>& p)
{
  int j = 0;
  for (int i = 0; i < s.size(); i++)
  {
    if (isdigit(s[i]))
    {
      j = i;
      while (isdigit(s[j]))
      {
        j++;
      }
      if (j != i + 1)
      {
        p = { i, j - 1 };
        return true;
      }
    }
  }
  return false;
}


string splitSnailfish(string s, pair<int, int> i)
{
  auto value = stoi(s.substr(i.first, i.second - i.first + 1));
  string newPair = "[" + to_string(value / 2) + "," + to_string(value / 2 + value % 2) + "]";
  s.replace(i.first, i.second - i.first + 1, newPair);
  return s;
}


void addSnailfish(string& snailfish)
{
  bool stop = false;
  while (!stop)
  {
    pair<int, int> index{ 0,0 };
    stop = true;
    while (isThereAPairNestedInside4Pairs(snailfish, index))
    {
      auto newSnailfish = explode(snailfish, index);
      snailfish = newSnailfish;
      stop = false;
    }
    while (canSplit(snailfish, index))
    {
      auto newSnailfish = splitSnailfish(snailfish, index);
      snailfish = newSnailfish;
      stop = false;
      while (isThereAPairNestedInside4Pairs(snailfish, index))
      {
        auto newSnailfish = explode(snailfish, index);
        snailfish = newSnailfish;;
      }
    }
  }
}

bool is_number(const std::string& s)
{
  std::string::const_iterator it = s.begin();
  while (it != s.end() && std::isdigit(*it)) ++it;
  return !s.empty() && it == s.end();
}

int getSum(string line)
{
  int sum = 0;
  while (line.size() > 2)
  {
    char beforeLast = 0;
    char last = 0;

    int indexBeforeLast = -1;
    int indexLast = -1;

    int  right = 0;
    int  left = 0;
    for (int i = 0; i != line.size(); i++)
    {
      if (beforeLast == '[' && last == ',' && line[i] == ']')
      {
        int sum = left * 3 + right * 2;
        line.replace(indexBeforeLast, i - indexBeforeLast + 1, to_string(sum));
        if (is_number(line))
        {
          return stoi(line);
        }
        break;
      }
      if (!isdigit(line[i]))
      {
        beforeLast = last;
        last = line[i];
        indexBeforeLast = indexLast;
        indexLast = i;
      }
      if (isdigit(line[i]))
      {
        left = right;
        right = 0;
        while (isdigit(line[i]))
        {
          right = right * 10 + (line[i] - '0');
          i++;
        }
        i--;
      }
    }
  }
  return sum;
}

vector<int> split2(string line, string delimiters = ",./;")
{
  vector<int> words;

  int index = line.find_first_of(delimiters);
  if (!line.substr(0, index).empty())
  {
    words.push_back(stoi(line.substr(0, index)));
  }

  while (index != -1) {
    index++;
    line = line.substr(index, line.length() - index);
    index = line.find_first_of(delimiters);
    auto newWord = line.substr(0, index);
    if (!newWord.empty())
    {
      words.push_back(stoi(newWord));
    }
  }
  return words;
}

int main()
{
  print_title();
  freopen("../Input/day18.txt", "r", stdin);

  string line;
  string result = "";

  vector<string> input;
  while (getline(cin, line))
  {
    input.push_back(line);
    if (result == "")
    {
      result = line;
      continue;
    }
    line = "[" + result + "," + line + "]";
    addSnailfish(line);
    result = line;

  }
  cout << "Puzzle 1: " << getSum(line) << endl;

  int Max = 0;
  for (auto i : input)
  {
    for (auto j : input)
    {
      if (i != j)
      {
        string line = "[" + i + "," + j + "]";
        addSnailfish(line);
        int x = getSum(line);
        Max = max(x, Max);
      }
    }
  }
  cout << "Puzzle 2: " << Max << endl;
  string stuff_final(72, '=');
    cout << endl;
    cout << stuff_final << endl;
}