# bjsim

This is a simple Blackjack simulator originally written in C++. It builds a command line application that runs a few hard coded test games.

## Building

A `Makefile` is provided. To build the program just run:

```bash
make
```

This produces an executable named `bjsim` in the project directory. Use `make clean` to remove build artifacts.

## Running

After building, run the simulator with:

```bash
./bjsim
```

The main function currently invokes a demonstration using a continuous shuffling machine (CSM) and a basic strategy player. You can modify `bjsim.cpp` if you want to run one of the other test functions.


### Requirements

- GNU Make
- A C++17 compatible compiler (tested with `g++`)
