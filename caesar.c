#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

#include "convlib.c"


int main(int argc, char** argv) {
	unsigned char key = 13, crack = 0;
	int opt;
	while ((opt = getopt(argc, argv, "ck:d:H")) != -1) {
		switch (opt) {
		case 'c':
			crack = 1; key = 1;
			break;
		case 'k':
			key = atoi(optarg);
			break;
		default: /* '?' */
			fprintf(stderr, "Usage: %s [-k KEY] [-c] DATA [DATA...]\n",
				argv[0]);
			exit(EXIT_FAILURE);
		}
	}

	if (optind >= argc) {
		fprintf(stderr, "Expected argument after options\n");
		exit(EXIT_FAILURE);
	}

	do {
		opt = optind;
		if (crack) printf("key %d : ", key);
		while(opt < argc) {
			char *out = (char*)malloc(strlen(argv[opt]));
			caesar(argv[opt], out, key, strlen(argv[opt]));
			printf("%s ", out);
			opt++;
		}
		key++;
		printf("\n");
	} while(key != 27 && crack);

}

