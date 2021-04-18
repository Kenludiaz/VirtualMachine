#include "memoryOperations.h"
#include "bitpack.h"

// Defined macro "max" in stdint was overflowing
#define twopower32 4294967296

// Reads instructions from fp and
// writes it to a segment
Segment readInstructions(FILE * fp) {
    int input = getchar(fp);
    unsigned inputWidth = 8;
    unsigned lsb = 24;
    uint32_t word = 0;
    uint32_t counter = 0;
    Segment seg = Table_new(2, NULL, NULL);

    while (input != EOF) {
        word = Bitpack_newu(word, inputWidth, lsb, input);
        lsb -= inputWidth;
        int input = getchar(fp);

        // printf("Width: %u, lsb: %u\n", inputWidth, lsb);
        printf("Count: %u\n", counter++);
        if (input == '\n') {
            Table_put(seg, &counter, &word);
            return seg;
            lsb = 24;
            word = 0;
        }
    }
    return seg;
}

// Writes segment[segmentIndex] into fp
void writeSegment(segmentContainer segments, unsigned segmentIndex, FILE * fp);

// Returns the word at segments[index][offset]
// word getWord(segmentContainer segments, uint32_t index, uint32_t offset) {
//     void * value = Table_get(segments, (void *)index);
//     if (value == NULL) {
//         fprintf(stderr, "Segment not mapped.\n");
//         Halt();
//     }
//     Table_T segment = (Table_T)value;
//     word value = (word)Table_get(segment, offset);
//     return value;
// }

// Reads the first four bytes of the instruction
// and returns the appropriate Opcode
int readOpCode(word instruction) {
    return (int)(instruction >> 28);
}

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
    r[A] = ((r[B] + r[C]) % twopower32);
}

// Multiplies r[B] and r[C] into r[A]
void multiply(threeRegisters) {
    r[A] = ((r[B] * r[C]) % twopower32);
}

// Divides r[B] by r[C] and saved into r[A] (integer divition)
void divide(threeRegisters) {
    r[A] = (r[B] / r[C]);
}

// Bitwise NAND gate on r[B] and r[C] into r[A]
void NANDGate(threeRegisters) {
    r[A] = ~(r[B] & r[C]);
}

// Stops computation
void Halt() {
    exit(0);
}

// // Creates a segment with r[C] number of words
// // A currently unused bit identifier will be placed in r[B]
// // Will map to m[ r[B] ]
// int mapSegment(segmentContainer m, registerContainer r,  int B, int C);

// // Unmapps segment m [ r[C] ], and adds the r[C] identifier
// // into the available segments
// int unMapSegment(segmentContainer m, registerContainer r, int C);

// Writes the contents of r[C], only values from 0 to 255
void output(registerContainer r, int C) {
    printf("%u\n", (r[C] % 256) );
}

// Gets input and stores it into r[C],
// value must be from 0 to 255.
// Will have a full 32-bit word with every bit is 1
void input(registerContainer r, int C) {
    __u_char input;
    input = getchar();

    // if (input == EOF) {
    //     r[C] = UINT32_MAX;
    //     return;
    // }
    r[C] = input % 256;
}

// // Duplicates segment m[ r[B] ] and usurps  m [ 0 ]
// // The program counter will be set to r[C]
// // Returns 1 if successful and -1 if unsuccessful
// int loadProgram(segmentContainer m, registerContainer r, int B, int C);

// //  Loads value into register A
// int loadValue(registerContainer r, int A, word value);

#undef twopower32