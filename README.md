# Hamming ECC calculator

`SPDX-License-Identifier: GPL-2.0+`

Hamming code calculator for blocks of data

## Build

```
make
cc -c engine.c -o engine.o

Building hamming
cc hamming.c engine.o -o hamming
```


## Usage
```
cat data.bin | ./hamming [OPTIONS]
Or: ./hamming <-256|-512> <-smartmedia> -f data.bin
Or: ./hamming <-256|-512> <-smartmedia> -d /dev/mtdX -s (seek/start byte) -l (length in bytes)
OPTIONS:     -256 256-byte   ECC sectors (default)
             -512 512-byte   ECC sectors
             -sm             Smartmedia byte order
             -b              Output is 3-byte raw data (no newline) instead
                              of printing hex.
```

- Data should be in multiples of 256 or 512 bytes raw binary.
- The ECC output does not place it at a specific OOB location or offset.
- I wrote this because my NAND boards were throwing a lot of ECC errors and I wanted
  to find out which tool is handling them incorrectly.
- This tool checks only 1-bit check 2-bit correct software Hamming code and not higher
  ECC algorithms like BCH or Hardware PMECC-generated ones.
- The logic portion was shamelessly copied from u-boot, Linux.
- Ghazan Haider 2023-07-27
