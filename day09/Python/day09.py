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