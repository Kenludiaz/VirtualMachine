/* Preforms operations on registers
   Registers will hold a 32-bit word 
*/

#include <stdlib.h>

// Some operations will require accessing segments,
// Declared void * in order to decouple this module from
// segmentOperations
typedef void *      segmentContainer;
typedef uint32_t * registerContainer;
#define threeRegisters registerContainer r, int A, int B, int C

// Saves the value of r[B] into r[A], if r[C] == true
// Returns 1 if move successful, and -1 otherwise
int conditionalMove(threeRegisters);

// Saves the value of m[ r[B] ][ r[C] ] into r[A] 
void segmentedLoad(segmentContainer m, threeRegisters);

// Adds r[B] and r[C] into r[A]
void add(threeRegisters);

// Multiplies r[B] and r[C] into r[A]
void multiply(threeRegisters);

// Divides r[B] by r[C] and saved into r[A] (integer divition)
void divide(threeRegisters);

// Bitwise NAND gate on r[B] and r[C] into r[A]
void NAND(threeRegisters);

// Stops computation
void Halt();

// Creates a segment with r[C] number of words
// Will map to m[ r[B] ], if 
int mapSegment(segmentContainer m, threeRegisters);