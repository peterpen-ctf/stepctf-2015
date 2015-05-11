#!/usr/bin/env python

import re
import os
import time
import hashlib

orig_text = open('pf.scala').read()

def compute_tempvalue(prog_text):
    digest = hashlib.sha1(prog_text).hexdigest()
    tempvalue = hashlib.sha1('42' + digest).hexdigest()
    return tempvalue


for x in range(10000, 99999):
    new_text = re.sub(r'z\.contains\("\w+"\)', 
                      'z.contains("{}")'.format(x), 
                      orig_text)

    if x % 1000 == 0:
        print("--- Attempt {}".format(x))
    tempvalue = compute_tempvalue(new_text)
    if str(x) in tempvalue:
        print('SUCCESS!')
        print(x)
        break

