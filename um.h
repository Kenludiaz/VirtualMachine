/*
  Module that contains the Universal Machine and ties the 
  other modules together
  
*/
#include "memoryOperations.h"
#include "table.h"
#include "um-dis.h"
// Runs a program until completion
int run(FILE * program);






// // Registers r[0] and r[7] initialized and 0-ed
// Seq_T initRegisters();

// // Fp must point to 32-bit words
// // Will then return a sequence of a sequence of
// // words with m[0] mapped
// Seq_T readInstructions(FILE* fp);
// void writeSegment(Seq_T segments, int index);

// uint32_t getWord(Seq_T segments, int segment, int offset);


// // Will return the the int representation of the
// // first 4 bits of an instruction
// int readOpCode(uint32_t word);