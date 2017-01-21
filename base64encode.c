#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

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


int main(int argc, char** argv) {
	#define BUFSIZE 255
	char buf[BUFSIZE];
	char dst[BUFSIZE*4/3 + 1];
#if DEBUG
printf("inbuf %lu, outbuf %lu\n", sizeof(buf), sizeof(dst));
#endif
	char *ptr = buf;
	ssize_t len;
	while(1) {
		len = read(STDIN_FILENO, ptr, BUFSIZE - (ptr-buf));
#if DEBUG
		printf("read %zd bytes\n", len);
#endif
		if (len == -1) {
			perror("read"); return 1;
		}
		ptr += len;
		if ((ptr-buf) % 3 == 0 || len == 0) {
#if DEBUG
			printf("converting %lu bytes\n", ptr-buf);
#endif
			bin2base64(buf, dst, ptr-buf);
			printf("%s\n", dst);
			ptr = buf;
		}
		if (len == 0) return 0; //eof
	}
}


