from termcolor import colored
from pyfiglet import *
print(colored("Advent of Code - Day 11", "yellow").center(80, "-"))
print(colored(figlet_format("Dumbo Octopus",font="small",justify="center"), 'green'))
print(colored("Output","yellow").center(80, "-"))

f = open("../Input/day11.txt","r")
list_1 = []
for line in f:
    list_1.append([int(x) for x in line.strip()])


R = len(list_1)
C = len(list_1[0])

ans = 0
def flash(r,c):
    global ans
    ans += 1
    list_1[r][c] = -1
    for dr in [-1,0,1]:
        for dc in [-1,0,1]:
            rr = r+dr
            cc = c+dc
            if 0<=rr<R and 0<=cc<C and list_1[rr][cc]!=-1:
                list_1[rr][cc] += 1
                if list_1[rr][cc] >= 10:
                    flash(rr,cc)

t = 0
while True:
    t += 1
    for r in range(R):
        for c in range(C):
            list_1[r][c] += 1
    for r in range(R):
        for c in range(C):
            if list_1[r][c] == 10:
                flash(r,c)
    done = True
    for r in range(R):
        for c in range(C):
            if list_1[r][c] == -1:
                list_1[r][c] = 0
            else:
                done = False
    if t == 100:
        print("\nPuzzle 1: ",ans)
    if done:
        print("Puzzle 2: ",t,"\n")
        break
print(colored("=".center(71, "="), "yellow"))