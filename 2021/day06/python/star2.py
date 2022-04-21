import sys


def solution(input_file):

    counts = [0 for i in range(9)]

    with open(input_file, 'r') as f:
        fishies = [int(fish) for fish in f.readline().split(",")]

        for fish in fishies:
            counts[fish] += 1

        for i in range(256):
            new_fishies = counts[0]
            for j in range(1, 9):
                counts[j-1] = counts[j]
                counts[j] = 0
            counts[6] += new_fishies
            counts[8] = new_fishies

    return sum(counts)


if __name__ == "__main__":
    print(solution(sys.argv[1]))
