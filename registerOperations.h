#include <stdlib.h>
#include "seq.h"

/*
Copies the value of register B to A, if register C
is not equal to 0.
*/
int conditionalMove(uint32_t * registers, int A, int B, int C);


// If none of the values 
void segmentedLoad(Seq_T segments, uint32_t * registers, int A, int B, int C);

