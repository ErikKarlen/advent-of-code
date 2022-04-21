import sys
from collections import defaultdict
from math import copysign


def solution(input_file):

    counts = defaultdict(lambda: 0)
    total_count = 0

    with open(input_file, 'r') as f:
        for line in f:
            x1, y1 = line.split()[0].split(",")
            x1, y1 = int(x1), int(y1)
            x2, y2 = line.split()[2].split(",")
            x2, y2 = int(x2), int(y2)

            if x1 == x2:
                for y in range(min(y1, y2), max(y1, y2) + 1):
                    counts[x1, y] += 1
                    total_count += 1 if counts[x1, y] == 2 else 0
            elif y1 == y2:
                for x in range(min(x1, x2), max(x1, x2) + 1):
                    counts[x, y1] += 1
                    total_count += 1 if counts[x, y1] == 2 else 0
            else:
                x_dir = copysign(1, x2 - x1)
                y_dir = copysign(1, y2 - y1)
                for i in range(abs(x2 - x1) + 1):
                    x = x1 + i * x_dir
                    y = y1 + i * y_dir
                    counts[x, y] += 1
                    total_count += 1 if counts[x, y] == 2 else 0

    return total_count


if __name__ == "__main__":
    print(solution(sys.argv[1]))
