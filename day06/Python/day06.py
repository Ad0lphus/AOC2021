from termcolor import colored
from pyfiglet import *
print(colored("Advent of Code - Day 6", "yellow").center(80, "-"))
print(colored(figlet_format("Lanternfish",font="small",justify="center"), 'green'))
print(colored("Output","yellow").center(80, "-"))
f= open("../Input/day6.txt","r")
fishes = [int(n) for n in f.readline().strip().split(",")]
ocean = [0] * 9

for fish in fishes:
    ocean[fish] += 1

def solver(ocean):
    temp_spawn = ocean[0]
    ocean = ocean[1:] + [0]
    ocean[6] += temp_spawn
    ocean[8] += temp_spawn
    return ocean
for i in range(80):
    ocean = solver(ocean)

print("\npuzzle 1: ",sum(ocean))
for i in range(256 - 80):
    ocean = solver(ocean)
print("puzzle 2: ",sum(ocean),"\n")
print(colored("=".center(71, "="), "yellow"))