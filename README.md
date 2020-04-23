# number_partitions

Run make to compile partitions
Partitions takes in a flag, and algorithm, and an input file <br/>
Flag 0 is pset mode, flags 1 and 2 are testing mode <br/>

**Pset mode** has a singular output of the residue of the specified algorithm: <br/>
0 -- Karmarker Karp<br/>
1 -- Repeated Random<br/>
2 -- Hill Climbing<br/>
3 -- Simulated Annealing<br/>
11 -- Prepartitioned Repeated Random<br/>
12 -- Prepartitioned Hill Climibing<br/>
13 -- Prepartitioned Simulated Annealing<br/>
There are comments in partition.c describing each algorithm and all helper functions.<br/>

**Testing mode** runs all 7 of these algorithms.<br/>
Testing mode rewrites test.txt and fills it with randomly generated numbers.<br/>
In testing mode, use test.txt as the input file.<br/>
**Flag 1** Prints redisual results<br/>
**Flag 2** Prints time results<br/>
Results from testing available gdoc:
https://docs.google.com/spreadsheets/d/1GSNGNi3w-h-WoM0mPtApfjqQwkluPZKpQMXI9Qqdm7Q/edit?usp=sharing

Recommended usage is to pipe (>) to output.txt<br/>
For testing mode, recommended parameter inputs are:<br/>
**./partition 1 0 test.txt > output.txt**<br/>
**./partition 2 0 test.txt > output.txt**<br/>

