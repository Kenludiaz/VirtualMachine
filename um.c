#include "um.h"

int main(int argc, char** argv) {
    assert(argc < 3);
    // Add more file handeling
    FILE * fp = fopen(argv[1], "r");
    run(fp);
    fclose(fp);
}

// Runs a program until completion
int run(FILE * program) {
    uint32_t  r[8] = { 0 };
    segmentContainer m = Table_new(2, NULL, NULL);
    Segment zero = readInstructions(program);
    const char * home = Atom_int((int)0);
    Table_put(m, home, zero);

    for (unsigned programCounter = 0; programCounter < UINT32_MAX; programCounter++) {
        word instruction = (uint32_t)(uintptr_t)Seq_get(zero, programCounter);
        // printf("Instruction: %x\n", instruction);
        int opCode = readOpCode(instruction);
        // printf("Opcode: %d\n", opCode);
        switch (opCode) {

        case CMV:
{           
            uint32_t A =  CALC_A(instruction);
            uint32_t B =  CALC_B(instruction);
            uint32_t C =  CALC_C(instruction);
            conditionalMove(r, A, B, C);
}
            break;
        // case SLOAD:
// {

// }            
        //     break;
        // case SSTORE:
//  {

//  }           
        //     break;
        // case SSTORE:
//  {

//  }           
        //     break;
        // case ADD:
//  {

//  }           
        //     break;
        // case MULT:
//  {

//  }           
        //     break;
        // case DIVIDE:
//  {

//  }           
        //     break;
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
        // case MAP:
//  {

//  }           
        //     break;
        // case UMAP:
//  {

//  }           
        //     break;
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
        // printf("B : %u, C : %u\n", B, C);
        // printf("R[B] : %u, R[C] : %u\n", r[B], r[C]);
        loadProgram(m, r, B);
        // -1 counteracts the increment at the end of the loop 
        programCounter = r[C] - 1;
        // This might point to the same zero as in before the loop
        zero = getSegment(m, r[B]);
}            
            break;
        case LOADV:
 {
        unsigned A = Bitpack_getu(instruction, 3, 25);
        loadValue(r, A, instruction);
 }           
            break;
        case 14:
                break;
        case 15:
                break;
        default:
        //     fprintf(stderr, "Opcode out of bounds.\n");
            break;
        }
    }
    Table_free(&m);
    return 0;
}