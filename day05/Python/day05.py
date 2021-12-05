'''
--- Day 5: Hydrothermal Venture ---
You come across a field of hydrothermal vents on the ocean floor! These vents constantly produce large, opaque clouds, so it would be best to avoid them if possible.

They tend to form in lines; the submarine helpfully produces a list of nearby lines of vents (your puzzle input) for you to review. For example:

0,9 -> 5,9
8,0 -> 0,8
9,4 -> 3,4
2,2 -> 2,1
7,0 -> 7,4
6,4 -> 2,0
0,9 -> 2,9
3,4 -> 1,4
0,0 -> 8,8
5,5 -> 8,2
Each line of vents is given as a line segment in the format x1,y1 -> x2,y2 where x1,y1 are the coordinates of one end the line segment and x2,y2 are the coordinates of the other end. These line segments include the points at both ends. In other words:

An entry like 1,1 -> 1,3 covers points 1,1, 1,2, and 1,3.
An entry like 9,7 -> 7,7 covers points 9,7, 8,7, and 7,7.
For now, only consider horizontal and vertical lines: lines where either x1 = x2 or y1 = y2.

So, the horizontal and vertical lines from the above list would produce the following diagram:

.......1..
..1....1..
..1....1..
.......1..
.112111211
..........
..........
..........
..........
222111....
In this diagram, the top left corner is 0,0 and the bottom right corner is 9,9. Each position is shown as the number of lines which cover that point or . if no line covers that point. The top-left pair of 1s, for example, comes from 2,2 -> 2,1; the very bottom row is formed by the overlapping lines 0,9 -> 5,9 and 0,9 -> 2,9.

To avoid the most dangerous areas, you need to determine the number of points where at least two lines overlap. In the above example, this is anywhere in the diagram with a 2 or larger - a total of 5 points.

Consider only horizontal and vertical lines. At how many points do at least two lines overlap?

Your puzzle answer was ____.

--- Part Two ---
Unfortunately, considering only horizontal and vertical lines doesn't give you the full picture; you need to also consider diagonal lines.

Because of the limits of the hydrothermal vent mapping system, the lines in your list will only ever be horizontal, vertical, or a diagonal line at exactly 45 degrees. In other words:

An entry like 1,1 -> 3,3 covers points 1,1, 2,2, and 3,3.
An entry like 9,7 -> 7,9 covers points 9,7, 8,8, and 7,9.
Considering all lines from the above example would now produce the following diagram:

1.1....11.
.111...2..
..2.1.111.
...1.2.2..
.112313211
...1.2....
..1...1...
.1.....1..
1.......1.
222111....
You still need to determine the number of points where at least two lines overlap. In the above example, this is still anywhere in the diagram with a 2 or larger - now a total of 12 points.

Consider all of the lines. At how many points do at least two lines overlap?

Your puzzle answer was _____.
'''
from termcolor import colored
from pyfiglet import *
print(colored("Advent of Code - Day 5", "yellow").center(80, "-"))
print(colored(figlet_format("Hydrothermal Venture",font="small",justify="center"), 'green'))
print(colored("Output","yellow").center(80, "-"))
f = open("../Input/day5.txt")
readed = f.readlines()
def part_1():
    Dict = {}
    crossCount = 0
    for y in range(0,1000):
        for x in range(0,1000):
            SName = str(x)+"x"+str(y)
            Dict[SName] = 0

    for read in readed:
        L1 = read.split(" -> ")[0].split(",")
        L2 = read.split(" -> ")[1].split(",")
        
        is_Level_x = 0
        is_Level_y = 0

        if int(L1[0]) == int(L2[0]):
            is_Level_x = 1
        if int(L1[1]) == int(L2[1]):
            is_Level_y = 1
        if is_Level_x == 1 or is_Level_y == 1:
            start = 0
            end = 0
            pos = 0
            if is_Level_x == 1:
                pos = 1
            if int(L1[pos])>int(L2[pos]):
                start = int(L2[pos])
                end = int(L1[pos])+1
            else:
                start = int(L1[pos])
                end = int(L2[pos])+1
            for ctr in range(start, end):
                SName = ""
                if is_Level_x == 1:
                    SName = L1[0]+"x"+str(ctr)
                else:
                    SName = str(ctr)+"x"+L1[1]
                Dict[SName] +=1

    for element in Dict:
        if Dict[element] > 1:
            crossCount+=1

    print("\npuzzle 1: ",str(crossCount))

def part_2():
    Dict = {}
    crossCount = 0
    for y in range(0,1000):
        for x in range(0,1000):
            SName = str(x)+"x"+str(y)
            Dict[SName] = 0

    for read in readed:
        L1 = read.split(" -> ")[0].split(",")
        L2 = read.split(" -> ")[1].split(",")
        
        is_Level_x = 0
        is_Level_y = 0

        if int(L1[0]) == int(L2[0]):
            is_Level_x = 1
        if int(L1[1]) == int(L2[1]):
            is_Level_y = 1
        if is_Level_x == 1 or is_Level_y == 1:
            start = 0
            end = 0
            pos = 0
            if is_Level_x == 1:
                pos = 1
            if int(L1[pos])>int(L2[pos]):
                start = int(L2[pos])
                end = int(L1[pos])+1
            else:
                start = int(L1[pos])
                end = int(L2[pos])+1
            for ctr in range(start, end):
                SName = ""
                if is_Level_x == 1:
                    SName = L1[0]+"x"+str(ctr)
                else:
                    SName = str(ctr)+"x"+L1[1]
                
                Dict[SName] +=1
        else:
            startX = int(L1[0])
            endX = int(L2[0])
            startY = int(L1[1])
            endY = int(L2[1])
            diffX = endX - startX
            diffY = endY - startY
            ranger = diffX
            if ranger < 0:
                ranger *=-1
            for diagonal in range(ranger+1):
                edX = 1
                edY = 1
                if diffX < 0:
                    edX =-1
                if diffY < 0:
                    edY =-1
                SName = str(startX + (diagonal*edX)) +"x"+ str(startY + (diagonal*edY))
                Dict[SName] +=1

    for element in Dict:
        if Dict[element] > 1:
            crossCount+=1

    print("puzzle 2: ",str(crossCount),"\n")

part_1()
part_2()
print(colored("=".center(71, "="), "yellow"))