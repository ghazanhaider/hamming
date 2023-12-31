#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include "hamming.h"



// ============================== TEST DATA ==========================

/*
// TEST 4 bittest
uint8_t test3[] = {
  0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00
};



// TEST 3 test11 from mtd5@0x800 should give F3 FF 3F
uint8_t test3[] = {
  0x0b, 0x00, 0x50, 0xe1, 0x02, 0x00, 0x00, 0xca, 0x3e, 0x0f, 0x07, 0xee,
  0x01, 0x00, 0x80, 0xe0, 0xfa, 0xff, 0xff, 0xea, 0x9a, 0xaf, 0x07, 0xee,
  0x15, 0xaf, 0x07, 0xee, 0x9a, 0xaf, 0x07, 0xee, 0x95, 0xaf, 0x07, 0xee,
  0x0e, 0xf0, 0xa0, 0xe1, 0x01, 0x00, 0x14, 0xe3, 0x0e, 0xf0, 0xa0, 0x11,
  0x7e, 0xff, 0x17, 0xee, 0xfd, 0xff, 0xff, 0x1a, 0x15, 0x0f, 0x07, 0xee,
  0x9a, 0x0f, 0x07, 0xee, 0x0e, 0xf0, 0xa0, 0xe1, 0x01, 0x00, 0x14, 0xe3,
  0x0e, 0xf0, 0xa0, 0x11, 0x01, 0x28, 0xa0, 0xe3, 0x20, 0xb0, 0xa0, 0xe3,
  0x30, 0x3f, 0x10, 0xee, 0x09, 0x00, 0x33, 0xe1, 0x09, 0x00, 0x00, 0x0a,
  0x23, 0x19, 0xa0, 0xe1, 0x07, 0x10, 0x01, 0xe2, 0x01, 0x2b, 0xa0, 0xe3,
  0x12, 0x21, 0xa0, 0xe1, 0x01, 0x09, 0x13, 0xe3, 0xa2, 0x20, 0x82, 0x10,
  0x23, 0x36, 0xa0, 0xe1, 0x03, 0x30, 0x03, 0xe2, 0x08, 0xb0, 0xa0, 0xe3,
  0x1b, 0xb3, 0xa0, 0xe1, 0x0f, 0x10, 0xa0, 0xe1, 0x3f, 0x10, 0xc1, 0xe3,
  0x02, 0x20, 0x81, 0xe0, 0x0b, 0x30, 0x91, 0xe6, 0x02, 0x00, 0x31, 0xe1,
  0xfc, 0xff, 0xff, 0x1a, 0x15, 0x1f, 0x07, 0xee, 0x16, 0x1f, 0x07, 0xee,
  0x9a, 0x1f, 0x07, 0xee, 0x0e, 0xf0, 0xa0, 0xe1, 0x01, 0x00, 0x14, 0xe3,
  0x0e, 0xf0, 0xa0, 0x11, 0x00, 0x10, 0xa0, 0xe3, 0x10, 0x1f, 0x07, 0xee,
  0x0e, 0xf0, 0xa0, 0xe1, 0x00, 0x00, 0xa0, 0xe3, 0x07, 0x10, 0xa0, 0xe1,
  0x08, 0x20, 0xa0, 0xe1, 0x04, 0xf0, 0xa0, 0xe1, 0x0d, 0xc0, 0xa0, 0xe1,
  0x00, 0xd8, 0x2d, 0xe9, 0x04, 0xb0, 0x4c, 0xe2, 0x01, 0x30, 0xd0, 0xe4,
  0x00, 0x00, 0x53, 0xe3, 0xfc, 0xff, 0xff, 0x1a, 0x00, 0xa8, 0x9d, 0xe8,
  0x0d, 0xc0, 0xa0, 0xe1, 0x00, 0xd8, 0x2d, 0xe9, 0x04, 0xb0, 0x4c, 0xe2,
  0x00, 0x20, 0xa0, 0xe1
};

// TEST 2 from mtd5@0 ? should give FC FC 
uint8_t test3[] = {
  0x27, 0x05, 0x19, 0x56, 0xd8, 0x03, 0x00, 0x1f, 0x64, 0xbf, 0x51, 0x62,
  0x00, 0x5d, 0xf8, 0xb8, 0x22, 0x00, 0x00, 0x00, 0x22, 0x00, 0x00, 0x00,
  0xa6, 0x03, 0xc3, 0x00, 0x05, 0x02, 0x02, 0x00, 0x4c, 0x69, 0x6e, 0x75,
  0x78, 0x2d, 0x36, 0x2e, 0x34, 0x2e, 0x35, 0x67, 0x68, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xa0, 0xe1, 0x00, 0x00, 0xa0, 0xe1,
  0x00, 0x00, 0xa0, 0xe1, 0x00, 0x00, 0xa0, 0xe1, 0x00, 0x00, 0xa0, 0xe1,
  0x00, 0x00, 0xa0, 0xe1, 0x00, 0x00, 0xa0, 0xe1, 0x00, 0x00, 0xa0, 0xe1,
  0x05, 0x00, 0x00, 0xea, 0x18, 0x28, 0x6f, 0x01, 0x00, 0x00, 0x00, 0x00,
  0xb8, 0xf8, 0x5d, 0x00, 0x01, 0x02, 0x03, 0x04, 0x45, 0x45, 0x45, 0x45,
  0xc8, 0x5c, 0x00, 0x00, 0x00, 0x90, 0x0f, 0xe1, 0x01, 0x70, 0xa0, 0xe1,
  0x02, 0x80, 0xa0, 0xe1, 0x00, 0x20, 0x0f, 0xe1, 0x03, 0x00, 0x12, 0xe3,
  0x01, 0x00, 0x00, 0x1a, 0x17, 0x00, 0xa0, 0xe3, 0x56, 0x34, 0x12, 0xef,
  0xd3, 0xf0, 0x21, 0xe3, 0x09, 0xf0, 0x6f, 0xe1, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x0f, 0x00, 0xa0, 0xe1, 0x3e, 0x03, 0x00, 0xe2, 0x6d, 0x1f, 0x8f, 0xe2,
  0x00, 0xd0, 0x91, 0xe5, 0x01, 0xd0, 0x8d, 0xe0, 0x08, 0x10, 0xa0, 0xe1,
  0x4f, 0x15, 0x00, 0xeb, 0x02, 0x49, 0x80, 0xe2, 0x0f, 0x00, 0xa0, 0xe1,
  0x04, 0x00, 0x50, 0xe1, 0x9c, 0x01, 0x9f, 0x35, 0x0f, 0x00, 0x80, 0x30,
  0x00, 0x00, 0x54, 0x31, 0x01, 0x40, 0x84, 0x33, 0x68, 0x00, 0x00, 0x2b,
  0x06, 0x0d, 0x8f, 0xe2
};
// OOB should be cf f0 c3

*/

// TEST1 test should give 59 56 AB
uint8_t test3[] = {
  0x14, 0x9f, 0x01, 0xc3, 0x13, 0x04, 0x1f, 0xf8, 0x8c, 0x77, 0x98, 0x1b,
  0x5e, 0x40, 0x00, 0x07, 0xcc, 0x97, 0xfe, 0xe5, 0xf7, 0x37, 0x04, 0x3a,
  0x5b, 0x6f, 0x8a, 0x17, 0x9e, 0xcd, 0xc6, 0xb2, 0x6c, 0xc8, 0x76, 0x7f,
  0xcc, 0x95, 0x77, 0x58, 0x0c, 0x10, 0x74, 0x6a, 0x50, 0x74, 0x71, 0x1d,
  0x0b, 0x70, 0x02, 0x03, 0xa7, 0x06, 0x3d, 0x02, 0x75, 0xc7, 0x19, 0x13,
  0x95, 0xe0, 0xc6, 0x01, 0xa8, 0x3c, 0x81, 0x74, 0xd1, 0xf8, 0xcd, 0xdd,
  0x08, 0x41, 0x47, 0x59, 0xb5, 0xb8, 0x76, 0xc0, 0x28, 0x78, 0xc3, 0xcf,
  0x7e, 0x01, 0xd2, 0xf4, 0xc8, 0xeb, 0x07, 0x5d, 0xcb, 0xcd, 0x5f, 0x73,
  0x09, 0xe0, 0xe8, 0xda, 0xd8, 0xb5, 0xb7, 0xe1, 0xf6, 0xfe, 0x3a, 0xab,
  0xb7, 0xb0, 0x6b, 0xdf, 0x28, 0x2f, 0xaf, 0xa6, 0x30, 0x81, 0x9a, 0xf8,
  0x6c, 0xa2, 0x56, 0x38, 0x6f, 0xb5, 0xab, 0x79, 0x95, 0x93, 0x53, 0x6d,
  0x48, 0x0b, 0x4e, 0x3e, 0x09, 0x88, 0xe9, 0xc0, 0x38, 0x55, 0xa0, 0x60,
  0x84, 0x4f, 0x07, 0xb4, 0xd0, 0xa1, 0xac, 0x3c, 0x43, 0x02, 0x74, 0xb3,
  0xb7, 0x20, 0x2c, 0x4c, 0xb3, 0x7f, 0xba, 0xfc, 0x8a, 0x08, 0x3a, 0x94,
  0x91, 0x24, 0x54, 0xc9, 0x79, 0xf4, 0x2a, 0xfd, 0x43, 0x31, 0xb1, 0x13,
  0xd2, 0x5d, 0x50, 0x16, 0x60, 0xc4, 0xc9, 0x17, 0xe4, 0xf5, 0x64, 0x98,
  0x74, 0x1e, 0x94, 0xff, 0x26, 0xce, 0x93, 0xb7, 0xf2, 0xe7, 0x81, 0x6b,
  0xdc, 0xab, 0x68, 0x1f, 0xdc, 0x19, 0x33, 0xae, 0x77, 0x83, 0xc4, 0xd7,
  0x47, 0x8d, 0xee, 0x2c, 0x82, 0x52, 0xc4, 0xf7, 0x70, 0x58, 0xf6, 0x97,
  0x26, 0x89, 0x4e, 0x19, 0x70, 0xcf, 0x84, 0x4c, 0x7a, 0xed, 0x6c, 0x56,
  0x06, 0x9f, 0x05, 0x7d, 0x22, 0xc9, 0x54, 0x69, 0x57, 0x43, 0x95, 0xd9,
  0x95, 0x59, 0xd0, 0x06
};


// ====================================== U-Boot Code ===============

uint8_t nand_ecc_precalc_table[] = {
	0x00, 0x55, 0x56, 0x03, 0x59, 0x0c, 0x0f, 0x5a, 0x5a, 0x0f, 0x0c, 0x59, 0x03, 0x56, 0x55, 0x00,
	0x65, 0x30, 0x33, 0x66, 0x3c, 0x69, 0x6a, 0x3f, 0x3f, 0x6a, 0x69, 0x3c, 0x66, 0x33, 0x30, 0x65,
	0x66, 0x33, 0x30, 0x65, 0x3f, 0x6a, 0x69, 0x3c, 0x3c, 0x69, 0x6a, 0x3f, 0x65, 0x30, 0x33, 0x66,
	0x03, 0x56, 0x55, 0x00, 0x5a, 0x0f, 0x0c, 0x59, 0x59, 0x0c, 0x0f, 0x5a, 0x00, 0x55, 0x56, 0x03,
	0x69, 0x3c, 0x3f, 0x6a, 0x30, 0x65, 0x66, 0x33, 0x33, 0x66, 0x65, 0x30, 0x6a, 0x3f, 0x3c, 0x69,
	0x0c, 0x59, 0x5a, 0x0f, 0x55, 0x00, 0x03, 0x56, 0x56, 0x03, 0x00, 0x55, 0x0f, 0x5a, 0x59, 0x0c,
	0x0f, 0x5a, 0x59, 0x0c, 0x56, 0x03, 0x00, 0x55, 0x55, 0x00, 0x03, 0x56, 0x0c, 0x59, 0x5a, 0x0f,
	0x6a, 0x3f, 0x3c, 0x69, 0x33, 0x66, 0x65, 0x30, 0x30, 0x65, 0x66, 0x33, 0x69, 0x3c, 0x3f, 0x6a,
	0x6a, 0x3f, 0x3c, 0x69, 0x33, 0x66, 0x65, 0x30, 0x30, 0x65, 0x66, 0x33, 0x69, 0x3c, 0x3f, 0x6a,
	0x0f, 0x5a, 0x59, 0x0c, 0x56, 0x03, 0x00, 0x55, 0x55, 0x00, 0x03, 0x56, 0x0c, 0x59, 0x5a, 0x0f,
	0x0c, 0x59, 0x5a, 0x0f, 0x55, 0x00, 0x03, 0x56, 0x56, 0x03, 0x00, 0x55, 0x0f, 0x5a, 0x59, 0x0c,
	0x69, 0x3c, 0x3f, 0x6a, 0x30, 0x65, 0x66, 0x33, 0x33, 0x66, 0x65, 0x30, 0x6a, 0x3f, 0x3c, 0x69,
	0x03, 0x56, 0x55, 0x00, 0x5a, 0x0f, 0x0c, 0x59, 0x59, 0x0c, 0x0f, 0x5a, 0x00, 0x55, 0x56, 0x03,
	0x66, 0x33, 0x30, 0x65, 0x3f, 0x6a, 0x69, 0x3c, 0x3c, 0x69, 0x6a, 0x3f, 0x65, 0x30, 0x33, 0x66,
	0x65, 0x30, 0x33, 0x66, 0x3c, 0x69, 0x6a, 0x3f, 0x3f, 0x6a, 0x69, 0x3c, 0x66, 0x33, 0x30, 0x65,
	0x00, 0x55, 0x56, 0x03, 0x59, 0x0c, 0x0f, 0x5a, 0x5a, 0x0f, 0x0c, 0x59, 0x03, 0x56, 0x55, 0x00
};

/**
 * nand_calculate_ecc - [NAND Interface] Calculate 3-byte ECC for 256-byte block
 * @mtd:	MTD block structure
 * @dat:	raw data
 * @ecc_code:	buffer for ECC
 */
struct ecc_t nand_calculate_ecc(uint8_t *dat)
{
	//uint8_t ecc_code[3];
	uint8_t idx, reg1, reg2, reg3, tmp1, tmp2;
	int i;
	struct ecc_t ecc_code;

	/* Initialize variables */
	reg1 = reg2 = reg3 = 0;

	/* Build up column parity */
	for(i = 0; i < 256; i++) {
		/* Get CP0 - CP5 from table */
		idx = nand_ecc_precalc_table[*dat++];
		reg1 ^= (idx & 0x3f);

		/* All bit XOR = 1 ? */
		if (idx & 0x40) {
			reg3 ^= (uint8_t) i;
			reg2 ^= ~((uint8_t) i);
		}
	}

	/* Create non-inverted ECC code from line parity */
	tmp1  = (reg3 & 0x80) >> 0; /* B7 -> B7 */
	tmp1 |= (reg2 & 0x80) >> 1; /* B7 -> B6 */
	tmp1 |= (reg3 & 0x40) >> 1; /* B6 -> B5 */
	tmp1 |= (reg2 & 0x40) >> 2; /* B6 -> B4 */
	tmp1 |= (reg3 & 0x20) >> 2; /* B5 -> B3 */
	tmp1 |= (reg2 & 0x20) >> 3; /* B5 -> B2 */
	tmp1 |= (reg3 & 0x10) >> 3; /* B4 -> B1 */
	tmp1 |= (reg2 & 0x10) >> 4; /* B4 -> B0 */

	tmp2  = (reg3 & 0x08) << 4; /* B3 -> B7 */
	tmp2 |= (reg2 & 0x08) << 3; /* B3 -> B6 */
	tmp2 |= (reg3 & 0x04) << 3; /* B2 -> B5 */
	tmp2 |= (reg2 & 0x04) << 2; /* B2 -> B4 */
	tmp2 |= (reg3 & 0x02) << 2; /* B1 -> B3 */
	tmp2 |= (reg2 & 0x02) << 1; /* B1 -> B2 */
	tmp2 |= (reg3 & 0x01) << 1; /* B0 -> B1 */
	tmp2 |= (reg2 & 0x01) << 0; /* B7 -> B0 */

	/* Calculate final ECC code */
	ecc_code.first = ~tmp1;
	ecc_code.second = ~tmp2;
	ecc_code.third = ((~reg1) << 2) | 0x03;

	printf("UBoot code\n=======\n");
	printf("%#.2x %#.2x %#.2x\n",ecc_code.first,ecc_code.second,ecc_code.third);
	printf("%2d %2d %2d\n",ecc_code.first,ecc_code.second,ecc_code.third);
	puts("===================\n");

	return ecc_code;
}


uint32_t test3_len = 256;
// =============================================== My Code =====================


// 256-BIT ECC should end up being 59 56 ab


/* 
 // Cant figure out this caculation
 
struct ecc_t my_calculate_ecc(uint8_t *dat) {
    uint8_t rp0,rp1,rp2,rp3,rp4,rp5,rp6,rp7,rp8,rp9,rp10,rp11,rp12,rp13,rp14,rp15;
    uint8_t cp0,cp1,cp2,cp3,cp4,cp5;
    uint32_t rp;
	uint8_t ecc0,ecc1,ecc2,cp;
    uint32_t x,i;
	struct ecc_t ecc_code;

    rp0=rp1=rp2=rp3=rp4=rp5=rp6=rp7=rp8=rp9=rp10=rp11=rp12=rp13=rp14=rp15=RPINIT;
	cp0=cp1=cp2=cp3=cp4=cp5=CPINIT;
	cp=0;
	rp=0;

	for (x=RPINIT; x < test3_len; x++)
	{
    i = test3[x];
    //printf("Doing X:%d : %x\n",x,test3[x]);
    //printf("BIT0: %x BIT1: %x BIT2: %x BIT3: %x BIT4: %x BIT5: %x BIT6: %x BIT7: %x\n",BIT0,BIT1,BIT2,BIT3,BIT4,BIT5,BIT6,BIT7);

    if (i & 0x01)
       rp1 = BIT7 ^ BIT6 ^ BIT5 ^ BIT4 ^ BIT3 ^ BIT2 ^ BIT1 ^ BIT0 ^ rp1;
    else
       rp0 = BIT7 ^ BIT6 ^ BIT5 ^ BIT4 ^ BIT3 ^ BIT2 ^ BIT1 ^ BIT0 ^ rp0;
    if (i & 0x02)
       rp3 = BIT7 ^ BIT6 ^ BIT5 ^ BIT4 ^ BIT3 ^ BIT2 ^ BIT1 ^ BIT0 ^ rp3;
    else
       rp2 = BIT7 ^ BIT6 ^ BIT5 ^ BIT4 ^ BIT3 ^ BIT2 ^ BIT1 ^ BIT0 ^ rp2;
    if (i & 0x04)
      rp5 = BIT7 ^ BIT6 ^ BIT5 ^ BIT4 ^ BIT3 ^ BIT2 ^ BIT1 ^ BIT0 ^ rp5;
    else
      rp4 = BIT7 ^ BIT6 ^ BIT5 ^ BIT4 ^ BIT3 ^ BIT2 ^ BIT1 ^ BIT0 ^ rp4;
    if (i & 0x08)
      rp7 = BIT7 ^ BIT6 ^ BIT5 ^ BIT4 ^ BIT3 ^ BIT2 ^ BIT1 ^ BIT0 ^ rp7;
    else
      rp6 = BIT7 ^ BIT6 ^ BIT5 ^ BIT4 ^ BIT3 ^ BIT2 ^ BIT1 ^ BIT0 ^ rp6;
    if (i & 0x10)
      rp9 = BIT7 ^ BIT6 ^ BIT5 ^ BIT4 ^ BIT3 ^ BIT2 ^ BIT1 ^ BIT0 ^ rp9;
    else
      rp8 = BIT7 ^ BIT6 ^ BIT5 ^ BIT4 ^ BIT3 ^ BIT2 ^ BIT1 ^ BIT0 ^ rp8;
    if (i & 0x20)
      rp11 = BIT7 ^ BIT6 ^ BIT5 ^ BIT4 ^ BIT3 ^ BIT2 ^ BIT1 ^ BIT0 ^ rp11;
    else
      rp10 = BIT7 ^ BIT6 ^ BIT5 ^ BIT4 ^ BIT3 ^ BIT2 ^ BIT1 ^ BIT0 ^ rp10;
    if (i & 0x40)
      rp13 = BIT7 ^ BIT6 ^ BIT5 ^ BIT4 ^ BIT3 ^ BIT2 ^ BIT1 ^ BIT0 ^ rp13;
    else
      rp12 = BIT7 ^ BIT6 ^ BIT5 ^ BIT4 ^ BIT3 ^ BIT2 ^ BIT1 ^ BIT0 ^ rp12;
    if (i & 0x80)
      rp15 = BIT7 ^ BIT6 ^ BIT5 ^ BIT4 ^ BIT3 ^ BIT2 ^ BIT1 ^ BIT0 ^ rp15;
    else
      rp14 = BIT7 ^ BIT6 ^ BIT5 ^ BIT4 ^ BIT3 ^ BIT2 ^ BIT1 ^ BIT0 ^ rp14;


    //printf("rp0: %x rp1: %x rp2: %x rp3: %x\n",rp0,rp1,rp2,rp3);
    cp0 = BIT6 ^ BIT4 ^ BIT2 ^ BIT0 ^ cp0;
    cp1 = BIT7 ^ BIT5 ^ BIT3 ^ BIT1 ^ cp1;
    cp2 = BIT5 ^ BIT4 ^ BIT1 ^ BIT0 ^ cp2;
    cp3 = BIT7 ^ BIT6 ^ BIT3 ^ BIT2 ^ cp3;
    cp4 = BIT3 ^ BIT2 ^ BIT1 ^ BIT0 ^ cp4;
    cp5 = BIT7 ^ BIT6 ^ BIT5 ^ BIT4 ^ cp5;

	}

    cp = ~((cp0) | (cp1 << 1) | (cp2 << 2) | (cp3 << 3) | (cp4 << 4) | (cp5 << 5));
    rp = ~((rp0) | (rp1 << 1) | (rp2 << 2) | (rp3 << 3) | (rp4 << 4) | (rp5 << 5) | (rp6 << 6) | (rp7 << 7) | (rp8 << 8) | (rp9 << 9) | (rp10 << 10) | (rp11 << 11) | (rp12 << 12) | (rp13 << 13) | (rp14 << 14) | (rp15 << 15));

    ecc0 = ~((rp0) | (rp1 << 1) | (rp2 << 2) | (rp3 << 3) | (rp4 << 4) | (rp5 << 5) | (rp6 << 6) | (rp7 << 7));
    ecc1 = ~((rp8) | (rp9 << 1) | (rp10 << 2) | (rp11 << 3) | (rp12 << 4) | (rp13 << 5) | (rp14 << 6) | (rp15 << 7));
    ecc2 = (0x3 | ~((cp0 << 2) | (cp1 << 3) | (cp2 << 4) | (cp3 << 5) | (cp4 << 6) | (cp5 << 7)));

	printf("My code\n=======\n");
    printf("cp5: %x cp4: %x cp3: %x cp2: %x cp1: %x cp0: %x\n",cp5,cp4,cp3,cp2,cp1,cp0);
    printf("rp7: %x rp6: %x rp5: %x rp4: %x rp3: %x rp2: %x rp1: %x rp0: %x\n",rp0,rp1,rp2,rp3,rp4,rp5,rp6,rp7);
    printf("r15: %x r14: %x r13: %x r12: %x r11: %x r10: %x rp9: %x rp8: %x\n",rp15,rp14,rp13,rp12,rp11,rp10,rp9,rp8);
    printf("CP: %u  RP: %u\n",cp,rp);
    printf("ECC0: %x  ECC1: %x  ECC2: %x\n",ecc0,ecc1,ecc2);
    printf("=================================\n");
    printf("Should be: 59 56 AB\n");
    printf("=================================\n");
    return ecc_code;
}
*/

int main(void) {

    //unsigned char buffer[256];

   // my_calculate_ecc(test3);
    nand_calculate_ecc(test3);
}
