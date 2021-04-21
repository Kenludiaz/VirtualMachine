/* Preforms operations on registers and memory segments
   Registers will hold a 32-bit word 
   Memory segments will be stored as tables in order to
   allow ease of lookup, addition, and removal at any segment
   Memory will be stored in a sequence with the form of unsigned 32-bit words
*/
#include "table.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "atom.h"
#include "bitpack.h"
#include "seq.h"

typedef uint32_t * registerContainer;
typedef Table_T     segmentContainer;
typedef Seq_T                Segment;
typedef uint32_t                word;

// Defined macro "max" in stdint was overflowing
#define twopower32 4294967296
#define threeRegisters registerContainer r, unsigned A, unsigned B, unsigned C
enum ops {CMV = 0, SLOAD, SSTORE, ADD, MULT, DIVIDE, NAND, HALT, MAP,
                                      UMAP, OUT, IN, LOADP, LOADV};
enum regs { r0 = 0, r1, r2, r3, r4, r5, r6, r7 };

// Reads instructions from fp and
// writes it to a segment[0]
Segment readInstructions(FILE * fp);

// Writes segment[segmentIndex] into fp
void writeSegment(segmentContainer segments, unsigned segmentIndex, FILE * fp);

// Returns the segment at segments[index]
Segment getSegment(segmentContainer segments, unsigned index);

// Returns the word at segment[offset]
word getWord(Segment seg, unsigned offset);

// Reads the first four bytes of the instruction
// and returns the appropriate opCode
int readOpCode(word instruction);

// Returns the corresponding values to from an instruction
static inline uint32_t CALC_A(word instruction) {
    return Bitpack_getu(instruction, 3, 6);
}
static inline uint32_t CALC_B(word instruction) {
    return Bitpack_getu(instruction, 3, 3);
}
static inline uint32_t CALC_C(word instruction) {
    return Bitpack_getu(instruction, 3, 0);
}


// Copies r[B] to r[A] if r[C] != 0
int conditionalMove(threeRegisters);

// Saves the value of r[B] into r[A]
void segmentedLoad(segmentContainer m, threeRegisters);

// Stores the value of r[C] int m[r [A] ][r [B]]
void segmentStore(segmentContainer m, threeRegisters);

// Adds r[B] and r[C] into r[A]
void add(threeRegisters);

// Multiplies r[B] and r[C] into r[A]
void multiply(threeRegisters);

// Divides r[B] by r[C] and saved into r[A] (integer divition)
void divide(threeRegisters);

// Bitwise NAND gate on r[B] and r[C] into r[A]
void NANDGate(threeRegisters);

// Stops computation
void Halt();

// Creates a segment with r[C] number of words
// A currently unused bit identifier will be placed in r[B]
// Will map to m[ r[B] ]
void mapSegment(segmentContainer m, Seq_T unmappedIDs, registerContainer r,  unsigned B, unsigned C);

// Adds items amount of elements ('0's) to seg 
void padNewSegment(Segment seg, unsigned items);

// Loops until ID is not mapped into m
word findValidIdentifier(segmentContainer m);


// Unmapps segment m [ r[C] ], and returns the r[C]
word unMapSegment(segmentContainer m, registerContainer r, unsigned C);

// Writes the contents of r[C], only values from 0 to 255
void output(registerContainer r, unsigned C);

// Gets input and stores it into r[C],
// value must be from 0 to 255.
// Will equal UINT32_Max if EOF
void input(registerContainer r, unsigned C);

// Duplicates segment m[ r[B] ] and usurps  m [ 0 ]
// The program counter will be set to r[C]
void loadProgram(segmentContainer m, registerContainer r, unsigned B);

//  Loads value into register A
static inline void loadValue(registerContainer r, unsigned A, word value) {
    r[A] = Bitpack_getu(value, 25, 0);
}
