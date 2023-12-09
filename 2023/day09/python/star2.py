import sys


def extrapolate_previous(history):
    if all(v == 0 for v in history):
        return 0
    diff = [history[i] - history[i-1] for i in range(1,len(history))]
    return history[0] - extrapolate_previous(diff)


def solution(input_file):

    extrapolated = []

    with open(input_file, 'r') as f:
        for line in f:
            history = [int(e) for e in line.strip().split()]
            extrapolated.append(extrapolate_previous(history))

    return sum(extrapolated)


if __name__ == "__main__":
    print(f"The sum of the extrapolated values is {solution(sys.argv[1])}.")
