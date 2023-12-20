import sys

from collections import defaultdict


def solution(input_file):

    tile_to_dir = {
        "|": ((-1, 0), (1, 0)),
        "-": ((0, -1), (0, 1)),
        "L": ((-1, 0), (0, 1)),
        "J": ((-1, 0), (0, -1)),
        "7": ((1, 0), (0, -1)),
        "F": ((1, 0), (0, 1)),
    }
    dir_to_tile = dict(zip(tile_to_dir.values(), tile_to_dir.keys()))
    tiles = defaultdict(list)
    start = None
    pos = start
    loop = set()
    enclosed = set()

    with open(input_file, 'r') as f:
        for row, line in enumerate(f):
            for col, c in enumerate(line):
                if c in tile_to_dir:
                    tiles[(row, col)] = [(row + d[0], col + d[1]) for d in tile_to_dir[c]]
                elif c == "S":
                    start = (row, col)
                    loop.add(start)
    
    start_dirs = []

    # Find start's neighbours
    for r in range(-1, 2):
        for c in range(-1, 2):
            t = (start[0] + r, start[1] + c)
            if t in tiles and start in tiles[t]:
                pos = t
                loop.add(t)
                start_dirs.append((t[0] - start[0], t[1] - start[1]))
    
    start_dirs = tuple(start_dirs)
    if start_dirs in dir_to_tile:
        start_tile = dir_to_tile[start_dirs]
    else:
        start_tile = dir_to_tile[(start_dirs[1], start_dirs[0])]

    # Find loop
    while True:
        for n in tiles[pos]:
            if n not in loop:
                pos = n
                loop.add(pos)
                break
        else:
            break

    # Loop over all tiles and toggle inside or outside by checking for |, FJ or L7
    with open(input_file, 'r') as f:
        for row, line in enumerate(f):
            is_inside = False
            prev_corner = None
            for col, c in enumerate(line):
                tile = (row, col)
                if tile in loop:
                    if c == "S":
                        c = start_tile
                    if c == "|" or (c == "J" and prev_corner == "F") or (c == "7" and prev_corner == "L"):
                        is_inside = not is_inside
                    if c in "FJL7":
                        prev_corner = c
                elif is_inside:
                    enclosed.add(tile)

    return len(enclosed)


if __name__ == "__main__":
    print(f"The number of tiles enclosed by the loop is {solution(sys.argv[1])}.")
