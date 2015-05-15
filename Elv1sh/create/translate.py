#!/usr/bin/env python3

import random

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


def translate_source(filename):
    contents = open(filename, 'r').read()
    res = ''
    for c in contents:
        if c.upper() in tr:
            new_char = random.choice(tr[c.upper()])
            res += new_char
        else:
            res += c
    print(res, end='')

parse_table()
translate_source('print_flag/pf.scala')
