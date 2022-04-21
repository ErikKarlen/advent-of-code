import sys

import collections


risks = None
costs = None
start = None
end = None


def check_coord(c):
    return not(c[0] < 0 or c[1] < 0 or c[0] >= len(risks) or c[1] >= len(risks[0]))


def neighbours(coord):
    global risks
    dirs = [(-1, 0), (0, -1), (1, 0), (0, 1)]
    coords = []
    for d in dirs:
        c = (coord[0] + d[0], coord[1] + d[1])
        if check_coord(c):
            coords.append(c)
    return coords


def path_cost(path):
    cost = sum([risks[c[0]][c[1]] for c in path])
    return cost - risks[start[0]][start[1]] if start in path else cost


def dijkstras():
    global risks, costs, start, end
    visited = set()
    while not end in visited:
        min_coord = (0, 0)
        for row in range(len(costs)):
            for col in range(len(costs[0])):
                if not (row, col) in visited:
                    min_coord = (row, col)
        for row, costs_row in enumerate(costs):
            for col, cost in enumerate(costs_row):
                if not (row, col) in visited and cost < costs[min_coord[0]][min_coord[1]]:
                    min_coord = (row, col)
        visited.add(min_coord)
        for neighbour in neighbours(min_coord):
            new_cost = costs[min_coord[0]][min_coord[1]] + risks[neighbour[0]][neighbour[1]]
            if new_cost < costs[neighbour[0]][neighbour[1]]:
                costs[neighbour[0]][neighbour[1]] = new_cost
    return costs[end[0]][end[1]]


def solution(input_file):

    global risks, costs, start, end

    with open(input_file, 'r') as f:
        risks = [[int(risk) for risk in line.strip()] for line in f]
        costs = [[sys.maxsize for col in range(len(risks[0]))] for row in range(len(risks))]

        start = 0, 0
        end = len(risks) - 1, len(risks[0]) - 1
        costs[start[0]][start[1]] = 0
        min_cost = dijkstras()

    return min_cost


if __name__ == "__main__":
    print(solution(sys.argv[1]))
