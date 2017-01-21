#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <getopt.h>

int main(int argc, char** argv) {
	unsigned int counter[256];
	unsigned int allcount = 0;
	int i;

	char verbose = 0;
	while ((i = getopt(argc, argv, "v")) != -1) {
		switch (i) {
		case 'v':
			verbose = 1;
			break;
		default: /* '?' */
			fprintf(stderr, "Usage: %s [-v]\n",
				argv[0]);
			exit(EXIT_FAILURE);
		}
	}

	memset(counter, 0, sizeof(counter));
	i = getchar();
	while(i != -1) {
		allcount++;
		counter[i] ++;
		i = getchar();
	}
	unsigned char out;
	float freq;
	for (i = 0; i < 256; i++) {
		freq = ((float)counter[i]) / allcount;
		out = (unsigned char) (freq * 255);
		if (counter[i] > 0 && verbose) printf("%d	%f	0x%02x	'%c'\n", counter[i], freq, i, (i>=32)?i:'.');
		if (!verbose) printf("%02X", out);
	}
	putchar('\n');
}

