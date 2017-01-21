

#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

#include "convlib.c"
#include "fdist_helper.c"

int hamming_keysize(unsigned char *data, size_t dlen, int from, int to) {
	
	float hamming_avg, hamming_cnt;
	float hamming_best = INFINITY; int keysize_best = -1;
	int idx;
	int keysize;
	for (keysize = from; keysize < to; keysize ++) {
		hamming_avg = 0; hamming_cnt = 0;
		for(idx = 0; idx + keysize*2 < dlen; idx += keysize*2){
			hamming_avg += hamming(&data[idx], &data[idx+keysize], keysize);
			hamming_cnt ++;
		}
		hamming_avg /= hamming_cnt;
		hamming_avg /= keysize;
		printf("%f\t%d\n", hamming_avg, keysize);
		if (hamming_best > hamming_avg) {
			hamming_best = hamming_avg; keysize_best = keysize;
		}
	}
	return keysize_best;
}

int main(int argc, char** argv) {
	unsigned char *data;
	size_t dlen;

	unsigned char probdist[256];
	int from=2,to=40;
	int opt;
	while ((opt = getopt(argc, argv, "Ha:b:p:")) != -1) {
		switch(opt) {
		case 'a':
			from=atoi(optarg);
			break;
		case 'b':
			to=atoi(optarg);
			break;
		case 'p':
			if (strlen(optarg) != 256*2) {
				fprintf(stderr, "frequency distribution string must be 256 hex bytes\n"); exit(1);
			}
			hex2bin(optarg, probdist, 256);
			break;
		default: /* '?' */
			fprintf(stderr, "Usage: %s [-a FROM] [-b TO]\n",
				argv[0]);
			exit(EXIT_FAILURE);
		}
	}
	
	fprintf(stderr, "reading from stdin ...\n");
	data = (unsigned char*)malloc(4096);
	dlen = read(0, data, 4096);

	// find most probable keysize
	printf("Trying out keysizes ...\n");
	int keysize = hamming_keysize(data, dlen, from, to);
	printf("using keysize %d\n", keysize);

	//printf("orig matrix\n");
	//printmatrix(data, keysize, dlen);

	//transpose data by keysize
	int matsize = ROUND_UP(dlen, keysize);
	int blocksize = matsize / keysize;
	unsigned char *dtrans = (unsigned char*) malloc(matsize);
	transposematrix(data, dtrans, blocksize, keysize);

	unsigned char *tmp = (unsigned char*) malloc(blocksize);
	char *keystr = (char*) malloc(keysize);

	//crack individual blocks with same key each
	for (int blockidx = 0; blockidx < keysize; blockidx++) {
		printf("Cracking block %d\n", blockidx);
		unsigned char* block = dtrans + (blockidx * blocksize);
		int key = 0;
		float best_fdev = INFINITY;
		for (key = 0; key < 256; key++) {
			fixed_xor(block, tmp, (unsigned char)key, blocksize);
			float fdev = fdist_dev(tmp, probdist, blocksize);
			if (fdev < best_fdev) {
				printf("%f\t%d\t", fdev, key);
				printout(STRING, tmp, blocksize);
				printf("\n");
				keystr[blockidx] = key;
				best_fdev = fdev;
			}
		}
	}

	printf("This might be the key: ");
	printout(STRING, (unsigned char*)keystr, keysize);
	printf("\n");

	printf("Decrypting: ");
	xor((char*)data, keystr, dlen, keysize);
	printout(STRING, data, dlen);
	printf("\n");
}


