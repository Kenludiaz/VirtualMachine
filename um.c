#include "um.h"


int main(int argc, char** argv) {
    assert(argc < 3);
    FILE * fp = fopen(argv[1], "r");
    if (fp == NULL) {
            fp = stdin;
    }
    assert(fp);
    run(fp);
    fclose(fp);
}


// Program will never be null
int run(FILE * program) {
    uint32_t  r[8] = { 0 };
    // Hints set arbitrarilly
    segmentContainer m = Seq_new(2);    
    Seq_T unmappedIDs = Seq_new(0);
    Segment zero = readInstructions(program);
//     printf("Hello: \n");
    
    Seq_addhi(m, zero);

    // Although it is up to the programmer to not overflow an instruction set
    // I used the maximum possible value as a safety precaution
    for (unsigned programCounter = 0; programCounter < UINT32_MAX; programCounter++) {
        word instruction = getWord(zero, programCounter);
        int opCode = readOpCode(instruction);
        // fprintf(stdout, "Opcode: %d\n", opCode);
        switch (opCode) {

        case CMV:
{           
        uint32_t A =  CALC_A(instruction);
        uint32_t B =  CALC_B(instruction);
        uint32_t C =  CALC_C(instruction);
        conditionalMove(r, A, B, C);
}
            break;
        case SLOAD:
{
        unsigned A = CALC_A(instruction);
        unsigned B = CALC_B(instruction);
        unsigned C = CALC_C(instruction);
        segmentedLoad(m, r, A, B, C);
}            
            break;
        case SSTORE:
 {
        unsigned A = CALC_A(instruction);
        unsigned B = CALC_B(instruction);
        unsigned C = CALC_C(instruction);
        segmentStore(m, r, A, B, C);
 }           
            break;
        case ADD:
 {
        unsigned A = CALC_A(instruction);
        unsigned B = CALC_B(instruction);
        unsigned C = CALC_C(instruction);
        add(r, A, B, C);
 }           
            break;
        case MULT:
 {
        unsigned A = CALC_A(instruction);
        unsigned B = CALC_B(instruction);
        unsigned C = CALC_C(instruction);
        multiply(r, A, B, C);
 }           
            break;
        case DIVIDE:
 {
        unsigned A = CALC_A(instruction);
        unsigned B = CALC_B(instruction);
        unsigned C = CALC_C(instruction);
        divide(r, A, B, C);
 }           
            break;
        case NAND:
  {
        uint32_t A =  CALC_A(instruction);
        uint32_t B =  CALC_B(instruction);
        uint32_t C =  CALC_C(instruction);
        NANDGate(r, A, B, C);
  }          
            break;
        case HALT:
 {
        Halt();
 }           
            break;
        case MAP:
 {
        uint32_t B =  CALC_B(instruction);
        uint32_t C =  CALC_C(instruction);
        mapSegment(m, unmappedIDs, r, B, C);
 }           
            break;
        case UMAP:
 {
        uint32_t C =  CALC_C(instruction);
        Seq_addhi(unmappedIDs, (void *)(uintptr_t)unMapSegment(m, r, C));
 }           
            break;
        case OUT:
{
        uint32_t C =  CALC_C(instruction);
        output(r, C);
}           
            break;
        case IN:
{
        uint32_t C =  CALC_C(instruction);
        input(r, C);
}           
            break;
        case LOADP:
{
        unsigned B = CALC_B(instruction);
        unsigned C = CALC_C(instruction);
        loadProgram(m, r, B);
        // - 1 counteracts the increment at the end of the loop 
        programCounter = r[C] - 1;
        zero = getSegment(m, r[B]);
}            
            break;
        case LOADV:
 {
        unsigned A = ((instruction << (4)) >> 29);
        loadValue(r, A, instruction);
 }           
            break;
        default:

            break;
        }
    }
    Seq_free(&m);
    Seq_free(&unmappedIDs);
    return 0;
}

