with open('../Input/day3.txt','r') as f:
    binaryNumbers = [line.strip() for line in f.readlines()]

length_of_bits = len(binaryNumbers[0])
gammaRate = []
epsilonRate = []

for i in range(0,length_of_bits):
    counterOne, counterZero = (0,0)
    currentPosBits = [n[i] for n in binaryNumbers]
    counterOne = currentPosBits.count('1')
    counterZero = currentPosBits.count('0')

    if counterOne > counterZero:
        gammaRate.append('1')
        epsilonRate.append('0')
    else:
        gammaRate.append('0')
        epsilonRate.append('1')
    
gammaRate = ''.join(gammaRate)
epsilonRate = ''.join(epsilonRate)

print("puzzle 1: ",int(gammaRate,2)*int(epsilonRate,2))

def get_num(binaryNumbers,gas):
    numbers = binaryNumbers.copy()
    length_of_bits = len(binaryNumbers[0])
    for i in range(0,length_of_bits):
        counterOne, counterZero = (0,0)
        currentPosBits = [n[i] for n in numbers]
        counterOne = currentPosBits.count('1')
        counterZero = currentPosBits.count('0')

        if gas == 'o2':
            if counterOne >= counterZero:
                required_bit = '1'
            else:
                required_bit = '0'
        else:
            if counterOne >= counterZero:
                required_bit = '0'
            else:
                required_bit = '1'
        
        requiredNumbers = [n for n in numbers if n[i] == required_bit]
        if len(requiredNumbers) == 1:
            return int(''.join(requiredNumbers[0]),2)
        else:
            numbers = requiredNumbers
        
o2_num = get_num(binaryNumbers,'o2')
co2_num = get_num(binaryNumbers,'co2')

print("puzzle 2: ",o2_num * co2_num)    
