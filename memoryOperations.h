/* Preforms operations on registers
   Registers will hold a 32-bit word 
*/

#include "table.h"
#include <stdint.h>
#include <stdio.h>
// Some operations will require accessing segments,
// Declared void * in order to decouple this module from
// segmentOperations
typedef uint32_t * registerContainer;
typedef Table_T     segmentContainer;
typedef Table_T Segment;
typedef uint32_t word;


#define threeRegisters registerContainer r, int A, int B, int C

enum ops {CMV = 0, SLOAD, SSTORE, ADD, MULT, DIVIDE, NAND, HALT, MAP,
                                      UMAP, OUT, IN, LOADP, LOADV};
enum regs { r0 = 0, r1, r2, r3, r4, r5, r6, r7 };

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

// Copies r[B] to r[A] if r[C] != 0
int conditionalMove(threeRegisters);

// Saves the value of r[B] into r[A]
void segmentedLoad(segmentContainer m, threeRegisters);

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
int mapSegment(segmentContainer m, registerContainer r,  int B, int C);

// Unmapps segment m [ r[C] ], and adds the r[C] identifier
// into the available segments
int unMapSegment(segmentContainer m, registerContainer r, int C);

// Writes the contents of r[C], only values from 0 to 255
void output(registerContainer r, int C);

// Gets input and stores it into r[C],
// value must be from 0 to 255.
// Will have a full 32-bit word with every bit is 1
void input(registerContainer r, int C);

// Duplicates segment m[ r[B] ] and usurps  m [ 0 ]
// The program counter will be set to r[C]
// Returns 1 if successful and -1 if unsuccessful
int loadProgram(segmentContainer m, registerContainer r, int B, int C);

//  Loads value into register A
int loadValue(registerContainer r, int A, word value);

#undef segmentContainer
#undef word