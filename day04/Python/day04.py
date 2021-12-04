f = open("../Input/day4.txt",'r')
numbers = None
list1 = []
list2 = []
board_list = []
for line in f:
    line = line.strip()
    if numbers is None:
        numbers = [int(x) for x in line.split(',')]
    else:
        if line:
            board_list.append([int(x) for x in line.split()])
        else:
            if board_list:
                list1.append(board_list)
            board_list = []
list1.append(board_list)

for element in list1:
    assert len(element)==5 and len(element[0])==5
    list2.append([[False for i in range(5)] for i in range(5)])
puzzle = 0
won_check = [False for i in range(len(list1))]
for num in numbers:
    for i in range(len(list1)):
        for j in range(5):
            for k in range(5):
                if list1[i][j][k] == num:
                    list2[i][j][k] = True

        won = False
        for j in range(5):
            ok = True
            for k in range(5):
                if not list2[i][j][k]:
                    ok = False
            if ok:
                won = True
        for k in range(5):
            ok = True
            for j in range(5):
                if not list2[i][j][k]:
                    ok = False
            if ok:
                won = True
        if won and not won_check[i]:
            won_check[i] = True
            nwin = len([j for j in range(len(list1)) if won_check[j]])
            if nwin == 1 or nwin == len(list1):
                puzzle+=1
                unmarked = 0
                for j in range(5):
                    for k in range(5):
                        if not list2[i][j][k]:
                            unmarked += list1[i][j][k]
                print("puzzle {}: ".format(puzzle),unmarked * num)