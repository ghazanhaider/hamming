#include <stdint.h>

#define NONE 0
#define STDIN 1
#define FILEIN 2
#define MTD 3

#define RPINIT 0
#define CPINIT 0

#define BIT0 (i & 0x1)
#define BIT1 ((i & 0x2) >> 1)
#define BIT2 ((i & 0x4) >> 2)
#define BIT3 ((i & 0x8) >> 3)
#define BIT4 ((i & 0x10) >> 4)
#define BIT5 ((i & 0x20) >> 5)
#define BIT6 ((i & 0x40) >> 6)
#define BIT7 ((i & 0x80) >> 7)

typedef uint8_t eccbyte;

struct ecc_t {
	eccbyte first;
	eccbyte second;
	eccbyte third;
};

struct ecc_t nand_calculate_ecc(uint8_t *dat, int ecc_sectors);
