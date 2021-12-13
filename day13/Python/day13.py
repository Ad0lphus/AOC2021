'''
--- Day 13: Transparent Origami ---
You reach another volcanically active part of the cave. It would be nice if you could do some kind of thermal imaging so you could tell ahead of time which caves are too hot to safely enter.

Fortunately, the submarine seems to be equipped with a thermal camera! When you activate it, you are greeted with:

Congratulations on your purchase! To activate this infrared thermal imaging
camera system, please enter the code found on page 1 of the manual.
Apparently, the Elves have never used this feature. To your surprise, you manage to find the manual; as you go to open it, page 1 falls out. It's a large sheet of transparent paper! The transparent paper is marked with random dots and includes instructions on how to fold it up (your puzzle input). For example:

6,10
0,14
9,10
0,3
10,4
4,11
6,0
6,12
4,1
0,13
10,12
3,4
3,0
8,4
1,10
2,14
8,10
9,0

fold along y=7
fold along x=5
The first section is a list of dots on the transparent paper. 0,0 represents the top-left coordinate. The first value, x, increases to the right. The second value, y, increases downward. So, the coordinate 3,0 is to the right of 0,0, and the coordinate 0,7 is below 0,0. The coordinates in this example form the following pattern, where # is a dot on the paper and . is an empty, unmarked position:

...#..#..#.
....#......
...........
#..........
...#....#.#
...........
...........
...........
...........
...........
.#....#.##.
....#......
......#...#
#..........
#.#........
Then, there is a list of fold instructions. Each instruction indicates a line on the transparent paper and wants you to fold the paper up (for horizontal y=... lines) or left (for vertical x=... lines). In this example, the first fold instruction is fold along y=7, which designates the line formed by all of the positions where y is 7 (marked here with -):

...#..#..#.
....#......
...........
#..........
...#....#.#
...........
...........
-----------
...........
...........
.#....#.##.
....#......
......#...#
#..........
#.#........
Because this is a horizontal line, fold the bottom half up. Some of the dots might end up overlapping after the fold is complete, but dots will never appear exactly on a fold line. The result of doing this fold looks like this:

#.##..#..#.
#...#......
......#...#
#...#......
.#.#..#.###
...........
...........
Now, only 17 dots are visible.

Notice, for example, the two dots in the bottom left corner before the transparent paper is folded; after the fold is complete, those dots appear in the top left corner (at 0,0 and 0,1). Because the paper is transparent, the dot just below them in the result (at 0,3) remains visible, as it can be seen through the transparent paper.

Also notice that some dots can end up overlapping; in this case, the dots merge together and become a single dot.

The second fold instruction is fold along x=5, which indicates this line:

#.##.|#..#.
#...#|.....
.....|#...#
#...#|.....
.#.#.|#.###
.....|.....
.....|.....
Because this is a vertical line, fold left:

#####
#...#
#...#
#...#
#####
.....
.....
The instructions made a square!

The transparent paper is pretty big, so for now, focus on just completing the first fold. After the first fold in the example above, 17 dots are visible - dots that end up overlapping after the fold is completed count as a single dot.

How many dots are visible after completing just the first fold instruction on your transparent paper?

Your puzzle answer was ___.

--- Part Two ---
Finish folding the transparent paper according to the instructions. The manual says the code is always eight capital letters.

What code do you use to activate the infrared thermal imaging camera system?

Your puzzle answer was ________________.
'''
from termcolor import colored
from pyfiglet import *
print(colored("Advent of Code - Day 13", "yellow").center(80, "-"))
print(colored(figlet_format("Transparent Origami",font="small",justify="center"), 'green'))
print(colored("Output","yellow").center(80, "-"))

def part1(data):
    paper = draw_paper(data)
    fold_instructions = get_fold_instructions(data)
    folded_paper = get_folded_paper(paper, [fold_instructions[0]])

    total_dots = count_dots(folded_paper)
    return total_dots

def part2(data):
    paper = draw_paper(data)
    fold_instructions = get_fold_instructions(data)
    folded_paper = get_folded_paper(paper, fold_instructions)

    make_pretty_code(folded_paper)

def make_pretty_code(folded_paper):
    for row in folded_paper:
        row = ''.join(row)
        code = row.replace('.', ' ')
        print(code)


def draw_paper(data):
    instructions = data[:-13]
    instructions = [instruction.split(',') for instruction in instructions]

    x_lst = [int(instruction[0]) for instruction in instructions]
    y_lst = [int(instruction[1]) for instruction in instructions]

    paper_right_bottom = (max(x_lst), max(y_lst))

    paper = []
    for row in range(0, paper_right_bottom[1]+2):
        row = []
        for _ in range(0, paper_right_bottom[0]+1):
            row.append('.')
        paper.append(row)
    
    for instruction in instructions:
        paper[int(instruction[1])][int(instruction[0])] = '#'

    return paper

def get_fold_instructions(data):
    folds = data[-12:]
    items = [item.split()[2].split('=') for item in folds]

    return items
    
def get_folded_paper(folded_paper, fold_instructions):

    if fold_instructions:
        if fold_instructions[0][0] == 'x':
            folded_paper = fold_left_right(folded_paper, fold_instructions[0][1])

        if fold_instructions[0][0] == 'y':
            folded_paper = fold_bottom_up(folded_paper, fold_instructions[0][1])

        fold_instructions = fold_instructions[1:]
        return get_folded_paper(folded_paper, fold_instructions)
    else:
        return folded_paper

def fold_left_right(paper, on_position):

    on_position = int(on_position)

    folded_paper = []
    for row in paper:
        first_half = row[:on_position]
        second_half = row[on_position+1:]
        second_half = second_half[::-1]

        folded_row = first_half
        for pos, i in enumerate(second_half):
            if i == '#':
                folded_row[pos] = i
        folded_paper.append(folded_row)
    
    return folded_paper

def fold_bottom_up(paper, on_position):

    on_position = int(on_position)
    paper_len = len(paper)

    if paper_len % 2 == 0:
        first_half = paper[:on_position]
        second_half = paper[on_position:]

    else:
        first_half = paper[:on_position]
        second_half = paper[on_position+1:]
   
    second_half = second_half[::-1]
    folded_paper = first_half

    for row_num, row in enumerate(second_half):
        for char_pos, char in enumerate(row):
            if char == '#':
                folded_paper[row_num][char_pos] = char
 
    return folded_paper

def count_dots(folded_paper):
    dots = 0
    for row in folded_paper:
        for elem in row:
            if elem == '#':
                dots += 1

    return dots


f = open(f"../Input/day13.txt", "r")
data = [line.rstrip('\n') for line in f]
solution1 = part1(data)
print(f"\nPuzzle 1: {solution1}")
print(f"Puzzle 2:")
solution2 = part2(data)
print()
print(colored("=".center(71, "="), "yellow"))