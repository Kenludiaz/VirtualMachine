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