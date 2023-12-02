import sys


def solution(input_file):

    calibration_sum = 0
    digits = {
        "one": 1,
        "two": 2,
        "three": 3,
        "four": 4,
        "five": 5,
        "six": 6,
        "seven": 7,
        "eight": 8,
        "nine": 9,
    }

    with open(input_file, 'r') as f:
        for line in f:
            calibration_value = 0
            lowest_text_index = 10000
            highest_text_index = -10000
            lowest_num_index = 10000
            highest_num_index = -10000

            for d in digits.keys():
                ind = line.find(d)
                if ind < lowest_text_index and ind != -1:
                    lowest_text_index = ind
                    lowest_text_digit = digits[d]
            for d in digits.keys():
                ind = line.rfind(d)
                if ind > highest_text_index and ind != -1:
                    highest_text_index = ind
                    highest_text_digit = digits[d]
            

            for i in range(len(line)):
                if line[i] in '0123456789':
                    lowest_num_index = i
                    break
            for i in range(len(line) -1, -1, -1):
                if line[i] in '0123456789':
                    highest_num_index = i
                    break

            if lowest_num_index < lowest_text_index:
                calibration_value += int(line[lowest_num_index]) * 10
            else:
                calibration_value += lowest_text_digit * 10

            if highest_num_index > highest_text_index:
                calibration_value += int(line[highest_num_index])
            else:
                calibration_value += highest_text_digit

            calibration_sum += calibration_value

    return calibration_sum


if __name__ == "__main__":
    print(f"The sum of all the calibration values is {solution(sys.argv[1])}.")
