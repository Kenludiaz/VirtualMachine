#include "um.h"

// Runs a program until completion
int run(FILE * program) {
    // uint32_t  r[8] = { 0 };
    // unsigned programCounter = 0;
    segmentContainer m = Table_new(2, NULL, NULL);
    Segment zero = readInstructions(program);
    uint32_t home = 0;
    Table_put(m, &home, zero);
    
    return 0;
}