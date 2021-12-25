from termcolor import colored
from pyfiglet import *
print(colored("Advent of Code - Day 24", "yellow").center(80, "-"))
print(colored(figlet_format("Arithmetic Logic Unit",font="small",justify="center"), 'green'))
print(colored("Output","yellow").center(80, "-"))

puzzle_input = open("../Input/day24.txt").read().split("\n")
sections = [puzzle_input[i:i+18] for i in range(0, len(puzzle_input), 18)]  # input comprises 14 sections of 18 lines

pairs = list()
stack = list()

for i in range(len(sections)):
    section = sections[i]
    if section[4] == "div z 1":
        stack.append((i, int(section[15].split(" ")[-1])))
    else:
        left, a = stack.pop()
        right = i
        b = int(section[5].split(" ")[-1])
        pairs.append((left, right, a + b)) 


min_model_number = [0] * 14
max_model_number = [0] * 14

for left, right, difference in pairs:
    if difference > 0:
        max_model_number[right] = 9
        max_model_number[left] = 9 - difference
        min_model_number[left] = 1
        min_model_number[right] = 1 + difference
    else: 
        max_model_number[left] = 9
        max_model_number[right] = 9 + difference
        min_model_number[right] = 1
        min_model_number[left] = 1 - difference

print("\nPuzzle 1: ", "".join(map(str, max_model_number)))
print("Puzzle 2: ", "".join(map(str, min_model_number)),end = "\n\n")
print(colored("=".center(71, "="), "yellow"))