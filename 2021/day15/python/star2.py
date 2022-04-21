import sys
import math
from time import sleep


risks = None
start = None
end = None


class Node():
    def __init__(self, parent=None, position=None):
        self.parent = parent
        self.position = position

        self.g = 0
        self.h = 0
        self.f = 0

    def __eq__(self, other):
        return self.position == other.position

    def __repr__(self):
      return f"{self.position} - g: {self.g} h: {self.h} f: {self.f}"

    def __hash__(self):
        return hash(self.position)


def check_coord(c):
    return not(c[0] < 0 or c[1] < 0 or c[0] >= len(risks) or c[1] >= len(risks[0]))


def neighbours(coord):
    dirs = [(-1, 0), (0, -1), (1, 0), (0, 1)]
    coords = []
    for d in dirs:
        c = (coord[0] + d[0], coord[1] + d[1])
        if check_coord(c):
            coords.append(c)
    return coords


def path_cost(path):
    cost = sum([risks[c[0]][c[1]] for c in path])
    return cost - risks[start.position[0]][start.position[1]] if start.position in path else cost


def cave_string(closed, size=10):
    global risks
    out = ""
    for row in range(size):
        out += "\n"
        for col in range(size):
            if (row, col) in closed:
                out += "."
            else:
                out += str(risks[row][col])
    return out


def return_path(current_node):
    path = []
    current = current_node
    while current is not None:
        path.append(current.position)
        current = current.parent
    return path[::-1]


def a_star():
    global risks, start, end
    closed_set = set()
    open_dict = {start.position: start}
    while len(open_dict) > 0:
        #print(cave_string(closed_set, 50))
        current_node = start
        for pos in open_dict:
            if current_node == start or open_dict[pos].f < current_node.f:
                current_node = open_dict[pos]
        del open_dict[current_node.position]
        closed_set.add(current_node)

        if current_node == end:
            return return_path(current_node)

        children = []
        for neighbour_coord in neighbours(current_node.position):
            neighbour_node = Node(current_node, neighbour_coord)
            children.append(neighbour_node)

        for child in children:
            if child in closed_set:
                continue

            child.g = current_node.g + risks[child.position[0]][child.position[1]]
            #child.h = math.sqrt(((child.position[0] - end.position[0]) ** 2) + ((child.position[1] - end.position[1]) ** 2))
            child.h = child.position[0] - end.position[0] + child.position[1] - end.position[1]
            child.f = child.g + child.h

            if child.position in open_dict and child.g > open_dict[child.position].g:
                continue

            open_dict[child.position] = child
    return paths


def solution(input_file):

    global risks, start, end

    with open(input_file, 'r') as f:
        risks = [[int(risk) for risk in line.strip()] for line in f]
        dup_size = 5
        new_risks = []
        for box_row in range(dup_size):
            for row in range(len(risks)):
                new_risks.append([])
                for box_col in range(dup_size):
                    risk_row = risks[row]
                    for risk in risk_row:
                        new_risk = (risk + box_col + box_row - 1) % 9 + 1
                        new_risks[box_row * len(risks) + row].append(new_risk)

        risks = new_risks

        start = Node(None, (0, 0))
        end = Node(None, (len(risks) - 1, len(risks[0]) - 1))
        best_path = a_star()

    return path_cost(best_path)


if __name__ == "__main__":
    print(solution(sys.argv[1]))
