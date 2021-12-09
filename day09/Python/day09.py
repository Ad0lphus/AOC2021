'''
--- Day 9: Smoke Basin ---
These caves seem to be lava tubes. Parts are even still volcanically active; small hydrothermal vents release smoke into the caves that slowly settles like rain.

If you can model how the smoke flows through the caves, you might be able to avoid it and be that much safer. The submarine generates a heightmap of the floor of the nearby caves for you (your puzzle input).

Smoke flows to the lowest point of the area it's in. For example, consider the following heightmap:

2199943210
3987894921
9856789892
8767896789
9899965678
Each number corresponds to the height of a particular location, where 9 is the highest and 0 is the lowest a location can be.

Your first goal is to find the low points - the locations that are lower than any of its adjacent locations. Most locations have four adjacent locations (up, down, left, and right); locations on the edge or corner of the map have three or two adjacent locations, respectively. (Diagonal locations do not count as adjacent.)

In the above example, there are four low points, all highlighted: two are in the first row (a 1 and a 0), one is in the third row (a 5), and one is in the bottom row (also a 5). All other locations on the heightmap have some lower adjacent location, and so are not low points.

The risk level of a low point is 1 plus its height. In the above example, the risk levels of the low points are 2, 1, 6, and 6. The sum of the risk levels of all low points in the heightmap is therefore 15.

Find all of the low points on your heightmap. What is the sum of the risk levels of all low points on your heightmap?

Your puzzle answer was 532.

--- Part Two ---
Next, you need to find the largest basins so you know what areas are most important to avoid.

A basin is all locations that eventually flow downward to a single low point. Therefore, every low point has a basin, although some basins are very small. Locations of height 9 do not count as being in any basin, and all other locations will always be part of exactly one basin.

The size of a basin is the number of locations within the basin, including the low point. The example above has four basins.

The top-left basin, size 3:

2199943210
3987894921
9856789892
8767896789
9899965678
The top-right basin, size 9:

2199943210
3987894921
9856789892
8767896789
9899965678
The middle basin, size 14:

2199943210
3987894921
9856789892
8767896789
9899965678
The bottom-right basin, size 9:

2199943210
3987894921
9856789892
8767896789
9899965678
Find the three largest basins and multiply their sizes together. In the above example, this is 9 * 14 * 9 = 1134.

What do you get if you multiply together the sizes of the three largest basins?

Your puzzle answer was 1110780.
'''
import math
from termcolor import colored
from pyfiglet import *
print(colored("Advent of Code - Day 9", "yellow").center(80, "-"))
print(colored(figlet_format("Smoke Basin",font="small",justify="center"), 'green'))
print(colored("Output","yellow").center(80, "-"))

f = open("../Input/day9.txt","r")
data = [[int(m) for m in x] for x in f.read().split("\n")][:~0]
def find_neighbors(line,chr):
    neighbors = []
    if chr != 0:
        neighbors.append([data[line][chr-1],(line,chr-1)])
    if chr != len(data[line])-1:
        neighbors.append([data[line][chr+1],(line,chr+1)])
    if line != 0:
        neighbors.append([data[line-1][chr],(line-1,chr)])
    if line != len(data)-1:
        neighbors.append([data[line+1][chr],(line+1,chr)])
    return neighbors


basin_lens = []
def basin():
    num = 0
    for line in range(len(data)):
        for chr in range(len(data[line])):
            neighbors = find_neighbors(line,chr)
            if data[line][chr] < min([x[0] for x in neighbors]):
                    num += data[line][chr] + 1
                    basin_lens.append(len(flood(line,chr)))
    return num

def flood(line,chr):
    final = {(line,chr)}
    for i in [m[1] for m in find_neighbors(line,chr)]:
        if data[i[0]][i[1]] != 9 and data[i[0]][i[1]] > data[line][chr]:
            final.update(flood(i[0],i[1]))
    return final

print("\nPuzzle 1:",basin())
print("Puzzle 2:",math.prod(sorted(basin_lens)[~2:]),"\n")
print(colored("=".center(71, "="), "yellow"))