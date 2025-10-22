#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

void dump_to_file(FILE *infile, FILE *outfile) {
    unsigned char buf[4];
    long offset = 0;
    while(fread(buf, 1, 4, infile) == 4) {
        uint32_t word = (buf[0] << 24) | (buf[1] << 16) | (buf[2] << 8) | buf[3];
        fprintf(outfile, "0x%08X @ byte %ld\n", word, offset);
        offset += 4;
    }
}

int main(int argc, char *argv[]) {
    if(argc != 3) {
        fprintf(stderr, "Usage: %s <input_bitstream> <output_txt>\n", argv[0]);
        return 1;
    }

    FILE *fin = fopen(argv[1], "rb");
    if(!fin) {
        perror("Error opening input file");
        return 1;
    }

    FILE *fout = fopen(argv[2], "w");
    if(!fout) {
        perror("Error opening output file");
        fclose(fin);
        return 1;
    }

    dump_to_file(fin, fout);

    fclose(fin);
    fclose(fout);

    printf("Bitstream dump written to %s\n", argv[2]);
    return 0;
}
