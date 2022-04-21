import sys


def do_insertion(template, rules):
    result = []
    for i in range(len(template) - 1):
        pair = template[i] + template[i+1]
        result.append(pair[0])
        result.append(rules[pair])
    result.append(pair[1])

    return result


def solution(input_file):

    rules = {}
    template = []

    with open(input_file, 'r') as f:
        template = list(next(f).strip())
        next(f)
        for line in f:
            p1, p2 = line.strip().split(" -> ")
            rules[p1] = p2

        for step in range(10):
            template = do_insertion(template, rules)

    counts = [template.count(p) for p in set(template)]

    return max(counts) - min(counts)


if __name__ == "__main__":
    print(solution(sys.argv[1]))
