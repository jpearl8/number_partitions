# number_partitions

Run make to compile partitions
Partitions takes in a flag, and algorithm, and an input file
Flag 0 is pset mode, flag 1 is testing mode
Pset mode has a singular output of the residue of the specified algorithm:
0 -- Karmarker Karp
1 -- Repeated Random
2 -- Hill Climbing
3 -- Simulated Annealing
11 -- Prepartitioned Repeated Random
12 -- Prepartitioned Hill Climibing
13 -- Prepartitioned Simulated Annealing
There are comments in partition.c describing each algorithm and all helper functions.

Testing mode runs all 7 of these algorithms.
Testing mode rewrites test.txt and fills it with randomly generated numbers.
In testing mode, use test.txt as the input file.

Recommended usage is to pipe (>) to output.txt
For testing mode, recommended parameter inputs are:
./partition 1 0 test.txt > output.txt

