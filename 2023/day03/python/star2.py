import sys

from collections import defaultdict


def gear_pos(num, row, col, schematic):
    str_num = str(num)
    row_start = max(row - 1, 0)
    col_start = max(col - len(str_num) - 1, 0)
    row_end = min(row + 2, len(schematic))
    col_end = min(col + 1, len(schematic[0]))
    res = ()

    for i in range(row_start, row_end):
        for j in range(col_start, col_end):
            c = schematic[i][j]
            if c == "*":
                res = (i, j)

    return res

def solution(input_file):

    gear_parts = defaultdict(list)
    gear_ratios_sum = 0
    schematic = []

    with open(input_file, 'r') as f:
        for line in f:
            schematic.append(line.strip() + ".")
        
    row = 0
    for line in schematic:
        col = 0
        num = 0
        for c in line:
            if c in "0123456789":
                num = 10 * num + int(c)
            elif num != 0:
                gp = gear_pos(num, row, col, schematic)
                if gp:
                    gear_parts[gp].append(num)
                num = 0
            col += 1
        row += 1

    for pos in gear_parts:
        if len(gear_parts[pos]) == 2:
            gear_ratios_sum += gear_parts[pos][0] * gear_parts[pos][1]

    return gear_ratios_sum


if __name__ == "__main__":
    print(f"The sum of all the part numbers in the engine schematic is {solution(sys.argv[1])}.")
