import sys

import pandas as pd


def solution1():
    df = pd.read_csv(sys.argv[1], names=["binary_num"], dtype=str)
    num_columns = len(df["binary_num"][0])

    df = df.binary_num.apply(lambda bin_str: list(bin_str))
    df = pd.DataFrame(df.to_list(), columns=range(num_columns))

    df_mode = df.mode()
    gamma = ""
    epsilon = ""

    for i in range(num_columns):
        gamma += "1" if df_mode[i][0] == "1" else "0"
        epsilon += "0" if df_mode[i][0] == "1" else "1"

    gamma = int(gamma, 2)
    epsilon = int(epsilon, 2)

    return gamma * epsilon


if __name__ == "__main__":
    print(solution1())
