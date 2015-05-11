#!/usr/bin/env python3
import random
import subprocess

from time import sleep


FLAG = 'STCTF#uN1oCKd00r#'

MAX_COMMAND_INTERVAL = 10


def char2tristate(char):
    return 'FFFFF{0:07b}'.format(ord(char))


def random_tristate():
    return ''.join((random.choice(['0', '1', 'F']) for i in range(12)))


RANDOM_COMMANDS = [random_tristate() for i in range(10)]


def send_tristate(tristate):
    subprocess.call(['./trisend', tristate])


def send_random_commands(number):
    for i in range(number):
        send_tristate(random.choice(RANDOM_COMMANDS))
        sleep(random.randrange(MAX_COMMAND_INTERVAL))


print("# Sending random commands")
send_random_commands(23)

print("# Sending FLAG commands")
for c in FLAG:
    tristate = char2tristate(c)
    subprocess.call(['./trisend', tristate])
    sleep(random.randrange(MAX_COMMAND_INTERVAL))

print("# Sending random commands")
send_random_commands(12)
