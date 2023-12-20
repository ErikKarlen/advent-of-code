import sys

from collections import defaultdict


def solution(input_file):

    input_galaxy_rows = set()
    input_galaxy_cols = set()
    input_galaxies = set()
    galaxies = set()

    with open(input_file, 'r') as f:
        for input_row, line in enumerate(f):
            for input_col, c in enumerate(line):
                if c == "#":
                    input_galaxy_rows.add(input_row)
                    input_galaxy_cols.add(input_col)
                    input_galaxies.add((input_row, input_col))
    
    row = 0
    for r in range(input_row + 1):
        col = 0
        if r not in input_galaxy_rows:
            row += 1
        for c in range(input_col + 1):
            if c not in input_galaxy_cols:
                col += 1
            if (r, c) in input_galaxies:
                galaxies.add((row, col))
            col += 1
        row += 1
    
    galaxy_pairs = set()
    pair_distances = {}

    for g1 in galaxies:
        for g2 in galaxies:
            if g1 == g2 or (g1, g2) in galaxy_pairs or (g2, g1) in galaxy_pairs:
                continue
            galaxy_pairs.add((g1, g2))

    for gp in galaxy_pairs:
        g1 = gp[0]
        g2 = gp[1]
        pair_distances[gp] = abs(g1[0] - g2[0]) + abs(g1[1] - g2[1])

    return sum(pair_distances.values())


if __name__ == "__main__":
    print(f"The sum of the lengths of the shortest paths between every pair of galaxy is {solution(sys.argv[1])}.")
