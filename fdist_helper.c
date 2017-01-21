#import <math.h>

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

