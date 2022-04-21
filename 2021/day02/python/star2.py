import sys
from timeit import default_timer as timer

import numpy as np
import pandas as pd


def alt_main():
    df = pd.read_csv(sys.argv[1], sep=" ", names=["command", "value"])
    df.loc[df["command"] == "up", "value"] *= -1

    df["aim"] = 0
    df["aim"] += df.loc[df["command"] != "forward", "value"].cumsum()
    df = df.fillna(method='ffill')
    df = df.fillna(0)

    df["depth"] = 0
    df["depth"] += (df.loc[df["command"] == "forward", "value"] * df.loc[df["command"] == "forward", "aim"]).cumsum()
    df = df.fillna(method='ffill')
    df = df.fillna(0)

    df["pos"] = 0
    df["pos"] += df.loc[df["command"] == "forward", "value"].cumsum()
    df = df.fillna(method='ffill')
    df = df.fillna(0)
    
    #print(int(df["depth"].iloc[-1] * df["pos"].iloc[-1]))


def main():
    df = pd.read_csv(sys.argv[1], sep=" ", names=["command", "value"])

    aim = 0
    pos = 0
    depth = 0

    for index, row in df.iterrows():
        if row["command"] == "down":
            aim += row["value"]
        if row["command"] == "up":
            aim -= row["value"]
        if row["command"] == "forward":
            depth += aim * row["value"]
            pos += row["value"]

    #print(pos * depth)


if __name__ == "__main__":

    num_iter = 200
    main_total_time = 0
    start = timer()
    for i in range(num_iter):
        alt_main()
    end = timer()
    main_total_time = end - start

    alt_main_total_time = 0
    start = timer()
    for i in range(num_iter):
        alt_main()
    end = timer()
    alt_main_total_time = end - start

    print(f"main total time: {main_total_time}")
    print(f"alt_main total time: {alt_main_total_time}")
