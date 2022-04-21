import sys


def solution(input_file):

    total_count = 0

    with open(input_file, 'r') as f:
        for line in f:
            i, o = [x for x in line.split("|")]
            input_digits = [digit for digit in i.split()]
            output_digits = [digit for digit in o.split()]
            for digit in output_digits:
                if len(digit) in {2, 3, 4, 7}:
                    total_count += 1
            #print(input_digits)
            #print(output_digits)
        

    return total_count


if __name__ == "__main__":
    print(solution(sys.argv[1]))
