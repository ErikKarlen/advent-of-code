import sys

from statistics import median


def solution(input_file):

    moves = []

    with open(input_file, 'r') as f:
        positions = [int(pos) for pos in f.readline().split(",")]
        opti_pos = int(sum(positions) / len(positions) )
        print(opti_pos)
        diffs = [abs(pos - opti_pos) for pos in positions]
        moves = [diff * (diff + 1) / 2 for diff in diffs]
        #print(moves)


    return sum(moves)


if __name__ == "__main__":
    print(solution(sys.argv[1]))
