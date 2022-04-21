import sys
import pandas as pd


def main():
    df = pd.read_csv(sys.argv[1], names=[0])
    df_diff = df - df.shift(1)

    print(df_diff[0].fillna(0).gt(0).sum())

if __name__ == "__main__":
    main()
