#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define hex2nibble(hexdigit) ((((hexdigit) >= 'A') ? ((hexdigit) - 'A' + 0xA) : ((hexdigit) - '0')) & 0x0f)
#define nibble2hex(val) (((val) >= 0x0A) ? ((val) + 'A' - 0xA) : ((val) + '0'))

void hex2bin(char* src, void* dst, size_t output_length) {
	while(output_length --> 0) {
		char high = hex2nibble(*src) << 4;
		src++;
		*((unsigned char*)dst++) = high | hex2nibble(*src);
		src++;
	}
}
void bin2hex(void* src, char* dst, size_t input_length) {
	unsigned char* SRC=src;
	while(input_length --> 0) {
		*(dst++) = nibble2hex(*SRC >> 4);
		*(dst++) = nibble2hex(*SRC & 0x0f);
		SRC++;
	}
	*(dst++) = 0;
}


char base64map[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
void bin2base64(char* src, char* dst, ssize_t input_length) {
	char b;
	while (input_length > 0) {
		//printf("%ld\n", input_length);
		b = *src >> 2;
		*(dst++) = base64map[b];
		b = (*src & 0x03) << 4;
		if (input_length > 1) {
			src++;
			b |= (*src >> 4);
			*(dst++) = base64map[b];
			b = (*src & 0x0f) << 2;
			if (input_length > 2) {
				src++;
				b |= (*src & 0xc0) >> 6;
				*(dst++) = base64map[b];
				b = *src & 0x3f;
				src++;
				*(dst++) = base64map[b];
			} else {
				*(dst++) = base64map[b];
				*(dst++) = '=';
			}
		} else {
			*(dst++) = base64map[b];
			*(dst++) = '=';
			*(dst++) = '=';
		}
		input_length -= 3;
	}
	*(dst++) = 0;
}



void caesar(char* src, char* dst, char rotdist, size_t length) {
	while(length --> 0) {
		if (*src >='a' && *src <= 'z') {
			*dst = *src + rotdist;
			if (*dst > 'z') *dst -= 26;
		} else if (*src >='A' && *src <= 'Z') {
			*dst = *src + rotdist;
			if (*dst > 'Z') *dst -= 26;
		} else *dst = *src;
		dst++; src++;
	}
}

