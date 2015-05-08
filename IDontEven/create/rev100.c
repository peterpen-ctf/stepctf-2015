#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int dumb_hash(char* input, int length){
    int result = 1, i;
    for(i = 1; i < length; ++i){
        result *= (((input[i] << 2) + 123456 - input[i-1]) * 3 + 2254) % 5557;
    }
    return result % 5557;
}

char strings[5][100] = {"\xaa\xa1\x41\x34\xc4\xcb\xb1\xa7\xe9\x73\x43\x3\xa9\x83\x3a\x17\x1c\xa3\xfa\x93\x85\x40\x66\x50\xae\x32\x3a\x79\x7f\xc6",
                        "\xa4\x8a\x1a\x7b\xd0\xc6\xa4\xb3\xe1\x73\x7e\x18\xec\x91\x39\x1d\x49\xfd\xef\x9c\x94\x52\x6c\xb\xed\x77\x6a\x7e\x34\x90\xb7\xc3\x42\x8c\x7b\x15\x5d\x3f\x9f\x4\x58\x75\xfa\x4a\xd4\xd6\x89\x70\xd3\xea\x9\xc6\xc4\x41\x9e\xcc\x3a\x3a\xf6\x75\x8f\x1e\x6c\x24\x8\xf5\x13\xfd\x82\x17\xad\x73\xeb\x2c\x51\x25\x25\xbe\x58\x7e\x3a\xd3\xb0\x26\xaf\xc5",
                        "\xa7\xa1\x5f\x36",
                        "\xbe\xa1\x58\x7f\x96\xde\xad\xb5\xbc\x74\x64\x4b\xad\xcd\x7c\x12\x13\xb0\xbf\x88\x93\x13\x7c\x56\xb4\x75\x72\x75\x69\xc6\xee\xda\x51\xdc\x3c\x53\x49\x60\x93",
                        "\xbd\xa6\x4e\x27\x91\xd9\xe5\xbe\xbd\x20\x63\x4b\xbf\xd7\x29\xb\x14\xa0"
                        };

void decrypt(int n){
    srand(1337);
    int i, len = strlen(strings[n]);
    for(i = 0; i < len; ++i)
        strings[n][i] ^= rand() % 256;
}

int main(int argc, char* argv[]){
    int i;
    int hashes[5];
    if(argc != 5){
        decrypt(2);
        puts(strings[2]);
        return 1;
    }
    for(i = 0; i < argc; ++i){
        int len = strlen(argv[i]);
        if(len < 8){
            decrypt(2);
            puts(strings[2]);
            return 1;
        }
        hashes[i] = dumb_hash(argv[i], len);
    }
    if(hashes[0] < 13 && hashes[5] > 6000){
        decrypt(0);
        puts(strings[0]);
    } else if(hashes[2] % 123 == 44 || hashes[4] == 0){
        decrypt(4);
        puts(strings[4]);
    } else if(hashes[1] > hashes[0] * 5 && hashes[3] - hashes[2] > 5001){
        decrypt(1);
        puts(strings[1]);
    } else if(hashes[4] * hashes[1] < hashes[3] / hashes[4]){
        decrypt(3);
        puts(strings[3]);
    } else {
        decrypt(2);
        puts(strings[2]);
    }
    return 0;
}
