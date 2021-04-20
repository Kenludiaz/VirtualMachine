#include "memoryOperations.h"
#include "bitpack.h"

// Defined macro "max" in stdint was overflowing
#define twopower32 4294967296

// Reads instructions from fp and
// writes it to a segment
Segment readInstructions(FILE * fp) {
    unsigned inputWidth = 8;
    int lsb = 24;


    word *wordPtr = (word *)malloc(sizeof(word));
    word Word = (*(wordPtr));
    uint32_t counter = 0;
    Segment seg = Table_new(2, NULL, NULL);

    int input = getc(fp);
    while (input != EOF) {
        // printf("Input: %d\n", input);

        Word = Bitpack_newu(Word, inputWidth, lsb, input);
        lsb -= inputWidth;
        input = getc(fp);

        if (lsb < 0) {
            const char * key   = Atom_int(counter);

            Table_put(seg, key, wordPtr);
            printf("Word From Table: %x\n", (*(word *)Table_get(seg, key)));
            printf("Word: %x\n", Word);
            counter++;
            lsb = 24;
            wordPtr = (word *)malloc(sizeof(word));
            Word = (*wordPtr);
        }
    }
    return seg;
}

// Writes segment[segmentIndex] into fp
void writeSegment(segmentContainer segments, unsigned segmentIndex, FILE * fp);

    // const char * firstKey  =  Atom_int(index);
    // const char * secondKey = Atom_int(offset);
    // void ** Arr = Table_toArray(segments, NULL);
    // for (int i = 0; i < 2; i++) {
    //     printf("Char: %d\n", *((int*)Arr[i]));
    //     printf("function: %lu\n", &index);
    // }
    // uint32_t * indexPtr = &index;
// Returns the word at segments[index][offset]
word getWord(segmentContainer segments, const char * index, const char * offset) {
    // printf("Get Word: %s\n", index);
    
    void * segmentPtr = Table_get(segments, index);
    

    if (segmentPtr == NULL) {
        fprintf(stderr, "Segment not mapped.\n");
        Halt();
    }
    Table_T segment = (Table_T)segmentPtr;
    // printf("Container.length: %d\n", Table_length(segment));


    void * wordPtr = Table_get(segment, offset);

    if (wordPtr == NULL) {
        fprintf(stderr, "Word not mapped.\n");
        Halt();
    }
    word Word = (*(word *)wordPtr);
    return Word;
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
    printf("%u\n", (r[C] % 256) );
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
    r[C] = input % 256;
}

// // Duplicates segment m[ r[B] ] and usurps  m [ 0 ]
// // The program counter will be set to r[C]
// // Returns 1 if successful and -1 if unsuccessful
// int loadProgram(segmentContainer m, registerContainer r, int B, int C);

// //  Loads value into register A
// int loadValue(registerContainer r, int A, word value);

#undef twopower32