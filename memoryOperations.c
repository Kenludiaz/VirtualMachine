#include "memoryOperations.h"
#include "array.h"
#include "stdio.h"

// Reads instructions from fp 
// Fp will never be null
Segment readInstructions(FILE * fp) {

    // Code obtained from Tim Colaneri
    // Goes to the beginning of the file
    fseek(fp, 0, SEEK_END);
    // Dividing by the 4 Bytes containted in an instruction
    // gives us the total number of instructions
    int instructions = ((ftell(fp)) / 4);
    fseek(fp, 0, SEEK_SET);
    Segment zero = calloc(instructions, sizeof(word));

    int input = 0;
    int counter = 0;
    while ((input = getc(fp)) != EOF) {
        word currentWord = 0;
        currentWord = newWord(currentWord, 24, input);
		input = getc(fp);
        currentWord = newWord(currentWord, 16, input);
		input = getc(fp);
        currentWord = newWord(currentWord, 8 , input);
		input = getc(fp);
        currentWord = newWord(currentWord, 0 , input);
        
        zero[counter++] = currentWord;
    }
    return zero;
}
// Accessing unmapped segments is a checked run-time error
Segment getSegment(segmentContainer segments, unsigned index) {
    void * segmentPointer = Seq_get(segments, index);
    if (segmentPointer == NULL) {
        exit(1);
    }
    return (Segment)segmentPointer;
}

// Will return the first four bits of a word
int readOpCode(word instruction) {
    return (instruction >> 28);
}
// Every register will never exceed the value of the typedef of word
int conditionalMove(threeRegisters) {
    if (r[C] != 0) {
        r[A] = r[B];
        return 1;
    }
    return -1;
}
// Checked run-time error to load unmapped memory
void segmentedLoad(segmentContainer m, threeRegisters) {
    Segment seg = getSegment( m, r[B] );
    r[A] = getWord(seg, r[C]);
}
// Checked run-time error to store in unmapped memory
void segmentStore(segmentContainer m, threeRegisters) {
    Segment seg = getSegment(m, r[A]);
    seg[ r[B] ] = r[C];
}

// r[A] will always be < 2^32
void add(threeRegisters) {
    r[A] = ((r[B] + r[C]) % twopower32);
}

// r[A] will always be < 2^32
void multiply(threeRegisters) {
    r[A] = ((r[B] * r[C]) % twopower32);
}

// r[A] will always be an int
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

// r[B] will return a non-zero word
void mapSegment(segmentContainer m, Seq_T unmappedIDs, registerContainer r,  unsigned B, unsigned C) {
    unsigned identifier;
    Segment seg = calloc(r[C], sizeof(word));

    if (Seq_length(unmappedIDs) == 0) {
        identifier = Seq_length(m);
        Seq_addhi(m, seg);
    } else {
        identifier = ((uint32_t)(uintptr_t)Seq_remlo(unmappedIDs));
        Seq_put(m, identifier, seg);
    }
    r[B] = identifier;
}

// m[0] and unmapped memory will not be unmapped
word unMapSegment(segmentContainer m, registerContainer r, unsigned C) {
    void * removedItem = Seq_put(m, r[C], 0);
    if (removedItem == NULL || r[C] == 0) {
        exit(1);
    }
    free((Segment)removedItem);
    return r[C];
}

// Only values from 0 to 255 will be printed
// since a char is only a byte
void output(registerContainer r, unsigned C) {
    printf("%c", (char)r[C]);
}

// Input will only be negative during EOF
void input(registerContainer r, unsigned C) {
    int input = getchar();
    if (input == EOF) {
        r[C] = UINT32_MAX;
        return;
    }
    r[C] = input;
}

// Loading an unmapped segment is a checked run-time error
void loadProgram(segmentContainer m, registerContainer r, unsigned B) {
    Segment program = getSegment(m, r[B]);
    Seq_put(m, 0, program);
}


#undef twopower32