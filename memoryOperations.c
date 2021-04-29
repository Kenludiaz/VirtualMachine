#include "memoryOperations.h"
#include "bitpack.h"
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
    printf("Instructions: %d\n", instructions);
    Segment zero = calloc(instructions, sizeof(word));
    // printf("Array Size: %d\n", Array_length(seg));

    int input = 0;
    int counter = 0;
    while ((input = getc(fp)) != EOF) {
        word currentWord = 0;

        currentWord = Bitpack_newu(currentWord, 8, 24, input);
		input = getc(fp);
		currentWord = Bitpack_newu(currentWord, 8, 16, input);
		input = getc(fp);
		currentWord = Bitpack_newu(currentWord, 8, 8, input);
		input = getc(fp);
		currentWord = Bitpack_newu(currentWord, 8, 0, input);
        
        // printf("Word: %u\n", currentWord);
        zero[counter++] = currentWord;
        // printf("Array Get : %u\n", *(uint32_t *)Array_get(zero, counter - 1));
    }
    return zero;
}
// Accessing unmapped segments is a checked run-time error
Segment getSegment(segmentContainer segments, unsigned index) {
    void * segmentPointer = Table_get(segments, Atom_int(index));
    if (segmentPointer == NULL) {
        exit(1);
    }
    return (Segment)segmentPointer;
}

// Will return the first four bits of a word
int readOpCode(word instruction) {
    return (int)(instruction >> 28);
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

    seg[r[B]] = r[C];
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
    word identifier;
    Segment seg = calloc(r[C], sizeof(word));

    if (Seq_length(unmappedIDs) == 0) {
        identifier = Table_length(m);
    } else {
        identifier = ((uint32_t)(uintptr_t)Seq_remlo(unmappedIDs));
    }
    Table_put(m, Atom_int(identifier), seg);
    r[B] = identifier;
}

// m[0] and unmapped memory will not be unmapped
word unMapSegment(segmentContainer m, registerContainer r, unsigned C) {
    void * removedItem = Table_remove(m, Atom_int(r[C]));
    if (removedItem == NULL || r[C] == 0) {
        exit(1);
    }
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
    Table_put(m, Atom_int(0), program);
}

// Frees segments from A[0], A[1], A[length]
void freeSegments(const void *key, void **value, void *cl) {
    (void)key;
    (void)cl;
    word * seg = *value;
    // Array_map(seq, freeSegments, NULL);
    free(seg);
}

// Frees words from A[0], A[1], A[length]
// void freeWords(Array_T array, int idx, void *elem, void *cl), void *cl) {
//     (void)idx;
//     (void)array;
//     (void)cl;
//     word Word = *value;
//     free(&Word);
// }

#undef twopower32