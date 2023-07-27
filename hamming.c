// SPDX-License-Identifier: GPL-2.0+
/********************************
 * hamming code calculator for blocks of data
 * Usage: cat data.bin | ./hamming [OPTIONS]
 * Or: ./hamming <-256|-512> <-smartmedia> -f data.bin
 * Or: ./hamming <-256|-512> <-smartmedia> -d /dev/mtdX -s (seek/start byte) -l (length in bytes)
 * OPTIONS:     -256 256-byte   ECC sectors (default)
 *              -512 512-byte   ECC sectors
 *              -sm				Smartmedia byte order
 *              -b				Output is 3-byte raw data (no newline) instead
 *                               of printing hex.
 *
 * Data should be in multiples of 256 or 512 bytes raw binary.
 * The ECC output does not place it at a specific OOB location or offset.
 * I wrote this because my NAND boards were throwing a lot of ECC errors and I wanted
 *  to find out which tool is handling them incorrectly.
 * This tool checks only 1-bit check 2-bit correct software Hamming code and not higher
 *  ECC algorithms like BCH or Hardware PMECC-generated ones.
 * The logic portion was shamelessly copied from u-boot, Linux.
 *  - Ghazan Haider 2023-07-27
 ********************************/

#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include "hamming.h"

int main(int argc, char **argv) {

//=================================================  Variables
	
    uint8_t buffer[512];
	int filename = 0; // Not a string, points to the argc number
	FILE *fp;
	size_t result;
	uint8_t byte;
    int smartmedia = 0;
    int ecc_sectors = 256;
	int counter = 0;
    int binary_output = 0;
    int input_type = NONE; // STDIN | FILEIN | MTD


	struct ecc_t ecc_code;
						   
//=========================================== Process cli arguments

        for(int argcount=1; argcount < argc; argcount++ ) {
			if (!strcmp(argv[argcount],"-256")) ecc_sectors = 256;
			else if (!strcmp(argv[argcount],"-sm")) smartmedia = 1;
			else if (!strcmp(argv[argcount],"-b")) binary_output = 1;
			else if (!strcmp(argv[argcount],"-512")) ecc_sectors = 512;
			else if (!strcmp(argv[argcount],"-f")) {
				filename = ++argcount;
#ifdef DEBUG
				printf("Input type file: %s\n",argv[argcount]);
#endif
				input_type = FILEIN;
			}
			else if (!strcmp(argv[argcount],"-d")) {
				if (input_type != NONE) {
					puts("Error: multiple input types specified\n");
					exit(-1);
				}
#ifdef DEBUG
				puts("Setting input type to mtd\n");
#endif
				input_type = MTD;

			}
			else if (!strcmp(argv[argcount],"-i")) {
				if (input_type != NONE) {
                    puts("Error: multiple input types specified\n");
                    exit(-1);
				}
#ifdef DEBUG
				puts("Setting input type to stdin\n");
#endif
				input_type = STDIN;
			}
			else {
				printf("Invalid argument: %s\n",argv[argcount]);
				exit(-1);
			}
#ifdef DEBUG
            printf("ARG is -%s-\n",argv[argcount]);
#endif
	}


//==================================== Ingest data depending on input type specified

		if (input_type == NONE) {
            printf("Error: no input file/mtd device specified and no data piped in\n");
            exit(-1);
		}
		else if (input_type == STDIN) {
			while(read(STDIN_FILENO, &byte, 1) > 0)
			{
				// DEBUG: printf("%#02x ",byte);
				buffer[counter++] = byte;
			}
		}
		else if (input_type == MTD) {
			puts("MTD not yet implemented :(\n");
			exit(-2);
		}
		else if (input_type == FILEIN) {
#ifdef DEBUG
			printf("Testing and opening file %s\n",argv[filename]);
#endif
			fp = fopen(argv[filename],"r");
			if (fp == NULL) {puts ("File error"); exit (1);}
			result = fread(buffer,1,ecc_sectors,fp);
			if (result != ecc_sectors) {fputs ("Reading error",stderr); fclose(fp); exit (3);}
			//printf("Success reading file! buffer: \n%.*s\n",ecc_sectors,(const char *)buffer);
			fclose(fp);
		}



//==================================================== Run it against the engine
	
	ecc_code = nand_calculate_ecc(buffer,ecc_sectors);


//============================================================= Display output
	
#ifdef DEBUG
    printf("Output\n===================\n");
#endif
	if (binary_output == 1) {
		if (smartmedia == 1) {
			fputc(ecc_code.second,stdout);
			fputc(ecc_code.first,stdout);
			fputc(ecc_code.third,stdout);
		}
		else {
			fputc(ecc_code.first,stdout);
			fputc(ecc_code.second,stdout);
			fputc(ecc_code.third,stdout);
		}
	}

	else {
		if (smartmedia == 1) printf("%#.2x %#.2x %#.2x\n",ecc_code.second,ecc_code.first,ecc_code.third);
		else printf("%#.2x %#.2x %#.2x\n",ecc_code.first,ecc_code.second,ecc_code.third);
	}
#ifdef DEBUG
    puts("===================\n");
#endif

    return 0;
}
