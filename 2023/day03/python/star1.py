import sys


def is_part(num, row, col, schematic):
    str_num = str(num)
    row_start = max(row - 1, 0)
    col_start = max(col - len(str_num) - 1, 0)
    row_end = min(row + 2, len(schematic))
    col_end = min(col + 1, len(schematic[0]))
    res = False

    for i in range(row_start, row_end):
        for j in range(col_start, col_end):
            c = schematic[i][j]
            if c not in ".0123456789":
                res = True

    return res

def solution(input_file):

    part_numbers_sum = 0
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
                if is_part(num, row, col, schematic):
                    part_numbers_sum += num
                num = 0
            col += 1
        row += 1
            
    return part_numbers_sum


if __name__ == "__main__":
    print(f"The sum of all the part numbers in the engine schematic is {solution(sys.argv[1])}.")
