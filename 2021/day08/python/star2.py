import sys


def decode_lines(digit_map, lines):
    if len(lines) == 2:
        return 1
    elif len(lines) == 3:
        return 7
    elif len(lines) == 4:
        return 4
    elif len(lines) == 7:
        return 8
    elif len(lines) == 5:
        if digit_map["b"] in lines:
            return 5
        elif digit_map["e"] in lines:
            return 2
        else:
            return 3
    elif len(lines) == 6:
        if digit_map["d"] not in lines:
            return 0
        elif digit_map["c"] not in lines:
            return 6
        else:
            return 9

def solution(input_file):

    output_nums = []

    with open(input_file, 'r') as f:
        for line in f:
            digit_map = {}
            digit_map["a"] = {"a", "b", "c", "d", "e", "f", "g"}
            digit_map["b"] = digit_map["a"].copy()
            digit_map["c"] = digit_map["a"].copy()
            digit_map["d"] = digit_map["a"].copy()
            digit_map["e"] = digit_map["a"].copy()
            digit_map["f"] = digit_map["a"].copy()
            digit_map["g"] = digit_map["a"].copy()

            i, o = [x for x in line.split("|")]
            input_digits = [digit for digit in i.split()]
            output_digits = [digit for digit in o.split()]

            for digit in input_digits:
                if len(digit) == 2:
                    one = {c for c in digit}
                    digit_map["a"] -= one
                    digit_map["b"] -= one
                    digit_map["c"] = digit_map["c"].intersection(one)
                    digit_map["d"] -= one
                    digit_map["e"] -= one
                    digit_map["f"] = digit_map["f"].intersection(one)
                    digit_map["g"] -= one
            for digit in input_digits:
                if len(digit) == 3:
                    seven = {c for c in digit}
                    digit_map["a"] = digit_map["a"].intersection(seven)
                    digit_map["b"] -= seven
                    digit_map["c"] = digit_map["c"].intersection(seven)
                    digit_map["d"] -= seven
                    digit_map["e"] -= seven
                    digit_map["f"] = digit_map["f"].intersection(seven)
                    digit_map["g"] -= seven
            for digit in input_digits:
                if len(digit) == 4:
                    four = {c for c in digit}
                    digit_map["a"] -= four
                    digit_map["b"] = digit_map["b"].intersection(four)
                    digit_map["c"] = digit_map["c"].intersection(four)
                    digit_map["d"] = digit_map["d"].intersection(four)
                    digit_map["e"] -= four
                    digit_map["f"] = digit_map["f"].intersection(four)
                    digit_map["g"] -= four

            six_lines_inter = {"a", "b", "c", "d", "e", "f", "g"}
            for digit in input_digits:
                if len(digit) == 6:
                    six_lines_inter = six_lines_inter.intersection({d for d in digit})
            digit_map["b"] = six_lines_inter.intersection(digit_map["b"])
            digit_map["f"] = six_lines_inter.intersection(digit_map["f"])
            digit_map["g"] = six_lines_inter.intersection(digit_map["g"])
            digit_map["c"] -= digit_map["f"]
            digit_map["d"] -= digit_map["b"]
            digit_map["e"] -= digit_map["g"]
            for k in digit_map:
                (digit_map[k],) = digit_map[k]

            output_num = 0
            for digit in output_digits:
                output_num = 10*output_num + decode_lines(digit_map, digit)
            output_nums.append(output_num)

            #print(output_digits)
        

    return sum(output_nums)


if __name__ == "__main__":
    print(solution(sys.argv[1]))
