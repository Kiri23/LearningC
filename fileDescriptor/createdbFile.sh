#!/bin/bash
echo -ne "\x01\x00\xff\x00\x08\x00\x00\x00" > ./my-db.db

# use xxd to check the file content
# 00000000  01 00 ff 00 08 00 00 00                           |........|
# Hex    : 01 00 | ff 00 | 08 00 00 00
# Field  : version | employee | filesize
# Value  : 0x0001  | 0x00FF   | 0x00000008
# Decimal:    1    |   255    |    8
