import math
import sys


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

checked = {}

def find_num_possible_arrangements(springs, records):

    global checked

    sr = (springs, records)
    if sr in checked:
        return checked[sr]

    num_arrangements = 0
    num_damaged = sum([len(d) for d in springs if d == "#"])
    num_unknown = sum([len(u) for u in springs if u == "?"])
    total_damaged = sum(records)

    if num_damaged > total_damaged:
        checked[sr] = num_arrangements
        return num_arrangements
    if num_damaged == 0 and num_unknown > 0 and len(records) == 1:
        num_arrangements = math.comb(num_unknown, records[0])
        checked[sr] = num_arrangements
        return num_arrangements
    if (num_damaged == total_damaged or num_unknown + num_damaged == total_damaged) and len(records) == 1:
        num_arrangements = 1
        checked[sr] = num_arrangements
        return num_arrangements
    if total_damaged > num_unknown + num_damaged:
        checked[sr] = num_arrangements
        return num_arrangements

    if len(springs) > 1 and springs[0:1] == "?#" and len(records) > 0 and records[0] == 1:
        springs = springs[1:]

    first_damaged = springs.find("#")
    last_damaged = first_damaged

    while 0 <= last_damaged < len(springs) and springs[last_damaged] == "#":
        last_damaged += 1
    if last_damaged >= 0 and first_damaged >= 0 and last_damaged - first_damaged > records[0] and springs[0] == "#":# and springs[last_damaged] != "?":
        checked[sr] = num_arrangements
        return num_arrangements
    if last_damaged >= 0 and first_damaged >= 0 and last_damaged - first_damaged == records[0] and springs[0] == "#":# and springs[last_damaged] != "?":
        rest_springs = springs[records[0] + 1:]
        rest_records = records[1:]
        num_arrangements = find_num_possible_arrangements(rest_springs, rest_records)
        checked[sr] = num_arrangements
        return num_arrangements

    max_start_ind = len(springs) - sum(records) - len(records) + 1
    #if len(records) == 0:
    #    return 1
    #if max_start_ind == 0:
    #    return 1
    #if max_start_ind < 0:
    #    return 1

    if first_damaged > 0 and all(d == "#" for d in springs[first_damaged:records[0]]) and max_start_ind > first_damaged:
        max_start_ind = first_damaged + 1

    #if len(ud) == 0:
    #    return 1
    #if all(c == "#" for c in ud[0]) and len(ud[0]) == records[0]:
    #    n = springs.find("#") + len(ud[0])
    #    rest_springs = springs[n:]
    #    rest_records = records[1:]
    #    return find_num_possible_arrangements(rest_springs, rest_records)
    
    while len(springs) > 0 and springs[0] == ".":
        springs = springs[1:]

    for start in range(max_start_ind + 1):
        #if sr_start in checked:
        #    num_arrangements += checked[sr_start]
        #    continue
        if len(records) == 0:
            break
        n = springs[start:start + records[0]]
        if all(e in "?#" for e in n) and start + len(n) < len(springs) and springs[start + len(n)] != "#":
            if start > 0 and springs[start - 1] == "#":
                continue
            rest_springs = springs[start + records[0] + 1:]

            #while len(rest_springs) > 0 and rest_springs[0] == ".":
            #    rest_springs = rest_springs[1:]
            rest_records = records[1:]

            num_arrangements += find_num_possible_arrangements(rest_springs, rest_records)
    
    checked[sr] = num_arrangements
    return num_arrangements

def solution(input_file):

    global checked
    num_possible_arrangements = 0

    with open(input_file, 'r') as f:
        for line in f:
            springs, records = line.strip().split()
            n = 1
            records = [int(c) for c in records.split(",")] * n
            records = tuple(records)
            springs = (n * (springs + "?"))[:-1]
            checked = {}
            num_possible_arrangements += find_num_possible_arrangements(springs, records)

    return num_possible_arrangements


if __name__ == "__main__":
    print(f"The new total count of all the different arrangements of operational and broken springs "
          f"is {solution(sys.argv[1])}.")
