import sys


def solution(input_file):

    nbr_record_ways = 0

    with open(input_file, 'r') as f:
        time = int(f.readline().strip().split(":")[1].replace(" ", ""))
        distance = int(f.readline().strip().split(":")[1].replace(" ", ""))

        for t in range(1, time):
            d = (time - t) * t # distance = time * velocity
            if d > distance:
                nbr_record_ways += 1

    return nbr_record_ways


if __name__ == "__main__":
    print(f"The number of ways you can beat the record in the longer race is {solution(sys.argv[1])}.")
