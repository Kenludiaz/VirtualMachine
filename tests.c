#include "memoryOperations.h"

void printRegisters(registerContainer r);

int main() {
    uint32_t  r[8] = { 0 };
    int A = 2;
    int B = 3;
    int C = 0;    
    
    r[A] = 2;
    r[B] = 8;
    r[C] = UINT32_MAX;
    // r[C] = 5;
    printRegisters(r);
    
    // conditionalMove(r, A, B, C);
    // add(r, A, B, C);
    // multiply(r, A, B, C);
    printRegisters(r);
}

void printRegisters(registerContainer r) {
    for (int index = 0; index < 8; index++)
    {
        printf("%u\n", r[index]);
    }
}