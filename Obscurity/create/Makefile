.PHONY: all
# секретный ключ и флаг
key = 0x9d8d8d9d24ll
flag = "Good job! Congratulations! Your flag is: STCTF\#chocolate_chip_c00kies_arrive_on_monday\#"

# файлы, включаемые в архив
given_files = cipher.h tag.c reader.c
arch = obscurity.7z

all: tag reader $(arch)

$(arch): $(given_files)
	@rm -vf $@
	7z a $@ $^

tag: cipher.h tag.c Makefile
	echo $(flag)
	gcc tag.c -o $@ -D__key__=$(key) -D__flag__='$(flag)'

reader: cipher.h reader.c Makefile
	gcc reader.c -o $@ -D__key__=$(key)
