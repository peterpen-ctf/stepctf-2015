#!/usr/bin/env python3
from socket import create_connection
from os import urandom
from subprocess import Popen, PIPE
from binascii import hexlify, unhexlify

bits_to_skip = 23

def xor(a,b):
    result = b''
    for i in range(len(a)):
        result += bytes([ a[i] ^ b[i] ])
    return result

def possible_flags():
    with create_connection(('localhost', 6543)) as reader, create_connection(('localhost', 3456)) as tag:
        nonce = tag.recv(4)
        reader.send(nonce)
        nonce_enc = reader.recv(4)
        tag.send(nonce_enc)
        n = tag.recv(4)
        n = int.from_bytes(n, 'little')
        flag_enc = tag.recv(n)
        
    nonce = int.from_bytes(nonce, 'little')
    nonce_enc = int.from_bytes(nonce_enc, 'little')
    keystream = nonce ^ nonce_enc
    process = Popen(['./solver', hex(keystream), str(bits_to_skip),  str(n)], stdout=PIPE)
    ans = process.communicate()[0]
    ans = ans.split()
    ans = [unhexlify(x) for x in ans]
    result = set()

    for flag_keystream in ans:
        assert len(flag_keystream) == len(flag_enc)
        flag = xor(flag_keystream, flag_enc)
        result.add(flag)
    return result

def main():
    result = possible_flags()
    result &= possible_flags()
    print(result)

if __name__ == '__main__':
    main()
