#include "memoryOperations.h"
#include "bitpack.h"


// Reads instructions from fp and
// writes it to a segment
Segment readInstructions(FILE * fp) {

    Segment seg = Seq_new(2);

    int input = 0;
    while ((input = getc(fp)) != EOF) {
        word currentWord = 0;

        currentWord = Bitpack_newu(currentWord, 8, 24, input);
		input = getc(fp);
		currentWord = Bitpack_newu(currentWord, 8, 16, input);
		input = getc(fp);
		currentWord = Bitpack_newu(currentWord, 8, 8, input);
		input = getc(fp);
		currentWord = Bitpack_newu(currentWord, 8, 0, input);
        
        // printf("%x\n", currentWord);
        Seq_addhi(seg, (void *)(uintptr_t)currentWord);
    }
    // printf("Sequence Lenth: %d\n", Seq_re(seg));
    return seg;
}

// Returns the word at segments[index][offset]
Segment getSegment(segmentContainer segments, unsigned index) {
    void * segmentPointer = Table_get(segments, Atom_int(index));
    if (segmentPointer == NULL) {
        Halt();
    }
    return (Segment)segmentPointer;
}

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

// Creates a segment with r[C] number of words
// A currently unused bit identifier will be placed in r[B]
// Will map to m[ r[B] ]
// int mapSegment(segmentContainer m, registerContainer r,  unsigned B, unsigned C) {
//     // Check if there are unmapped id's
//     // if yes then r[B] = unmapped register
//     // else check registerContainer[ length] 
//     // if it does not already exist
//     // if already exists length++
// }

// // Unmapps segment m [ r[C] ], and adds the r[C] identifier
// // into the available segments
// int unMapSegment(segmentContainer m, registerContainer r, int C);

// Writes the contents of r[C], only values from 0 to 255
void output(registerContainer r, unsigned C) {
    printf("%c", (char)r[C]);
}

// Gets input and stores it into r[C],
// value must be from 0 to 255.
// Will have a full 32-bit word with every bit is 1
void input(registerContainer r, unsigned C) {
    int input;
    input = getchar();
    if (input == EOF) {
        r[C] = UINT32_MAX;
        return;
    }
    r[C] = input;
}

// Duplicates segment m[ r[B] ] and usurps  m [ 0 ]
// The program counter will be set to r[C]
void loadProgram(segmentContainer m, registerContainer r, unsigned B) {
    Segment program = getSegment(m, r[B]);
    Table_put(m, Atom_int(0), program);
}


#undef twopower32