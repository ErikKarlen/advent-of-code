import sys


def solution(input_file):

    maps = [] # elements are: ("map name", <list of ranges>)
    locations = []

    with open(input_file, 'r') as f:
        seeds = [int(s) for s in f.readline().strip().split()[1:]]

        for line in f:
            if line == "\n":
                continue
            if line.find("map") > 0:
                current_map = line.split(" map")[0]
                maps.append((current_map, []))
                continue
            dest_start, source_start, length = [int(n) for n in line.strip().split()]
            maps[-1][1].append((range(source_start, source_start + length), range(dest_start, dest_start + length)))
        
        for s in seeds:
            loc = s
            for m in maps:
                for r in m[1]:
                    if loc in r[0]:
                        loc = r[1].start + loc - r[0].start
                        break
                    
            locations.append(loc)

    return min(locations)


if __name__ == "__main__":
    print(f"The lowest location number that corresponds to any of the initial seed numbers is {solution(sys.argv[1])}.")
