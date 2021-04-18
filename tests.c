#include "memoryOperations.h"

void printRegisters(registerContainer r);

int main() {
    uint32_t  r[8] = { 0 };
    int A = 2;
    int B = 3;
    int C = 0;    
    
    r[A] = 1;
    r[B] = 255;
    // r[C] = UINT32_MAX;
    r[C] = 15;
    printRegisters(r);
    
    // conditionalMove(r, A, B, C);
    // add(r, A, B, C);
    // multiply(r, A, B, C);
    // divide(r, A, B, C);
    // NANDGate(r, A, B, C);
    printRegisters(r);
}

void printRegisters(registerContainer r) {
    for (int index = 0; index < 8; index++)
    {
        printf("%u\n", r[index]);
    }
}