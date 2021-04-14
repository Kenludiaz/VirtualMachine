/* 
    Parses and stores words into memory segments
    Memory segments will be stored as tables in order to
    allow ease of lookup, addition, and removal at any segment
*/
#include "table.h"
#include <stdlib.h>

typedef Table_T Segment;
// Stores memory segments
typedef Table_T segmentContainer;
typedef uint32_t word;

// Reads instructions from fp and
// writes it to a segment[0]
Segment readInstructions(FILE * fp);

// Writes segment[segmentIndex] into fp
void writeSegment(segmentContainer segments, unsigned segmentIndex, FILE * fp);

// Returns the word at segments[index][offset]
word getWord(segmentContainer segments, int index, int offset);

// Reads the first four bytes of the instruction
// and returns the appropriate Opcode
int readOpCode(word instruction);