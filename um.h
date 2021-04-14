#include <stdlib.h>
#include "seq.h"



  enum ops {CMV = 0, SLOAD, SSTORE, ADD, MULT, DIVIDE, NAND, HALT, MAP,
                                        UMAP, OUT, IN, LOADP, LOADV};
  enum regs { r0 = 0, r1, r2, r3, r4, r5, r6, r7 };
// Registers r[0] and r[7] initialized and 0-ed
Seq_T initRegisters();

// Fp must point to 32-bit words
// Will then return a sequence of a sequence of
// words with m[0] mapped
Seq_T readInstructions(FILE* fp);
void writeSegment(Seq_T segments, int index);

uint32_t getWord(Seq_T segments, int segment, int offset);


// Will return the the int representation of the
// first 4 bits of an instruction
int readOpCode(uint32_t word);