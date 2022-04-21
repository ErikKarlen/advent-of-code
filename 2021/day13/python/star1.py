import sys


def fold(points, fold_point, direction):
    remove_list = []
    add_list = []
    for p in points:
        if direction == "y" and p[1] > fold_point:
            remove_list.append(p)
            add_list.append((p[0], 2 * fold_point - p[1]))
        if direction == "x" and p[0] > fold_point:
            remove_list.append(p)
            add_list.append((2 * fold_point - p[0], p[1]))

    for p in remove_list:
        points.remove(p)
    for p in add_list:
        points.add(p)


def solution(input_file):

    points = set()

    with open(input_file, 'r') as f:
        for line in f:
            if line == "\n":
                break

            x, y = int(line.split(",")[0]), int(line.split(",")[1])
            points.add((x, y))
    
        instruction = next(f)
        direction, fold_point = instruction.split("=")[0][-1], int(instruction.split("=")[1])
        fold(points, fold_point, direction)

    return len(points)


if __name__ == "__main__":
    print(solution(sys.argv[1]))
