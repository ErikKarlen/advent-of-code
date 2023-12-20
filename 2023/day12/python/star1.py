import sys

from itertools import combinations


def check_possible_arrangement(arrangement, springs, records):
    r = ""
    for i, s in enumerate(springs):
        if i in arrangement:
            r += "#"
        elif s == "?":
            r += "."
        else:
            r += s

    r = r.strip().split(".")
    l = [len(e) for e in r if len(e) > 0]

    return l == records

def solution(input_file):

    num_possible_arrangements = 0

    with open(input_file, 'r') as f:
        for line in f:
            springs, records = line.strip().split()
            records = [int(c) for c in records.split(",")]
            unknowns_ind = [i for i, c in enumerate(springs) if c == "?"]
            num_guesses = sum(records) - springs.count("#")
            arrangements = combinations(unknowns_ind, num_guesses)
            for arrangement in arrangements:
                if check_possible_arrangement(arrangement, springs, records):
                    num_possible_arrangements += 1

    return num_possible_arrangements


if __name__ == "__main__":
    print(f"The total count of all the different arrangements of operational and broken springs is "
          f"{solution(sys.argv[1])}.")
