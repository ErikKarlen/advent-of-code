import sys

from collections import defaultdict


def solution(input_file):

    card_counts = defaultdict(lambda:1)

    with open(input_file, 'r') as f:
        line_ind = 1
        for line in f:
            card = line.strip().split(":")[1]
            winning = set(card.split("|")[0].split())
            numbers = set(card.split("|")[1].split())
            num_copies = len(numbers.intersection(winning))

            for i in range(card_counts[line_ind]):
                for j in range(num_copies):
                    card_counts[line_ind + j + 1] += 1

            line_ind += 1

    return sum(card_counts.values())


if __name__ == "__main__":
    print(f"The number of scratch cards that we end up with is {solution(sys.argv[1])}.")
