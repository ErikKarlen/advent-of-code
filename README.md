# Erik Karlen's Advent of Code Solutions

My solutions to Advent of Code challenges across multiple years and programming languages.

**Note:** Input files and external libraries are not included in this repository. You'll need to fetch your own input files from [Advent of Code](https://adventofcode.com) and download any required external libraries manually.

## Python

Use Python 3+ with the input file as an argument:

```bash
python3 2023/day01/python/star1.py 2023/day01/input.txt
```

## C

Compile using GNU compiler and run the binary:

```bash
gcc -o 2021/day01/c/star1 2021/day01/c/star1.c
./2021/day01/c/star1 2021/day01/input.txt
```

## C++

Compile using GNU compiler and run the binary:

```bash
g++ -o 2022/day01/cpp/star1 2022/day01/cpp/star1.cpp
./2022/day01/cpp/star1 2022/day01/input.txt
```

## Rust

Use cargo run with the input file as an argument:

```bash
cargo run --manifest-path 2024/day01/rust/star1/Cargo.toml 2024/day01/input.txt
```

## BQN

Use CBQN with the input file as an argument:

```bash
BQN 2025/day01/bqn/star1.bqn 2025/day01/input.txt
```

**Note:** Solutions that import libraries like `strings.bqn` require them in the same folder:

```bash
ls 2025/day01/bqn/
star1.bqn  star2.bqn  strings.bqn
```

Libraries come from [mlochbaum's bqn-libs](https://github.com/mlochbaum/bqn-libs) and can be symbolic links:

```bash
ls -l 2025/day01/bqn/strings.bqn
2025/day01/bqn/strings.bqn -> /path/to/mlochbaum/bqn-libs/strings.bqn
```