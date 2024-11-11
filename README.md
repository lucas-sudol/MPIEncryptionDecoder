# Project Title

A2 - MPI Based Decryption

## Description
Uses linux MPI to to perform process based scheudling of decryption

Workload is divided by giving each process a branch of the permutations, done with a different starting letter in the encrypted dictionary

## Getting Started

### Dependencies

Linux 3090 Docker Containter

### Executing program

* How to build and run the program
make all

./a2encrypt "(input string)" - provide string to be encrypted

./a2decrypt_serial (cipher txt file) (system dictionary txt file)

mpiexec -n (process count )./a2decrypt (cipher txt file) (system dictionary txt file)

* include the expected output


## Limitations

## Author Information
Lucas Sudol
Sebastian Kula


## Development History

## Acknowledgments



