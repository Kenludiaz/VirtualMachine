#include "aux.h"

int unsignedToInt(unsigned value) {
    // int upperByte;
    // // See if the value is less than 2^16 to speed up the function
    // if (value >= 65536) {
    //     upperByte = 32;
    // } else {
    //     upperByte = 16;
    // }
    // int sum = 0;
    // for (int i = 0; i < upperByte; i++) {
    //     int bit = Bitpack_gets(value, 1, i);
    //     if (bit == 1) {
    //         sum += pow(2, i); 
    //     }
    // }
    // return sum;
    int sum = value | 0;
    return sum;
}
