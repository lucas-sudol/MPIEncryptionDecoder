# MPI Based String Decryption

## Description
Uses MPI to to perform multi-process based scheudling of decryption.

Workload is divided by giving each process a branch of the permutations, done with a different starting letter in the encrypted dictionary.
When distributed unevenly, workers with a lower rank in the pool will receive remaining branches.

Sample american-english dictionary is provided in the repository.

Dictionary is loaded into a trie to speed up checking if decrypted words are found in the dictionary. Trie is used to speed up decryption, as the program does not have to scan the entire dictionary for every word in the decrypted string. Spell check exits on first word with no dictionary match.

Results from MPI workers are only printed when all work is completed, in order to reduce communication overhead.

## Getting Started

### Dependencies

MPI library

### Executing program

* How to build and run the program
    make all

    ./encrypt "(input string)" - provide string to be encrypted

    ./decrypt_serial (cipher txt file) (system dictionary txt file)

mpiexec -n (process count) ./a2decrypt (cipher txt file) (system dictionary txt file)


## Author Information
Lucas Sudol
Sebastian Kula

## Acknowledgments
Open source trie library sourced from https://github.com/skeeto



