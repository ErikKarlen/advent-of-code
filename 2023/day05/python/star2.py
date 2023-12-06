import sys


def solution(input_file):

    maps = [] # elements are: ("map name", <list of ranges>)
    locations = []

    with open(input_file, 'r') as f:
        temp_seeds = [int(s) for s in f.readline().strip().split()[1:]]
        seed_ranges = []
        for i in range(0, len(temp_seeds), 2):
            seeds_start = temp_seeds[i]
            seeds_length = temp_seeds[i+1]
            seed_ranges.append(range(seeds_start, seeds_start + seeds_length))

        for line in f:
            if line == "\n":
                continue
            if line.find("map") > 0:
                current_map = line.split(" map")[0]
                maps.append((current_map, []))
                continue
            dest_start, source_start, length = [int(n) for n in line.strip().split()]
            maps[-1][1].append((range(source_start, source_start + length), range(dest_start, dest_start + length)))
        
        for sr in seed_ranges:
            next_seed = sr.start
            while next_seed in sr:
            #for s in sr:
                loc = next_seed
                min_next = sr.stop - next_seed
                for m in maps:
                    for r in m[1]:
                        if loc in r[0]:
                            loc = r[1].start + loc - r[0].start
                            if r[1].stop - loc < min_next:
                                min_next = r[1].stop - loc # Skip unneeded ranges
                            break
                locations.append(loc)
                next_seed += min_next

    return min(locations)


if __name__ == "__main__":
    print(f"The lowest location number that corresponds to any of the initial seed numbers is {solution(sys.argv[1])}.")
