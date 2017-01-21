#include <stdio.h>
#include <stdlib.h>

#include "convlib.c"

void fixed_xor(char* buf, char* xor_key, size_t length) {
	while(length --> 0) {
		*buf = *buf ^ *xor_key;
		buf++; xor_key++;
	}
}

int main(int argc, char** argv) {
	if (argc != 3) {
		printf("usage: %s data key\n", argv[0]);
		return 1;
	}
	size_t hexlen = strlen(argv[1]);

	if (hexlen != strlen(argv[2])) {
		printf("key and data must be same length\n");
		return 2;
	}

	char* data = (char*) malloc(hexlen/2);
	char* key = (char*) malloc(hexlen/2);
	hex2bin(argv[1], data, hexlen/2);
	hex2bin(argv[2], key, hexlen/2);
	
	fixed_xor(data, key, hexlen/2);
	char* out = (char*) malloc(hexlen+1);
	bin2hex(data, out, hexlen/2);
	printf("%s\n", out);
}

