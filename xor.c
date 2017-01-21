#include <stdio.h>
#include <stdlib.h>

#include "convlib.c"


int main(int argc, char** argv) {
	if (argc != 3) {
		printf("usage: %s data key\n", argv[0]);
		return 1;
	}
	size_t dlen = strlen(argv[1])/2;
	size_t keylen = strlen(argv[2])/2;

	char* data = (char*) malloc(dlen);
	char* key = (char*) malloc(keylen);
	hex2bin(argv[1], data, dlen);
	hex2bin(argv[2], key, keylen);
	
	xor(data, key, dlen, keylen);
	char* out = (char*) malloc(dlen*2+1);
	bin2hex(data, out, dlen);
	printf("%s\n", out);
	free(out);
}

