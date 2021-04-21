# Kenneth Lu Diaz

## Architecture
 - um.c
   - Processes file pointer and runs the program
   - Ties all of the memory operations together
   - Main(Event) loop of the program
   - Contains the switch statement that decides which operation to run
   - Frees memory
   - memoryOperations.c
     - Contains all the operations done on segments and registers
     - Contains the secrets as to what are the datastructures I use
     - bitpack.c
       - Handles the processing of words
     - table.h
       - Represents a collection of memory segments
       - seq.h
         - Represents a segment of memory that holds unsigned words

### Comments
I decided to implement all functions inside one module because if I were to change my datastructure 
I would have to change my type definitions across various files, which is not a good indication
of decoupled code.

## Time spent
Analyzing: ~4 hrs
Designing: ~4 hrs
Working after Design: ~16 hrs
A lot more time had to be taken to thinking about my design, since I underestimated the difficulty
with implementing my initial design (A table that contains a table).

## Prospectives
I hope to try an implementation were the segments are stored inside a sequence
and the sequences are stored within henson arrays. 
Sequence => Arrays => Words
According to valgrind, there seems to be a lot of memory lost
specifically because of using a sequence for the inner data structure.