import sys

import pandas as pd


def solution1():
    df = pd.read_csv(sys.argv[1], names=["binary_num"], dtype=str)
    num_columns = len(df["binary_num"][0])
    columns = ["bin" + str(s) for s in range(num_columns)]

    df = df.binary_num.apply(lambda bin_str: list(bin_str))
    df = pd.DataFrame(df.to_list(), columns=columns)

    df_oxygen = df.copy()
    df_co2 = df.copy()
    
    for col in columns:
        #print(df_oxygen)
        if len(df_oxygen) == 1:
            break

        df_oxygen_mode = df_oxygen.mode()[col].dropna()
        if len(df_oxygen_mode) == 2:
            df_oxygen = df_oxygen.loc[df_oxygen[col] == "1"]
        else:
            most_common = "0" if df_oxygen_mode[0] == "0" else "1"
            df_oxygen = df_oxygen.loc[df_oxygen[col] == most_common]
    
    for col in columns:
        #print(df_co2)
        #print()
        if len(df_co2) == 1:
            break

        df_co2_mode = df_co2.mode()[col].dropna()
        if len(df_co2_mode) == 2:
            df_co2 = df_co2.loc[df_co2[col] == "0"]
        else:
            least_common = "0" if df_co2_mode[0] == "1" else "1"
            df_co2 = df_co2.loc[df_co2[col] == least_common]


    oxygen = ""
    co2 = ""

    for col in columns:
        oxygen += "1" if df_oxygen[col].iloc[0] == "1" else "0"
        co2 += "1" if df_co2[col].iloc[0] == "1" else "0"

    oxygen = int(oxygen, 2)
    co2 = int(co2, 2)

    return oxygen * co2


if __name__ == "__main__":
    print(f"{solution1()}")
