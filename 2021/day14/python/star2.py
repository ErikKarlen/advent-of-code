import sys
from collections import defaultdict


def calc_pair_counts(current_pair_counts, rules):
    new_pair_counts = dict(current_pair_counts)
    for pair in current_pair_counts:
        p0 = pair[0] + rules[pair]
        p1 = rules[pair] + pair[1]
        new_pair_counts[pair] -= current_pair_counts[pair]
        new_pair_counts[p0] += current_pair_counts[pair]
        new_pair_counts[p1] += current_pair_counts[pair]

    return new_pair_counts


def solution(input_file):

    rules = {}
    template = []
    pair_counts = {}
    counts_dict = defaultdict(int)

    with open(input_file, 'r') as f:
        template = list(next(f).strip())
        next(f)
        for line in f:
            p1, p2 = line.strip().split(" -> ")
            rules[p1] = p2
            pair_counts[p1] = 0


        for i in range(len(template) - 1):
            pair = template[i] + template[i+1]
            pair_counts[pair] += 1


        for step in range(40):
            pair_counts = calc_pair_counts(pair_counts, rules)

    for pair in pair_counts:
        counts_dict[pair[0]] += pair_counts[pair]
        counts_dict[pair[1]] += pair_counts[pair]

    counts = [int(counts_dict[count]/2) for count in counts_dict]
    print(counts_dict)

    return max(counts) - min(counts)


if __name__ == "__main__":
    print(solution(sys.argv[1]))
