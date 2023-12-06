import math
import sys


def solution(input_file):

    nbr_record_ways = []

    with open(input_file, 'r') as f:
        times = [int(n) for n in f.readline().strip().split()[1:]]
        distances = [int(n) for n in f.readline().strip().split()[1:]]

        for i, time in enumerate(times):
            nbr_record_ways.append(0)
            for t in range(1, time):
                d = (time - t) * t # distance = time * velocity
                if d > distances[i]:
                    nbr_record_ways[-1] += 1

    return math.prod(nbr_record_ways)


if __name__ == "__main__":
    print(f"The result when multiplying the number of ways to beat the record for each race is {solution(sys.argv[1])}.")
