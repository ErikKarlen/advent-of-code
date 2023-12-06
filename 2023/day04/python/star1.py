import sys


def solution(input_file):

    total_points = 0

    with open(input_file, 'r') as f:
        for line in f:
            card = line.strip().split(":")[1]
            winning = set(card.split("|")[0].split())
            numbers = set(card.split("|")[1].split())
            total_points += int(2 ** (len(numbers.intersection(winning)) - 1))

    return total_points


if __name__ == "__main__":
    print(f"The total point worth of the cards is {solution(sys.argv[1])}.")
