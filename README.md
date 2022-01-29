# Wordler
## A small solver for Wordle-style puzzles.

## What's it do?
Solve Wordle-style puzzles.

## Right, but I mean, what does it look like?

```
$ ./bin/wordler
Start by entering 'serai' as your first guess
Enter hint (use '.' for miss, '+' for yellow match, '#' for green match):
.....
-----
Now guess: phony
Please enter hint:
..+..
-----
Now guess: gombo
Please enter hint:
.#...
-----
Now guess: would
Please enter hint:
.####
-----
Now guess: could
Please enter hint:
#####
Congratulations, puzzle solved!
```

The included wordlist (see wordlist.txt) is taken directly from [the official Wordle game](https://www.powerlanguage.co.uk/wordle/) and hence has all 5-letter words, but this program can use any list of words of length 1 through 255 without modification.

## Dependencies
This program depends on [TCLAP](http://tclap.sourceforge.net/) for commandline argument parsing. Check if it's available through your distribution's package manager.

[Googletest](https://github.com/google/googletest) and [Googlebench](https://github.com/google/benchmark) are used for unit testing and benchmarking respectively; these are automatically downloaded and compiled as part of the build process.

## Installation and usage:

Compilation should be as simple as `make` (or `make all`); you will likely want to set the `CMAKE_BUILD_TYPE` option to `Release` to enable the maximum optimization level (ex: `CMAKE_BUILD_TYPE=Release make all`).

After the build is complete, run the binary with `--help` for usage information.

Thanks to [the Wordler dude](https://twitter.com/powerlanguish/) for making the game.
Thanks to Donald Knuth for generally being a baller, but specifically for his [algorithm to solve Mastermind](http://www.cs.uni.edu/~wallingf/teaching/cs3530/resources/knuth-mastermind.pdf), which I relied on heavily while writing this program.
