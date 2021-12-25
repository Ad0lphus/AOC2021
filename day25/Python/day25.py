import numpy as np
from termcolor import colored
from pyfiglet import *
print(colored("Advent of Code - Day 25", "yellow").center(80, "-"))
print(colored(figlet_format("Sea Cucumber",font="small",justify="center"), 'green'))
print(colored("Output","yellow").center(80, "-"))

g = np.array([[{".": 0, ">": 2, "v": 1}[a] for a in a.strip()] for a in open("../Input/day25.txt")])

i = 0
while True:
	i += 1
	a = (g == 2) & (np.roll(g, -1, 1) == 0)
	g[a], g[np.roll(a, 1, 1)] = 0, 2
	b = (g == 1) & (np.roll(g, -1, 0) == 0)
	g[b], g[np.roll(b, 1, 0)] = 0, 1
	if not (a|b).any():
		break

print("\nPuzzle 1: ",i)
print("Puzzle 1:  Completed :))",end = "\n\n")
print(colored("=".center(71, "="), "yellow"))