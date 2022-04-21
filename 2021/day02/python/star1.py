import sys

import pandas as pd


def main():
    df = pd.read_csv(sys.argv[1], sep=" ", names=["command", "value"])

    forward_sum = df.loc[df["command"] == "forward"]["value"].sum()
    down_sum = df.loc[df["command"] == "down"]["value"].sum()
    up_sum = df.loc[df["command"] == "up"]["value"].sum()

    print(forward_sum * (down_sum - up_sum))


if __name__ == "__main__":
    main()
