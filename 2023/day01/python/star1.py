import sys


def solution(input_file):

    calibration_sum = 0

    with open(input_file, 'r') as f:
        for line in f:
            calibration_value = 0
            for i in range(len(line)):
                if line[i] in '0123456789':
                    calibration_value += int(line[i]) * 10
                    break
            for i in range(len(line) -1, -1, -1):
                if line[i] in '0123456789':
                    calibration_value += int(line[i])
                    break
            calibration_sum += calibration_value

    return calibration_sum


if __name__ == "__main__":
    print(f"The sum of all the calibration values is {solution(sys.argv[1])}.")
