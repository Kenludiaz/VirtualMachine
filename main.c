#include "um.h"

int main() {
    FILE * fp = fopen("instructions.txt", "r");
    run(fp);
}