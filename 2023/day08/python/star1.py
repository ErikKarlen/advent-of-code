import sys


def solution(input_file):

    instructions = ""
    nodes = {}
    steps = 0
    start = "AAA"
    end = "ZZZ"
    pos = start

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
    
    while pos != end:
        d = instructions[steps % len(instructions)]
        if d == "L":
            pos = nodes[pos][0]
        elif d == "R":
            pos = nodes[pos][1]
        steps += 1

    return steps


if __name__ == "__main__":
    print(f"The number of steps required to reach ZZZ is {solution(sys.argv[1])}.")
