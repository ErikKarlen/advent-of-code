import math
import sys


def solution(input_file):

    instructions = ""
    nodes = {}
    steps_list = []
    starts = set()
    ends = set()

    with open(input_file, 'r') as f:
        instructions = f.readline().strip()
        f.readline()

        for line in f:
            line = line.strip().split(" = ")
            node = line[0]
            dirs = line[1].split(", ")
            dirs[0] = dirs[0][1:]
            dirs[1] = dirs[1][:-1]
            nodes[node] = dirs
            if node[-1] == "A":
                starts.add(node)
            elif node[-1] == "Z":
                ends.add(node)

    for i, start in enumerate(starts):
        pos = start
        steps = 0
        while pos not in ends:
            d = instructions[steps % len(instructions)]
            if d == "L":
                pos = nodes[pos][0]
            elif d == "R":
                pos = nodes[pos][1]
            steps += 1
        steps_list.append(steps)

    return math.lcm(*steps_list)


if __name__ == "__main__":
    print(f"The number of steps it takes to reach only nodes that end in Z is {solution(sys.argv[1])}.")
