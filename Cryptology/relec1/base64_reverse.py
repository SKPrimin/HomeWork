#!/usr/bin/env python
# visit https://tool.lu/pyc/ for more information
# Version: Python 3.9

import libnum

code = [
    "A",    "B",    "C",    "D",    "E",    "F",    "G",    "H",    "I",    "J",
    "K",    "L",    "M",    "N",    "O",    "P",    "Q",    "R",    "S",    "T",
    "U",    "V",    "W",    "X",    "Y",    "Z",    "a",    "b",    "c",    "d",
    "e",    "f",    "g",    "h",    "i",    "j",    "k",    "l",    "m",    "n",
    "o",    "p",    "q",    "r",    "s",    "t",    "u",    "v",    "w",    "x",
    "y",    "z",    "0",    "1",    "2",    "3",    "4",    "5",    "6",    "7",
    "8",    "9",    "+",    "/",    "=",
]
data = libnum.s2b(input("Input what you want to encode : "))
pad = 0
if len(data) % 6 != 0:
    pad = (6 - len(data) % 6) // 2
    data += (6 - len(data) % 6) * "0"
result = []
result.append(pad * "=")
print("".join(result))
