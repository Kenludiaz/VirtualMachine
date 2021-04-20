#include "um.h"
#include "assert.h"

int main(int argc, char** argv) {
    assert(argc < 3);
    // Add more file handeling
    FILE * fp = fopen(argv[1], "r");
    run(fp);

}

// Runs a program until completion
int run(FILE * program) {
    uint32_t  r[8] = { 0 };
    segmentContainer m = Table_new(2, NULL, NULL);
    Segment zero = readInstructions(program);
    int programHome = (int)0;
    const char * home = Atom_int(programHome);
    Table_put(m, home, zero);

        // printf("Word in Main: %x\n", (*(word *)Seq_get(zero, 3)));
        // printf("Seq Length: %d\n", Seq_length(zero));

    // Remember to recalculate this when a program is loaded
        int length = Seq_length(zero);
    for (int programCounter = 0; programCounter < length; programCounter++) {
        word instruction = getWord(m, home, programCounter);
        int opCode = readOpCode(instruction);
        // printf("Instruction: %x\n", instruction);
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
        // case NAND:
//   {

//   }          
        //     break;
        // case HALT:
//  {

//  }           
        //     break;
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
        // case LOADP:
{

}            
        //     break;
        // case LOADV:
 {

 }           
        //     break;
        default:
            fprintf(stderr, "Opcode out of bounds.\n");
            break;
        }
    }
    Table_free(&m);
    return 0;
}