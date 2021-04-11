#include <stdlib.h>
#include "seq.h"

// Registers r[0] and r[7] initialized and 0-ed
Seq_T initRegisters();

// Reads instructions and maps segment[0]
// fp must point to 32-bit words
Seq_T readInstructions(FILE* fp);
