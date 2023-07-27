#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include "hamming.h"



// ====================================== U-Boot engine  ===============

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
struct ecc_t nand_calculate_ecc(uint8_t *dat, int ecc_sectors)
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

	return ecc_code;
}


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

