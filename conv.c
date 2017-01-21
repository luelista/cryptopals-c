#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define hex2nibble(hexdigit) ((((hexdigit) >= 'A') ? ((hexdigit) - 'A' + 0xA) : ((hexdigit) - '0')) & 0x0f)
#define nibble2hex(val) (((val) >= 0x0A) ? ((val) + 'A' - 0xA) : ((val) + '0'))

void hex2bin(char* src, char* dst, size_t output_length) {
	while(output_length --> 0) {
		char high = hex2nibble(*src) << 4;
		src++;
		*(dst++) = high | hex2nibble(*src);
		src++;
	}
}
void bin2hex(char* src, char* dst, size_t input_length) {
	while(input_length --> 0) {
		*(dst++) = nibble2hex(*src >> 4);
		*(dst++) = nibble2hex(*src & 0x0f);
		src++;
	}
	*(dst++) = 0;
}

int main(int argc, char** argv) {
	if (argc > 1) {
		size_t len = strlen(argv[1]) / 2;
		char* dst = (char*) malloc(len);
		hex2bin(argv[1], dst, len);
		write(STDOUT_FILENO,dst,len);
		return 0;
	} else {
		#define BUFSIZE 256
		char buf[BUFSIZE];
		char dst[BUFSIZE*2 + 1];
		ssize_t len;
		while(1) {
			len = read(STDIN_FILENO, buf, BUFSIZE);
			if (len == -1) {
				perror("read"); return 1;
			}
			if (len == 0) return 0; //eof
			bin2hex(buf, dst, len);
			write(STDOUT_FILENO, dst, len*2);
			putchar('\n');
		}
	}
}


