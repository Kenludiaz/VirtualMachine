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
//     printf("Run: %s\n", home);
    Table_put(m, home, zero);

    // Cast might become problematic
//     printf("Length : %d\n", Table_length(m));
    for (unsigned programCounter = 0; programCounter < (unsigned)Table_length(zero); programCounter++) {
        const char * instructionNumber = Atom_int(programCounter);
        word instruction = getWord(m, home, instructionNumber);
        int opCode = readOpCode(instruction);
        pr
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
    return 0;
}