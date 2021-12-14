from termcolor import colored
from pyfiglet import *
print(colored("Advent of Code - Day 14", "yellow").center(80, "-"))
print(colored(figlet_format("Extended Polymerization",font="small",justify="center"), 'green'))
print(colored("Output","yellow").center(80, "-"))

def ingestFile():
    f = open("../Input/day14.txt","r")
    lines = f.readlines()

    resultList = [x.strip() for x in lines]
    
    # Get the bingo number call list
    template = resultList[0].strip()

    cipher = {}

    for x in resultList[2:]:
        tmp = x.split(' -> ')
        cipher[tmp[0]] = tmp[0][0] + tmp[1] + tmp[0][1]

    return template, cipher

def genStringPairList(inString):
    tmpString = []
    for i in range(len(inString)):
        if i == (len(inString) - 2):
            tmpString.append(inString[i] + inString[i+1])
            break
        else:
            tmpString.append(inString[i] + inString[i+1])

    return tmpString


def part_1(template, cipher, steps):
    curString = template[:]

    for i in range(steps):
        newStringList = genStringPairList(curString)
        curString = ''
        for key, pair in enumerate(newStringList):
            newStringList[key] = cipher[pair]

        for key, value in enumerate(newStringList):
            if key == (len(newStringList) - 1):
                curString += value
            else:
                curString += value[:2]

    letterCount = dict()
    for i in curString:
        letterCount[i] = letterCount.get(i, 0) + 1


    maxElementCount = max(letterCount.values())
    minElementCount = min(letterCount.values())

    print(f'\nPuzzle 1: {maxElementCount - minElementCount}')

def part_2(template, cipher, steps):
    tmpList = genStringPairList(template)
    dPairs = {}

    result = {}
    for l in template:
        result[l] = result.get(l, 0) + 1

    for i in tmpList:
        dPairs[i] = dPairs.get(i,0) + 1

    for x in range(steps):
        tmpDict = {}
        for key, value in dPairs.items():
            tmpDict[cipher[key][:2]] = tmpDict.get(cipher[key][:2], 0) + value
            tmpDict[cipher[key][1:3]] = tmpDict.get(cipher[key][1:3], 0) + value
            result[cipher[key][1]] = result.get(cipher[key][1], 0) + value

        dPairs = tmpDict

    maxElementCount = max(result.values())
    minElementCount = min(result.values())

    print(f'Puzzle 2: {maxElementCount - minElementCount}')


template, cipher = ingestFile()

part_1(template, cipher, 10)

part_2(template, cipher, 40)
print()
print(colored("=".center(71, "="), "yellow"))