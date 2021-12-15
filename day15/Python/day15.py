import numpy as np
from termcolor import colored
from pyfiglet import *
print(colored("Advent of Code - Day 15", "yellow").center(80, "-"))
print(colored(figlet_format("Chiton",font="small",justify="center"), 'green'))
print(colored("Output","yellow").center(80, "-"))


def create_grid_for_puzzle_2(grid: np.ndarray):
    grid_copy = grid.copy()
    for i in range(1, 5):
        to_copy = (grid_copy.copy() + 1) % 10
        to_copy[to_copy == 0] = 1
        grid_copy = to_copy
        grid = np.concatenate((grid, to_copy), axis=0)
    grid_copy = grid.copy()
    for i in range(1, 5):
        to_copy = (grid_copy.copy() + 1) % 10
        to_copy[to_copy == 0] = 1
        grid_copy = to_copy
        grid = np.concatenate((grid, to_copy), axis=1)
    return grid


def possible_moves(grid: np.ndarray, pos: tuple):
    moves = []
    if pos[0] - 1 > 0:
        moves.append((-1, 0))
    if pos[0] + 1 < len(grid):
        moves.append((1, 0))
    if pos[1] + 1 < len(grid[0]):
        moves.append((0, 1))
    if pos[1] - 1 > 0:
        moves.append((0, -1))
    return moves


def puzzle(grid: np.ndarray) -> int:
    starting_point = (0, 0)
    stack = [(starting_point, 0, starting_point)]
    covered_grid = np.zeros(grid.shape)
    i = 0
    while True:
        i += 1
        to_evaluate = stack.pop()
        moves = possible_moves(grid, to_evaluate[0])
        if moves == [(-1, 0), (0, -1)]:
            final_answer = to_evaluate[1]
            break
        for move in moves:
            if move != (-to_evaluate[2][0], -to_evaluate[2][1]):
                next_point = ((to_evaluate[0][0] + move[0], to_evaluate[0][1] + move[1]),
                              to_evaluate[1] + grid[to_evaluate[0][0] + move[0], to_evaluate[0][1] + move[1]], move)
                if covered_grid[next_point[0][0], next_point[0][1]] > next_point[1] or covered_grid[
                    next_point[0][0], next_point[0][1]] == 0:
                    stack.append(next_point)
                    covered_grid[next_point[0][0], next_point[0][1]] = next_point[1]
        stack = list(sorted(stack, key=lambda x: x[1], reverse=True))
        
    return final_answer

f = open("../Input/day15.txt", "r")
inputs = f.readlines()
grid = []
for line in inputs:
    grid.append([int(x) for x in list(line.strip())])
input_grid = grid
input_grid = np.array(input_grid)
answer1 = puzzle(input_grid)
input_grid_2 = create_grid_for_puzzle_2(input_grid)
answer2 = puzzle(input_grid_2)
print(f"\npuzzle 1: ",answer1)
print(f"puzzle 2: ",answer2,end="\n\n")
print(colored("=".center(71, "="), "yellow"))