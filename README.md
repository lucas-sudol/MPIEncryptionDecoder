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

ASK about how we are suppposed to schedule number of processes - just use what is available, or always make sure it is properly distributed

Talk about performance analysis - ask if we must go over things already covered in the last assignment -ex multithreading, having 1 more task then worker functions

Do we always need to complete calculating every permutation?

talk about format for printing results -is there one, or just up to us


