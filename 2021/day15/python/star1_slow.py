import sys


risks = None
start = None
end = None


def end_diff(c):
    return end[0] + end[1] - c[0] - c[1]


def check_coord(c):
    return not(c[0] < 0 or c[1] < 0 or c[0] >= len(risks) or c[1] >= len(risks[0]))

def single_step(coord):
    global risks
    dirs = [(-1, 0), (0, -1), (1, 0), (0, 1)]
    coords = []
    for d in dirs:
        c = (coord[0] + d[0], coord[1] + d[1])
        if check_coord(c):
            coords.append(c)
    return coords


def path_cost(path):
    cost = sum([risks[c[0]][c[1]] for c in path]) + 10* end_diff(path[-1])*end_diff(path[-1])
    return cost - risks[start[0]][start[1]] if start in path else cost


def path_steps(paths, steps, taken_path):
    if steps > 0:
        new_paths = []
        for path in paths:
            for neighbour in single_step(path[-1]):
                if not neighbour in path and not neighbour in taken_path:
                    new_path = path.copy()
                    new_path.append(neighbour)
                    new_paths.append(new_path)
        paths = new_paths
        return path_steps(paths, steps - 1, taken_path)
    return paths

def optimal_path(paths, steps):
    optimal_path = []
    paths = path_steps([[start]], 2)
    path_costs = []
    for path in paths:
        path_costs.append(path_cost(path))

    return optimal_path



def solution(input_file):

    global risks, start, end

    with open(input_file, 'r') as f:
        risks = [[int(risk) for risk in line.strip()] for line in f]

        start = 0, 0
        end = len(risks) - 1, len(risks[0]) - 1
        best_path = [start]
        finished = False
        num_steps = 16

        while not end in best_path:
            current_coord = best_path[-1]
            paths = path_steps([[current_coord]], num_steps, best_path)
            path_costs = []
            for path in paths:
                if end in path:
                    finished = True
                path_costs.append(path_cost(path))
            
            if finished:
                min_cost = path_costs[0]
                min_cost_idx = 0
                for idx, cost in enumerate(path_costs):
                    if cost <= min_cost and end in paths[idx]:
                        min_cost_idx = idx
                        min_cost = cost
                for coord in paths[min_cost_idx][1:]:
                    best_path.append(coord)
                break
            else:
                min_cost = path_costs[0]
                min_cost_idx = 0
                for idx, cost in enumerate(path_costs):
                    if cost < min_cost:
                        min_cost_idx = idx
                        min_cost = cost

            best_path.append(paths[min_cost_idx][1])
    print(best_path)
    return path_cost(best_path)


if __name__ == "__main__":
    print(solution(sys.argv[1]))
