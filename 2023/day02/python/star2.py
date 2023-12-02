import sys


def solution(input_file):

    power_sum = 0

    with open(input_file, 'r') as f:
        for line in f:
            line = line.strip().split(": ")
            game_id = int(line[0].split()[1])
            sets = line[1].split("; ")
            colour_limits = {
                "red": 0,
                "green": 0,
                "blue": 0,
            }
            for s in sets:
                reveals = s.split(", ")
                for r in reveals:
                    r_split = r.split()
                    num_balls = int(r_split[0])
                    colour = r_split[1]
                    if colour_limits[colour] < num_balls:
                        colour_limits[colour] = num_balls

            power_sum += colour_limits["red"] * colour_limits["green"] * colour_limits["blue"]
            
    return power_sum


if __name__ == "__main__":
    print(f"The sum of powers of the sets is {solution(sys.argv[1])}.")
