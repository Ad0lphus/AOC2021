
'''
--- Day 4: Giant Squid ---
You're already almost 1.5km (almost a mile) below the surface of the ocean, already so deep that you can't see any sunlight. What you can see, however, is a giant squid that has attached itself to the outside of your submarine.

Maybe it wants to play bingo?

Bingo is played on a set of boards each consisting of a 5x5 grid of numbers. Numbers are chosen at random, and the chosen number is marked on all boards on which it appears. (Numbers may not appear on all boards.) If all numbers in any row or any column of a board are marked, that board wins. (Diagonals don't count.)

The submarine has a bingo subsystem to help passengers (currently, you and the giant squid) pass the time. It automatically generates a random order in which to draw numbers and a random set of boards (your puzzle input). For example:

7,4,9,5,11,17,23,2,0,14,21,24,10,16,13,6,15,25,12,22,18,20,8,19,3,26,1

22 13 17 11  0
 8  2 23  4 24
21  9 14 16  7
 6 10  3 18  5
 1 12 20 15 19

 3 15  0  2 22
 9 18 13 17  5
19  8  7 25 23
20 11 10 24  4
14 21 16 12  6

14 21 17 24  4
10 16 15  9 19
18  8 23 26 20
22 11 13  6  5
 2  0 12  3  7
After the first five numbers are drawn (7, 4, 9, 5, and 11), there are no winners, but the boards are marked as follows (shown here adjacent to each other to save space):

22 13 17 11  0         3 15  0  2 22        14 21 17 24  4
 8  2 23  4 24         9 18 13 17  5        10 16 15  9 19
21  9 14 16  7        19  8  7 25 23        18  8 23 26 20
 6 10  3 18  5        20 11 10 24  4        22 11 13  6  5
 1 12 20 15 19        14 21 16 12  6         2  0 12  3  7
After the next six numbers are drawn (17, 23, 2, 0, 14, and 21), there are still no winners:

22 13 17 11  0         3 15  0  2 22        14 21 17 24  4
 8  2 23  4 24         9 18 13 17  5        10 16 15  9 19
21  9 14 16  7        19  8  7 25 23        18  8 23 26 20
 6 10  3 18  5        20 11 10 24  4        22 11 13  6  5
 1 12 20 15 19        14 21 16 12  6         2  0 12  3  7
Finally, 24 is drawn:

22 13 17 11  0         3 15  0  2 22        14 21 17 24  4
 8  2 23  4 24         9 18 13 17  5        10 16 15  9 19
21  9 14 16  7        19  8  7 25 23        18  8 23 26 20
 6 10  3 18  5        20 11 10 24  4        22 11 13  6  5
 1 12 20 15 19        14 21 16 12  6         2  0 12  3  7
At this point, the third board wins because it has at least one complete row or column of marked numbers (in this case, the entire top row is marked: 14 21 17 24 4).

The score of the winning board can now be calculated. Start by finding the sum of all unmarked numbers on that board; in this case, the sum is 188. Then, multiply that sum by the number that was just called when the board won, 24, to get the final score, 188 * 24 = 4512.

To guarantee victory against the giant squid, figure out which board will win first. What will your final score be if you choose that board?

Your puzzle answer was ______.

--- Part Two ---
On the other hand, it might be wise to try a different strategy: let the giant squid win.

You aren't sure how many bingo boards a giant squid could play at once, so rather than waste time counting its arms, the safe thing to do is to figure out which board will win last and choose that one. That way, no matter which boards it picks, it will win for sure.

In the above example, the second board is the last to win, which happens after 13 is eventually called and its middle column is completely marked. If you were to keep playing until this point, the second board would have a sum of unmarked numbers equal to 148 for a final score of 148 * 13 = 1924.

Figure out which board will win last. Once it wins, what would its final score be?

Your puzzle answer was ______.


'''
from termcolor import colored
from pyfiglet import *
print(colored("Advent of Code - Day 4", "yellow").center(80, "-"))
print(colored(figlet_format("Giant Squid",font="small",justify="center"), 'green'))
print(colored("Output","yellow").center(80, "-"))
f = open("../Input/day4.txt",'r')
print()
numbers = None
list1 = []
list2 = []
board_list = []
for line in f:
    line = line.strip()
    if numbers is None:
        numbers = [int(x) for x in line.split(',')]
    else:
        if line:
            board_list.append([int(x) for x in line.split()])
        else:
            if board_list:
                list1.append(board_list)
            board_list = []
list1.append(board_list)

for element in list1:
    assert len(element)==5 and len(element[0])==5
    list2.append([[False for i in range(5)] for i in range(5)])
puzzle = 0
won_check = [False for i in range(len(list1))]
for num in numbers:
    for i in range(len(list1)):
        for j in range(5):
            for k in range(5):
                if list1[i][j][k] == num:
                    list2[i][j][k] = True

        won = False
        for j in range(5):
            ok = True
            for k in range(5):
                if not list2[i][j][k]:
                    ok = False
            if ok:
                won = True
        for k in range(5):
            ok = True
            for j in range(5):
                if not list2[i][j][k]:
                    ok = False
            if ok:
                won = True
        if won and not won_check[i]:
            won_check[i] = True
            nwin = len([j for j in range(len(list1)) if won_check[j]])
            if nwin == 1 or nwin == len(list1):
                puzzle+=1
                unmarked = 0
                for j in range(5):
                    for k in range(5):
                        if not list2[i][j][k]:
                            unmarked += list1[i][j][k]
                print("puzzle {}: ".format(puzzle),unmarked * num)

print("\n",colored("=".center(71, "="), "yellow"))