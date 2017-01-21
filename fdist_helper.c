#include <math.h>
#include <stdlib.h>
#include <string.h>

float fdist_dev(unsigned char* data, unsigned char* fdist_comp, size_t data_len) {
	unsigned int fdist_out[256];
	memset(fdist_out, 0, sizeof(fdist_out));
	int i = data_len;
	while (i --> 0) {
		fdist_out[*data]++;
		data++;
	}
	float fa, fb, fdev = 0;//printf("%d",data_len);
	for(i = 0; i < 256; i++) {
		fa = ((float)fdist_out[i]) / data_len;
		fb = ((float)fdist_comp[i]) / 255;
		//printf("%02x  %d   %f  %f  %f\n", i, fdist_out[i], fa, fb, fa-fb);
		fdev += fabsf(fa-fb);
	}
	return fdev;
}

#define ROUND_UP(x, y) ((x) + ((y) - (x) % (y)) % (y))

#define BITCOUNT(i) ( ((i>>7)&1)+((i>>6)&1)+((i>>5)&1)+((i>>4)&1)+((i>>3)&1)+((i>>2)&1)+((i>>1)&1)+(i&1) )
unsigned int hamming(unsigned char* a, unsigned char* b, size_t length) {
	unsigned int c = 0;
	unsigned char x;
	while (length --> 0) {
		x = (unsigned char) (*a ^ *b);
		c += BITCOUNT(x);
		//printf("%c %c %02x %02x %02x  %d\n", *a, *b, *a, *b, x, c);
		a++; b++;
	}
	return c;
}

/*
void print_fdist() {
	for (i = 0; i < 256; i++) {
		freq = ((float)counter[i]) / allcount;
		out = (unsigned char) (freq * 255);
		if (counter[i] > 0 && verbose) printf("%d	%f	0x%02x	'%c'\n", counter[i], freq, i, (i>=32)?i:'.');
		if (!verbose) printf("%02X", out);
	}
}
*/

