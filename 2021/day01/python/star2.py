import sys

import pandas as pd


WINDOW_SIZE = 3

def main():
    df = pd.read_csv(sys.argv[1], names=[0])
    df_sum = 0
    for i in range(WINDOW_SIZE):
        df_sum += df.shift(i)

    df_diff = df_sum - df_sum.shift(1)

    print(df_diff[0].fillna(0).gt(0).sum())

if __name__ == "__main__":
    main()
