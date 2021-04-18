#include "memoryOperations.h"

// Defined macro "max" in stdint was overflowing
#define twoto32 4294967296

int conditionalMove(threeRegisters) {
    if (r[C] != 0) {
        r[A] = r[B];
        return 1;
    }
    return -1;
}


// void segmentedLoad(segmentContainer m, threeRegisters) {
//     if ()
// }

// Adds r[B] and r[C] into r[A]
void add(threeRegisters) {
    r[A] = ((r[B] + r[C]) % twoto32);
}

// Multiplies r[B] and r[C] into r[A]
void multiply(threeRegisters) {
    r[A] = ((r[B] * r[C]) % twoto32);
}

// Divides r[B] by r[C] and saved into r[A] (integer divition)
void divide(threeRegisters);

// // Bitwise NAND gate on r[B] and r[C] into r[A]
// void NAND(threeRegisters);

// // Stops computation
// void Halt();

// // Creates a segment with r[C] number of words
// // A currently unused bit identifier will be placed in r[B]
// // Will map to m[ r[B] ]
// int mapSegment(segmentContainer m, registerContainer r,  int B, int C);

// // Unmapps segment m [ r[C] ], and adds the r[C] identifier
// // into the available segments
// int unMapSegment(segmentContainer m, registerContainer r, int C);

// // Writes the contents of r[C], only values from 0 to 255
// void output(registerContainer r, int C);

// // Gets input and stores it into r[C],
// // value must be from 0 to 255.
// // Will have a full 32-bit word with every bit is 1
// void input(registerContainer r, int C);

// // Duplicates segment m[ r[B] ] and usurps  m [ 0 ]
// // The program counter will be set to r[C]
// // Returns 1 if successful and -1 if unsuccessful
// int loadProgram(segmentContainer m, registerContainer r, int B, int C);

// //  Loads value into register A
// int loadValue(registerContainer r, int A, word value);

#undef twoto32