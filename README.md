# 2round-Keccak384
Preimage attack on 2-round Keccak-384

All the programs can be directly compiled and executed.

test.cpp:
  This program will show you the details of our algorithm.
  The preimage will be writen in res.txt (in big-endian order).

SHA3.h/EQU.h:
  Some functions about Keccak-f permutation and solving linear equation system.

res.txt:
  This file prints the initial state in order of 5*5 lanes, where the first 13 lanes compose the preimage.

verify.cpp:
  This program reads res.txt as input and examines the execution status of 2-round Keccak-384 step-by-step.
