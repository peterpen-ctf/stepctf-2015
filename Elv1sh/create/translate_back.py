#!/usr/bin/env python3

import random
import re

tr = {}

def parse_table():
    for l in open('table.txt', 'r').readlines():
        (char, options) = l.split(' = ')
        char = char.strip()
        options = [x.strip() for x in options.split(',')]
        assert len(options) <= 2
        options.append(char.lower())
        tr[char.upper()] = options


def print_tr():
    for key in sorted(tr.keys()):
        print("{} -> {}".format(key, tr[key]))


def translate_back(filename):
    contents = open(filename, 'r').read()

    ext_tr = []
    for c, opts in tr.items():
        for opt in opts:
            ext_tr.append( (opt, c) )

    ext_tr = sorted(ext_tr, key=lambda t: -len(t[0]))

    for leet_c, c in ext_tr:
        contents = re.sub(re.escape(leet_c), c.lower(), contents)

    print(contents)


parse_table()
translate_back('message')
