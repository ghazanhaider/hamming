#!/usr/bin/python3
#
# A script to build nand_ecc_precalc_table entries
# Used in engine.c, the code is from u-boot but
#  I wanted to understand what went into that table.

def clz(x):
    evenodd = (   (x & 0x01)
             ^ ((x & 0x02) >> 1)
             ^ ((x & 0x04) >> 2)
             ^ ((x & 0x08) >> 3)
             ^ ((x & 0x10) >> 4)
             ^ ((x & 0x20) >> 5)
             ^ ((x & 0x40) >> 6)
             ^ ((x & 0x80) >> 7))

    cp0 = (   (x & 0x01)
           ^ ((x & 0x04) >> 2)
           ^ ((x & 0x10) >> 4)
           ^ ((x & 0x40) >> 6))

    cp1 = ((  (x & 0x02) >> 1)
           ^ ((x & 0x08) >> 3)
           ^ ((x & 0x20) >> 5)
           ^ ((x & 0x80) >> 7))

    cp2 = (   (x & 0x01)
           ^ ((x & 0x02) >> 1)
           ^ ((x & 0x10) >> 4)
           ^ ((x & 0x20) >> 5))

    cp3 = ((  (x & 0x04) >> 2)
           ^ ((x & 0x08) >> 3)
           ^ ((x & 0x40) >> 6)
           ^ ((x & 0x80) >> 7))

    cp4 = (   (x & 0x01)
           ^ ((x & 0x02) >> 1)
           ^ ((x & 0x04) >> 2)
           ^ ((x & 0x08) >> 3))

    cp5 = ((  (x & 0x10) >> 4)
           ^ ((x & 0x20) >> 5)
           ^ ((x & 0x40) >> 6)
           ^ ((x & 0x80) >> 7))

    tmp = ( cp0
           | (cp1 << 1)
           | (cp2 << 2)
           | (cp3 << 3)
           | (cp4 << 4)
           | (cp5 << 5)
           | (evenodd << 6))

    return tmp



for xx in range(0 , 0x10):
    for yy in range(0,0x10):
        x = ((xx << 4) | yy)
        print(format(clz(x),'02x'), end=", ")
    print("")
