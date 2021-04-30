# Kenneth Lu Diaz

## Acknowledgements
Tim was able to assist me in coming up with the code for finding the number of instructions fed to the um.
** See readInstructions function in memoryOperations.c

## Assembly Analysis
It seems to most costly routine (apart from run) is getSegment. Theres is a little function overhead, but
most of the calls come from Seq_get. While, moving %esi into %edx might reduce IR by one. This program may run faster
by making this function inline and leaving the bounds checking to failure mode or Hanson's Seq_get.

## Time spent
Analyzing: ~4 hrs
Solving: ~4 hrs

