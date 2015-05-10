#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
	FILE *fi, *fo, *fk;
	int i, r;
	char key[20], text[100];

	fi = fopen("flag.txt", "r");
	fo = fopen("encrypted.txt", "w");
	fk = fopen("key.txt", "r");

	fscanf(fi, "%s", text);
	fscanf(fk, "%s", key);

	srand(key[0] * key[1] * key[2] * key[3]);
	for(i = 0; i < strlen(text); ++i)
	{
		r = rand();
		putc(r ^ key[(r % strlen(key))] ^ text[i], fo);
	}

	fclose(fi);
	fclose(fo);
	fclose(fk);
	return 0;
}