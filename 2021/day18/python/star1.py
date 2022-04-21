import sys


def read_snailfish_number(num_str, parent):
    if num_str[0] in "0123456789":
        return int(num_str[0])
    elif num_str[0] == "[":
        new_num_str = num_str[1:num_str.rfind("]")]
        parent.append([])
        parent[0].append(read_snailfish_number(new_num_str, parent))
    elif num_str[0] == ",":
        new_num_str = num_str[1:num_str.rfind("]")]
        parent[1].append(read_snailfish_number(new_num_str, parent))

    return parent


def print_num(num):
    if num[0] in "0123456789":
        print(num, end="")
    else:
        print(print_num(num))


def solution(input_file):

    with open(input_file, 'r') as f:

        for line in f:
            root = []
            read_snailfish_number(line.strip()[1:-1], root)
            print_num(root)
            break

    return 0


if __name__ == "__main__":
    print(solution(sys.argv[1]))
