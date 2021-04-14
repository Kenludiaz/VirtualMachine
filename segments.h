/* 
    Parses and stores words into memory segments
    Memory segments will be stored as tables in order to
    allow ease of lookup, addition, and removal at any segment
*/
#include "table.h"
#include <stdlib.h>

typedef Table_T Segment;
typedef uint32_t word;

// Reads instructions from fp and
// writes it to a segment[0]
Segment readInstructions(FILE * fp);

// Writes segment[segmentIndex] into fp
void writeSegment(Table_T segments, unsigned segmentIndex, FILE * fp);

word getWord(Table_)