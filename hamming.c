#include <stdio.h>
#include "fdist_helper.c"
int main(int argc, char** argv) {
	int h = hamming((unsigned char*)argv[1], (unsigned char*)argv[2], strlen(argv[1]));
	printf("%d\n", h);
}

