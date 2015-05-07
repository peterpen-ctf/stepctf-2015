.PHONY: all clean

keep_symbols = -K main -K __libc_start_main -K super_secure_call -K super_secure_return
all: main

main: main.c safecall.s fun.s
	gcc -nostartfiles -o $@ $^ -Wl,-e_start -g
	strip $(keep_symbols) $@

clean:
	rm main