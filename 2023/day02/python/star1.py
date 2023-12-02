import sys


def solution(input_file):

    possible_game_id_sum = 0
    colour_limits = {
        "red": 12,
        "green": 13,
        "blue": 14,
    }

    with open(input_file, 'r') as f:
        for line in f:
            possible = True
            line = line.strip().split(": ")
            game_id = int(line[0].split()[1])
            sets = line[1].split("; ")
            for s in sets:
                reveals = s.split(", ")
                for r in reveals:
                    r_split = r.split()
                    num_balls = int(r_split[0])
                    colour = r_split[1]
                    if num_balls > colour_limits[colour]:
                        possible = False

            if possible:
                possible_game_id_sum += game_id
            
    return possible_game_id_sum


if __name__ == "__main__":
    print(f"The sum of the IDs of the possible games is {solution(sys.argv[1])}.")
