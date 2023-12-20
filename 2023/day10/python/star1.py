import sys

from collections import defaultdict

def solution(input_file):

    pipe_map = {
        "|": ((-1, 0), (1, 0)),
        "-": ((0, -1), (0, 1)),
        "L": ((-1, 0), (0, 1)),
        "J": ((-1, 0), (0, -1)),
        "7": ((1, 0), (0, -1)),
        "F": ((1, 0), (0, 1)),
    }
    tiles = defaultdict(list)
    start = None
    pos = start
    visited = set()

    with open(input_file, 'r') as f:
        for row, line in enumerate(f):
            for col, c in enumerate(line):
                if c in pipe_map:
                    tiles[(row, col)] = [(row + d[0], col + d[1]) for d in pipe_map[c]]
                elif c == "S":
                    start = (row, col)
                    visited.add(start)

    # Find one of start's neighbours
    for r in range(-1, 2):
        for c in range(-1, 2):
            t = (start[0] + r, start[1] + c)
            if t not in tiles:
                continue
            if start in tiles[t]:
                pos = t
                visited.add(t)
                break
        if len(visited) == 2:
            break

    # Go through loop
    while True:
        for n in tiles[pos]:
            if n not in visited:
                pos = n
                visited.add(pos)
                break
        else:
            break

    return len(visited) // 2


if __name__ == "__main__":
    print(f"The number of steps to reach the farthest position from the starting point is {solution(sys.argv[1])}.")
